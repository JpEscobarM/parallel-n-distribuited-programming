//
// Created by jmartins on 10/08/2026.
//

#include "leilao.h"


static pthread_mutex_t lock  = PTHREAD_MUTEX_INITIALIZER;

Proposta *melhor_venda =  NULL;
Proposta *melhor_compra = NULL;


void leilao_init()
{
}

void analisaCompra(Proposta* proposta)
{
    // Verifica se passou a ser a melhor
    if( melhor_compra == NULL ) {
        printf("Assume oferta compra %lf como melhor\n", proposta->valor);
        melhor_compra = proposta;		// Nova melhor compra
        proposta->resultado = 0;		// Está em espera
    } else if( melhor_compra != NULL  &&  proposta->valor > melhor_compra->valor ) {
        printf("Assume oferta compra %lf como melhor no lugar de %lf\n", proposta->valor, melhor_compra->valor);
        melhor_compra->resultado = -1;		// Oferta foi descartada
        pthread_cond_signal( &melhor_compra->altera_status);
        melhor_compra = proposta;		// Nova melhor compra
        proposta->resultado = 0;		// Está em espera
    } else {
        printf("Descarta oferta compra %lf pois melhor eh %lf\n", proposta->valor, melhor_compra->valor);
        proposta->resultado = -1;
    }

    // Verifica se deu negócio
    if( proposta->resultado == 0  &&
        melhor_venda != NULL  &&  proposta->valor >= melhor_venda->valor ) {
        double negocio = ( proposta->valor + melhor_venda->valor ) / 2;
        printf("Fechado negocio com compra %lf e venda %lf == %lf\n", proposta->valor, melhor_venda->valor, negocio);
        proposta->resultado = negocio;
        melhor_venda->resultado = negocio;
        pthread_cond_signal( &melhor_venda->altera_status);
        pthread_cond_signal( &melhor_compra->altera_status);
        melhor_venda = NULL;	// Oferta foi usada
        melhor_compra = NULL;	// Oferta foi usada
        }

}
void analisaVenda(Proposta *proposta)
{

    // Verifica se passou a ser a melhor
    if( melhor_venda == NULL ) {
        printf("Assume oferta venda %lf como melhor\n",proposta->valor);
        melhor_venda = proposta;		// Nova melhor compra
        proposta->resultado = 0;		// Está em espera
    } else if( melhor_venda != NULL  &&  proposta->valor < melhor_venda->valor ) {
        printf("Assume oferta venda %lf como melhor no lugar de %lf\n", proposta->valor, melhor_venda->valor);
        melhor_venda->resultado = -1;		// Oferta foi descartada
        pthread_cond_signal( &melhor_venda->altera_status);
        melhor_venda = proposta;		// Nova melhor compra
        proposta->resultado = 0;		// Está em espera
    } else {
        printf("\nDescarta oferta venda %lf pois melhor eh %lf\n", proposta->valor, melhor_venda->valor);
        proposta->resultado = -1;
    }

    // Verifica se deu negocio
    if( proposta->resultado == 0  &&
        melhor_compra != NULL  &&  proposta->valor <= melhor_compra->valor ) {
        double negocio = ( proposta->valor + melhor_compra->valor ) / 2;
        printf("Fechado negocio com compra %lf e venda %lf == %lf\n", melhor_compra->valor, proposta->valor, negocio);
        proposta->resultado = negocio;
        melhor_compra->resultado = negocio;
        pthread_cond_signal( &melhor_compra->altera_status);
        pthread_cond_signal( &melhor_venda->altera_status);
        melhor_venda = NULL;	// Oferta foi usada
        melhor_compra = NULL;	// Oferta foi usada
        }
}

double leilao_oferta_compra(double preco)
{
    Proposta propostaCompra;

    pthread_mutex_lock(&lock);
    printf("\n<MONITOR_LEILAO>leilao_oferta_compra: %lf", preco);
    propostaCompra.valor = preco;
    propostaCompra.resultado = 0;
    pthread_cond_init(&propostaCompra.altera_status,NULL);

    analisaCompra(&propostaCompra);

    while (propostaCompra.resultado == 0)
    {
        pthread_cond_wait(&propostaCompra.altera_status, &lock);
    }

    pthread_mutex_unlock(&lock);
    return propostaCompra.resultado;
}

double leilao_oferta_venda(double preco)
{
    Proposta propostaVenda;

    pthread_mutex_lock(&lock);
    printf("\n<MONITOR_LEILAO>leilao_oferta_venda: %lf", preco);

    propostaVenda.valor = preco;
    propostaVenda.resultado = 0;
    pthread_cond_init(&propostaVenda.altera_status,NULL);

    analisaVenda(&propostaVenda);
    while (propostaVenda.resultado == 0)
    {
        pthread_cond_wait(&propostaVenda.altera_status, &lock);
    }

    pthread_mutex_unlock(&lock);
    return propostaVenda.resultado;
}

double leilao_melhor_oferta_compra()
{
    double consulta;

    pthread_mutex_lock(&lock);
    consulta = melhor_compra == NULL ? -1 : melhor_compra->valor;
    pthread_mutex_unlock(&lock);

    return consulta;
}

double leilao_melhor_oferta_venda()
{
    double consulta;

    pthread_mutex_lock(&lock);
    consulta = melhor_venda == NULL ? -1 : melhor_venda->valor;
    pthread_mutex_unlock(&lock);

    return consulta;
}
