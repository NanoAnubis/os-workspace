#include<stdio.h>
#include<stdlib.h>
#include<err.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]) {
	if(argc !=3){
		errx(1,"Wrong number of arguments!");
	}

	int N = atoi(argv[1]);
	int D = atoi(argv[2]);

	//check if N and D are in [1,9]
	
	for(int i=1;i<=N;i++) {

		printf("DING\n");
		pid_t ch=fork();
		if(ch==-1) {
			err(2,"Forkn't");
		}
		if(ch==0) {
			printf("DONG\n");
			exit(0);
		}
		wait(NULL);
		sleep(D);

	}


	exit(0);
}
