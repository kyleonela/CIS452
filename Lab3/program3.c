#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <signal.h>
#include <sys/resource.h>
#include <time.h>
#include <sys/wait.h>

void signalHandler(int);
void exitSignal(int);


//printf allows everything to be on one line instead of using puts
void signalHandler(int sigNum){
	if(sigNum == SIGUSR1){
		printf("Received a SIGUSR1 signal\n");
	}
	if (sigNum == SIGUSR2){
		printf("Received a SIGUSR2 signal\n");
	}
}

void exitSignal(int sigNum){
	printf(" recieved. That's it, I'm shutting you down...\n");
	exit(0);
}

int main(){
	pid_t pid;

	int randomNumber = (rand()%5)+1;
	signal(SIGUSR1, signalHandler);
	signal(SIGUSR2, signalHandler);

	//standard parent/child functionality
	if((pid=fork())<0){
		perror("fork failure");
		exit(1);
	}
	else if (pid == 0){
		while(1){
			sleep(randomNumber);
			
			int randomSignal = rand()%2;
			//picks a random signal
			if(randomSignal==0){
				kill(getppid(), SIGUSR1);
			}
			else{
				kill(getppid(), SIGUSR2);
			}
		}
	}
	else {
		printf("spawn child PID #%d\n\n", pid);
		printf("waiting...    ");
		fflush(stdout);
		pause();

		while(1){
			printf("waiting...    ");
			fflush(stdout);
			pause();
			signal(SIGINT, signalHandler);
			signal(SIGINT, exitSignal);
		}
	}
}
