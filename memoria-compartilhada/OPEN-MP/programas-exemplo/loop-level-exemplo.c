#include <omp.h>
#include <stdio.h>

#define N 100
#define NTHREADS 2

int main(){

	int A[N],B[N],C[N];
	int i,id;

	for(i = 0 ; i < N; i++) A[i]=B[i]=1;
	
	omp_set_num_threads(NTHREADS);


	#pragma omp parallel for private(id)
	for(int j = 0 ; j < N ; j ++){
		
		id = omp_get_thread_num();
		C[j] = A[j]+B[j]*j;
		 printf("\nTHREAD[%d]-%d",id,C[j]);
	}	
	
	printf("\n");

return 0;
}


