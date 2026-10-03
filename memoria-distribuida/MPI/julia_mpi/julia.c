#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <stdio.h>

#define buffer(y,x) buffer[y*nx + x]

int max_iterations = 255;

//*******************************************************************************//
int calcula_ponto(int x, int y) {
  int iteracoes = 0;
  complex double z, c;
  
  c = -0.625 - 0.4*I;
  z = (-2 + x*0.001) + (-2 + y*0.001)*I;
  iteracoes = 0;
  while (cabs(z) < 2 && iteracoes < max_iterations){
         z = z*z + c; 
         iteracoes++;
        
  } 
  return iteracoes; 
}

//*******************************************************************************//
void calcula_julia(int *buffer, int nx, int ny) {
  
    int x, y;

    for (y=0;  y<ny; y++){
        for (x=0; x<nx; x++) {
              buffer(y,x) = calcula_ponto(x, y);
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
	int nx = 4000;
	int ny = 4000;
	
	int *buffer = NULL;	
	
	buffer = (int *) malloc(ny * nx * sizeof(int) );
	
	calcula_julia(buffer, nx, ny);

	gera_arquivo_ppm("julia.ppm", buffer, nx, ny, 255);

	free(buffer);
}
//*******************************************************************************//
	
	




