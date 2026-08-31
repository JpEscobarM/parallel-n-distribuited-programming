#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char **argv){

    
    int id,np;
    char msg[100];
    MPI_Status status;
   
    //BLOQUEANTE: funciona como barreira em threads, não deve ter comunicação antes disso, um parametro de entrada é usado 
    //no init para todas as maquinas, TUDO que vem antes de MPI_Init é executado em todas as maquinas
    MPI_Init(&argc, &argv);

    
    //IDENTIFICA O PID DO PROCESSO
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    //IDENTIFICA A QUANTIDADE DE PROCESSOS RODANDO
    MPI_Comm_size(MPI_COMM_WORLD, &np);

   
    printf("\nPROCESSOS[%d] = PID[%d] - %s\n",np, id ,argv[1]);

    if(id == 0){//SE FOR O PROCESSO 0 MANDA MENSAGEM PRO PROCESSO 1 
        strcpy(msg,"Hello World");
        //O PROCESSO 0 ESTA ENVIANDO PARA TODOS OS PROCESSOS
        for(int i = 0 ; i < np; i++){
            MPI_Send(msg,strlen(msg)+1, MPI_CHAR,i,100,MPI_COMM_WORLD);
        }
        
    }   
    else
    {   
        //PROCESSO TODOS RECEBENDO A MENSAGEM
        MPI_Recv(msg,100,MPI_CHAR,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
    }


    printf("\nPID %d STRING: %s\n",id,msg);

    //BLOQUEANTE: funciona como barreira em threads
    MPI_Finalize();

    return 0;
}