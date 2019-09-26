#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define NUM 50

//globals
int totalNumberOfFiles = 0;
int totalTimeForAllFiles = 0;

void exitProgram(int sig);
void *getFile(void * arg);

void exitProgram (int sig){
	//statistics, total number of file requests recieved
	
	//extra credit time for each file and average
	int average = totalTimeForAllFiles / totalNumberOfFiles;
	printf("\n\nEnd of Program Statistics:\n");
	printf("Total number of file requests recieved: %d files.\n",totalNumberOfFiles);
	printf("Average amount of time to get each file: %d seconds.\n", average);	
	printf("Total amount of time to get all files: %d seconds.\n",totalTimeForAllFiles);

	printf("\nShutting down...\n");
	exit(0);
}

void *getFile(void * arg){
	//obtain file from dispatcher
	char *file = (char *) arg;
	int random = rand()%100;
	int random2 = rand()%4;
	int counter = 0; //counter for file access time

	//sleep seven to ten seconds, twenty percent probability
	if(random<20){
		//seven plus a random number,
		int sleepTime = 7 + random2;
		sleep(sleepTime);

		//e.c. time for each file
		counter = sleepTime;
		totalTimeForAllFiles += sleepTime;

		//wakes up, prints diagnostic message and then terminates
		fprintf(stdout, " File %s was found in hard drive! It took %d seconds.\n", file, sleepTime);
	}
	else { //else sleep for one second, eighty percent probability
		sleep(1);

		//e.c. time for each file
		counter=1;
		totalTimeForAllFiles+=counter;

		//wakes up, prints diagnostic message and then terminates
		fprintf(stdout, " File %s was found in disc cache! It took %d second.\n",file,counter);
	}
	
	//clean up
	free(file);
	return NULL;
}

int main(){
	int status;
	pthread_t thread;//dispatch thread
	char* file;

	//ctrl-c to exit if user wants to
	signal(SIGINT, exitProgram);
	
	while(1){
		file = malloc(NUM * sizeof(char));
		printf("What file would you like to access? ");
		scanf("%s",file);

		//make sure user can quit
		if(!strcmp(file,"quit"))
			break;

		//creates thread to find the file
		if((status = pthread_create(&thread,NULL,getFile,file)) != 0){
			//thread error
			fprintf(stderr,"failed to create thread %d: %s\n", status, strerror(status));
			exit(1);
		}

		//increases the count number of files
		totalNumberOfFiles++;
	}
}
