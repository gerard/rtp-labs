#include <stdio.h>
#include <unistd.h>

int main() {
	long int posix_version, ticks, pthread, rtsignals;
	
	posix_version = sysconf(_SC_VERSION);
	ticks = sysconf(_SC_CLK_TCK);
	pthread = sysconf(_SC_THREADS);
	rtsignals = sysconf(_SC_REALTIME_SIGNALS);
	printf("POSIX Version: %ld\n", posix_version);
	printf("Clock ticks per second: %ld\n", ticks);
	if(pthread) printf("pthread Support Enabled\n");
		else printf("No pthread Support\n");
	if(rtsignals) printf("RTSignals Support Enabled\n");
		else printf("No RTSignal Support\n");
	
	return 0;
}
