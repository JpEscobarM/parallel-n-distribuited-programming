#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv){

	struct sockaddr_in endereco_cliente, endereco_servidor;
	int soquete;
	int tamanho;
	char msg[50];

	if ( argc != 2){
		printf("%s <porta>\n", argv[0]);
		exit(0);
	}

	soquete = socket(AF_INET, SOCK_DGRAM, 0);

	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = INADDR_ANY;
	endereco_servidor.sin_port = htons(atoi(argv[1]));

	bind(soquete,(struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor)); 

	tamanho = sizeof(tamanho);

	recvfrom(soquete, msg, 50, 0, (struct sockaddr *)&endereco_cliente, &tamanho);

	strcpy(msg,"Alo mundo");
	sendto(soquete, msg, strlen(msg)+1,0,(struct sockaddr *)&endereco_cliente, sizeof(endereco_cliente));

	close(soquete);
}

/*---------------------------------------------------------------------------------------------------*/
