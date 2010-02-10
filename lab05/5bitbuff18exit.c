#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_SIZE 5

int main() {
	char buffer[BUF_SIZE];
	int fd;
	char c;

	fd = open("test2.txt", O_RDONLY);
	setvbuf(stdout, buffer, _IOFBF, BUF_SIZE);
	
	do {
		read(fd, &c, 1);
		sleep(1);
	} while(c != 'q' && putchar(c));
	putchar('\n');
	
	exit(0);
}
