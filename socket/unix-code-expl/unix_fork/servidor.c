#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CONEXOES 5
#define MENSAGEM 60
#define N 100

void  envio (int soquete){
	char string[60];
	int i;

	for(i=0;i<N;i++){

		recv (soquete, string, MENSAGEM*sizeof(char), 0);
 
        	printf("%s\n",string);
	        fflush(stdout);
   
        	strcpy (string, "MENSAGEM ENVIADA PELO SERVIDOR");
  
	 	send (soquete, string, (strlen(string)+1)*sizeof(char), 0);
		sleep(1);

	}

	close(soquete);
	

}

void main(int argc, char **argv){

	struct sockaddr_in endereco_servidor;
	struct sockaddr_in endereco_cliente;
	int soquete_servidor;
	int soquete_cliente;
	int tamanho;
	int pid;
	char string[MENSAGEM];
	int i=0;

	soquete_servidor = socket (AF_INET,SOCK_STREAM,0);

	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_port = htons(atoi(argv[1]));
	endereco_servidor.sin_addr.s_addr = INADDR_ANY;

	bind (soquete_servidor, (struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor));
 
	listen (soquete_servidor,CONEXOES);

	while (1){
		
		tamanho = sizeof(endereco_cliente);

		soquete_cliente = accept (soquete_servidor, (struct sockaddr *)&endereco_cliente, &tamanho);
		
		pid = fork();
		
		if (pid > 0)	
			close(soquete_cliente);
		else {
			envio(soquete_cliente);
			close(soquete_cliente);
		}	
	}


	close(soquete_servidor);

}

