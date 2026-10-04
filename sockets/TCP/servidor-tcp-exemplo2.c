#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

#define CONEXOES 5


void clock_to_socket(int soqueteDeEnvio){

    time_t tempo;
    char *text; 

    while(1){
        tempo = time(NULL);
        text = ctime(&tempo);
        
        send(soqueteDeEnvio,text,strlen(text)+1,0);
        sleep(2);
    }

}

int main(int argc, char **argv){

    struct sockaddr_in enderecoServidor,enderecoCliente;
    socklen_t tamanhoEnderecoCliente = sizeof(enderecoCliente);

    int soqueteServidor, soqueteCliente, pid;

    if(argc != 2){
        printf("\nDigite a porta que deseja subir o servidor: ./servidor-tcp-exemplo2 <PORTA>\n");
        exit(1);
    }

    //cria soquete
    soqueteServidor  = socket(AF_INET,SOCK_STREAM,0);

    //seleciona uma porta
    
    bzero((char*)&enderecoServidor,sizeof(enderecoServidor)); //ZERA TUDO

    enderecoServidor.sin_family = AF_INET; //ipv4
    enderecoServidor.sin_port = htons(atoi(argv[1])); //porta
    enderecoServidor.sin_addr.s_addr= INADDR_ANY; //aceita conexao de qualquer origem

    //associe o soqueteServidor ao endereço configurado em enderecoServidor
    bind(soqueteServidor,(struct sockaddr*)&enderecoServidor,sizeof(enderecoServidor));


    //aceita no maximo 5 conexoes simultaneas
    listen(soqueteServidor,CONEXOES);

    printf("\nServidor na porta %s aceitando conexoes\n",argv[1]);
   

    while(1){
        
        soqueteCliente = accept(soqueteServidor,(struct sockaddr*)&enderecoCliente,&tamanhoEnderecoCliente);
        printf("\nAceitou um cliente: %s:%d\n",inet_ntoa(enderecoCliente.sin_addr), ntohs(enderecoCliente.sin_port));

        pid = fork();

        if(pid == 0 ) //processo filho trata de responder as conexoes
        {
            close(soqueteServidor); //filho nao precisa aceitar mais conexoes
            
            clock_to_socket(soqueteCliente);
        }

        close(soqueteCliente);
    }

    return 0;
}