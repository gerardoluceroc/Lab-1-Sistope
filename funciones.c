#include <stdio.h> 
#include <stdlib.h>

void liberarMatrizEnteros(int** matrizEnteros, int cantidadFilas);
int** crearMatrizCuadrada(int cantidadFIlas, int cantidadColumnas);
int calcularPromedio(int* arreglo, int largoArreglo);


float calcularDistancia(char cadena[], int cantidadElementos);

//Función que recibe la cadena de caracteres perteneciente a una linea del archivo de entrad
//Y a traves de esta cadena, obtiene la distancia de la visibilidad (coordenadas (u,v)) al origen
//Entrada: Cadena de caracteres, largo de la cadena de caracteres
//Salida: Distancia de la coordenada u,v al origen
float calcularDistancia(char cadena[], int cantidadElementos){

    //variables para guardar los valores de las coordenadas
    float coordenadaU;
    float coordenadaV;

    //se realiza un primer split para obtener la coordenada U en forma de char*
    char* coordenadaUChar = strtok(cadena, ",");

    //se obtiene ahora la coordenada V en forma de char*
    char* cadenaRestante = strtok(NULL, " ");
    char* coordenadaVChar = strtok(cadenaRestante, ",");

    //se obtiene las coordenas u y v como flotantes con la funcion atof
    coordenadaU = strtof(coordenadaUChar,NULL);
    coordenadaV = strtof(coordenadaVChar,NULL);

    //se procede a calcular la distancia
    float argumentoRaiz = ((coordenadaU * coordenadaU) + (coordenadaV * coordenadaV));

    //Se calcula la raiz cuadrada
    float resultado = sqrtf(argumentoRaiz);

    //Finalmente, se retornan el resultado obtenido
    return(resultado);


}//fin calcularDistancia





































void liberarMatrizEnteros(int** matrizEnteros, int cantidadFilas){

	//iterador
	int i;

	//mientras queden filas en la matriz sin liberar
	for(i = cantidadFilas-1; i>=0;i--){

		//se libera la fila correspondiente
		free(matrizEnteros[i]);

	}//fin for

}//fin liberarMatrizEnteros





int** crearMatrizCuadrada(int cantidadFIlas, int cantidadColumnas){

	int i,j;

	//se pide el espacio en memoria de la matriz
	int** matriz = (int**)malloc(sizeof(int*)*cantidadFIlas);

	for(i=0;i<cantidadFIlas;i++){

		//se pide el espacio en memoria en cada fila
		matriz[i] = (int*)malloc(sizeof(int)*cantidadColumnas);


	}//fin for

	//se retorna la matriz creada
	return(matriz);


}// fin crearMatrizCuadrada






int calcularPromedio(int* arreglo, int largoArreglo){

	int i;
	int suma = 0;

	for(i=0; i<largoArreglo;i++){

		suma = suma + arreglo[i];


	}//fin for

	int resultado = suma/largoArreglo;
	return(resultado);



}//fin calcularPromedio









int funciones(){





	return(0);

}