#include <stdio.h>
#include <sys/wait.h>
#define MAXLIN 80
#define TIMES 5

int main(int argc, char *argv[]) {
	int i;
	FILE *f;
	char l[MAXLIN];
	
	if(argc != 2) {
		fprintf(stderr, "Usage: %s string\n", argv[0]);
		return 1;
	}
	if(strlen(argv[1]) > MAXLIN) {
		fprintf(stderr, "The string should be shorter than %d\n", MAXLIN);
		return 2;
	}
	
	if(fork()) { // Parent
		wait(NULL);
		
		f = fopen("test.txt", "r");
		printf("Showing the contents of the file:\n");
		while(fgets(l, MAXLIN, f)) printf("%s", l);
		fclose(f);
		return 0;
	}
	
	// Child process
	f = fopen("test.txt", "w");
	for(i=0; i<TIMES; i++) fprintf(f, "%s\n", argv[1]);
	fclose(f);
	return 0;
}
