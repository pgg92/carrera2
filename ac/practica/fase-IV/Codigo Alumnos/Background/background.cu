/*
* Ejemplo en CUDA de la implementación background subtraction
* aplicado a dos imágenes
*
* Adaptacion de un codigo de calculo de mediana
* desarrollado por Sergio Orts-Escolano
* Copyright Universidad de Alicante, 2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if _WIN32
#include <Windows.h>
#else
#include <sys/types.h>
#include <sys/time.h>
#endif

// Ficheros de inclusión para que funcione el intellisense en Visual Studio
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "EasyBMP.h"

#if _WIN32
typedef LARGE_INTEGER timeStamp;
void getCurrentTimeStamp(timeStamp& _time);
timeStamp getCurrentTimeStamp();
double getTimeMili(const timeStamp& start, const timeStamp& end);
double getTimeSecs(const timeStamp& start, const timeStamp& end);
#endif

// Dimensiones de la imagen a procesar
int WIDTH;
int HEIGHT;

// valor del umbral 
int Threshold;


// Funciones auxiliares
double get_current_time();
void checkCUDAError(const char*);


// Tamaño de grid y bloque CUDA
#define GRID_W  32
#define GRID_H  32
#define BLOCK_W 32
#define BLOCK_H 32

// Buffers de imagenes
unsigned char *input_imageb;
unsigned char *input_imagef;
unsigned char *gpu_output;




// CUDA kernel background
__global__ void Background(unsigned char *d_output, unsigned char *d_inputb, unsigned char *d_inputf, int width)
{

	/*
	* Calculamos la fila y columna global para este hilo
	*/
	// TO DO


	// Realizar la substracción para el pixel correspondiente a este hilo 
	// TO DO


}

/***********************************************************************************/

