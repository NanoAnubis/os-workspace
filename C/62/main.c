#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

struct byte {
	uint16_t off;
	uint8_t o;
	uint8_t n;

}__attribute__((packed));

struct word {
	uint32_t off;
	uint16_t o;
	uint16_t n;

}__attribute__((packed));


int main (int argc, char* argv[]) {

	if(argc != 4) errx(1,"argc");

	int p = open(argv[1], O_RDONLY);
	if(p==-1) err(2,"open p");

	int f1 = open(argv[2], O_RDONLY);
	if(f1==-1) err(2,"open f1");

	int f2 = open(argv[3], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if(f2==-1) err(2,"open f2");

	uint32_t magic;
	if(read(p,&magic,sizeof(magic))==-1) err(3,"read magic");
	if(magic!=0xEFBEADDE) err(4,"wrong magic");

	uint8_t header;
	if(read(p,&header,sizeof(header))==-1) err(3,"read header");
	if(header!=0x01) err(4,"wrong header");

	uint8_t datav;
	if(read(p,&datav,sizeof(datav))==-1) err(3,"read data v");

	uint16_t count;
	if(read(p,&count,sizeof(count))==-1) err(3,"read count");

	struct stat fs;
	fstat(p,&fs);

	if(datav==0x00) {	
		struct byte data;
		uint8_t s;

		if((uint16_t)fs.st_size!=16+count*sizeof(data)) errx(4,"wrong size p");

		fstat(f1,&fs);
		if(fs.st_size%sizeof(data.o)!=0) errx(4,"wrong size f1");

		lseek(p,16,SEEK_SET);

		ssize_t r;
		uint8_t b;
		uint32_t n = fs.st_size/sizeof(data.o);
		while((r=read(f1,&b,sizeof(b)))>0){
			if(r==-1) err(5,"read f1");
			if(write(f2,&b,sizeof(b))==-1) err(6,"write f2");
		}

		while((r=read(p,&data,sizeof(data)))>0) {
			if(r==-1) err(5,"read p");
			if(data.off>=n) {
				err(7,"Offset out of range");
				//continue;
			}
			lseek(f2,data.off,SEEK_SET);
			if(read(f2,&s,sizeof(s))==-1) err(5,"read f2");
			if(s!=data.o && s!=data.n) errx(7,"wrong byte/word");
			lseek(f2,data.off,SEEK_SET);
			if(write(f2,&data.n,sizeof(data.n))==-1) err(6,"write f2");

		}
	}
	if(datav==0x01) {
		struct word data;
		uint16_t s;

		if((uint16_t)fs.st_size!=16+count*sizeof(data)) errx(4,"wrong size p");

		fstat(f1,&fs);
		if(fs.st_size%sizeof(data.o)!=0) errx(4,"wrong size f1");

		lseek(p,16,SEEK_SET);

		ssize_t r;
		uint8_t b;
		uint32_t n = fs.st_size/sizeof(data.o);
		while((r=read(f1,&b,sizeof(b)))>0){
			if(r==-1) err(5,"read f1");
			if(write(f2,&b,sizeof(b))==-1) err(6,"write f2");
		}

		while((r=read(p,&data,sizeof(data)))>0) {
			if(r==-1) err(5,"read p");
			if(data.off>=n) {
				err(7,"Offset out of range");
				//continue;
			}
			lseek(f2,data.off,SEEK_SET);
			if(read(f2,&s,sizeof(s))==-1) err(5,"read f2");
			if(s!=data.o && s!=data.n) errx(7,"wrong byte/word");
			lseek(f2,data.off,SEEK_SET);
			if(write(f2,&data.n,sizeof(data.n))==-1) err(6,"write f2");

		}
	}
	else err(4,"wrong data v");
	exit(0);
}
