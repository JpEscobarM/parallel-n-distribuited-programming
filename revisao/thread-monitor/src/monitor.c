//
// Created by jmartins on 10/08/2026.
//

#include "monitor.h"
#include "leilao.h"
static pthread_t threds_compradores[NUM_THREADS];
static pthread_t threads_vendedores[NUM_THREADS];


//REALIZA 10 COMPRAS, UMA A CADA SEGUNDO
void *codigo_tarefa_compradora( void *args)
{
    for (int i =0; i < 10; i++)
    {
        double compra = 1 + rand() % 1000; //preços de 1 a 1000
        double ofertaCompra = leilao_oferta_compra(compra);
        printf("Oferta de COMPRA %lf resultou em : %lf \n", compra, ofertaCompra);
        sleep(1);
    }

}

void *codigo_tarefa_vendedora(void *args)
{
    for (int i =0; i < 10; i++)
    {
        double venda = 1 + rand() % 1000;
        double ofertaVenda = leilao_oferta_venda(venda);
        printf("Oferta de VENDA %lf resultou em: %lf \n",venda, ofertaVenda);
        sleep(1);
    }
}



void cria_threads_compradores()
{
    for (int i =0; i < NUM_THREADS; i++)
    {
        pthread_create(&threds_compradores[i],NULL,codigo_tarefa_compradora,NULL);
    }
}

void cria_threads_vendedores()
{
    for (int i =0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads_vendedores[i],NULL,codigo_tarefa_vendedora,NULL);
    }

}

void finaliza()
{
    for (int i =0; i < NUM_THREADS; i++)
    {
        pthread_join(threads_vendedores[i],NULL);
        pthread_join(threds_compradores[i],NULL);
    }
}


