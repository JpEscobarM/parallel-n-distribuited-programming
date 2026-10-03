#include <stdio.h>
#include <stdlib.h>

#define alpha 0.08
#define CICLOS 10000

#define LINHAS 100
#define COLUNAS 100

/*--------------------------------------------------------------------*/
void gera_matriz(float *mat, int l, int c){
	int i, j;
	for (i = 0; i < l; i++) {
		for (j = 0; j < c; j++) {
			if (i == 0 || j == 0){
				mat[i*c+j] = 1000;  
			}
			else{
				mat[i*c+j] = 0;
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
void calcula(float *mat_antiga, float *mat_nova, int l, int c){
	int i, j;
    	for (i = 1; i < l-1; i++){
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
void copia(float *mat_antiga, float *mat_nova, int l, int c){
	int i, j;
	for (i = 0; i < l; i++){
		for (j = 0; j < c; j++){
			mat_antiga[i*c+j] = mat_nova[i*c+j];
		}
	}
}

/*--------------------------------------------------------------------*/
int main(){

	int i;
	float *mat_nova = malloc(LINHAS*COLUNAS*sizeof(float));
	float *mat_antiga = malloc(LINHAS*COLUNAS*sizeof(float));

	gera_matriz(mat_nova, LINHAS, COLUNAS);

	FILE *arq = fopen("saida.txt","w");
	if (!arq) { 
		printf("Erro ao abrir arquivo\n"); 
		exit(0);
	}

	for (i = 0; i < CICLOS; i++){
     
		copia(mat_antiga, mat_nova, LINHAS, COLUNAS);
		calcula(mat_antiga, mat_nova, LINHAS, COLUNAS);

		if (!(i % 100)){  
			escreve_matriz(arq, mat_nova, LINHAS, COLUNAS);
		}
	}

	fclose(arq);
    
	free(mat_nova);
	free(mat_antiga);

	return 0;
}
/*--------------------------------------------------------------------*/

