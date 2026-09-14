#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define  alpha 0.25
#define CICLOS 10000

#define LINHAS 100
#define COLUNAS 100


void gera_matriz(float ***mat)
{
    *mat = malloc(sizeof(float*)*LINHAS);

    for (int i = 0 ; i < LINHAS ; i++)
    {
        (*mat)[i] = malloc(sizeof(float) * COLUNAS);
    }
}

void inicializa_matriz(float ***mat)
{
    for (int i = 0 ; i < LINHAS ; i ++)
    {
        for (int j = 0 ;  j < COLUNAS ; j++)
        {
            if ( i == 0 || j == 0)
            {
                (*mat)[i][j] = 1000;
            }
            else
            {
                (*mat)[i][j] = 0;
            }
        }
    }
}


void abre_arquivo(FILE **arquivo, char *nome_arquivo)
{
        *arquivo = fopen(nome_arquivo,"w");

        if (*arquivo == NULL)
        {
            printf("\nErro em abertura de arquivo de saida\n");
        }
}

void escreve_matriz(FILE *arquivo, float ***matriz)
{
    for (int i = 0 ; i < LINHAS ; i++)
    {
        for (int j = 0 ; j < COLUNAS ; j++)
        {
            fprintf(arquivo,"%f ",(*matriz)[i][j]);
        }
        fprintf(arquivo,"\n");
    }
    fprintf(arquivo,"\n");
}

void calcula( float ***matrizOriginal, float ***matrizResultante, int linhaInicial,int linhaFinal)
{
        for (int i = linhaInicial ; i < linhaFinal; i++)
        {
            for (int j = 1 ; j < (COLUNAS-1) ; j++)
            {
                (*matrizResultante)[i][j] = (*matrizOriginal)[i][j] + alpha * (
                    (*matrizOriginal)[i-1][j]+
                    (*matrizOriginal)[i+1][j]+
                    (*matrizOriginal)[i][j-1]+
                    (*matrizOriginal)[i][j+1] -
                    4 * (*matrizOriginal)[i][j]
                    );
            }
        }
}

void copia_matriz(float **origem, float **destino)
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            destino[i][j] = origem[i][j];
        }
    }
}

typedef struct {
    int inicio_linha;
    int fim_linha;
}MPI_Param;


int divide_matriz(int numeroDeProcessosAtivos) {

    if (numeroDeProcessosAtivos < 1) return 0;

    

}

int main(int argc, char **argv)
{
    printf("\n<MPI>Gerando matriz...\n");

    float **matriz = NULL;
    float **matrizResultante = NULL;
    int id, np;

    char *arquivoSaida = "saida.txt";
    FILE *arquivo = NULL;


    //ALOCA PONTEIROS
    gera_matriz(&matriz);
    gera_matriz(&matrizResultante);
    //========================

    //INICIALIZA CALOR NAS EXTREMIDADES
    inicializa_matriz(&matriz);

    //CONFIGURACAO INICIAL
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    //================



    //ID 0 ABRE O ARQUIVO DE SAIDA
    if (id == 0) {
        abre_arquivo(&arquivo,arquivoSaida);
        if (arquivo != NULL) printf("\nSou o id %d e o arquivo esta aberto", id);



        copia_matriz(matriz, matrizResultante);
        for ( int i = 0;  i < CICLOS ; i ++)
        {
            copia_matriz(matrizResultante,matriz);
            calcula(&matriz,&matrizResultante,1,98);
            if (!(i%100))
            {
                escreve_matriz(arquivo,&matrizResultante);
            }
        }



        fclose(arquivo);
        free(matriz);
        free(matrizResultante);

    }









    MPI_Finalize();
    return 0;
}