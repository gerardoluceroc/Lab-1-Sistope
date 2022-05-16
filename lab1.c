#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.
#include <string.h> 
#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h>
#include <stdint.h>
//#include <jpeglib.h> //no lo encuentra el compilador
#include <getopt.h>
#include <stdbool.h>
#include "funciones.c"

#define LECTURA 0
#define ESCRITURA 1

int main(int argc, char* argv[]){

//banderas para verificar el formato de entrada de los parametros
	int flagI = 0;
	int flagO = 0;
	int flagD = 0;
	int flagN = 0;

//Variables para almacenar lo recibido por teclado
	char* nombreArchivoEntrada;
	char* nombreArchivoSalida;
	char* numeroDiscos;
	char* ancho;
	int flag; //booleano que indica si se activa la bandera

	int c;

	char* xd;//BORRAR

    //ciclo para obtener los parametros ingresados por teclado
	while((c = getopt(argc, argv, "i:o:d:n:b")) != -1){
		switch(c){
        	case 'i':
                nombreArchivoEntrada = optarg;
                //se levanta la bandera de i
                flagI = 1;
                break;
            case 'o':
                nombreArchivoSalida = optarg;
                //se levanta la bandera de o
                flagO = 0;
                break;
            case 'd':
                ancho = optarg;
                //se levanta la bandera de d
                flagD = 1;
                 break;
            case 'n':
                numeroDiscos = optarg;
                //se levanta la bandera de n
                flagN = 1;
                break;
            case 'b':
                flag = 1;
                xd = optarg;//BORRAR
                break;
            default:
                printf("Opcion Incorrecta\n");
                return 1;
        }//fin switch
    }//fin while

    printf("resultados de la wea obtenidos:i = %s,o = %s,d = %s,n = %s,b = %s,flag = %d\n",nombreArchivoEntrada,nombreArchivoSalida,ancho,numeroDiscos,xd,flag);























	return(0);
}//fin main