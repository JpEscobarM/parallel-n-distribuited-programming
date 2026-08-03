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
    struct sockaddr_in endereco_multicast, endereco_emissor;
    struct ip_mreq mreq;
    char mensagem[N];

    int tamanho;
    
    soquete = socket(AF_INET, SOCK_DGRAM, 0);
    
    int reuso = 1;

    setsockopt(soquete, SOL_SOCKET, SO_REUSEADDR, (char *)&reuso, sizeof(reuso));
    
    memset(&endereco_multicast, 0, sizeof(endereco_multicast));
    endereco_multicast.sin_family = AF_INET;
    endereco_multicast.sin_addr.s_addr = htonl(INADDR_ANY);
    endereco_multicast.sin_port = htons(PORTA);

    mreq.imr_multiaddr.s_addr = inet_addr(GRUPO);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(soquete, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)); 
   
    bind(soquete, (struct sockaddr *)&endereco_multicast, sizeof(endereco_multicast));

    
    while (1) {
            tamanho = sizeof(endereco_emissor);    
            recvfrom(soquete, mensagem, 50, 0, (struct sockaddr *)&endereco_emissor, &tamanho);
            printf("Recebido: %s\n", mensagem);
    }
    close(soquete);
}


