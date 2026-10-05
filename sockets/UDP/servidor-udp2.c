#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MENSAGEM 124

int main(int argc, char **argv)
{       


    if ( argc != 2){
		printf("%s <porta>\n", argv[0]);
		exit(0);
	}



    struct sockaddr_in enderecoServidor, enderecoCliente;

    int soqueteServidor;
    int tamanho;

    char texto[MENSAGEM];

    soqueteServidor  = socket(AF_INET,SOCK_DGRAM,0);

    bzero((char*)&enderecoServidor, sizeof(enderecoServidor));

    enderecoServidor.sin_family = AF_INET;
    enderecoServidor.sin_port = htons(atoi(argv[1])); 
    enderecoServidor.sin_addr.s_addr = INADDR_ANY;

    bind(soqueteServidor, (struct sockaddr*) &enderecoServidor, sizeof(enderecoServidor));

    printf("\nServidor UDP rodando na porta %s\n",argv[1]);

    while(1){

        tamanho = sizeof(enderecoCliente);
        
        recvfrom(soqueteServidor,texto,sizeof(texto),0,(struct sockaddr*)&enderecoCliente,&tamanho);

        strcat(texto," - ECHO -");
        
        sendto(soqueteServidor,texto,strlen(texto)+1,0,(struct sockaddr *)&enderecoCliente,sizeof(enderecoCliente));


    }


    return 0;
}