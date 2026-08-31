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


    n = 2 *id;
    /*
    if(id != 0 )
    {
         MPI_Send(&n,1,MPI_INT,0,100,MPI_COMM_WORLD);
        
    }
    else
    {
        
        s = n ;
        for(int i = 0 ; i < np; i ++)
        {
                
            MPI_Recv(&n,1,MPI_INT,i,100,MPI_COMM_WORLD,&status);
            s += n;
        }
           
    }

    if( id == 0){
         for(int i = 1 ; i < np; i ++)
        {
            MPI_Send(&n,1,MPI_INT,i,200,MPI_COMM_WORLD);
        }
    }
    else{
          MPI_Recv(&s,1,MPI_INT,0,200,MPI_COMM_WORLD,&status);
    }
    */

    MPI_Allreduce(&n,&s,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);


     printf("ID = %d N = %d SomaTotal = %d \n",id,n,s);

    MPI_Finalize();

    return 0;
}