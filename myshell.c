#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	
	char *args[100] // command line argument
	int should_run = 1;

	while(should_run){
		printf("my_shell>>");

		input = (char*)malloc(100*sizeof(char));
		fgets(input, 101, stdin); // get command line as much as 100

		i = 0;
		// tokenize command line
		args[i] = strtok(input, " \n");
		while(args[i] != NULL){
			i++;
			args[i] = strtok(NULL, " \n");
		}

		if(args[0] == NULL){ // if no argument, return to at the start of while loop
			
		}
		else{
			if(strcmp(imput, "exit") == 0){ // if command is exit, exit shell
				break;
			}
		}
	}

	return 0;
}
