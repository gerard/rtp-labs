#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	struct stat s;

	if(argc!= 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		return 1;
	}
	if(stat(argv[1], &s)) {
		perror("Error");
		return 1;
	}

	if(S_ISREG(s.st_mode)) printf("Regular file\n");
	if(S_ISDIR(s.st_mode)) printf("Directory\n");
	if(S_ISCHR(s.st_mode)) printf("Character device\n");

	return 0;
}
