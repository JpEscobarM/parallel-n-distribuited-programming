## Crie um programa que faz o controle de acesso a um conjunto de portas.

O prédio possui cerca de **100 portas**, identificadas por números de **3 dígitos**.

Cada porta possui uma lista de usuários autorizados, cada usuário é identificado por um código de 7 dígitos.

Crie um monitor 's12-a57-listaportas' que implementa uma lista de portas e,
para cada porta, uma lista de usuários autorizados. Use a estrutura de dados que
lhe for mais confortável. Precisa ser um monitor pois esta estrutura de dados
será acessada concorrentemente por várias threads.

Sugestão de rotinas de acesso :

Cadastra 'usuario' como autorizado a acessar 'porta'.
Os strings precisam ser copiados.
Caso 'usuario' já esteja autorizado para 'porta', nada muda.
Esta rotina será chamada eventualmente por threads do tipo escritor.
Retorna -1 caso o monitor não tenha sido inicializado ou parâmetros incorretos.

extern int listaportas_insere( char *porta, char *usuario);

Indaga se 'usuario' está autorizado a acessar 'porta'.
Retorna 1 para autorizado e 0 para não autorizado.
Retorna -1 caso o monitor não tenha sido inicializado ou parâmetros incorretos.
Esta rotina será chamada frequentemente por threads do tipo leitor.

extern int listaportas_consulta( char *porta, char *usuario);

Dado o elevado número de portas será utilizado um pool de threads para processar
as consultas. Crie um monitor 's12-a57-threadpool' adaptando o monitor threadpool
descrito na aula 's11-a51-threadpool'.

No módulo principal crie uma thread que simula o cadastramento de usuários, gerando
aleatoriamente códigos de porta e usuário e inserindo a informação na lista de portas.

No módulo principal, crie uma thread para simular a recepção pela rede de consultas
sobre autorizações de usuários. Esta thread deve gerar aleatoriamente códigos de usuários
e portas e inserir o trabalho de consulta na fila de trabalhos do threadpool. O resultado
(autorizado ou não) deve ser escrito na tela como parte do trabalho.

Trabalhos não são descartados. Caso a fila de trabalhos esteja lotada, esta thread fica
bloqueada até conseguir inserir o novo trabalho na fila.

No módulo principal, inicialize o threadpool com 10 threads para realizar o trabalho
de consultar as listas de portas.

O programa é terminado quando o usuário teclar <enter>.


