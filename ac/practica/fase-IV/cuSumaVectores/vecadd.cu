/*
 * Copyright 1993-2006 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.
 *
 * This software and the information contained herein is PROPRIETARY and
 * CONFIDENTIAL to NVIDIA and is being provided under the terms and
 * conditions of a Non-Disclosure Agreement.  Any reproduction or
 * disclosure to any third party without the express written consent of
 * NVIDIA is prohibited.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.  This source code is a "commercial item" as
 * that term is defined at 48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer software" and "commercial computer software
 * documentation" as such terms are used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 */

// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define VECTOR_ELEMENTS 30000000
#define COMPUTE_N_ELEMENTS_PER_THREAD 1

// includes, project
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include "vecadd.h"
#include <Windows.h>

#define DEBUG_ 1

typedef LARGE_INTEGER timeStamp;
double getTime();

__global__ void vecadd(float* C, const float* A, const float* B)
{
    // ===================================================================
    // Calcula el �ndice para acceder a cada elemento
    // Calcula la suma de las posiciones correspondientes y almacena el resultado
    // ===================================================================

    const int i = (threadIdx.x + blockIdx.x * blockDim.x) * COMPUTE_N_ELEMENTS_PER_THREAD;
	if( i < VECTOR_ELEMENTS )
	{
		for(int j=0; j < COMPUTE_N_ELEMENTS_PER_THREAD; j++)
		{
			C[i+j] = A[i+j] + B[i+j];
		}
	}
}

#define ERROR_CHECK { cudaError_t err; \
  if ((err = cudaGetLastError()) != cudaSuccess) { \
    printf("CUDA error: %s, line %d\n", cudaGetErrorString(err), __LINE__);}}

////////////////////////////////////////////////////////////////////////////////
// declaration, forward
void runTest(int argc, char** argv);

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int
main(int argc, char** argv)
{
    runTest(argc, argv);
		getchar();
}

////////////////////////////////////////////////////////////////////////////////
//! Run a simple test for CUDA
////////////////////////////////////////////////////////////////////////////////
void
runTest(int argc, char** argv)
{
    float *A, *B, *C, *reference;
    float *A_d, *B_d, *C_d;

	double gpu_start_time_trans, gpu_end_time_trans;
	double gpu_start_time, gpu_end_time;
	double cpu_start_time, cpu_end_time;

    // Allocate input vectors (host memory)
    A = (float *) malloc(VECTOR_ELEMENTS * sizeof(float));
    assert(A != NULL);
    B = (float *) malloc(VECTOR_ELEMENTS * sizeof(float));
    assert(B != NULL);

    printf("  Allocate host memory for input vectors A, B\n");
    printf("    A: %d elements\n", VECTOR_ELEMENTS);
    printf("    B: %d elements\n", VECTOR_ELEMENTS);

	printf(" Required memory for %d elements: %d MB ",VECTOR_ELEMENTS, (VECTOR_ELEMENTS*3*sizeof(float)) / (1024*1024) );

    // Allocate output vector (host memory)
    C = (float *) malloc(VECTOR_ELEMENTS * sizeof(float));
    assert(C != NULL);

	#ifdef DEBUG_
		printf("  Allocate memory for the output vector on host side.\n");
	#endif

	    // Initialize input vectors with some values
    for (int i = 0; i < VECTOR_ELEMENTS; i++) {
        A[i] = 1.f;
        B[i] = 2.f;
    }

    // Allocate input vectors (device memory)
    cudaMalloc((void **) &A_d, VECTOR_ELEMENTS * sizeof(float));
    cudaMalloc((void **) &B_d, VECTOR_ELEMENTS * sizeof(float));

	#ifdef DEBUG_
		printf("  Allocate device memory.\n");
	#endif

	gpu_start_time_trans = getTime();

    // Allocate output vector (device memory)
    cudaMalloc((void **) &C_d, VECTOR_ELEMENTS * sizeof(float));

	#ifdef DEBUG_
		printf("  Allocate device memory for output vector.\n");
	#endif

    // Copy input vectors to device memory
    cudaMemcpy(A_d, A, VECTOR_ELEMENTS * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(B_d, B, VECTOR_ELEMENTS * sizeof(float), cudaMemcpyHostToDevice);

    #ifdef DEBUG_
		printf("  Copy host memory to device.\n");
		printf("  Setup kernel execution parameters.\n");
	#endif

    // ===================================================================
    // Calcula las dimensiones del grid e invoca el kernel
    // ===================================================================
    dim3 block(512);
    dim3 grid( (VECTOR_ELEMENTS + (block.x*COMPUTE_N_ELEMENTS_PER_THREAD-1) )/ (block.x*COMPUTE_N_ELEMENTS_PER_THREAD) );

	#ifdef DEBUG_
		printf("  # of threads in a block: %d\n", block.x);
		printf("  # of blocks in a grid  : %d\n", grid.x);
		printf("  Executing the kernel...\n");
	#endif

	gpu_start_time = getTime();

    vecadd<<<grid,block>>>(C_d,A_d,B_d);

    cudaThreadSynchronize();
	gpu_end_time = getTime();
    ERROR_CHECK

    cudaMemcpy(C, C_d, VECTOR_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);

	gpu_end_time_trans = getTime();

	#ifdef DEBUG_
		printf("  Copy result from device to host.\n");
	#endif

    // Compare results
    {
        printf("\nCheck results with those computed by CPU.\n");
        printf ("  Computing reference solution.\n");

		reference = (float *) malloc(VECTOR_ELEMENTS * sizeof(float));
        
		cpu_start_time = getTime();
		// Compute reference vector
        computeGold(reference, A, B, VECTOR_ELEMENTS);
		cpu_end_time = getTime();

        // Compare results
        bool correct = true;
		for( int j = 0; j < 10; j++)
		{
        for (int i = 0; i < VECTOR_ELEMENTS; i++) {
            if (reference[i] != C[i]) {
                correct = false;
                break;
            }
        }
		}

        if (correct == true) {
            printf("  test: passed!\n");
        } else {
            printf("  test: failed!\n");
        }
		free(reference);
    }

	printf("Tiempo ejecuci�n GPU (sin incluir transferencia de datos): %fs\n", \
	 gpu_end_time - gpu_start_time);
	printf("Tiempo ejecuci�n GPU (con transferencia de datos): %fs\n", \
	 gpu_end_time_trans - gpu_start_time_trans);
	printf("Tiempo de ejecuci�n en la CPU                          : %fs\n", \
	 cpu_end_time - cpu_start_time);


	printf("Se ha conseguido un factor de aceleraci�n %fx utilizando CUDA (sin considerar transferencias) \n", (cpu_end_time - cpu_start_time) / (gpu_end_time - gpu_start_time) );
    // clean up memory
    free(A);
    free(B); 
    free(C);

    cudaFree(A_d);
    cudaFree(B_d);
    cudaFree(C_d);
}

/* Funciones auxiliares */
double getTime()
{
	timeStamp start;
	timeStamp dwFreq;
	QueryPerformanceFrequency(&dwFreq);
	QueryPerformanceCounter(&start);
	return double(start.QuadPart) / double(dwFreq.QuadPart);
}

