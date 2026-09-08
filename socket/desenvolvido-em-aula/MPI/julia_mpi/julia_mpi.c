#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <stdio.h>
#include <mpi.h>

#define buffer(y,x) buffer[y*nx + x]

int max_iterations = 255;

//*******************************************************************************//
//CALCULA A POSICAO DE CADA PIXEL NA IMAGEM NAS CORDENADAS X e Y
int calcula_ponto(int x, int y) {
  int iteracoes = 0;

  //Um numero complexo tem a formula: z=a+bi onde a=parte real, b=parte imaginaria e i=raiz(-1) sendo i a "unidade imaginaria"

  complex double z, c;
  
  //C é uma constante fixa para a imagem toda.
  c = -0.625 - 0.4*I;
 
  //Transforma a cordenada (x,y) em um numero complexo em Z,
  z = 
  (-2 + x*0.001) // parte real, mapeia os pixeis para -2 -------- -1 -------- 0 -------- 1 -------- 2 no eixo hroizontal x, para testar basta multiplicar a posicao do pixel: -2 + (X=0000)*(0.001) -2+0 = -2
   +
   (-2 + y*0.001)*I;//parte imaginaria parte real, mapeia os pixeis para -2 -------- -1 -------- 0 -------- 1 -------- 2 no eixo vertical y: -2 + (Y=4000)*(0.001)= -2 + 4 = 2,
  
   iteracoes = 0;

  while (cabs(z) < 2 && iteracoes < max_iterations){

        
         z = z*z + c; 
         iteracoes++;
        
  } 
  return iteracoes; 
}

//*******************************************************************************//
void calcula_julia(int id, int nproc, int *buffer, int nx, int ny) {
  
    int x, y, yi;
    int ini, fim;

    ini = id * (ny/nproc);
    fim = ini + (ny/nproc);

    for (y=ini, yi=0;  y<fim; y++, yi++){
        for (x=0; x<nx; x++) {
              buffer(yi,x) = calcula_ponto(x, y);
        }
    }
}

//*******************************************************************************//
void gera_arquivo_ppm(char *nome_arquivo, int *buffer, int nx, int ny, int max) {
  int i;

  FILE *file = fopen(nome_arquivo,"w");

  fprintf(file,"P2\n");
  fprintf(file,"%d %d\n",nx,ny);

  fprintf(file,"%d",max);

  for (i=0; i<nx*ny; i++) {
    if (!(i%nx)){ 
	fprintf(file,"\n");
    }	
    fprintf(file,"%d ",buffer[i]);
  }
  fclose(file);
}

//*******************************************************************************//
int main( int argc,  char **argv ){
	
    //DIMENSAO DA IMAGEM == 4000 * 4000 == 16.000.000 pixels
    int nx = 4000;
	int ny = 4000;
	
	int *buffer = NULL;	
    int *final = NULL;
    int id, nproc;
	
    double ti, tf;
    	
    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);	

    ti = MPI_Wtime();

    if ( id == 0 ){
        final = (int *) malloc(ny * nx * sizeof(int));
	}
	buffer = (int *) malloc(ny/nproc * nx * sizeof(int));
	
	calcula_julia(id, nproc, buffer, nx, ny);

    MPI_Gather(buffer, ny/nproc * nx, MPI_INT, final, ny/nproc* nx, MPI_INT, 0, MPI_COMM_WORLD);

	if ( id == 0 ){
		gera_arquivo_ppm("julia.ppm", final, nx, ny, 255);
    }

    tf = MPI_Wtime();

    if ( id == 0 ){
        printf("Tempo: %f\n", tf - ti);
        free(final);
    }

    free(buffer);

}
//*******************************************************************************//
	
	




