#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	
	char *args[51]; // command line argument
	char *input;

	int should_run = 1;
	int i;

	int status; // status of child process
	int chk; // check if child process exited normally

	pid_t pid;

	while(should_run){
		printf("my_shell>> ");
		fflush(stdout);

		input = (char*)malloc(100*sizeof(char));
		fgets(input, 101, stdin); // get command line as much as 100

		printf("input: %s\n", input);

		i = 0;
		// tokenize command line
		args[i] = strtok(input, " \n");
		while(args[i] != NULL){
			i++;
			args[i] = strtok(NULL, " \n");
		}

		// printf("input: %s\n", input);
		if(args[0] == NULL){ // if no argument, return to the start of while loop
			
		}

		if(strcmp(input, "exit") == 0){ //if command is exit, exit shell
			break;
		}

		else{
			printf("input : %s\n", input);
			printf("args[0] : %s\n", args[0]);
			printf("args[1] : %s\n", args[1]);

			pid = fork();
			if(pid < 0){
				perror("fork error");
				exit(0);
			}

			if(pid == 0){ // child process
				if(strcmp(args[0], "cat") == 0){
					execv("./cat", args);
				}
				else{
					execvp(args[0], args);
				}
			}

			if(pid > 0){ // parent process
				chk = waitpid(pid, &status, 0); // parent process wait until child process complete
				if(chk < 0){
					printf("Unexpected error\n");
					exit(0);
				}
			}
		}
	}
	free(input);

	return 0;
}
