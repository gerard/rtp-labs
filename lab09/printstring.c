#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int i, j, l, times, fd;
	char nl = '\n';
	
	if(argc != 4) {
		fprintf(stderr, "Usage: %s times descriptor string\n", argv[0]);
		return 1;
	}

	if((times = atoi(argv[1])) < 0) {
		fprintf(stderr, "A positive value of times should be specified\n");
		return 2;
	}

	if((fd = atoi(argv[2])) < 0) {
		fprintf(stderr, "A valid descriptor should be specified\n");
		return 3;
	}
	
	l = strlen(argv[3]);
	for(i=0; i<times; i++) {
		for(j=0; j<l; j++) write(fd, &(argv[3][j]), 1);
		write(fd, &nl, 1);
	}
	
	fprintf(stderr, "Child done\n");
	return 0;
}
