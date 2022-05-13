#include <pthread.h>
#include <stdio.h>

void *helloworld(void *param)
{
  printf("Hello World, soy hebra %ld\n", (long) param);
  pthread_exit((void *) 100);
}

int main(int argc, char *argv[])
{
  pthread_t tid;       // Identidicador de la hebra
  pthread_attr_t attr; // atributos de la hebra
  long i;
  void *status;

  pthread_attr_init(&attr);
  for (i=1;i<=5; i++) {
    pthread_create(&tid, &attr, helloworld, (void *) i);
    pthread_join(tid, &status);
    printf("Retorna hebra %ld, con valor de retorno %ld\n", i, (long) status);
  }
  
  //pthread_exit(0);
}

