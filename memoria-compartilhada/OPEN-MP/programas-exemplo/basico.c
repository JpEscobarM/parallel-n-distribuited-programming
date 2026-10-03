#include <omp.h>
#include <stdio.h>

#define NTHREADS 4

int main(){


	int id, threads;

	omp_set_num_threads(NTHREADS);
	
	#pragma omp parallel private(id,threads)
	{

	threads = omp_get_num_threads();
	id = omp_get_thread_num();

	printf("\nHello World Open-MP- Sou a thread %d",id);
	printf("\nTotal de threads:  %d",threads);


	}	

	printf("\n");

return 0;
}


