#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#define NUMBER 50

//int functionTwo(int argc, char* argv[]){
//test	
//}

int main(){

	pid_t pid;
	int status;
	char* input;
	input = (char*)malloc(NUMBER);
	puts("Welcome to the shell!\n");

	while(1){
		puts("\nPlease enter a command to execute: ");
		fgets(input,NUMBER,stdin);
		if(!strcmp(input,"quit\n")){
			puts("\nQuitting...\n");
			exit(1);
		}

		int length = strlen(input);
		if(input[length-1]=='\n'){
			input[length-1]='\0';
		}

		char* token = strtok(input," ");
		char* commands[10] = {NULL};

		for(int i=0; token; i++){
			commands[i]=token;
			token = strtok(NULL," ");
		}

		//spawn a child process to execute command:
		if((pid = fork()) < 0 ){
			perror("fork failure");
			exit(1);
		} 
		if(pid==0){
			//child thats going to execute command
			//puts("in child");
			if(execvp(commands[0],&commands[0])<0){
				perror("execvp failed");
				exit(1);	
			}
		}
		else{
			//resource usage info in the parent
			struct rusage resUsage;
			struct timeval time;
			getrusage(RUSAGE_SELF, &resUsage);
			time = resUsage.ru_utime;
			printf("\nCPU time used: %ld seconds and %ld miliseconds\n",time.tv_sec,time.tv_usec );
			printf("Involuntary context switches: %ld\n",resUsage.ru_nivcsw);
			wait(&status);
		}
	}


	puts("\nProgram is done!\n");
	free(input);
	return 0;
}

