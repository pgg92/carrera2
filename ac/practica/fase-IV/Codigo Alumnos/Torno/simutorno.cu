/*----------------------------------------------------------------------------*/
/*  FICHERO:       simutorno.cu									          */
/*  AUTOR:         Antonio Jimeno											  */
/*													                          */
/*  RESUMEN												                      */
/*  ~~~~~~~												                      */
/* Ejercicio grupal para simulaci�n del movimiento de una herramienta         */
/* tipo torno utilizando GPUs                                                 */
/*----------------------------------------------------------------------------*/

// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>


// includes, project
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include "simutorno.h"
#include <Windows.h>



#define ERROR_CHECK { cudaError_t err; if ((err = cudaGetLastError()) != cudaSuccess) { printf("CUDA error: %s, line %d\n", cudaGetErrorString(err), __LINE__);}}

typedef LARGE_INTEGER timeStamp;
double getTime();

/*----------------------------------------------------------------------------*/
/*  FUNCION A PARALELIZAR  (versi�n secuencial-CPU)  				          */
/*	Simula el movimiento de una herramienta de una m�quina tipo torno         */
/*  Realiza pasossim pasos de simulacion sobre una superficie definida por    */
/*  una malla de vtotal x utotal puntos 3D                                    */
/*  El helicoide se define con un paso de PasoHelicoide mil�metros y          */
/*  con una definici�n de PuntosVueltaHelicoide por cada giro completo        */
/*----------------------------------------------------------------------------*/
int SimulacionTornoCPU(int pasossim)
{
	/* Parametros de mecanizado */
	double posX = 0.0;								// Posici�n de la herramienta
	double angle = 0.0;								// Posici�n del eje de giro
	double incX = PasoHelicoide / (double)PuntosVueltaHelicoide;
													// Incremento de la posici�n de la herramienta en cada paso de simulaci�n
	double incA = 360.0 / (double)PuntosVueltaHelicoide;
													// Incremento angular del eje de giro a cada paso de simulaci�n

	for (int i = 0; i < pasossim; i++)				// Bucle de simulaci�n
	{
		double AvanceMin = 1e10;					// Inicializaci�n del m�nimo
		for (int u = 0; u<S.UPoints; u++)			// Recorrido de todos los puntos de la superficie para cada paso de simulaci�n
		{
			for (int v = 0; v<S.VPoints; v++)
			{
				double px = S.Buffer[v][u].x + posX;// Cambio de la posici�n de la superficie por traslaci�n de la herramienta
													// Cambio de la posici�n de la superficie por giro sobre el eje X 
				double py = S.Buffer[v][u].y * cos(angle*M_PI_180) - S.Buffer[v][u].z * sin(angle*M_PI_180);
				double pz = S.Buffer[v][u].y * sin(angle*M_PI_180) + S.Buffer[v][u].z * cos(angle*M_PI_180);
													// Calcula la distancia del punto transformado a la herramienta situada en (0,TOOLYPOS,0)
				double modulo = sqrt(px*px + (py - TOOLYPOS)*(py - TOOLYPOS) + pz*pz);
													// Si el punto est� en la zona de influencia de la herramienta (-TOOLWIDTH<px<+TOOLWIDTH) y es el m�s cercano se guardan sus coordenadas U y V
				if ((fabs(px))<TOOLWIDTH && (modulo<AvanceMin))
				{
					AvanceMin = modulo; GanadorUCPU[i] = u; GanadorVCPU[i] = v;
				}
			}
		}
													// Se actualiza la posici�n para el nuevo paso de simulaci�n
		angle += incA;
		posX -= incX;
	}
	return OKSIM;									// Simulaci�n CORRECTA
}

// ---------------------------------------------------------------
// ---------------------------------------------------------------
// FUNCION A IMPLEMENTAR POR EL GRUPO (paralelizaci�n de SimulacionTornoCPU)
// ---------------------------------------------------------------
// ---------------------------------------------------------------

 int SimulacionTornoGPU(int pasossim)
{
	 return OKSIM;
}
 // ---------------------------------------------------------------
 // ---------------------------------------------------------------
 // ---------------------------------------------------------------
 // ---------------------------------------------------------------
 // ---------------------------------------------------------------

 // Declaraciones adelantadas de funciones
 int LeerSuperficie(const char *fichero);



