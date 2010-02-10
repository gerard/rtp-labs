#include <signal.h>

void signal_hand(int signo) {}

int main() {
	int child;
	char c1 = '1';
	char c2 = '2';
	
	signal(SIGUSR1, signal_hand);
	child = fork();
	
	if(child > 0) {
		while(1) {
			write(1, &c2, 1);
			kill(child, SIGUSR1);
			pause();
		}
	}
	
	if(child == 0) {
		//sleep(1);
		while(1) {
			pause();
			write(1, &c1, 1);
			kill(getppid(), SIGUSR1);
		}
	}
}
