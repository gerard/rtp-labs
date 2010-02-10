#include <stdio.h>
#include <signal.h>

void signal_hand(int signo) {}

int main() {
	int child;
	char c1 = '1';
	char c2 = '2';
	
	sigset_t smask, wmask;

	sigemptyset(&wmask);
	sigemptyset(&smask);
	sigaddset(&smask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &smask, NULL);
	signal(SIGUSR1, signal_hand);
	
	child = fork();
	
	if(child > 0) {
		while(1) {
			write(1, &c2, 1);
			kill(child, SIGUSR1);
			sigsuspend(&wmask);
		}
	}
	
	if(child == 0) {
		while(1) {
			sigsuspend(&wmask);
			write(1, &c1, 1);
			kill(getppid(), SIGUSR1);
		}
	}
}
