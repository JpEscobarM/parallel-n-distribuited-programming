#include <stdio.h>
#include <omp.h>

#define T 2

int main(int argc, char **argv){

	double pi = 0, passo, parcial;
	double x, h;
	double nr;

	int id, np, i;
	
	printf("Digite o numero de retangulos: ");
	scanf("%lf",&nr);
	
	omp_set_num_threads(T);

	passo = 1.0 / nr; 
        pi = 0.0; 

	#pragma omp parallel private (i,id,h,x,parcial)
	{
		id = omp_get_thread_num();

		parcial = 0;

            	for (i = id + 1; i <= nr; i+= T) { 
	                x = passo * (( double)i - 0.5) ; 
	                h = 4.0 / (1.0 + x*x); 
			parcial +=  h * passo;
		}

		#pragma omp critical
		{
			pi +=parcial;
		}

	}

	printf("Pi = %lf\n",pi);

}
