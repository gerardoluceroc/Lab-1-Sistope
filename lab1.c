#include <unistd.h> //Para utilizar fork(), pipes(), entre otros
#include <stdio.h> //Funciones de entrada y salida como printf
#include <stdlib.h> //Asignación de memoria, atoi, etc.
#include <string.h> 
#include <sys/wait.h> //Define las constantes simbólicas para usar con waitpid(), wait() por ejemplo
#include <sys/types.h>
#include <stdint.h>
#include <math.h>
//#include <jpeglib.h> //no lo encuentra el compilador
#include <getopt.h>
#include <stdbool.h>
#include "funciones.c"

#define LECTURA 0
#define ESCRITURA 1
#define RANGO_INF 0
#define RANGO_SUP 1
#define INFINITO 9999999
#define DECIMAL 0.0001
#define LIMITE_CADENA 300



int main(int argc, char* argv[]){

//banderas para verificar el formato de entrada de los parametros
	int flagI = 0;
	int flagO = 0;
	int flagD = 0;
	int flagN = 0;
    int flagB = 0; //booleano que indica si se activa la bandera -b

//Variables para almacenar lo recibido por teclado
	char* nombreArchivoEntrada;
	char* nombreArchivoSalida;
	char* numeroDiscos;
	char* ancho;

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
                flagB = 1;
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

    
printf("la bandera de -b flag es %d\n", flagB);//BORRAR

    //se transforman los valos obtenidos del ancho y la cantidad de discos a entero con la funcion atoi
    int anchoDisco = atoi(ancho);
    int cantidadDiscos = atoi(numeroDiscos);

    //si el ancho del disco o la cantidad de discos es menor o igual a cero
    //se indica el error por pantalla y se cierra el programa
    if(anchoDisco <= 0 || cantidadDiscos <=0){
    	printf("Error al indicar el ancho del disco y/o la cantidad del mismo, precure utilizar valores positivos\n");
    	return(1);
    }


    //A continuación, se crearán los pipes correspondientes para hacer la comunicacion del proceso padre con sus procesos hijos.
    //estos pipes se guardarán en un array, osea será una matriz en que cada fila será un pipe.
    //Como se debe crear una comunicación bidireccional, se realizarán 2 pipes por cada proceso hijo
    //en donde en el primer pipe, el padre escribirá y el hijo leerá y en el segundo el hijo escribirá y el padre leerá
    //Por lo tanto, cada 2 posiciones de la matriz de pipes, se guardarán los pipes correspondientes a la comunicación del
    //proceso padre con su respectivo proceso hijo.

    int cantidadPipes = cantidadDiscos*2;
    int matrizPipes[cantidadPipes][2];

    //iterador 
    int i=0;

    //Mientras queden pipes por crear
    while(i < cantidadPipes){


        //se crea el pipe en el que el padre escribe y el hijo lee
        pipe(matrizPipes[i]);
        printf("i = %d, en matrizPipes[%d][0] = %d\n", i, i, matrizPipes[i][0]);//borrar
        printf("i = %d, en matrizPipes[%d][1] = %d\n", i, i, matrizPipes[i][1]);//borrar

        //se aumenta el iterador
        i = i+1;

        //se crea el pipe en el que el hijo escribe y el padre lee
        pipe(matrizPipes[i]);
        printf("i = %d, en matrizPipes[%d][0] = %d\n", i, i, matrizPipes[i][0]);//borrar
        printf("i = %d, en matrizPipes[%d][1] = %d\n", i, i, matrizPipes[i][1]);//borrar
        

        //se aumenta el iterador
        i = i+1;
        

    }//fin while i<cantidadPipes







printf("cantidad de pipes %d\n", cantidadPipes);//borrar

//se comienzan a crear los procesos hijos
int cantidadProcesosHijos = cantidadDiscos;
int cantidadProcesosCreados = 0;
int pid = 1;

//mientras queden procesos hijos por crear 
while((cantidadProcesosCreados < cantidadProcesosHijos) && (pid > 0)){

    //Se crea el proceso hijo
    pid = fork();
    cantidadProcesosCreados = cantidadProcesosCreados + 1;

    //Proceso padre
    if(pid > 0){

        printf("Soy el proceso padre y mi variable pid es %d y mi pid como padre es %d\n", pid, getpid());//Borrar

        //se cierra la lectura en el pipe que el padre escribe para el proceso hijo correspondiente
        close(matrizPipes[(cantidadProcesosCreados*2) - 2][LECTURA]);

        //Se cierra la escritura en el pipe que el padre lee lo enviado por el proceso hijo
        close(matrizPipes[(cantidadProcesosCreados*2) - 1][ESCRITURA]);


    }//fin if pid > 0

    //Proceso hijo
    else if(pid == 0){

        printf("soy el proceso hijo y mi variable pid es %d y mi pid es %d\n", pid, getpid());//borrar

        //se cierra la escritura en el pipe que el hijo lee lo enviado por el padre
        close(matrizPipes[(cantidadProcesosCreados*2) - 2][ESCRITURA]);

        //Se cierra la lectura en el pipe que el hijo le escribe al proceso padre
        close(matrizPipes[(cantidadProcesosCreados*2) - 1][LECTURA]);
        

    }//fin if pid == 0

    else{
        printf("Error al crear el proceso hijo\n");
    }



}//fin while cantidadProcesosCreados < cantidadProcesosHijos





//Se declara un archivo tipo file donde se manipulará el archivo de entrada
FILE* archivo;

//Se crea una matriz donde en cada fila iran guardados los valores del rango inferior y superior del disco para enviar
//las visibilidades leídas a su proceso hijo correspondiente.
//cabe aclarar que a todo rango superior se le restara una constante de 0.0001 llamada DECIMAL para no tener problemas con los intervalos
//Por ejemplo, si son 2 discos con un ancho de 200, la matriz tendría los siguientes valores.
//matrizRango = [[0,199.999], [200,399.999], [400, infinito]];
float matrizRango[cantidadDiscos][2];


//En caso de estar en el proceso padre
if(pid > 0){
    //se abre el archivo de entrada en modo lectura para extraer las visibilidades
    archivo = fopen(nombreArchivoEntrada,"r");

    //Se procede a rellenar la matriz de rangos
    i = 0;
    float valorCota = 0.0; //valor para ir rellenando la matriz de rango

    //mientras se rellena la matriz
    while(i < cantidadDiscos){

        

        //Se ponen los valores de las cotas para los intervalos en la matriz de rangos
        matrizRango[i][RANGO_INF] = valorCota;

        //se suma el ancho para ponerlo en el rango o cota superior del intervalo
        //restandole el decimal constante 0.0001

        valorCota = (valorCota + anchoDisco) - DECIMAL;

        //se pone el valor en el rango superior
        matrizRango[i][RANGO_SUP] = valorCota;

        //Se le vuelve a sumar el decimal restado al valor para ponerlo de cota o rango inferior en la siguiente posicion o "intervalo"
        valorCota = valorCota + DECIMAL;

        //En caso de encontrarme en la ultima posición, se cambia el valor del rango superior por INFINITO
        if(i == cantidadDiscos-1){
            matrizRango[i][RANGO_SUP] = INFINITO;
        }
        
        //BORRAR ESTOS PRINT
        printf("dentro del while de la matriz rango, i = %d, valorCota = %f, matrizRango[%d][RANGO_INF] = %f, matrizRango[%d][RANGO_SUP] = %f\n",i,valorCota,i,matrizRango[i][RANGO_INF],i,matrizRango[i][RANGO_SUP]);
        printf("LA SUMA DE 200 - 0.0000001 ES %f\n",200.0 - 0.000001);
        i = i+1;

    }//finn while
}//fin if proceso padre



















//arreglo de caracteres donde se leerá la linea del archivo de entrada junto con su copia para poder trabajar con ella
char cadenaLeida[LIMITE_CADENA];
char copiaCadenaLeida[LIMITE_CADENA];


//Se procederá a leer las visibilidades del archivo y luego de acuerdo a su distancia respecto del origen
//se verá a que proceso hijo corresponde enviar la visibilidad leída






//Si estoy en el proceso padre
if(pid > 0){

    int ciclos = 0;//BORRAR
    int procesoElegido;

    //mientras no se llegue al final del documento
    while(feof(archivo) == 0 && (ciclos < 10)){


        //se lee la linea completa con un limite de 300 y se transforma a cadena de caracteres
        fgets(cadenaLeida,LIMITE_CADENA,archivo);

        //Para manipular la cadena leída, se pretende realizar split con la funcion strtok
        //pero esta funcion modifica el arreglo, por lo que para evitar problemas se hará una copia del arreglo

        //se procede a copiar la cadena leida
        i = 0;

        //mientras queden elementos por copiar
        while(i < LIMITE_CADENA){

            copiaCadenaLeida[i] = cadenaLeida[i];
            i = i+1;

        }//fin while donde se copia la cadena leida

        //Se calcula la distancia respecto del centro de la visibilidad observada 
        float distancia = calcularDistancia(copiaCadenaLeida,LIMITE_CADENA);

        //printf("la distancia es %f\n", distancia);//BORRAR
        

        //Una vez calculada la distancia
        //se procede a revisar a que proceso(disco) se debe enviar la visibilidad analizada

        //se revisa el valor de acuerdo a la matriz de rangos

        i=0;

        
        //mientras se recorre la matriz
        while(i < cantidadDiscos){

            //si la distancia es menor o igual que la cota superior
            if(distancia <= matrizRango[i][RANGO_SUP]){

                //se guarda el numero del proceso elegido para mandarle la cadena de caracteres de la visibilidad observada
                procesoElegido = i+1;
                //se detiene el while ya que se encontró la respuesta
                break;
            }//fin if

            i = i+1;
        }//fin while i < cantidadDiscos

        printf("\n\nLa distancia de la visibilidad observada es %f y se debe enviar al proceso hijo %d\n\n\n",distancia,procesoElegido);

        //Se envia a los procesos hijos el numero del proceso al cual se le enviará la cadena
        //Esto con el objetivo de que solo el proceso al que se le fue enviado la visibilidad la lea y no todos los procesos.
        //Para lograr esto, el numero del proceso elegido será enviado a todos los pipes para ser leído por su proceso hijo respectivo
        int i = 1;
        //mientras queden pipes por enviar
        while(i<=cantidadPipes){

            //se envia a los procesos hijos el numero del proceso que debe leer la visibilidad
            write(matrizPipes[(i * 2)- 2][ESCRITURA], &procesoElegido, sizeof(procesoElegido));
            i = i+1;


        }//fin while

        //write(matrizPipes[(procesoElegido * 2)- 2][ESCRITURA], &procesoElegido, sizeof(procesoElegido));
        printf("El procesoElegido es %d y este numero ya fue enviado a los procesos hijos\n", procesoElegido);
        sleep(0.1);



        //Se envia la visibilidad observada al proceso hijo correspondiente
        write(matrizPipes[(procesoElegido * 2)- 2][ESCRITURA], cadenaLeida, sizeof(cadenaLeida));
        printf("Mensaje enviado al proceso hijo %d\n",procesoElegido);//BORRAR
        sleep(0.2);

        
        
        


        //break;//BORRAR DESPUES ESTE BREAK
        ciclos=ciclos+1;//////////////////////////BORRAR

    }//fin while feof(archivo) == 0)

}//fin if proceso padre












/////////////////proceso hijo
if(pid == 0){

    int i =0;//borrar

    //se guarda el valor del proceso escogido guardado en la variable cantidadProcesosCreados cuando fue creado el proceso hijo
    int numeroProceso = cantidadProcesosCreados;

    //variable donde se guardará el numero del proceso al cual fue enviado la visibilidad
    int procesoElegido;

    //buffer para guardar la cadena(visibilidad) recibida
    char visibilidadRecibida[LIMITE_CADENA];

    //variable para guardar la cantidad total de visibilidades obtenidas por el proceso
    int cantidadVisibilidades = 0;


    while(i<10){ ////////AQUI DEBERIA CAMBIAR por un while true noma
        //Se lee el entero enviado por el proceso padre
        read(matrizPipes[(numeroProceso * 2)- 2][LECTURA], &procesoElegido, sizeof(procesoElegido));
        printf("Soy el hijo %d y recibi el entero de mi padre el cual es: %d\n",numeroProceso,procesoElegido);
        sleep(0.2);

        //Si la visibilidad fue enviada a ese proceso hijo
        if(numeroProceso == procesoElegido){

            //se lee la cadena enviada por el proceso padre
            read(matrizPipes[(numeroProceso * 2) - 2][LECTURA], visibilidadRecibida, sizeof(visibilidadRecibida));

            //se aumenta el contador de las visibilidades vistas
            cantidadVisibilidades = cantidadVisibilidades + 1;

            printf("Estoy en el proceso hijo %d y recibi la cadena de mi padre:\n%sKKK\n",numeroProceso,visibilidadRecibida);

            //Si lo leído es un "FIN", se deja de leer y se sale del ciclo
            if(visibilidadRecibida == "FIN"){
                break;

            }//fin if

        }//fin if numeroProceso == procesoElegido

            else{printf("soy el proceso hijo %d y no me toca leer la cadena a mi\n",numeroProceso);}//borrar

        
        i=i+1;////BORRAR (en volá)(si borrar)
    //printf("Estoy en el proceso hijo %d y recibi la cadena de mi padre:\n%sKKK\nAunque en realidad esta cadena fue enviada al proceso %d\n",numeroProceso,visibilidadRecibida,procesoElegido);//BORRAR
    sleep(0.2); ///borrar(no se aun, puede que no)/////////////////////////////////////////////

    }//fin while

    //HAY QUE VER COMO ALMACENAR LAS CADENAS RECIBIDAS
    //PERO PRIMERO SE VERA EL TEMA CON EL EXEC
    ///////////////////////////

    printf("visibilidades total vistas por el proceso hijo %d son %d\n", numeroProceso, cantidadVisibilidades);//borrar

    //Se procede a calcular las propiedas del disco con las visibilidades obtenidas.

  
    //Para esto, se sobreescribe codigo con un funcion parte de la familia de exec
    execl("./vis","./vis",(char*)NULL);
    printf("Si esto se ve en el proceso hijo %d hay algo malo\n",numeroProceso);

}//fin if proceso hijo









    //printf("Yo como proceso padre sigo vivo porsiaca\n");
    
    //char str1[300] = "hola";
    //char str2[300] = "como estais";
    //strcat(str1,str2);
    //printf("El resultado de la concatenación de %s con %s es: %s y el largo de str1 es %d\n",str1,str2,str1,sizeof(str1));

//En caso de estar en el proceso padre
if(pid > 0){

    //se cierra el archivo de entrada
    fclose(archivo);
}































    //float cordenada;
    //float cordenada2;
    //char* cadena;
    //char cadenaLeida[300];

    //printf("JJJJJJJJJ\n");


    //leerArchivo(nombreArchivoEntrada);


    ////////////////////////
    //Funcion que lee el archivo con la información de las jaulas
	//Entrada: nombre del archivo, puntero a la cantidad de jaulas
	//Salida: lista de todas las jaulas con su informacion correspondiente

   	//FILE* archivo = fopen(nombreArchivoEntrada,"r");
    
    //fscanf(archivo,"%f",&cordenada);
    //rewind(archivo);

    //fgets(cadenaLeida,300,archivo);

    //printf("lo leido es: %f\n",cordenada);
    //fscanf(archivo,"%f",&cordenada2);
    //printf("lo leido ess: %f\n",cordenada2);
   	//fgets(cadena2,100,archivo);
    //fclose(archivo);
   	//printf("la cadena rescatada es:%s\n",cadenaLeida);
   	//leo la cantidad de jaulas y lo almaceno en la variable cantidadJaulas
   	//fscanf(archivo,"%f",&cordenada);
   	//printf("lo leido es: %f\n",cordenada);

   	//fscanf(archivo,"%f",&cordenada2);
   	//printf("lo leido ess: %f\n",cordenada2);

   	//se le split a la cadena con la coma
   	//char* cadenaSplit = strtok(cadena,",");

   	//printf("Lo que hay en cadena es:%sYYYYY\n");


























    printf("soy el padre y voy a retornar\n");
    wait(NULL);
	return(0);
}//fin main