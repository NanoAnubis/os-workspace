#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

struct interval {
	uint16_t off;
	uint16_t count;

}__attribute__((packed));



int main (int argc, char* argv[]) {
	if(argc != 7) errx(1,"argc");
	
	int ax = open(argv[1],O_RDONLY);
	if(ax==-1) err(2,"ax");

	int pox = open(argv[2],O_RDONLY);
	if(pox==-1) err(2,"pox");

	int prx = open(argv[3],O_RDONLY);
	if(prx==-1) err(2,"prx");

	int ix = open(argv[4],O_RDONLY);
	if(ix==-1) err(2,"ix");

	int sx = open(argv[5],O_RDONLY);
	if(sx==-1) err(2,"sx");

	int cx = open(argv[6],O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if(cx==-1) err(2,"cx");

	uint16_t count;
	struct stat fs;

	lseek(ax,4,SEEK_SET);
	if(read(ax,&count,sizeof(count))==-1) err(3,"read ax");
	fstat(ax,&fs);
	if(fs.st_size != (16+count*2)) errx(4,"size ax");
	lseek(ax,16,SEEK_SET);

	//lseek(cx,4,SEEK_SET);	
	//write(cx,&count,sizeof(count));
	lseek(cx,16,SEEK_SET);

	lseek(pox,4,SEEK_SET);
	if(read(pox,&count,sizeof(count))==-1) err(3,"read pox");
	fstat(pox,&fs);
	if(fs.st_size != (16+count*4)) errx(4,"size pox");
	lseek(pox,16,SEEK_SET);	

	lseek(prx,4,SEEK_SET);
	if(read(prx,&count,sizeof(count))==-1) err(3,"read prx");
	fstat(prx,&fs);
	if(fs.st_size != (16+count*1)) errx(4,"size prx");
	lseek(prx,16,SEEK_SET);	

	lseek(ix,4,SEEK_SET);
	if(read(ix,&count,sizeof(count))==-1) err(3,"read ix");
	fstat(ix,&fs);
	if(fs.st_size != (16+count*2)) errx(4,"size ix");
	lseek(ix,16,SEEK_SET);	

	lseek(sx,4,SEEK_SET);
	if(read(sx,&count,sizeof(count))==-1) err(3,"read sx");
	fstat(sx,&fs);
	if(fs.st_size != (16+count*8)) errx(4,"size sx");
	lseek(sx,16,SEEK_SET);	
	
	struct interval k[4];
	
	ssize_t r;
	while((r=read(ax,&k,sizeof(k)))>0){
		if(r==-1) err(5,"k read");
		uint32_t post;
		uint8_t pre;
		uint16_t in;
		uint64_t suf;

		lseek(pox,16+k[0].off*4,SEEK_SET);
		for(uint16_t t = 1;t<=k[0].count;t++) {
			if(read(pox,&post,sizeof(post))==-1) err(6,"post read");
			if(write(cx,&post,sizeof(post))!=sizeof(post)) err(7,"post write");
		}
			
		lseek(prx,16+k[1].off*1,SEEK_SET);
		for(uint16_t t = 1;t<=k[1].count;t++) {
			if(read(prx,&pre,sizeof(pre))==-1) err(6,"pre read");
			if(write(cx,&pre,sizeof(pre))!=sizeof(pre)) err(7,"pre write");
		}
			
		lseek(ix,16+k[2].off*2,SEEK_SET);
		for(uint16_t t = 1;t<=k[2].count;t++) {
			if(read(ix,&in,sizeof(in))==-1) err(6,"in read");
			if(write(cx,&in,sizeof(in))!=sizeof(in)) err(7,"in write");
		}
			
		lseek(sx,16+k[3].off*8,SEEK_SET);
		for(uint16_t t = 1;t<=k[3].count;t++) {
			if(read(sx,&suf,sizeof(suf))==-1) err(6,"suf read");
			if(write(cx,&suf,sizeof(suf))!=sizeof(suf)) err(7,"suf write");
		}

	}
	
	lseek(cx,0,SEEK_SET);
	write(cx,"0123456789ABCDFi",sizeof("0123456789ABCDFi"));

	fstat(cx,&fs);	
	count=(fs.st_size-16);
	lseek(cx,4,SEEK_SET);
	write(cx,&count,sizeof(count));

	exit(0);
}
