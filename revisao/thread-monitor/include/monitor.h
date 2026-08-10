#ifndef THREAD_MONITOR_MONITOR_H
#define THREAD_MONITOR_MONITOR_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 5


extern  void *codigo_tarefa_compradora(void *arg);

extern  void *codigo_tarefa_vendedora(void *arg);


extern void cria_threads_compradores();

extern  void cria_threads_vendedores();

extern void finaliza();




#endif //THREAD_MONITOR_MONITOR_H