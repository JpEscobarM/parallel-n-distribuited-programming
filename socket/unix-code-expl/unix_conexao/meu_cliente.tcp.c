#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


/*---------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv){


    struct sockaddr_in endereco_servidor;
    int soquete;
    if ( argc != 3 ){
        printf("%s <ip> <porta>\n", argv[0]);
        exit(0);
    }


    soquete = socket(AF_INET,SOCK_STREAM,0);  //criando socket, AF_INET == ipv4



    //PASSANDO O ENDERECO DO SERVIDOR
    bzero((char *)&endereco_servidor,sizeof(endereco_servidor));
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_addr.s_addr = inet_addr(argv[1]);
    endereco_servidor.sin_port = htons(atoi(argv[2]));


    connect(soquete,(struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor));
    //ENVIANDO TEXTO PARA O SERVIDOR

    char msg[100]= "Teste";


    send(soquete,msg,strlen(msg)+1,0);
    recv(soquete,msg,100,0);


    printf("Retorno %s", msg);


    //FECHA O SOCKET
    close(soquete);


}
/*---------------------------------------------------------------------------------------------------*/

