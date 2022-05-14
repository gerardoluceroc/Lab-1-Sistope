#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.
#include <string.h> 
#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h>

#define LECTURA 0
#define ESCRITURA 1

int main(int argc, char* argv[]){

	int pid;
	int status;
	char buffer[100];
	int fd[2];

	pipe(fd);
	printf("FD[0] = %d y fd[1] = %d\n", fd[LECTURA], fd[ESCRITURA]);


	pid = fork();

	

	//hijo
	if(pid == 0){

		printf("Entré al if del hijo, osea mi pid como hijo es %d y la variable pid es %d, ah y bueno el pid de mi padre es%d\n\n\n",getpid() ,pid,getppid());

		//se cierra la lectura del hijo
		close(fd[LECTURA]);

		//se manda el mensaje
		write(fd[ESCRITURA], "Hola papa soy tu hijo\n", 23);
		//exit(0);


        
        //execl("./kkexeprueba","./kkexeprueba",(char*)NULL);

        //printf("Si esta wea se ve, algo falló\n");

	}//fin if

	else{

		wait(&status);

		printf("Soy el padre y mi pid es %d y la variable pid tieene el valor de %d\n", getpid(), pid);
		close(fd[ESCRITURA]);
		read(fd[LECTURA], buffer, sizeof(buffer));
		printf("Soy el padre y recibi un mensaje de mi hijo este es %s", buffer);

	}//fin else





	return(0);


}//fin main