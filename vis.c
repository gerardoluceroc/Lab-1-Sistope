#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.
#include <string.h> 
#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h>
#include "funciones.c"

#define POSICION_U 0
#define POSICION_V 1
#define VALOR_REAL 2
#define VALOR_IM 3
#define RUIDO 4


int main(int argc, char* argv[]){



	
	int i = 0;
	//variable para guardar la cadena recibida por el proceso padre
	char buffer[300];

	int cantidadVisibilidades = 0;

	//variable para guardar el numero del proceso hijo en donde me encuentro.
	//Esto en caso de que aquel dato sea requerido.
	int numeroProcesoHijo = atoi(argv[1]);

	//Variable para guardar el arreglo de flotantes con los datos de la visibilidad recibida en forma de cadena de caracteres por parte del proceso padre
	float* datosVisibilidad;

	//Con tal de no utilizar una matriz, se guardará en su propio array, los datos de las visibilidades recibidas.
	//como por ejemplo la posicion en el eje u, el valor real, etc.
	float* datosPosicionU = (float*)malloc(sizeof(float));
	float* datosPosicionV = (float*)malloc(sizeof(float));
	float* datosValorReal = (float*)malloc(sizeof(float));
	float* datosValorImaginario = (float*)malloc(sizeof(float));
	float* datosRuido = (float*)malloc(sizeof(float));

	printf("Acabo de entrar a vis.c siendo el hijo %d y el argumento es: %s\n",numeroProcesoHijo,argv[0]);


	while(1){

		//Se lee lo enviado por el proceso padre
		read(STDIN_FILENO, buffer, sizeof(buffer));

		//Si lo enviado es "FIN"
		if(buffer == "FIN"){
			//se detiene el ciclo y se deja de leer
			break;
		}

		else{

			if(strlen(buffer) > 0){

				//Se aumenta el contador de la cantidad de visibilidades a procesar
				cantidadVisibilidades = cantidadVisibilidades+1;

				//Se obtienen los datos de la cadena recibida
				datosVisibilidad = cadenaAFlotantes(buffer);

				//se agregan los datos recibidos a los arrays que contienen los datos correspondientes acumulados
				//Pero primero, estos arrays deben agrandar su tamaño, para esto se utiliza la funcion realloc
				datosPosicionU = (float*)realloc(datosPosicionU, sizeof(float)*cantidadVisibilidades);
				datosPosicionV = (float*)realloc(datosPosicionV, sizeof(float)*cantidadVisibilidades);
				datosValorReal = (float*)realloc(datosValorReal, sizeof(float)*cantidadVisibilidades);
				datosValorImaginario = (float*)realloc(datosValorImaginario, sizeof(float)*cantidadVisibilidades);
				datosRuido = (float*)realloc(datosRuido, sizeof(float)*cantidadVisibilidades);

				//Se agregan los datos
				datosPosicionU[cantidadVisibilidades-1] = datosVisibilidad[POSICION_U];
				datosPosicionV[cantidadVisibilidades-1] = datosVisibilidad[POSICION_V];
				datosValorReal[cantidadVisibilidades-1] = datosVisibilidad[VALOR_REAL];
				datosValorImaginario[cantidadVisibilidades-1] = datosVisibilidad[VALOR_IM];
				datosRuido[cantidadVisibilidades-1] = datosVisibilidad[RUIDO];

				//printf("estoy en el proceso hijo %d y los valores de las observaciones son:\nposicion u:%f\nposicion v:%f\n valor real:%f\nvalor im:%f\nruido:%f\n",numeroProcesoHijo,datosPosicionU[cantidadVisibilidades-1],datosPosicionV[cantidadVisibilidades-1],datosValorReal[cantidadVisibilidades-1],datosValorImaginario[cantidadVisibilidades-1],datosRuido[cantidadVisibilidades-1]);

			}//fin if buffer > 0

		}//Fin else
		

		printf("estoy en vis.c del proceso hijo %d y recibi la cadena:\n%s\n",numeroProcesoHijo,buffer);//BORRAR

	}//fin while

	//Se cierra la lectura del pipe
	close(STDIN_FILENO);



	//Se realiza el calculo de las propiedades del disco correspondiente
	float mediaReal = calcularPromedio(datosValorReal,cantidadVisibilidades);
	float mediaImaginaria = calcularPromedio(datosValorImaginario,cantidadVisibilidades);
	float potenciaDisco = calcularPotencia(datosValorReal,datosValorImaginario,cantidadVisibilidades);
	float ruidoTotal = sumatoria(datosRuido,cantidadVisibilidades);

	//Se guardan las propiedades en un array de flotantes
	float* propiedadesDisco = (float*)malloc(sizeof(float)*4);
    propiedadesDisco[0] = mediaReal;
    propiedadesDisco[1] = mediaImaginaria;
    propiedadesDisco[2] = potenciaDisco;
    propiedadesDisco[3] = ruidoTotal;




    //sleep(7);
	//close(STDIN_FILENO);
	//close(STDOUT_FILENO);
	printf("LA cantidad de visibilidades recibidas por el proceso %d es %d\n",numeroProcesoHijo,cantidadVisibilidades);
	//write(STDOUT_FILENO,"WENA COMPI TERMINÉ\n",sizeof("WENA COMPI TERMINÉ\n"));

	





/*
	printf("WENA MANOLO estoy en kkexeprueba.c y toi hablandooooooo\n");

	char* mensaje = "Este mensaje viene de kkexeprueba y eso xao\n";
	
	//se manda el mensaje al padre original de toa la wea
	write(STDOUT_FILENO, "Este mensaje viene de kkexeprueba y eso xao\n",45);

	//write(STDOUT_FILENO, mensaje,sizeof(mensaje));

	//write(STDOUT_FILENO, "Este mensaje viene de kkexeprueba y eso xao\n",strlen("Este mensaje viene de kkexeprueba y eso xao\n"));

*/





	//se libera la memoria utilizada
	free(datosVisibilidad);
	free(datosPosicionU);
	free(datosPosicionV);
	free(datosValorReal);
	free(datosValorImaginario);
	free(datosRuido);
	free(propiedadesDisco);

	return(0);


}//fin main	