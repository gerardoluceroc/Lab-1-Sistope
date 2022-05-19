#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.
#include <string.h> 
#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h>

int main(int argc, char* argv[]){


	int i = 0;
	char buffer[300];
	char matriz[300][300];
	int cantidadVisibilidades = 0;
	int numeroProcesoHijo = atoi(argv[1]);
	printf("Acabo de entrar a vis.c siendo el hijo %d y el argumento es: %s\n",numeroProcesoHijo,argv[0]);

	while(i<5){


		read(STDIN_FILENO, buffer, sizeof(buffer));
		printf("estoy en vis.c del proceso hijo %d y recibi la cadena:\n%s\n",numeroProcesoHijo,buffer);
		i=i+1;
		if(strlen(buffer) > 0){
			cantidadVisibilidades = cantidadVisibilidades+1;
		}
		//sleep(1);
		//wait(NULL);


	}

	printf("LA cantidad de visibilidades recibidas por el proceso %d es %d\n",numeroProcesoHijo,cantidadVisibilidades);
	





/*
	printf("WENA MANOLO estoy en kkexeprueba.c y toi hablandooooooo\n");

	char* mensaje = "Este mensaje viene de kkexeprueba y eso xao\n";
	
	//se manda el mensaje al padre original de toa la wea
	write(STDOUT_FILENO, "Este mensaje viene de kkexeprueba y eso xao\n",45);

	//write(STDOUT_FILENO, mensaje,sizeof(mensaje));

	//write(STDOUT_FILENO, "Este mensaje viene de kkexeprueba y eso xao\n",strlen("Este mensaje viene de kkexeprueba y eso xao\n"));

*/






	//exit(0);


	return(0);


}//fin main	