// El main puede tener como argumentos: nombres de los fichero de las imagenes (tiene que ser BMP) y el umbral
int main(int argc, char *argv[])
{
	int x, y, xWindow, yWindow, x2, y2;
	int i;
	int errors;
	int temp, mean, clr;

	double start_time_inc_data, end_time_inc_data;
	double cpu_start_time, cpu_end_time;

	unsigned char *d_inputb, *d_inputf, *d_output;

	unsigned char *output_image;
	unsigned char *imagen_resultado;
	int rows;
	int cols;

	// Leemos las imágenes 
	BMP Fondo, Image;
	Fondo.ReadFromFile("background.bmp");
	Image.ReadFromFile("imagen.bmp");
	//Fondo.ReadFromFile(argv[1]);
	//Image.ReadFromFile(argv[2]);

	BMP Resultado;

	// Leemos el valor del umbral
	Threshold = 120;
	//Threshold = atoi(argv[3]);

	// Calculo del tamaño de la imagen
	WIDTH = Fondo.TellWidth();
	HEIGHT = Fondo.TellHeight();

	// Establecemos el tamaño de la imagen de salida
	Resultado.SetSize(Fondo.TellWidth(), Fondo.TellHeight());
	Resultado.SetBitDepth(1);

	// Reserva memoria en el host para alojar la imagen
	input_imageb = (unsigned char*)calloc(((HEIGHT * WIDTH) * 1), sizeof(unsigned char));
	input_imagef = (unsigned char*)calloc(((HEIGHT * WIDTH) * 1), sizeof(unsigned char));
	gpu_output = (unsigned char*)calloc(((HEIGHT * WIDTH) * 1), sizeof(unsigned char));
	output_image = (unsigned char*)calloc(((WIDTH * HEIGHT) * 1), sizeof(unsigned char));


	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			input_imageb[i*WIDTH + j] = Fondo(i, j)->Red;
			input_imagef[i*WIDTH + j] = Image(i, j)->Red;
		}
	}


	/*
	* Versión CPU background
	*/

	printf("Grid size: %dx%d\n", GRID_W, GRID_H);
	printf("Block size: %dx%d\n", BLOCK_W, BLOCK_H);

	// Calculamos memoria necesaria para alojar las imagenes 
	size_t memSize = WIDTH * HEIGHT * sizeof(unsigned char);

	/* Reservamos memoria en la GPU */
	cudaMalloc(&d_inputb, memSize);
	cudaMalloc(&d_inputf, memSize);
	cudaMalloc(&d_output, memSize);


	start_time_inc_data = get_current_time();

	/*
	* Copiamos todos los arrays a la memoria de la GPU
	*/
	cudaMemcpy(d_inputb, input_imageb, memSize, cudaMemcpyHostToDevice);
	cudaMemcpy(d_inputf, input_imagef, memSize, cudaMemcpyHostToDevice);
	cudaMemcpy(d_output, input_imagef, memSize, cudaMemcpyHostToDevice);

	/***********************************************************/
	// Ejecutar background en la GPU
	/* Ejecución kernel  */
	// TO DO - Calcular tamaño de bloque y grid para la correcta ejecucion del kernel
	// TO DO - Ejecutar el kernel


	// Copiamos de la memoria de la GPU 
	cudaMemcpy(gpu_output, d_output, memSize, cudaMemcpyDeviceToHost);

	end_time_inc_data = get_current_time();

	checkCUDAError("Background CUDA: ");

	/*************************************************************/

	/****************************
	* Versión CPU background
	*****************************/
	cpu_start_time = get_current_time();


	for (y = 1; y < HEIGHT - 1; y++) {
		for (x = 1; x < WIDTH - 1; x++) {

			clr = 1;
			mean = 0;
			for (yWindow = -1; yWindow < 2; yWindow++) {
				y2 = y + yWindow;
				for (xWindow = -1; xWindow <2; xWindow++) {
					x2 = x + xWindow;
					mean += input_imagef[y2*WIDTH + x2];
				}
			}

			mean = mean / 9;
			temp = abs((mean - input_imageb[y*WIDTH + x]));

			if (temp > Threshold)
				clr = 0;
			if (clr == 0)
				output_image[y*WIDTH + x] = 255;
			else
				output_image[y*WIDTH + x] = 0;


		}
	}


	cpu_end_time = get_current_time();

	/* Comprobamos que los resultados de la GPU coinciden con los calculados en la CPU */

	errors = 0;
	for (y = 1; y < HEIGHT - 1; y++) {
		for (x = 1; x < WIDTH - 1; x++) {
			if (output_image[y *WIDTH + x] != gpu_output[y *WIDTH + x]) {
				errors++;
				printf("Error en %d,%d (CPU=%i, GPU=%i)\n", x, y, \
					output_image[y *WIDTH + x], \
					gpu_output[y*WIDTH + x]);
			}
		}
	}

	if (errors == 0) printf("\n\n ***TEST CORRECTO*** \n\n\n");

	imagen_resultado = (unsigned char*)calloc(((WIDTH * HEIGHT) * 1), sizeof(unsigned char));


	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			imagen_resultado[y*WIDTH + x] = gpu_output[y*WIDTH + x];
		}
	}

	cudaFree(d_inputb);
	cudaFree(d_inputf);
	cudaFree(d_output);

	printf("Tiempo ejecución GPU (Incluyendo transferencia de datos): %fs\n", \
		end_time_inc_data - start_time_inc_data);
	printf("Tiempo de ejecución en la CPU                          : %fs\n", \
		cpu_end_time - cpu_start_time);

	// Copiamos el resultado al formato de la libreria y guardamos el fichero BMP procesado
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			Resultado(i, j)->Red = imagen_resultado[i*WIDTH + j];
			Resultado(i, j)->Green = imagen_resultado[i*WIDTH + j];
			Resultado(i, j)->Blue = imagen_resultado[i*WIDTH + j];
		}
	}
	// Guardamos el resultado de aplicar el filtro en un nuevo fichero
	Resultado.WriteToFile("resultado_background.bmp");

	getchar();
	return 0;
}


/* Funciones auxiliares */

#if _WIN32
void getCurrentTimeStamp(timeStamp& _time)
{
	QueryPerformanceCounter(&_time);
}

timeStamp getCurrentTimeStamp()
{
	timeStamp tmp;
	QueryPerformanceCounter(&tmp);
	return tmp;
}

double getTimeMili()
{
	timeStamp start;
	timeStamp dwFreq;
	QueryPerformanceFrequency(&dwFreq);
	QueryPerformanceCounter(&start);
	return double(start.QuadPart) / double(dwFreq.QuadPart);
}
#endif 

double get_current_time()
{
#if _WIN32 
	return getTimeMili();
#else
	static int start = 0, startu = 0;
	struct timeval tval;
	double result;

	if (gettimeofday(&tval, NULL) == -1)
		result = -1.0;
	else if (!start) {
		start = tval.tv_sec;
		startu = tval.tv_usec;
		result = 0.0;
	}
	else
		result = (double)(tval.tv_sec - start) + 1.0e-6*(tval.tv_usec - startu);
	return result;
#endif
}

/* Función para comprobar errores CUDA */
void checkCUDAError(const char *msg)
{
	cudaError_t err = cudaGetLastError();
	if (cudaSuccess != err)
	{
		fprintf(stderr, "Cuda error: %s: %s.\n", msg, cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}
}

