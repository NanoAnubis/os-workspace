#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int main (int argc, char* argv[]) {

	if (argc != 3) {
		errx(1, "Script needs 2 arguments!");
	}

	int fd1;
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1) {
		err(2, "File %s can't be opened in read only", argv[1]);
	}

	int fd2;
	fd2 = open(argv[2], O_RDWR, O_TRUNC);
	if (fd2 == -1) {

		err(3, "File %s can't be opened in read-write", argv[2]);
	}

	const uint8_t bits[8]={0x01,
			 0x02,
			 0x04,
			 0x08,
			 0x10,
			 0x20,
			 0x40,
			 0x80};
		
	const uint16_t dict1[8]={0x0002,
				0x0008,
				0x0020,
				0x0080,
				0x0200,
				0x0800,
				0x2000,
				0x8000};

	const uint16_t dict0[8]={0x0001,
				0x0004,
				0x0010,
				0x0040,
				0x0100,
				0x0400,
				0x1000,
				0x4000};

	uint16_t storage[256];

	for(uint16_t a = 0;a<=255;a++){
		uint16_t tmp = 0;
		for(uint8_t i=0;i<8;i++){
			if((a & bits[i])>0)
			tmp=tmp|dict1[i];
		}	
		uint8_t b=~a;
		for(uint8_t i=0;i<8;i++){	
			if((b & bits[i])>0)
			tmp=tmp|dict0[i];
		}	
		storage[a]=tmp;
		//if(a==255) break;
	}

	//for(uint8_t i=0;i<=255;i++){
	//	printf("%d",storage[i]);
	//	if(i==255) break;
	//}
	
	uint8_t element;
	ssize_t rs;
	while((rs = read(fd1,&element,1)) > 0){

		uint16_t wr = storage[element];
		//printf("%d",wr);
		write(fd2,&wr,2);
	}

	exit(0);
}
