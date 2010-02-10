#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <aio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

struct aiocb aiocb1, aiocb2;
char chr1, chr2;
int fd1_pipe[2], fd2_pipe[2];

void sig_hand(int signo) {
	if(signo == SIGIO) { // We check which read was ready
		if(aio_error(&aiocb1) != EINPROGRESS) {
			write(1, &chr1, 1);
			aio_read(&aiocb1);
			return;
		}
		
		if(aio_error(&aiocb2) != EINPROGRESS) {
			write(1, &chr2, 1);
			aio_read(&aiocb2);
			return;
		}
	}
	
	return;
}

int main() {
	struct sigaction sigact;
	int child_stat, i;
	
	// Non-buffered stdout
	setvbuf(stdout, NULL, _IONBF, 0);
	pipe(fd1_pipe);
	pipe(fd2_pipe);

	// Installing the handler
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = sig_hand;
	sigact.sa_flags = 0;
	sigaction(SIGIO, &sigact, NULL);

	// Filling the first aiocb struct
	aiocb1.aio_fildes = fd1_pipe[0];
	aiocb1.aio_buf = &chr1;
	aiocb1.aio_nbytes = 1;
	aiocb1.aio_offset = 0;
	aiocb1.aio_reqprio = 0;
	aiocb1.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	aiocb1.aio_sigevent.sigev_signo = SIGIO;
	aiocb1.aio_sigevent.sigev_value.sival_ptr = &aiocb1;
	aiocb1.aio_lio_opcode = 0;
	
	// We just copy the struct to reduce the code size
	memcpy(&aiocb2, &aiocb1, sizeof(struct aiocb));
	aiocb2.aio_fildes = fd2_pipe[0];
	aiocb2.aio_buf = &chr2;
	aiocb2.aio_sigevent.sigev_value.sival_ptr = &aiocb2;
	
	if(!fork()) { // Child 1
		for(i = 48; i < 48 + 10; i++) {
			sleep(1);
			write(fd1_pipe[1], &i, 1);
		}
		return 0;
	}

	if(!fork()) { // Child 2
		for(i = 97; i < 97 + 5; i++) {
			sleep(2);
			write(fd2_pipe[1], &i, 1);
		}
		return 0;
	}
	
	// Parent launches the first reads, others are launched by the
	// signal handler
	aio_read(&aiocb1);
	aio_read(&aiocb2);
	
	// Wait returns when the process is signaled, so we need to check
	// that it has actually finished.
	do wait(&child_stat);
	while(!WIFEXITED(child_stat));
	
	do wait(&child_stat);
	while(!WIFEXITED(child_stat));
	
	printf("\n");
	return 0;
}
