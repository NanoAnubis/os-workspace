#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int main (int argc, char* argv[]) {
	
	if(argc != 3){
		errx(5,"argc");
	}

	int fd1=open(argv[1],O_RDONLY);
	if (fd1==-1) {
		err(3,"fd1");
	}
	int fd2=open(argv[2],O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd2==-1) {
		err(4,"fd2");
	}

	uint8_t byte;
	ssize_t r,w;
	uint8_t new;
	while((r=read(fd1,&byte,sizeof(byte))!=0)) {
		if(r==-1) {
			err(1,"R");
		}
		while(byte==0x55){
			read(fd1,&byte,sizeof(byte));
		}
		if(byte==0x7D) { 
			read(fd1,&byte,sizeof(byte));
			new=byte^0x20;
		}
		else new=byte;
		w=write(fd2,&new,sizeof(new));
		if(w!=r) {
			err(2,"W");
		}
	}



	exit(0);
}
