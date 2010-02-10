#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define NBLOCK 0

int main() {
	int fd, flags;

	if(NBLOCK) fd = open("exlog.txt", O_RDONLY | O_NONBLOCK);
	else fd = open("exlog.txt", O_RDONLY);

	if((flags=fcntl(fd, F_GETFL)) & O_NONBLOCK) {
		printf("O_NONBLOCK: On\n");
		fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
	} else {
		printf("O_NONBLOCK: Off\n");
		fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	}
	close(fd);
}
