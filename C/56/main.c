#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int main (int argc, char* argv[]) {
	uint8_t buff;
	if(argc == 1) {
		ssize_t r;
		while((r = read(0,&buff,sizeof(buff))) > 0){
			if(write(1,&buff,sizeof(buff))!=r){
				err(1,"Couldn't write to STDOUT");
			}

		}
	}
	
	for(uint8_t counter = 1; counter < argc; counter++){

		if(argv[counter][0]=='-') {
			ssize_t r;
			while((r = read(0,&buff,sizeof(buff))) > 0){
				if(write(1,&buff,sizeof(buff))!=r){
					err(1,"Couldn't write to STDOUT");
				}
			}
			continue;
		}

		int fd;
        	fd = open(argv[counter], O_RDONLY);
        	if (fd == -1) {
                	err(2, "File %s can't be opened in read only", argv[counter]);
        	}
		ssize_t r;
		while((r = read(fd,&buff,sizeof(buff))) > 0){
			if(write(1,&buff,sizeof(buff))!=r){
				err(1,"Couldn't write to STDOUT");
			}
	
		}
		close(fd);
	}
	
	exit(0);
}
