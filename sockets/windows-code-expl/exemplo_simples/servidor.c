#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------*/
#define N 50
/*----------------------------------------------------------------------------*/

int main(){

    int sock_srv, sock_cli;
    struct sockaddr_in addr_serv;
    int len;
    char echo[N]="Echo: ", msg[N];

    WSADATA ws;
    WSAStartup(0x0101,&ws);

    printf("criando o socket...\n");
    sock_srv = socket (AF_INET,SOCK_STREAM,0);
    printf("socket criado...\n\n");
    

    memset(&addr_serv,0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(5000);
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY); 

    printf("atribuindo uma porta...\n");
    bind(sock_srv,(struct sockaddr *)&addr_serv,sizeof(addr_serv));
    printf("porta atribuida...\n\n");

    printf("preparando para aceitar conexoes...\n");
    listen(sock_srv,3);
    printf("pronto para esperar conexoes...\n\n");
    
    
    len = sizeof(addr_serv); 
    printf("esperando conexoes...\n");
    sock_cli = accept(sock_srv,(struct sockaddr *)&addr_serv, &len);
    printf("conexao aceita...\n\n");

    printf("esperando mensagem...\n");    
    recv(sock_cli, msg, N, 0);
    printf("mensagem recebida...\n\n");
    
    printf("Recebi: %s\n",msg);
    strcat(echo,msg);
    
    printf("envidando mensagem...\n");    
    send(sock_cli, echo, strlen(echo)+1, 0);
    printf("mensagem enviada...\n");

    printf("fechando os sockets...\n"); 
    closesocket(sock_cli);
    closesocket(sock_srv);
    printf("sockets fechados...\n\n");    
    
    WSACleanup();
      
    system("pause");
}

/*----------------------------------------------------------------------------*/
