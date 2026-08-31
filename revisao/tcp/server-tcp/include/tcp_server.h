//
// Created by jmartins on 24/08/2026.
//

#ifndef TCP_CLIENT_TCP_SERVER_H
#define TCP_CLIENT_TCP_SERVER_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void verifica_parametros_srv(int qtdArgs, char **args);

void configurar_endereco_servidor_srv();

void configura_socket_srv();

void leitura_msg_srv();

void recebe_mensagem_srv();

#endif //TCP_CLIENT_TCP_SERVER_H