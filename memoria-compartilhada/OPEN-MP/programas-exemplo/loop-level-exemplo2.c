#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 400
#define NTHREADS 4

int main(){

    int A[N][N], B[N][N], C[N][N];
    int j, id;

    srand(time(NULL));

    for(int i = 0 ; i < N ; i ++ ){
        for(int j = 0 ; j < N ; j++){
            A[i][j] = rand()%10;
            B[i][j] = rand()%10;
        }
    }

    omp_set_num_threads(NTHREADS);

    #pragma omp parallel for private(j, id)
    for(int i = 0 ; i < N ; i++){
        for( j = 0 ; j < N ; j++){
        
            id = omp_get_thread_num();

            C[i][j] = A[i][j] + B[i][j];
        
            printf("\nTHREAD[%d]-%d", id, C[i][j]);

        }
    }   
    
    printf("\n");

    return 0;
}