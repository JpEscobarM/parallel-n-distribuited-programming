#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define alpha 0.08
#define CICLOS 10000

#define LINHAS 100
#define COLUNAS 100

/*--------------------------------------------------------------------*/
void gera_matriz(float *mat, int linhas, int colunas){
	int i, j;
	for (int i = 0; i < linhas; i++) {
		for (int j = 0; j < colunas; j++) {
			if (i == 0 || j == 0){
				mat[i*colunas+j] = 1000;  
			}
			else{
				mat[i*colunas+j] = 0;
			}    
		}
	}
}

/*--------------------------------------------------------------------*/
void escreve_matriz(FILE *arq, float *mat, int l, int c) {
	int i, j;
	for (i = 0; i < l; i++) {
		for (j = 0; j < c; j++) {
			fprintf(arq, "%f ", mat[i*c+j]);
		}
		fprintf(arq, "\n");
	}
	fprintf(arq, "\n");
}

/*--------------------------------------------------------------------*/
void calcula(float *mat_antiga, float *mat_nova, int li, int lf, int c){
	int i, j;
	for (i = li; i < lf; i++){
		for (j = 1; j < c-1; j++){
			mat_nova[i*c+j] = mat_antiga[i*c+j] + alpha * (
			mat_antiga[(i-1)*c+j] +
			mat_antiga[(i+1)*c+j] +
			mat_antiga[i*c+(j-1)] +
			mat_antiga[i*c+(j+1)] -
			4 * mat_antiga[i*c+j]
			);
		}
	}
}

/*--------------------------------------------------------------------*/
void copia(float *mat_antiga, float *mat_nova, int li, int lf, int c){
	int i, j;
	for (i = li; i < lf; i++){
		for (j = 0; j < c; j++){
			mat_antiga[i*c+j] = mat_nova[i*c+j];
		}
	}
}

/*--------------------------------------------------------------------*/
int main(int argc, char **argv){
	FILE *arq = NULL;
	int i, id, np, li, lf;
	MPI_Status status;
		
	MPI_Init(&argc, &argv);
    	MPI_Comm_rank(MPI_COMM_WORLD, &id);
    	MPI_Comm_size(MPI_COMM_WORLD, &np);

	float *mat_nova = malloc(LINHAS*COLUNAS*sizeof(float));
	float *mat_antiga = malloc(LINHAS*COLUNAS*sizeof(float));

    	if ( id == 0){
    		
    		gera_matriz(mat_nova, LINHAS, COLUNAS);
		
		arq = fopen("saida.txt","w");
    		if (!arq) { 
    			printf("Erro ao abrir arquivo\n"); 
    			exit(0);
    		}
	}
	
	MPI_Bcast(mat_nova, LINHAS*COLUNAS, MPI_FLOAT, 0, MPI_COMM_WORLD);	
    
	//DIVIDE EM PARTES
	li = id * LINHAS/np;
	lf = li + LINHAS/np;
	
	double ti = MPI_Wtime();
	
    	for (i = 0; i < CICLOS; i++){
     
             	copia(mat_antiga, mat_nova, li, lf, COLUNAS);
     		
     		if (id == 0 ){
			MPI_Sendrecv(&mat_nova[(lf-1)*COLUNAS], COLUNAS, MPI_FLOAT, id+1, 1,&mat_antiga[lf*COLUNAS], COLUNAS, MPI_FLOAT, id+1, 0,MPI_COMM_WORLD, &status);
		}
		else if (id == np-1){
			MPI_Sendrecv(&mat_nova[li*COLUNAS], COLUNAS, MPI_FLOAT, id-1, 0,
    				     &mat_antiga[(li-1)*COLUNAS], COLUNAS, MPI_FLOAT, id-1, 1,
   				     MPI_COMM_WORLD, &status);	
   		}
		else{
			MPI_Sendrecv(&mat_nova[li*COLUNAS], COLUNAS, MPI_FLOAT, id-1, 0,
    				     &mat_antiga[(li-1)*COLUNAS], COLUNAS, MPI_FLOAT, id-1, 1,
    				     MPI_COMM_WORLD, &status);
			MPI_Sendrecv(&mat_nova[(lf-1)*COLUNAS], COLUNAS, MPI_FLOAT, id+1, 1,
    				     &mat_antiga[lf*COLUNAS], COLUNAS, MPI_FLOAT, id+1, 0,
    				     MPI_COMM_WORLD, &status);
			
		}
     		
     		if (id == 0){
			calcula(mat_antiga, mat_nova, li+1, lf, COLUNAS);	
		}
		else if (id == np-1){
			calcula(mat_antiga, mat_nova, li, lf-1, COLUNAS);	
		}
		else{
			calcula(mat_antiga, mat_nova, li, lf, COLUNAS);	
		}

        	if (!(i % 100)){
        		MPI_Gather(&mat_nova[li*COLUNAS], LINHAS/np * COLUNAS, MPI_FLOAT, mat_nova, LINHAS/np * COLUNAS, MPI_FLOAT, 0, MPI_COMM_WORLD); 
			if ( id == 0 ){  
            			escreve_matriz(arq, mat_nova, LINHAS, COLUNAS);
    			}
    		}	
    	}
	
    	double tf = MPI_Wtime();
    	
    	
    	
    	if (id == 0){
    		printf("%f\n", tf - ti);
    		fclose(arq);
    	}
    	
    	free(mat_nova);
    	free(mat_antiga);

    	MPI_Finalize();
}
