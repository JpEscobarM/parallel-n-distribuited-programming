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
	struct sockaddr_in endereco_msg;
	int soquete, tamanho;
	char msg[100]="alo";

	if ( argc != 3 ){
		printf("%s <ip> <porta>\n", argv[0]);
		exit(0);
	}


	//SOCKET ORIENTADO A CONEXAO É SOCKSTREAM
	//AQUI SERA ORIENTADO A DATAGRAMA
	soquete = socket(AF_INET,SOCK_DGRAM,0);

	//ESTRUTURA PADRAO 
	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = inet_addr(argv[1]);
	endereco_servidor.sin_port = htons(atoi(argv[2]));

	//ENVIANDO MENSAGEM, SEMPRE IDENTIFICAR PRA QUEM VAI A MENSAGEM
	sendto(soquete,msg,strlen(msg)+1,0, ( struct sockaddr *)&endereco_servidor,sizeof(endereco_servidor));


	//POR PADRAO USARIA  recvfrom(soquete,msg,100,0,STRUCT DE ENDEREÇO,TAMANHO);
	//como nao vamos precisar armazenar usamos null
	recvfrom(soquete,msg,100,0,NULL,NULL);

	printf("\nRecebi: %s\n",msg);

	close(soquete);
}
/*---------------------------------------------------------------------------------------------------*/



