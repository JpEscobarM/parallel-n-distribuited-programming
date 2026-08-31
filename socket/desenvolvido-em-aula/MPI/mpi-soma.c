#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char **argv){

    
    int id,np,n, s;
    char msg[100];
    MPI_Status status;


    MPI_Init(&argc, &argv);

    
    //IDENTIFICA O PID DO PROCESSO
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    //IDENTIFICA A QUANTIDADE DE PROCESSOS RODANDO
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    n = id * 10;
    s = n;

   
    
    int seguinte= (id+1)%np;
    int anterior = (id-1+np) %np;

    for(int i = 0; i < np-1; i ++){
    MPI_Send(&n,1,MPI_INT,seguinte,100,MPI_COMM_WORLD);
    
    MPI_Recv(&n,1,MPI_INT,anterior,100,MPI_COMM_WORLD,&status);

    s+=n;
    }

     printf("ID = %d N = %d SomaTotal = %d \n",id,n,s);


    MPI_Finalize();

    return 0;
}