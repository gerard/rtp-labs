#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define TIMES 100000
#define STRING "AAAA"

int main() {
	int i, fd;

	fd = open("exlog.txt", O_WRONLY | O_CREAT | O_TRUNC);
	for(i=0; i<TIMES; i++) {
		lseek(fd, 0, SEEK_END);
		write(fd, STRING, 4);
	}
	close(fd);

	return 0;
}
