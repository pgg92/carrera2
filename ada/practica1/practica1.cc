// PRACTICA 1 ADA

#include <sys/resource.h>

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*****************************************************
Nombre funcion: tiempo(void)
Proposito: Calcular el tiempo de CPU de este proceso
(y sólo de este proceso)
Parametros de entrada: nada
Devuelve: El tiempo empleado en segundos
******************************************************/
long double
tiempo(void){
 struct rusage usage;
 getrusage(RUSAGE_SELF,&usage);
 return( (long double) usage.ru_utime.tv_sec +
	 (long double) usage.ru_utime.tv_usec/1e6 
	 /* + (long double) usage.ru_stime.tv_sec +
         (long double) usage.ru_stime.tv_usec/1e6 */  
       );
}

                                    
/******************************************************************
burbuja(int * v, unsigned long talla){

Algoritmo de ordenación burbuja sin ninguna mejora             
*******************************************************************/
void 
burbuja(int * v, unsigned long talla){
int aux;
                                    
for (unsigned long i=1; i<talla; i++)
   for (unsigned long j=0; j<talla-i; j++)
      if (v[j]>v[j+1]){  /*swap*/
         aux=v[j]; 
         v[j]=v[j+1]; 
         v[j+1]=aux;
      }
}

int main(){

	int tamanyo;
	int i, j, num;
	long double tiempoOrdenar = 0;

	tamanyo = 256;

	do{

		int vector[tamanyo];
	
		for (i = 0; i < tamanyo; i++)
		{
			num = rand()%70000;
			vector[i] = num;
		}

		tiempoOrdenar = tiempo();
		burbuja(vector, tamanyo);
		tiempoOrdenar += tiempo();
		 
		cout << "Para la talla " << tamanyo << " tarda " << tiempoOrdenar << " segundos " << endl;
		tamanyo *= 2;

	}while(tamanyo <= 65536);



}
















