#include <stdio.h>

int main() {
	FILE *file, *tty;
	
	file = fopen("/usr/include/stdio.h", "r");
	tty = fopen("/dev/tty", "r");
	
	fseek(file, 0, SEEK_END);
	printf("File Size: %d\n", file->_IO_read_end - file->_IO_read_base);
	printf("Buffer Size: %d\n", file->_IO_buf_end - file->_IO_buf_base);

	fseek(tty, 0, SEEK_END);
	printf("TTY File Size: %d\n", tty->_IO_read_end - tty->_IO_read_base);
	printf("TTY Buffer Size: %d\n", tty->_IO_buf_end - tty->_IO_buf_base);

	return 0;
}
