#include <stdio.h>

#include "tcp_client.h"

int main(int argc, char **argv)
{

    char msg[256];

    printf("\nIniciando verificação de parametros");
    verifica_parametros_cl(argc, argv);
    printf("\nVerificou");

    printf("\nConfigurando servidor remoto..");
    configurar_endereco_servidor_cl();


    printf("\nConfigurando socket do cliente...");
    configura_socket_cl();


    printf("\nConectando...");
     conecta_cl();


    char texto[TAM_MENSAGEM] = "MENSAGEM DE TESTE";

    printf("\nEnviando mensagem de teste: %s",texto);
    envia_texto_cl(texto);

    printf("\nRecebendo retorno do sevidor: ");
    recebe_retorno_cl();

    return 0;
}
