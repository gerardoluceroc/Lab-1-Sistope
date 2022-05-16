#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.
#include <string.h> 
#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h>
#include "funciones.c"

#define LECTURA 0
#define ESCRITURA 1

int main(int argc, char* argv[]){

	//int pid;
	int status;
	char buffer[100];
	char buffer2[100];
	int fd[2];

/////////////////////////// Seccion donde simulo el programa pero con listas y su promedio//////////////////////////////////////////////
///########################################################################################################################################
	int cantidadFilas = 3;
	int** matriz = crearMatrizCuadrada(cantidadFilas,3);

	//matriz[0] = {8.9,27}
	matriz[0][0] = 8;
	matriz[0][1] = 9;
	matriz[0][2] = 27;

	//matriz[1] = {5,6,8};
	matriz[1][0] = 5;
	matriz[1][1] = 6;
	matriz[1][2] = 8;

	//matriz[2] = {7,56,99}
	matriz[2][0] = 7;
	matriz[2][1] = 56;
	matriz[2][2] = 99;

	printf("El promedio es %d\n", calcularPromedio(matriz[2], cantidadFilas));



//////////////////////////////////////////////PROBANDO///////////////////////////////////////////////////////////////

	//array pa probar
	//float lista[] = 
	float lista[4] = {-2.0,3.0,9.0,5.0};


	printf("El numero de la lista qla es %f\n", lista[0]);

	int pipeMio[2];
	int pipeHijoEscribe[2];
	int pipePadreEscribe[2];

	pipe(pipeMio);
	pipe(pipeHijoEscribe);
	pipe(pipePadreEscribe);

	int pid = fork();

	//Pipe mio: el padre escribe y el hijo lee
	//pipeHijoEscribe: el hijo escribe y el padre lee

	//padre
	if(pid > 0){


//////////////////////////////////////////////PRUEBA DE ENVIO DE LISTA DE ENTEROS/////////////////////////////

		//se cierra la lecura del padre en este pipe y se le envia la lista de enteros
		close(pipePadreEscribe[LECTURA]);
		write(pipePadreEscribe[ESCRITURA], lista, sizeof(lista));
		printf("Lista enviada a mi hijo\n");

		//copio con el dup el pipe de lectura pa leer a proceso hijo
		close(pipeHijoEscribe[ESCRITURA]);
		dup2(pipeHijoEscribe[LECTURA], STDIN_FILENO);

		//creo una lista random
		float* listaRandom = (float*)malloc(sizeof(float)*2);
		listaRandom[0] = -77.0;
		listaRandom[1] = 84.7;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////PRUEBA DE ENVIO DE MENSAJES ENTRE PADRE E HIJO////////////////////////

		/*
		//cierro la lectura y le mando un mensaje a mi hijo
		close(pipeMio[LECTURA]);
		write(pipeMio[ESCRITURA], "hola hijo mio\n",15);	
		printf("mensaje enviado a mi hijo\n");

		//espero a hijo
		wait(&status);

		//cierro la escritura de este pipe y recibo el mensaje de hijo
		close(pipeHijoEscribe[ESCRITURA]);	
		read(pipeHijoEscribe[LECTURA],buffer2, sizeof(buffer2));
		printf("Recibi una respuesta de mi hijo y fue: %s\n", buffer2);
		
		*/
       /////////////////////////////////////////////////////////////////////////////////////////////






	}//fin if

	if (pid == 0){


//////////////////////////////////////////////PRUEBA DE ENVIO DE LISTA DE ENTEROS/////////////////////////////

		float lista1[4];
		//cierro la escritura de este pipe y leo lo enviado
		close(pipePadreEscribe[ESCRITURA]);
		read(pipePadreEscribe[LECTURA], lista1,sizeof(lista1));
		printf("Lista recibida por mi padre\n");
		printf("La posicion 0 es: %f\n", lista1[1]);

		printf("Ya calmao papi dejame sacarle el promedio a esta wea\n");

		//Se copia la escritura en el stdout
		//Pero con el pipe en el que escribe el hijo
		close(pipeHijoEscribe[LECTURA]);
		dup2(pipeHijoEscribe[ESCRITURA], STDOUT_FILENO);





//////////////////////////////////////////////////////////////////////////////////////////////////////////////		






	////////////////////PRUEBA DE ENVIO DE MENSAJES ENTRE PADRE E HIJO////////////////////////

        /*
		close(pipeMio[ESCRITURA]);
		read(pipeMio[LECTURA], buffer,sizeof(buffer));
		printf("mi taita me envio un mensaje dijo:%s\n", buffer);


		printf("Voy a tratar de enviarle un mesaje a mi taita\n");
		close(pipeHijoEscribe[LECTURA]);
		write(pipeHijoEscribe[ESCRITURA], "AA\n",4);
		printf("ya le envie el mensaje a mi taita\n");
		
		*/
    //////////////////////////////////////////////////////////////////////////////////////////




	}//fin if pid == 0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	




















/*
	pipe(fd);
	printf("FD[0] = %d y fd[1] = %d\n", fd[LECTURA], fd[ESCRITURA]);


	pid = fork();

	

	//hijo
	if(pid == 0){

		printf("Entré al if del hijo, osea mi pid como hijo es %d y la variable pid es %d, ah y bueno el pid de mi padre es%d\n\n\n",getpid() ,pid,getppid());

		//se cierra la lectura del hijo
		//close(fd[LECTURA]);

		//se manda el mensaje
		//write(fd[ESCRITURA], "Hola papa soy tu hijo\n", 23);
		//exit(0);
        //close(fd[LECTURA]);
		dup2(fd[ESCRITURA], STDOUT_FILENO);
        
        execl("./kkexeprueba","./kkexeprueba",(char*)NULL);

        printf("Si esta wea se ve, algo falló\n");

	}//fin if

	else{

		wait(&status);

		printf("Soy el padre y mi pid es %d y la variable pid tieene el valor de %d\n", getpid(), pid);
		//close(fd[ESCRITURA]);
		dup2(fd[LECTURA], STDIN_FILENO);
		read(STDIN_FILENO, buffer, sizeof(buffer));
		printf("Soy el padre y recibi un mensaje de mi hijo este es %s", buffer);

	}//fin else





*/









	liberarMatrizEnteros(matriz,cantidadFilas);
   
	return(0);


}//fin main