//
// Created by jmartins on 24/08/2026.
//

#ifndef TCP_TCP_CLIENT_H
#define TCP_TCP_CLIENT_H
#define TAM_MENSAGEM 256

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void verifica_parametros_cl(int qtdArgs, char **args);

void configurar_endereco_servidor_cl();

void configura_socket_cl();

int conecta_cl();

void envia_texto_cl(char *texto);

void exibe_texto_aos_poucos(char *texto, int tamanho);

void recebe_retorno_cl();


#endif //TCP_TCP_CLIENT_H