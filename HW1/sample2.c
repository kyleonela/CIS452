#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid, pid1;

	pid = fork();
	if (pid<0){
		fprintf(stderr, "fork() failed\n");
		return(1);
	}
	else if(pid == 0){
		pid1 = getpid();
		printf("a child pid = %d\n", pid);
		printf("b child pid1 = %d\n", pid1);
	}
	else{
		pid1 = getpid();
		printf("a parent pid = %d\n", pid);
		printf("b parent pid1 = %d\n", pid1);
		wait(NULL);
	}
	return 0;
}
