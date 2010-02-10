#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main (void) {
	pid_t pid;
	char buf[20];
	printf("Enter input (n = next, other input terminates):");
	fgets(buf, 20, stdin);
	while(buf[0] == 'n') {
    	pid = fork ();
    	if(pid < 0) {
			perror("Fork:");
			exit(1);
		}
    	if(pid == 0) { // 1st child
			if(fork()) exit(0);
			else { // 2nd child. Inherited by init as soon as the first ends
				sleep(1);		// This is actually something real work
				exit(0);
			}
		}
		wait(NULL); // We let the 1st child to finish
		printf ("Enter input (n = next, other input terminates):");
    	fgets (buf, 20, stdin);
	}
}
