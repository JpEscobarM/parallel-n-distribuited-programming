#include <stdio.h>


#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int idProcesso, quantidadeProcessos;

    char mensagem[100];

    MPI_Status status;

    MPI_Init(&argc, &argv);

    if (argc != 2)
    {
        printf("\nDigite a mensagem");
        exit(0);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &idProcesso);

    MPI_Comm_size(MPI_COMM_WORLD, &quantidadeProcessos);


    printf("\nEu sou o processo [%d]",idProcesso);


    if (idProcesso == 0)
    {
        printf("\nA quantidade de processos rodando é [%d]", quantidadeProcessos);
        strcpy(mensagem, argv[1]);

        for (int i =1 ; i < quantidadeProcessos; i++)
        {
            MPI_Send(mensagem,sizeof(mensagem),MPI_CHAR,i,171,MPI_COMM_WORLD);

        }

    }
    else
    {
        MPI_Recv(mensagem,sizeof(mensagem),MPI_CHAR,0,171,MPI_COMM_WORLD,&status);
    }

    if (idProcesso == 0)
    {
        printf("\nPID[%d]- lul\n",idProcesso);

    }
    else
    {
        printf("\nPID[%d] - Mensagem recebida: %s\n",idProcesso,mensagem);
    }

    MPI_Finalize();

    return 0;
}