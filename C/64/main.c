#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int main (int argc, char* argv[]) {
	
	if(argc != 4) errx(1,"argc");

	int scl = open(argv[1],O_RDONLY);
	if(scl==-1) err(2,"scl open");

	int sdl = open(argv[2],O_RDONLY);
	if(sdl==-1) err(2,"sdl open");

	int out = open(argv[3],O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if(out==-1) err(2,"out open");

	uint8_t bits[8]={1,2,4,8,16,32,64,128};

	uint8_t byte;
	uint16_t buf;
	ssize_t r;
	while((r=read(scl,&byte,sizeof(byte)))!=0) {
		if(r==-1) err(3,"scl read");

		for(uint8_t i = 0; i<8;i++){
			if(read(sdl,&buf,sizeof(buf))==-1) err(3,"sdl read");
			if((byte&bits[i])==bits[i]){
				if(write(out,&buf,sizeof(buf))!=sizeof(buf)) err(3,"out write");
			}
		}
	}

	exit(0);
}
