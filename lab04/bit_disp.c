#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void bit_disp(mode_t m) {
	int bit = sizeof(mode_t)*8;

	while((bit--)!=0) {
		if(m & (1 << bit)) putchar('1');
		else putchar('0');
	}
	putchar('\n');
}

void bit_mark(mode_t m) {
	int bit = sizeof(mode_t)*8;

	while((bit--)!=0) {
		if(m & (1 << bit)) putchar('|');
		else putchar(' ');
	}
	putchar('\n');
}
	

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

	bit_disp(s.st_mode);
	bit_mark(S_IFMT);

	return 0;
}
