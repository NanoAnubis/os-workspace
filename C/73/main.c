#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <sys/wait.h>
#include <stdbool.h>

int main (int argc, char* argv[]) {

	if(argc < 3) errx(4,"argc");
	//check argv[1] if in [1,9]
	//
	//
	int fd = open("run.log", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd==-1) err(1,"open't");

	while(true) {
		
		pid_t ch = fork();
		if(ch==-1) err(2,"forkn't");
		time_t start = time(NULL);
		if(ch==0) {
			dprintf(fd,"%ld ", start);
			if(argc == 4) execlp(argv[2], "cmd", argv[3],0);
			else execlp(argv[2], "cmd",0);
			exit(0);
		}
		int s;
		wait(&s);
		time_t end = time (NULL);
		dprintf(fd,"%ld ", end);
		int code;
		if(WIFEXITED(s)) {
			code = WEXITSTATUS(s);	
		}
		else err(3,"childn't");

		dprintf(fd,"%d\n",code);
		if(code!=0 && (end - start) <= atoi(argv[1])) break;

	}

	exit(0);

}