////////////////////////////////////////////////////////////////////////////////
//PROGRAMA PRINCIPAL
////////////////////////////////////////////////////////////////////////////////
void
runTest(int argc, char** argv)
{


	double gpu_start_time, gpu_end_time;
	double cpu_start_time, cpu_end_time;

	/* Numero de argumentos */
	if (argc != 3)
	{
		fprintf(stderr, "Numero de parametros incorecto\n");
		fprintf(stderr, "Uso: %s superficie pasossim\n", argv[0]);
		return;
	}

	/* Apertura de Fichero */
	printf("Prueba simulaci�n torno...\n");
	/* Datos de la superficie */
	if (LeerSuperficie((char *)argv[1]) == ERRORSIM)
	{
		fprintf(stderr, "Lectura de superficie incorrecta\n");
		return;
	}
	int pasossim = atoi((char *)argv[2]);
	// Creaci�n buffer resultados para versiones CPU y GPU
	GanadorVCPU = (int*)malloc(pasossim*sizeof(int));
	GanadorUCPU = (int*)malloc(pasossim*sizeof(int));
	GanadorVGPU = (int*)malloc(pasossim*sizeof(int));
	GanadorUGPU = (int*)malloc(pasossim*sizeof(int));

	/* Algoritmo a paralelizar */
	cpu_start_time = getTime();
	if (SimulacionTornoCPU(pasossim) == ERRORSIM)
	{
		fprintf(stderr, "Simulaci�n CPU incorrecta\n");
		BorrarSuperficie();
		if (GanadorVCPU != NULL) free(GanadorVCPU);
		if (GanadorUCPU != NULL) free(GanadorUCPU);
		if (GanadorVGPU != NULL) free(GanadorVGPU);
		if (GanadorUGPU != NULL) free(GanadorUGPU);		exit(1);
	}
	cpu_end_time = getTime();
	/* Algoritmo a implementar */
	gpu_start_time = getTime();
	if (SimulacionTornoGPU(pasossim) == ERRORSIM)
	{
		fprintf(stderr, "Simulaci�n GPU incorrecta\n");
		BorrarSuperficie();
		if (GanadorVCPU != NULL) free(GanadorVCPU);
		if (GanadorUCPU != NULL) free(GanadorUCPU);
		if (GanadorVGPU != NULL) free(GanadorVGPU);
		if (GanadorUGPU != NULL) free(GanadorUGPU);
		return;
	}
	gpu_end_time = getTime();
	// Comparaci�n de correcci�n
	int comprobar = OKSIM;
	for (int i = 0; i<pasossim; i++)
	{
		if ((GanadorVCPU[i] != GanadorVGPU[i]) || (GanadorUCPU[i] != GanadorUGPU[i]))
		{
			comprobar = ERRORSIM;
			fprintf(stderr, "Fallo en paso %d de simulaci�n, valor correcto V=%d U=%d\n", i, GanadorVCPU[i], GanadorUCPU[i]);
		}
	}
	// Impresion de resultados
	if (comprobar == OKSIM)
	{
		printf("Simulaci�n correcta!\n");

	}
	// Impresi�n de resultados
	printf("Tiempo ejecuci�n GPU : %fs\n", \
		gpu_end_time - gpu_start_time);
	printf("Tiempo de ejecuci�n en la CPU : %fs\n", \
		cpu_end_time - cpu_start_time);
	printf("Se ha conseguido un factor de aceleraci�n %fx utilizando CUDA\n", (cpu_end_time - cpu_start_time) / (gpu_end_time - gpu_start_time));
	// Limpieza de buffers
	BorrarSuperficie();
	if (GanadorVCPU != NULL) free(GanadorVCPU);
	if (GanadorUCPU != NULL) free(GanadorUCPU);
	if (GanadorVGPU != NULL) free(GanadorVGPU);
	if (GanadorUGPU != NULL) free(GanadorUGPU);
	return;
}

int
main(int argc, char** argv)
{
	runTest(argc, argv);
	getchar();
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



/*----------------------------------------------------------------------------*/
/*	Funci�n:  LeerSuperficie(char *fichero)						              */
/*													                          */
/*	          Lee los datos de la superficie de un fichero con formato .FOR   */
/*----------------------------------------------------------------------------*/
int LeerSuperficie(const char *fichero)
{
	int i, j, count;		/* Variables de bucle */
	int utotal,vtotal;		/* Variables de tama�o de superficie */
	FILE *fpin; 			/* Fichero */
	char cadena[255];
	double x, y, z;

	cadena[0] = 0;
	/* Apertura de Fichero */
	if ((fpin = fopen(fichero, "r")) == NULL) return ERRORSIM;
	/* Lectura de cabecera */
	while (!feof(fpin) && strcmp(cadena, "[HEADER]")) fscanf(fpin, "%s\n", cadena);
	if (fscanf(fpin, "SECTION NUMBER=%d\n", &utotal)<0) return ERRORSIM;
	if (fscanf(fpin, "POINTS PER SECTION=%d\n", &vtotal)<0) return ERRORSIM;
	if (fscanf(fpin, "STEP=%lf\n", &PasoHelicoide)<0) return ERRORSIM;
	if (fscanf(fpin, "POINTS PER ROUND=%d\n", &PuntosVueltaHelicoide)<0) return ERRORSIM;
	if (utotal*vtotal <= 0) return ERRORSIM;
	/* Localizacion de comienzo */
	while (!feof(fpin) && strcmp(cadena, "[GEOMETRY]")) fscanf(fpin, "%s\n", cadena);
	if (feof(fpin)) return ERRORSIM;
	/* Inicializaci�n de parametros geometricos */
	if (CrearSuperficie(utotal, vtotal) == ERRORSIM) return ERRORSIM;
	/* Lectura de coordenadas */
	count = 0;
	for (i = 0; i<utotal; i++)
	{
		for (j = 0; j<vtotal; j++)
		{
			if (!feof(fpin))
			{
				fscanf(fpin, "%lf %lf %lf\n", &x, &y, &z);
				S.Buffer[j][i].x = x;
				S.Buffer[j][i].y = y;
				S.Buffer[j][i].z = z;
				count++;
			}
			else break;
		}
	}
	fclose(fpin);
	if (count != utotal*vtotal) return ERRORSIM;
	return OKSIM;
}



