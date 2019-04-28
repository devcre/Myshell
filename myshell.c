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

		i = 0;
		// tokenize command line
		args[i] = strtok(input, " \n");
		while(args[i] != NULL){
			i++;
			args[i] = strtok(NULL, " \n");
		}

		if(args[0] == NULL){ // if no argument, return to the start of while loop
			goto no_input;	
		}

		if(strcmp(input, "exit") == 0){ //if command is exit, exit shell
			break;
		}
		else{
			pid = fork();
			if(pid < 0){
				perror("fork error\n");
			}

			if(pid == 0){ // child process
				if(strcmp(args[0], "cat") == 0){
					execv("./cat", args); // execute cat instruction
				}
				else if(strcmp(args[0], "ls") == 0){
					execv("./ls", args); // execute ls instructon
				}
				else if(strcmp(args[0], "mkdir") == 0){
					execv("./mkdir", args); // execute mkdir instruction
				}
				else{
					// execvp(args[0], args); // execute other instructions
					if(execvp(args[0], args) < 0){ // if executing instruction fail,
						printf("Command Not Found.\n");
						kill(getpid(), SIGINT); // kill useless child process
					}
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
		no_input:;
	}
	free(input);

	return 0;
}
