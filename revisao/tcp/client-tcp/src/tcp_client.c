//
// Created by jmartins on 24/08/2026.
//

#include "tcp_client.h"


struct  sockaddr_in endereco_local;
int soqueteDeConexao;
char IP[128];
char PORTA[32];


void verifica_parametros_cl(int qtdArgs, char **args)
{
    if (qtdArgs != 3)
    {
        printf("\nfalta endereço ip ou porta do servidor:");
        printf("\n./tcp_client <ip> <porta>");
        exit(0);
    }
    else
    {
        printf("\n iniciando conexao no servidor %s na porta %s\n", args[1],args[2]);
        strcpy(IP,args[1]);
        strcpy(PORTA,args[2]);
    }
}

void configurar_endereco_servidor_cl()
{
    bzero((char *)&endereco_local,sizeof(endereco_local));
    endereco_local.sin_family = AF_INET;
    endereco_local.sin_addr.s_addr = inet_addr(IP);
    endereco_local.sin_port = htons(atoi(PORTA));
}

void configura_socket_cl()
{
    soqueteDeConexao = socket(AF_INET,SOCK_STREAM,0);
}

int conecta_cl()
{
    int ret;
    ret = connect(soqueteDeConexao,(struct sockaddr *)&endereco_local, sizeof(endereco_local));

    return ret;
}

void envia_texto_cl(char *texto)
{
    send(soqueteDeConexao,texto,strlen(texto)+1,0);
}

void exibe_texto_aos_poucos(char *texto, int tamanho)
{
    for (int i =0; i < tamanho ; i++)
    {
        printf("%c", texto[i]);
    }
}

void recebe_retorno_cl()
{
    char msg[TAM_MENSAGEM];

    int total = 0;

    while (1)
    {

        int bytes = recv(
            soqueteDeConexao,
            msg + total, //aritimeticade ponteiros msg+total
            TAM_MENSAGEM-total, //parametro que indica quantos bytes o buffer pode ler no total PADRAO:TAM_MENSAGEM - total, troque por um inteiro pequeno para receber aos poucos ex: 5
            0
        );

        if (bytes == -1)
        {
            printf("\nNao foi possivel receber a mensagem do servidor\n");
            return;
        }

        if (bytes == 0)
        {
            printf("\nServidor encerrou a conexao\n");
            return;
        }

        total += bytes;

        //mude o o total de bytes recebidos na funcao recv() e descomente essa funcao abaixo para ver a mensagem chegar aos poucos
        //printf("\n");
        //exibe_texto_aos_poucos(msg,total);


        /*
         Basicamente procura o caracter '\0' dentro dos "total" bytes ja enviados, se achar, terminou a string.
         memchr(onde_procurar,byte_procurado, quantos_bytes_verificar );
         */
        if (memchr(msg, '\0', total) != NULL) break;

        // Buffer acabou e ainda não encontramos o '\0'.
        if (total == TAM_MENSAGEM)
        {
            printf("\nMensagem excedeu o tamanho do buffer\n");
            return;
        }
    }

    printf("\nRetorno: %s\n", msg);

}