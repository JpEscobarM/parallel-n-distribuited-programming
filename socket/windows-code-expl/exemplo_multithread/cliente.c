#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50

int main(){

    char msg[N];
    int sock;
    struct sockaddr_in addr;
    int len_addr;
    struct hostent *host;

    WSADATA ws;
    WSAStartup(0x0101,&ws);

    sock = socket (AF_INET,SOCK_STREAM,0);
  
    host = gethostbyname("localhost");

    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    memcpy(&addr.sin_addr, host->h_addr,host->h_length); 

    printf("conectando...\n");
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("conectou...\n\n");


    printf("Digite a mensagem: ");
    fgets(msg,N,stdin);

    printf("enviando mensagem...\n");
    send(sock, msg, strlen(msg)+1, 0);
    printf("mensagem enviada...\n\n");
    
    printf("recebendo mensagem...\n");
    recv(sock, msg, N, 0);
    printf("mensagem recebida...\n\n");
    
    printf("Recebi: %s\n", msg);

    printf("fechando o socket...\n"); 
    closesocket(sock);
    printf("socket fechado...\n\n");    
    
    WSACleanup();
    
    system("pause");
    return(0);

}

