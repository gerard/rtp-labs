#include <stdio.h>
#include <sys/select.h>

int main() {
	fd_set readfds;
	int fd_pipe[2];
	char i;
	
	pipe(fd_pipe);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	
	if(fork()) { // Parent
		close(fd_pipe[1]);	// No need to write
		
		FD_ZERO(&readfds);
		do {
			if(FD_ISSET(0, &readfds)) {
				if(read(0, &i, 1) > 0) printf("%c", i);
				else break;
			}
			
			if(FD_ISSET(fd_pipe[0], &readfds)) {
				if(read(fd_pipe[0], &i, 1) > 0) printf("%d", i);
				else break;
			}
			
			FD_SET(0, &readfds);
			FD_SET(fd_pipe[0], &readfds);
		} while(select(fd_pipe[0] + 1, &readfds, NULL, NULL, NULL) > 0);
		
		printf("\n");
	} else { // Child
		close(fd_pipe[0]);	// No need to read 
		close(0);			// No need to read from here neither
		
		for(i = 0; i < 10; i++) {
			sleep(1);
			write(fd_pipe[1], &i, 1);
		}
	}
	
	return 0;
}