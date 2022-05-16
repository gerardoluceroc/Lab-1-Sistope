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

//Funcion que lee un archivo y devuelve un listado de todas lo leído en cada linea del archivo
//Entradas: nombre del archivo (string)
//Salida: array de strings, en donde en cada posición hay una cadena, producto de lo leído en una linea del archivo
//Descripción: Se abre el archivo y se comienza a leer utilizando la función fgets y cada cadena leída se guarda en una posición del array
char* leerArchivo(char* nombreArchivo){
	printf("AAAAAAAAAAAAAA");

	//se abre el archivo en modo lectura
   	FILE* archivo = fopen(nombreArchivo,"r");

   	//Si el archivo no existe se retorna NULL
   	if(archivo == NULL){return(NULL);}

   	//valor para determinar las cadenas totales leídas
   	int cantidadCadenasLeidas = 0;

   	//variable para leer la cadena leída
   	char* cadenaLeida;

   	//Se solicita el espacio en memoria para el array de salida
   	char* arraySalida = (char*)malloc(sizeof(char));

   	fgets(cadenaLeida,1000,archivo);





   	

   	//Mientras no me encuentre al final del archivo
   	
   	//while(feof(archivo) == 0){

   		//Se lee la cadena del archivo
   		//fgets(cadenaLeida,1000,archivo);
   		//printf("Lo que hay en cadena es:%sYYYYY\n",cadenaLeida);


   		//se agrega la cadena leida al arreglo, para esto, se redimensiona el arreglo con la funcion realloc
   		//arraySalida = (char*)realloc(arraySalida,sizeof(char)*(cantidadCadenasLeidas+1));
   		//arraySalida[cantidadCadenasLeidas] = cadenaLeida;
   		//printf("la cadena agarrada en la posicion %d es %s\n", cantidadCadenasLeidas,arraySalida[cantidadCadenasLeidas]);
   		//cantidadCadenasLeidas = cantidadCadenasLeidas + 1;

   	//}//fin while
    
    fclose(archivo);
   	free(arraySalida);//BORRAR DESPUES 

   	return(NULL);



}//fin funcion leerArchivo

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
                flagO = 1;
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
                break;
            default:
                printf("Opcion Incorrecta\n");
                return 1;
        }//fin switch
    }//fin while

    //En caso de que alguna bandera no esté levantada quiere decir que el formato de entrada es incorrecto, por lo que se indica por pantalla y se termina el programa
    if(!(flagD && flagI && flagN && flagO)){

    	printf("Error en el formato de entrada\nEjemplo:./lab1 -i archivoeEntrada.csv -o ArchivoSalida.txt -d ancho -n cantidadDiscos \n");
    	return(1);


    }//fin if flag d,i,n,o

    

    //se transforman los valos obtenidos del ancho y la cantidad de discos a entero con la funcion atoi
    int anchoDisco = atoi(ancho);
    int cantidadDiscos = atoi(numeroDiscos);

    //si el ancho del disco o la cantidad de discos es menor o igual a cero
    //se indica el error por pantalla y se cierra el programa
    if(anchoDisco <= 0 || cantidadDiscos <=0){
    	printf("Error al indicar el ancho del disco y/o la cantidad del mismo, precure utilizar valores positivos\n");
    	return(1);
    }


    float cordenada;
    float cordenada2;
    char* cadena;



    leerArchivo(nombreArchivoEntrada);


    ////////////////////////
    //Funcion que lee el archivo con la información de las jaulas
	//Entrada: nombre del archivo, puntero a la cantidad de jaulas
	//Salida: lista de todas las jaulas con su informacion correspondiente
	//estructuraJaula* leerArchivo(char* nombreArchivo,int* cantidadJaulas){

   	//FILE * archivo = fopen(nombreArchivoEntrada,"r");
   	//fgets(cadena,1000,archivo);
   	//printf("la cadena rescatada es:%s\n",cadena);
   	//leo la cantidad de jaulas y lo almaceno en la variable cantidadJaulas
   	//fscanf(archivo,"%f",&cordenada);
   	//printf("lo leido es: %f\n",cordenada);

   	//fscanf(archivo,"%f",&cordenada2);
   	//printf("lo leido ess: %f\n",cordenada2);

   	//se le split a la cadena con la coma
   	//char* cadenaSplit = strtok(cadena,",");

   	//printf("Lo que hay en cadena es:%sYYYYY\n");




























	return(0);
}//fin main