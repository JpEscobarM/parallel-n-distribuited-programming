#include <omp.h>
#include <stdio.h>

#define N 100
#define NTHREADS 4

int main(){
    int A[N], B[N], C[N];
    int id, i, ini, fim, parte;

    // Inicialização dos vetores A e B
    for(i = 0; i < N; i++){
        A[i] = B[i] = 1;
    }

    // Configura o número de threads
    omp_set_num_threads(NTHREADS);

    // Região paralela dividindo manualmente as iterações
    #pragma omp parallel private (id, parte, ini, fim, i)
    {
        parte = N / omp_get_num_threads();
        id = omp_get_thread_num();

        ini = parte * id;
        fim = ini + parte;

        for (i = ini; i < fim; i++){
            C[i] = A[i] + B[i];
        }
    }

    return 0;
}