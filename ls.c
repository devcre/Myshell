#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

static void do_ls(char *path);

int main(int argc, char* argv[]){
	int i;

	//if(argc < 2){
	//	fprintf(stderr, "%s: no argments\n", argv[0]);
	//	exit(1);
	//}

	if(argc < 2){
		do_ls("./"); // default
	}
	else if(argc > 1){
		for(i=1; i<argc; i++){ //execute instruction "ls"
			do_ls(argv[i]); // argc[0] == ls
		}
	}
	else{
		printf("Unexpected Error\n");
		exit(1);
	}

	exit(0);
}

static void do_ls(char* path){
	DIR *d;
	struct dirent *ent;
	struct stat buf;

	d = opendir(path);
	if(!d){ // exception handle
		perror(path);
		exit(1);
	}

	while(ent = readdir(d)){
		lstat(ent -> d_name, &buf);

		if(S_ISDIR(buf.st_mode)){ // directories in path
			printf("[Directory Name] %s\n", ent->d_name);
		}
		else if(S_ISREG(buf.st_mode)){ // files in path
			printf("[File Name] %s\n", ent->d_name);
		}
	}

	closedir(d);
}
