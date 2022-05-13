#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd;
	int mi_pipe[2];
	int pid;
	
	if (pipe(mi_pipe) == -1) {
		printf("No se pudo crear el pipe\n");
		exit(-1);
	}
	
	if ( (pid = fork()) == -1) {
		printf("no se pudo crear un hijo\n");
		exit(-1);
        }
	
	if (pid == 0) { //soy hijo
		close(mi_pipe[0]); // cierra lado de lectura del pipe
		if (dup2(mi_pipe[1], STDOUT_FILENO) == -1) {
		    printf("Error in dup2()\n");
		    exit(-1);
		}
		execlp("ls", "ls", NULL); // si esto funciona no hay retorno
	}
	else {
		close(mi_pipe[1]); // cierra lado de escritura
		dup2(mi_pipe[0], STDIN_FILENO);
		execlp("wc", "wc", "-cwl", NULL); // si esto funciona no hay retorno
	}
	
   exit(0);
}

