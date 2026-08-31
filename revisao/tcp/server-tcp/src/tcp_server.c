//
// Created by jmartins on 24/08/2026.
//

#include "tcp_server.h"
#define TAM_MENSAGEM 256
#define CONEXOES 2
char PORTA[32];

struct  sockaddr_in endereco_local;
int soqueteDeEscuta, soqueteCliente;


int pid;

void verifica_parametros_srv(int qtdArgs, char **args)
{
    if (qtdArgs != 2)
    {
        printf("\nfalta porta de listen do servidor:");
        printf("\n./tcp_server <porta>");
        exit(0);
    }
    else
    {
        printf("\nporta TCP aberta no servidor na porta %s\n", args[1]);
        strcpy(PORTA,args[1]);
    }
}

void configurar_endereco_servidor_srv()
{


    bzero((char *)&endereco_local,sizeof(endereco_local));
    endereco_local.sin_family = AF_INET;
    endereco_local.sin_addr.s_addr = INADDR_ANY;
    endereco_local.sin_port = htons(atoi(PORTA));
}

void configura_socket_srv()
{
    soqueteDeEscuta = socket (AF_INET,SOCK_STREAM,0);
    bind(soqueteDeEscuta,(struct sockaddr *)&endereco_local,sizeof(endereco_local));
    listen(soqueteDeEscuta,CONEXOES);

}

void leitura_msg_srv()
{
    char msg[TAM_MENSAGEM];
    int total = 0;

    while (1)
    {
        int bytes = recv(
            soqueteCliente,
            msg + total,
            TAM_MENSAGEM - total,
            0
        );

        if (bytes == -1)
        {
            printf("\nNao foi possivel receber a mensagem do cliente\n");
            return;
        }

        if (bytes == 0)
        {
            printf("\nCliente encerrou a conexao\n");
            return;
        }

        total += bytes;

        /*
         * Procura '\0' somente dentro dos bytes já recebidos.
         *
         * memchr(
         *     onde_procurar,
         *     byte_procurado,
         *     quantos_bytes_verificar
         * );
         */
        if (memchr(msg, '\0', total) != NULL)
        {
            break;
        }

        if (total == TAM_MENSAGEM)
        {
            printf("\nMensagem excedeu o tamanho do buffer\n");
            return;
        }
    }

    printf("\nMensagem recebida: %s\n", msg);
}

void recebe_mensagem_srv()
{
    char msg[TAM_MENSAGEM];

    while (1)
    {
        soqueteCliente = accept(soqueteDeEscuta,NULL,NULL);

        pid = fork();

        if (pid > 0 )
        {
            close(soqueteCliente);
        }
        else
        {


            leitura_msg_srv();

            strcpy(msg,"Essa é a resposta do servidor");
            send(soqueteCliente,msg,strlen(msg)+1,0);
            close(soqueteDeEscuta);
            close(soqueteCliente);

            exit(0);
        }

    }

}