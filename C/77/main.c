#include <time.h>
#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdint.h>
#include <pwd.h>

int main (int argc, char* argv[]) {
	
	int log = open("foo.log", O_WRONLY | O_APPEND);
	if(log==-1) err(1,"log");
	
	uid_t user = getuid();
	struct passwd p = *getpwuid(user);

	time_t micros = time(NULL);
	struct tm t = *localtime(&micros);

	micros=micros%1000000;

	int y = t.tm_year + 1900;
	int m = t.tm_mon + 1;

	dprintf(log,"%04d-%02d-%02d %02d:%02d:%02d.%ld %s ",y,m,t.tm_mday,t.tm_hour,t.tm_min,t.tm_sec,micros, p.pw_name);

	for(int i = 0; i<argc; i++){
		dprintf(log,"%s ", argv[i]);
	}
	dprintf(log,"\n");

	pid_t ch;	
	if((ch=fork())==-1) err(1,"childn't");
	if(ch==0){
		printf("passwd -l %s\n",p.pw_name);
		exit(0);
	}
	wait(&ch);
	pid_t ch1;	
	if((ch1=fork())==-1) err(1,"childn't");
	if(ch1==0){
		printf("sudo killall -u %s\n",p.pw_name);
		exit(0);
	}
	wait(&ch1);
	exit(0);
}


