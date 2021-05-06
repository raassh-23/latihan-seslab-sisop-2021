#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd1[2];
	int fd2[2];

    if (pipe(fd1)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 

	if (pipe(fd2)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	}

    pid_t pid = fork();

    if(pid == 0) {
        dup2(fd1[1], STDOUT_FILENO);

        close(fd1[0]);
        close(fd1[1]);

        close(fd2[0]);
        close(fd2[1]);

        execlp("ls", "ls", argv[1], NULL);
    }

    pid = fork();

    if(pid == 0) {
        dup2(fd1[0], STDIN_FILENO);

        close(fd1[0]);
        close(fd1[1]);

        dup2(fd2[1], STDOUT_FILENO);

        close(fd2[0]);
        close(fd2[1]);

        execlp("head", "head", "-n", "3", NULL);
    } else if (pid > 0) {
        
        close(fd1[0]);
        close(fd1[1]);

        dup2(fd2[0], STDIN_FILENO);

        close(fd2[0]);
        close(fd2[1]);

        execlp("tail", "tail", "-n", "1", NULL);
    }
    
    return 0;
}