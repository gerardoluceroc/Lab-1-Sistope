//#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.
#include <string.h> 
#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h>

int main(int argc, char* argv[]){


	printf("Acabo de entrar a vis.c y el argumento es: %s\n",argv[1]);

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