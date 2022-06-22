#include<stdio.h>
#include<stdlib.h>
#include<err.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdbool.h>

void pr(int sig) {
	printf("DONG\n");
}


int main(int argc, char* argv[]) {
	if(argc !=3){
		errx(1,"Wrong number of arguments!");
	}

	int N = atoi(argv[1]);
	int D = atoi(argv[2]);

 	
	pid_t ch=fork();
	if(ch==-1) {
		err(2,"Forkn't");
	}

	for(int i=1;i<=N;i++) {

		if(ch==0) {
			signal(SIGUSR1, pr);
			pause();
		}

		if(ch!=0) {
			printf("DING\n");
			kill(ch, SIGUSR1);
			sleep(D);
		}

	}
	exit(0);
}
