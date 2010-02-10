#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define TIMES 100000
#define STRING "BBBB"

int main() {
	int i, fd;

	if((fd = open("exlog.txt", O_WRONLY | O_APPEND | O_TRUNC)) == -1) {
		perror("The file doesn't exist");
		return 1;
	}
	
	for(i=0; i<TIMES; i++) {
		write(fd, STRING, 4);
	}
	close(fd);

	return 0;
}
