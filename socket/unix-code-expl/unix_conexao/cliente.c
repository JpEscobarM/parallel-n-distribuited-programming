#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define MENSAGEM 60

void main(int argc, char **argv){

	struct sockaddr_in endereco_servidor;
	int soquete;
	char string[MENSAGEM];
	int result;
	
	soquete = socket (AF_INET,SOCK_STREAM,0);

	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_port = htons(atoi(argv[2]));
	endereco_servidor.sin_addr.s_addr = inet_addr(argv[1]);

	connect (soquete, (struct sockaddr *) &endereco_servidor, sizeof(endereco_servidor));

	strcpy (string, "MENSAGEM ENVIADA PELO CLIENTE");        

	send (soquete, string, (strlen(string)+1)*sizeof(char), 0);   

	recv (soquete, string, MENSAGEM*sizeof(char), 0);
 
        printf("%s\n",string);
        fflush(stdout);

	close(soquete);


}

