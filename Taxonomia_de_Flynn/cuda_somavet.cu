#include <stdio.h>

#define N 5

__global__  void somavet(float* A, float* B, float* C){
	int i = threadIdx.x;
	C[i] = A[i] + B[i];
}

int  main(){
        float A[N] = {5, 2, 3 ,8, 10};
	float B[N] = {8, 4, 3, 2, 11};
	float C[N];

        float *ptrA, *ptrB, *ptrC;

        cudaMalloc((void**)&ptrA, N*sizeof(float));
        cudaMalloc((void**)&ptrB, N*sizeof(float));
        cudaMalloc((void**)&ptrC, N*sizeof(float));

        cudaMemcpy(ptrA, A, N*sizeof(float),  cudaMemcpyHostToDevice);
        cudaMemcpy(ptrB, B, N*sizeof(float),  cudaMemcpyHostToDevice);

        somavet<<<1,N>>>(ptrA,  ptrB, ptrC);
        cudaMemcpy(C, ptrC, N*sizeof(float),  cudaMemcpyDeviceToHost);
  
        for (int i=0; i<N; i++){
              printf("C[%d]=%f\n",i,C[i]);
	}

        cudaFree(ptrA);
        cudaFree(ptrB);
        cudaFree(ptrC);
}

