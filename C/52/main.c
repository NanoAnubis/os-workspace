#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int main (int argc, char* argv[]) {

        if (argc != 5) {
                errx(1, "Script needs 5 arguments!");
        }

        int fd1;
        fd1 = open(argv[1], O_RDONLY);
        if (fd1 == -1) {
                err(2, "File %s can't be opened in read only", argv[1]);
        }

        int fd2;
        fd2 = open(argv[2], O_RDONLY);
        if (fd2 == -1) {

                err(3, "File %s can't be opened in read only", argv[2]);
        }

        int fd3;
        fd3 = open(argv[3], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd3 == -1) {
                err(4, "File %s can't be opened in read-write", argv[3]);
        }

        int fd4;
        fd4 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd4 == -1) {

                err(5, "File %s can't be opened in read-write", argv[4]);
	}

	ssize_t r;
	uint16_t from;
	uint8_t len,junk;
	uint16_t offset = 0;
	while((r = read(fd2,&from,sizeof(from))) > 0){
		read(fd2,&len,sizeof(len));
		read(fd2,&junk,sizeof(junk));

		lseek(fd1,from,SEEK_SET);
		
		char c;
		read(fd1,&c,sizeof(c));
		if(c < 'A' || c > 'Z') continue;
		
		lseek(fd1,from,SEEK_SET);
		
		uint8_t str;
		read(fd1,&str,len);

		write(fd3,&str,len);
		uint16_t oo = offset;
		write(fd4,&oo,sizeof(oo));
		write(fd4,&len,sizeof(len));
		write(fd4,&junk,sizeof(junk));
		
		offset+=(uint16_t)len;
			
	}



	exit(0);
}
