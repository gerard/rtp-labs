#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main(void) {
	DIR *directory;
	struct dirent *dp;
	char wrkdir[NAME_MAX+1];
	
	getcwd(wrkdir, NAME_MAX+1);
	if(!(directory = opendir(wrkdir))) {
		printf("\nError in opendir function");
		exit(1);
	}

	while((dp = readdir(directory)) != NULL) {
		printf("\n%s", dp->d_name);
	}
	closedir(directory);

	return 0;
}
