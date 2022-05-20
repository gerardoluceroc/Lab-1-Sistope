#include <stdio.h> 
#include <stdlib.h>
#include <math.h>


float calcularDistancia(char cadena[], int cantidadElementos);
void liberarMatrizFlotantes(float** matrizFlotantes, int cantidadFilas);
float* cadenaAFlotantes(char cadena[]);

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

    //se obtiene las coordenas u y v como flotantes con la funcion strtok
    coordenadaU = strtof(coordenadaUChar,NULL);
    coordenadaV = strtof(coordenadaVChar,NULL);

    //se procede a calcular la distancia
    float argumentoRaiz = ((coordenadaU * coordenadaU) + (coordenadaV * coordenadaV));

    //Se calcula la raiz cuadrada
    float resultado = sqrtf(argumentoRaiz);

    //Finalmente, se retornan el resultado obtenido
    return(resultado);


}//fin calcularDistancia





//Funcion que toma una cadena y la transforma en una array dinamico de enteros.
//Esta función lo que hará es recibir la cadena leída por fgets y la transformará
//En un arreglo de 5 enteros con la información de la visibilidad observada.

//Entrada: Cadena de caracteres la cual será evaluada
//Salida:arreglo de flotantes con los datos de la visibilidad recibida

float* cadenaAFlotantes(char cadena[]){

	//se guarda la cantidad de parametros que tiene la visibilidad, para este caso son 5
	int cantidadParametros = 5;

	//Se pide el espacio en memoria
	float* arraySalida = (float*)malloc(sizeof(float)*cantidadParametros);

	//variables para guardar los valores en sus respectivas posiciones
	int const_posicionU = 0;
	int const_posicionV = 1;
	int const_valorReal = 2;
	int const_valorImaginario = 3;
	int const_ruido = 4;

	//valores para guardar los valores flotantes

	float posicionU;
	float posicionV;
	float valorReal;
	float valorImaginario;
	float ruido;

	//Variable para guardar el valor flotante obtenido de la visibilidad pero en version char
	char* charLeido;

	//Variable para guardar el valor flotante obtenido de la visibilidad 
	char flotanteLeido;

	//Variable para guardar lo que queda de cadena de caracteres luego de aplicar la funcion strtok
	char* cadenaRestante;

	//Este proceso se realizará 5 veces con su respectiva variable


	//Se realiza split de la cadena para obtener un valor, para esto se utiliza la funcion strtok
	charLeido = strtok(cadena, ",");
	//Se guarda lo que queda de cadena
	cadenaRestante = strtok(NULL," ");
	//Se transforma el valor a flotante y se guarda en su variable respectiva
	posicionU = strtof(charLeido,NULL);

	//Se realiza split de la cadena para obtener un valor, para esto se utiliza la funcion strtok
	charLeido = strtok(cadenaRestante, ",");
	//Se guarda lo que queda de cadena
	cadenaRestante = strtok(NULL," ");
	//Se transforma el valor a flotante y se guarda en su variable respectiva
	posicionV = strtof(charLeido,NULL);

	//Se realiza split de la cadena para obtener un valor, para esto se utiliza la funcion strtok
	charLeido = strtok(cadenaRestante, ",");
	//Se guarda lo que queda de cadena
	cadenaRestante = strtok(NULL," ");
	//Se transforma el valor a flotante y se guarda en su variable respectiva
	valorReal = strtof(charLeido,NULL);

	//Se realiza split de la cadena para obtener un valor, para esto se utiliza la funcion strtok
	charLeido = strtok(cadenaRestante, ",");
	//Se guarda lo que queda de cadena
	cadenaRestante = strtok(NULL," ");
	//Se transforma el valor a flotante y se guarda en su variable respectiva
	valorImaginario = strtof(charLeido,NULL);

	//Se realiza split de la cadena para obtener un valor, para esto se utiliza la funcion strtok
	charLeido = strtok(cadenaRestante, ",");
	//Se guarda lo que queda de cadena
	cadenaRestante = strtok(NULL," ");
	//Se transforma el valor a flotante y se guarda en su variable respectiva
	ruido = strtof(charLeido,NULL);


	//Se guardan los valores leidos en el array
	arraySalida[const_posicionU] = posicionU;
	arraySalida[const_posicionV] = posicionV;
	arraySalida[const_valorReal] = valorReal;
	arraySalida[const_valorImaginario] = valorImaginario;
	arraySalida[const_ruido] = ruido;

	//Se retorna el array
	return(arraySalida);

	
}//Fin cadenaAFlotantes





//Funcion que calcula el promedio simple de los elementos de un array de flotantes.
//Esta función será utilizada para calcular la media imaginaria y real de las visibilidades obtenidas por el proceso hijo.

//Entrada: Array de numeros flotantes
//Salida: promedio simple del total de numeros que componen el array
float calcularPromedio(float* arrayElementos, int cantidadElementos){

	//iterador
	int i = 0;

	//variable donde se guardará el resultado final
	int resultado = 0;

	//mientras queden valores por sumar
	while(i<cantidadElementos){

		//se suma el valor al resultado
		resultado = resultado + arrayElementos[i];
		i = i+1;

	}//fin while

	//Se calcula el promedio simple
	resultado = (resultado/cantidadElementos);

	//se retorna el resultado
	return(resultado);

}//Fin funcion calcular promedio








//Funcion que calcula la sumatoria de los elementos de un array de flotantes.
//Esta función será utilizada para calcular el ruido total de las visibilidades obtenidas por el proceso hijo

//Entrada: Array de numeros flotantes
//Salida: sumatoria del total de numeros que componen el array
float sumatoria(float* arrayElementos, int cantidadElementos){

	//iterador
	int i = 0;

	//variable donde se guardará el resultado final
	int resultado = 0;

	//mientras queden valores por sumar
	while(i<cantidadElementos){


		//se suma el valor al resultado
		resultado = resultado + arrayElementos[i];
		i = i+1;

	}//fin while

	//se retorna el resultado
	return(resultado);

}//Fin funcion sumatoria









//Funcion que calcula la potencia de un array de flotantes.
//Esta función será utilizada para calcular la potencia de las visibilidades obtenidas por el proceso hijo

//Entrada: Array de numeros flotantes
//Salida: potencia del array de elementos
float calcularPotencia(float* valorReal,float* valorImaginario, int cantidadElementos){

	//iterador
	int i = 0;

	//variable donde se guardará el resultado final
	int resultadoFinal = 0;

	int resultadoParcial;

	//mientras queden valores por sumar
	while(i<cantidadElementos){

		//Se calcula el termino i de la sumatoria
		resultadoParcial = sqrtf((valorReal[i] * valorReal[i]) + (valorImaginario[i] * valorImaginario[i]));

		//se suma el valor al resultado
		resultadoFinal = resultadoFinal + resultadoParcial;
		i = i+1;

	}//fin while

	//se retorna el resultado
	return(resultadoFinal);

}//Fin funcion sumatoria






































//Funcion que libera la memoria utilizada por una matriz de flotantes

//Entrada:matriz de numeros flotantes, cantidad de filas de la matriz
void liberarMatrizFlotantes(float** matrizFlotantes, int cantidadFilas){

	//iterador
	int i;

	//mientras queden filas en la matriz sin liberar
	for(i = cantidadFilas-1; i>=0;i--){

		//se libera la fila correspondiente
		free(matrizFlotantes[i]);

	}//fin for

}//fin liberarMatrizEnteros









int funciones(){





	return(0);

}