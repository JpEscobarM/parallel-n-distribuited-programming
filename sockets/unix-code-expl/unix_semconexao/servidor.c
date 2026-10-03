#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define CONEXOES 5
#define MENSAGEM 60

void main(int argc, char **argv){

	struct sockaddr_in endereco_servidor;
	struct sockaddr_in endereco_cliente;
	int soquete_servidor;
	int soquete_cliente;
	int tamanho;
	char string[MENSAGEM];

	soquete_servidor = socket (AF_INET,SOCK_DGRAM,0);

	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_port = htons(atoi(argv[1]));
	endereco_servidor.sin_addr.s_addr = INADDR_ANY;

	bind (soquete_servidor, (struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor));
 
	while (1){
		
		tamanho = sizeof(endereco_cliente);

		recvfrom (soquete_servidor, string, MENSAGEM*sizeof(char), 0, (struct sockaddr *)&endereco_cliente, &tamanho);

                printf("%s\n",string);
                fflush(stdout);

		strcpy (string, "MENSAGEM ENVIADA PELO SERVIDOR");

		sendto ( soquete_servidor, string, (strlen(string)+1)*sizeof(char), 0, (struct sockaddr *)&endereco_cliente, sizeof(endereco_cliente));

	
	}

	close(soquete_servidor);

}

