#include <stdio.h>
#include <sys/wait.h>
#define NP 5

// Finds the index of one element in an array
int vsearch(int *v, int s, int e) {
	int i;
	
	for(i=0; i<s; i++) if(e==v[i]) return i; // Found
	return -1; // Not found
}

int main() {
	char c;
	int pids[NP];
	int i, j;
	int stat, proc, pid;
	
	for(i=0; i<NP; i++) {
		if(!(pids[i]=fork())) { // Child process. Parent will get the pid
			c='A'+i;
			for(j=0; j<i+2; j++) {
				write(0, &c, 1);
				sleep(1);
			}
			return j--; // Child exits
		}
	}
	while((pid=wait(&stat))!=-1) {
		proc=vsearch(pids, NP, pid);
		printf("\n%c: %d chars written\n", 'A'+proc, WEXITSTATUS(stat));
	}
	return 0;
}

