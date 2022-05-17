#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <>

struct pair {
	uint32_t x;
	uint32_t y;
};


int main (void) {
	
	
	int fd1=open("f1", O_RDONLY);
	if (fd1 == -1) {
		err(1,"File f1 can't be opened in read only");
	}
	
	struct stat f1stats;

	fstat(fd1,&f1stats);
	if (f1stats.st_size%4 != 1) {
		err(2,"File f1 doesn't have only pairs");
	}

	int fd2=open("f2", O_RDONLY);
	if (fd2 == -1) {
		err(1,"File f2 can't be opened in read only");
	}
	
	int fd3=open("f3", O_RDWR | O_TRUNC);
	if (fd3 == -1) {
		err(1,"File f3 can't be opened in read-write");
	}
	
	while(read(fd1, &pair, sizeof(pair))==sizeof(pair)) {
		lseek(fd2, pair.x*sizeof(uint32_t),SEEK_SET);
		for(uint32_t i = 0; i < pair.y; i++){
			read(fd2, &pair, sizeof(pair));
			write(fd3, &pair, sizeof(pair));
		}

	}

	close(fd1);
	close(fd2);
	close(fd3);

	exit(0);
}
