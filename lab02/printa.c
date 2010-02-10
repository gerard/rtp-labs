#include <unistd.h>

int main() {
	while(1) write(1, "a", 1);
}
