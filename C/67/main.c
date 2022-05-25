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
        fd2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd2 == -1) {

                err(3, "File %s can't be opened in read-write", argv[2]);
        }
	

	struct stat fs;
	fstat(fd1,&fs);
	uint32_t arrN = fs.st_size/2;
	
	char str[]="uint16_t arr[]={";
	write(fd2,&str,sizeof(str));

	uint16_t buff;
	ssize_t r;
        while((r = read(fd1,&buff,sizeof(buff))) > 0){
		//if(write(1,&buff,sizeof(buff))!=r){
                //        err(1,"Couldn't write to STDOUT");
                //}
		write(fd2,&buff,sizeof(buff));
		write(fd2,", ",sizeof(", "));
	}

	write(fd2,"0}\n",sizeof("}\n"));
	write(fd2,"uint32_t arrN = ",sizeof("uint32_t arrN = "));

	//printf("%d",arrN);
	fprintf(fd2,&arrN,"%d");

	exit(0);
}
