#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>


int main (int argc, char* argv[]) {
	
	if(argc != 2) errx(1,"argc");
	
	mkfifo ("pipe",S_IRUSR | S_IWUSR);
	int fd = open("pipe",  O_WRONLY);
	if(fd == -1) err(2,"pipen't");
	dup2(fd,1);

	execlp("cat","catcmd",argv[1],0);


	exit(0);
}
