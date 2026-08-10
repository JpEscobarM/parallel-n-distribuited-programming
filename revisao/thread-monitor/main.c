#include <stdio.h>

#include "leilao.h"
#include "monitor.h"



int main(void)
{

    leilao_init();
    cria_threads_vendedores();
    cria_threads_compradores();



    sleep(15);
    finaliza();
    printf("\n");
    printf("Melhor oferta de compra agora: %lf\n", leilao_melhor_oferta_compra() );
    printf("Melhor oferta de venda agora: %lf\n", leilao_melhor_oferta_venda() );



    printf("Fim\n");
    return 0;
}
