#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

/*---------------------------------------------------------------------------------------------------*/
#define CONEXOES 10
/*---------------------------------------------------------------------------------------------------*/

//COMPILAR UTILIZANDO ./server_tcp "PORTA_DE_LISTEN"

int main(int argc, char **argv){

	struct sockaddr_in endereco_servidor;
	int soquete_servidor, soquete_cliente;
	int tamanho;

	if ( argc != 2){
		printf("%s <porta>\n", argv[0]);
		exit(0);
	}

	//CRIANDO O SOCKET DO SERVIDOR
	soquete_servidor = socket (AF_INET,SOCK_STREAM,0);

	bzero((char *)&endereco_servidor,sizeof(endereco_servidor));       
	endereco_servidor.sin_family = AF_INET;
	endereco_servidor.sin_addr.s_addr = INADDR_ANY; //INADOR_ANY, QUALQUER MAQUINA PODE CONECTAR
	endereco_servidor.sin_port = htons(atoi(argv[1]));

	bind(soquete_servidor,(struct sockaddr*) &endereco_servidor, sizeof(endereco_servidor));

	//CRIA FILA DE CONEXOES
	listen(soquete_servidor, CONEXOES);

	char msg[100];
	int id; //PID DO FORK
	//PRECISA DO LOOP PARA CONTINUAR OUVINDO
	while(1){


	//NULL = SOCK_ADDR , PODE SER USADO PARA PEGAR O IP 
	soquete_cliente = accept(soquete_servidor,NULL,NULL);

	//FAZ O FORK DEPOIS QUE UM CLIENTE CONECTA
	id = fork();

	if(id  > 0) //ID > 0 == PAI
	{
		close(soquete_cliente); //FECHA A CONEXAO ATUAL DO CLIENTE
	}
	else //PROCESSO FILHO ATENDE A REQUISICAO
	{
	
	//RECEBE A PARTIR DO SOQUETE DO CLIENTE
	recv(soquete_cliente,msg,sizeof(msg),0);

	printf("RECEBI %s\n", msg);

	//PREPARA RESPOSTA
    strcpy(msg,"MAQUINA DO JOAO");

	//ENVIA A MENSAGEM DE VOLTA
	send(soquete_cliente,msg,strlen(msg)+1,0);


	close(soquete_cliente);

	}
	
	}


	close(soquete_servidor);

}

/*---------------------------------------------------------------------------------------------------*/
