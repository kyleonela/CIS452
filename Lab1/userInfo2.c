#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int main(){

	//sys commands: users, id -u, id -g, hostname
	//cat /etc/passwd | head -n (five) | cut -d: -f1
	
	FILE * file;
	int n = -1;

	char word[50];
	char userinput[20];
	char hostname[1024];
	gethostname(hostname, 1024);

	printf("\nUser is: %s\n\n", getlogin());
	printf("UID is: %d\n", getuid());
	printf("GID is: %d\n\n", getgid());
	printf("host is: %s\n\n", hostname);

	file = popen("cat /etc/passwd | head -n 5 | cut -d: -f1", "r");
	if(file != NULL){
		while(fgets(word, 50, file) != NULL){
			n++;
			printf("entry %d", n); 
			printf(": %s", word);
		}
		pclose(file);
	}

	printf("\nenvironment variable desired? ");
	scanf("%s", userinput);
	printf("value is: %s\n", getenv(userinput));
}
