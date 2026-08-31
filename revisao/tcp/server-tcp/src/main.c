#include <stdio.h>
#include "tcp_server.h"

int main(int argc,char **argv)
{

    verifica_parametros_srv(argc, argv);

    configurar_endereco_servidor_srv();

    configura_socket_srv();

    recebe_mensagem_srv();


    return 0;
}