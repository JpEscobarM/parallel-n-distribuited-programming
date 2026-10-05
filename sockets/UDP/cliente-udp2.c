#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define MENSAGEM 124

int main(int argc, char **argv)
{

    if (argc != 3)
    {
        printf("%s <ip> <porta>\n", argv[0]);
        exit(0);
    }

    struct sockaddr_in enderecoServidor;

    int soqueteDeConexao;

    char texto[MENSAGEM];

    soqueteDeConexao = socket(AF_INET, SOCK_DGRAM, 0);

    bzero((char *)&enderecoServidor, sizeof(enderecoServidor));

    enderecoServidor.sin_family = AF_INET;
    enderecoServidor.sin_port = htons(atoi(argv[2]));
    enderecoServidor.sin_addr.s_addr = inet_addr(argv[1]);

    printf("\nDigite uma mensagem para o servidor:\n");

    scanf("%123[^\n]", texto);

    sendto(soqueteDeConexao, texto, strlen(texto) + 1, 0, (struct sockaddr *)&enderecoServidor, sizeof(enderecoServidor));

    recvfrom(soqueteDeConexao, texto, MENSAGEM, 0, NULL, NULL);

    printf("\n%s\n", texto);

    close(soqueteDeConexao);

    return 0;
}