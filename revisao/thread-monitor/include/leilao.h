//
// Created by jmartins on 10/08/2026.
//

#ifndef THREAD_MONITOR_LEILAO_H
#define THREAD_MONITOR_LEILAO_H

#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include <stdio.h>

typedef struct
{
    double valor;
    double resultado;
    pthread_cond_t altera_status;

}Proposta;


extern void leilao_init();

extern double leilao_oferta_compra(double preco);

extern double leilao_oferta_venda(double preco);

extern double leilao_melhor_oferta_compra();

extern double leilao_melhor_oferta_venda();

extern void analisaCompra(Proposta *proposta);

extern void analisaVenda(Proposta *proposta);

#endif //THREAD_MONITOR_LEILAO_H