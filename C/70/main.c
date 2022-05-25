#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int main (void) {
	int a[2];
	if(pipe(a)==-1) {
		errx(1,"Cant open pipe");
	}
	pid_t p1=fork();
	if(p1==-1) {
		errx(2,"Cant fork proccess");
	}
	if(p1==0) {
		close(a[0]);
		dup2(a[1],1);
		execlp("cut", "cut", "-d", ":", "-f", "7", "/etc/passwd", 0);
	}
	close(a[1]);
	int b[2];
	if(pipe(b)==-1) {
		errx(1,"Cant open pipe");
	}
	pid_t p2=fork();
	if(p2==-1) {
		errx(2,"Cant fork proccess");
	}
	if(p2==0) {
		dup2(a[0],0);
		close(b[0]);
		dup2(b[1],1);
		execlp("sort", "sort", 0);

	}
	close(a[0]);
	close(b[1]);
	dup2(b[0],0);
	execlp("uniq","uniq","-c", 0);

	exit(0);
}
