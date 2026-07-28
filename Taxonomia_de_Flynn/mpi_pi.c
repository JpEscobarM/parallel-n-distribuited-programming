#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){

	double pi = 0, passo, parcial;
	double x, h;
	double nr;

	int id, np, i;
	
	MPI_Status status;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&id);


	if ( id == 0 ){
		printf("Digite o numero de retangulos: ");
		scanf("%lf",&nr);

		for ( i=1; i<np; i++){
			MPI_Send(&nr,1,MPI_DOUBLE,i,100,MPI_COMM_WORLD);
		}
	}
	else{
		MPI_Recv(&nr,1,MPI_DOUBLE,0,100,MPI_COMM_WORLD,&status);

	}

	passo = 1.0 / nr; 
        parcial = 0.0; 
 
        for (i = id + 1; i <= nr; i += np) { 
                x = passo * (( double) i - 0.5) ; 
                h = 4.0 / (1.0 + x*x); 
		parcial += h * passo;
        } 
        
	if  ( id != 0 ){
		MPI_Send(&parcial,1,MPI_DOUBLE,0,200,MPI_COMM_WORLD);
	}
	else{
		pi = parcial;

		for ( i=1; i<np; i++){
			MPI_Recv(&parcial,1,MPI_DOUBLE,i,200,MPI_COMM_WORLD,&status);
			pi += parcial;
		}
	}

	if ( id == 0 ){
		printf("Pi = %lf",pi);
	}

}
