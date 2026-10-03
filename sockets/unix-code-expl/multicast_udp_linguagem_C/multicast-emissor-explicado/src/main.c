#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define GRUPO "224.0.0.1"
#define PORTA 5000
#define N 50

int main() {
    int soquete;
    struct sockaddr_in endereco_multicast;

    char mensagem[N] = "Exemplo, multicast!";

    soquete = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&endereco_multicast, 0, sizeof(endereco_multicast));
    endereco_multicast.sin_family = AF_INET;
    endereco_multicast.sin_addr.s_addr = inet_addr(GRUPO);
    endereco_multicast.sin_port = htons(PORTA);

    sendto(soquete, mensagem, strlen(mensagem)+1 , 0, (struct sockaddr *)&endereco_multicast, sizeof(endereco_multicast));

    recvfrom(soquete,mensagem,N,0,NULL,NULL);

    printf("Resposta: %s\n", mensagem);

    close(soquete);

    return 0;
}


