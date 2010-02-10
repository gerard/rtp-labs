#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <pthread.h>
#define STRINGL 16
#define CHILDBIN "./printstring"

int childs_finished = 0;

static void sigchild_handler(int sig_no) {
	if(sig_no == SIGCHLD) {
		fprintf(stderr, "Child terminated\n");
		childs_finished++;
	}
	return;
}

int main(int argc, char *argv[3]) {
	char *param[5];
	char fd_str[STRINGL];
	int fd;
	
	if(argc != 3) {
		fprintf(stderr, "Usage: %s times string\n", argv[0]);
		return 1;
	}

	if(atoi(argv[1]) < 0) {
		fprintf(stderr, "A positive value of times should be specified\n");
		return 2;
	}
	
	if(signal(SIGCHLD, sigchild_handler) == SIG_ERR) {
		perror("Failed to install SIGCHILD handler");
		return 3;
	}	

	fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(!(fork() && fork())) { // Childs
		fprintf(stderr, "Creating child\n");
		snprintf(fd_str, STRINGL, "%d", fd);
		param[0]=argv[0];
		param[1]=argv[1];
		param[2]=fd_str;
		param[3]=argv[2];
		param[4]=(char *)0;
		execv(CHILDBIN, param);
		perror("exec failed: ");
	}

	while(childs_finished < 2) {
		fprintf(stderr, "Waiting for %d childs to finish\n", 2-childs_finished);
		sleep(1);
	}

	return 0;
}
