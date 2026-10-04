#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MESSAGE_SIZE 254

int main(int argc, char **argv){

    struct sockaddr_in enderecoServidor;
    
    int soqueteDeEnvio;
    
     char text[MESSAGE_SIZE];

     //criado soquete
    soqueteDeEnvio = socket(AF_INET,SOCK_STREAM,0);

    //zera os bytes
    bzero((char*)&enderecoServidor,sizeof(enderecoServidor));

    //configura endereço do host de destino
    enderecoServidor.sin_family = AF_INET;
    enderecoServidor.sin_port = htons(atoi(argv[2]));
    enderecoServidor.sin_addr.s_addr = inet_addr(argv[1]);

    //conecta no servidor
    connect(soqueteDeEnvio,(struct sockaddr*)&enderecoServidor,sizeof(enderecoServidor));

    while(1){

        recv(soqueteDeEnvio,text,MESSAGE_SIZE,0);
        printf("TEMPO NO SERVIDOR: %s",text);

    }



    return 0; 
}