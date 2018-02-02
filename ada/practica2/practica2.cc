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

/******************************************************************
quicksortCentral(int * v, long pi, long pf)

Algoritmo de ordenación Quicksort tomando como pivote el
elemento del vector que ocupa la posición central
*******************************************************************/
void 
quicksortCentral(int * v, long pi, long pf){
long i,j;
int pivote,aux; 
  if (pi<pf){
	i=pi; j=pf;
	pivote=v[(i+j)/2];
	do{
		while (v[i]<pivote) i++;
		while (v[j]>pivote) j--;
		if (i<=j) {
		  aux=v[i]; v[i]=v[j]; v[j]=aux;
		  i++; j--;
		}
	}while (i<=j);
	if (pi<j) quicksortCentral(v,pi,j);
	if (i<pf) quicksortCentral(v,i,pf);
  }
}


int main(){

	int tamanyo;
	int i, j, num;
	long double tiempoOrdenar = 0;
	long double tiempoOrdenar2 = 0;

	tamanyo = 256;
	tiempoOrdenar = 0;
	
	cout << "#Talla" << "    " << "Tiempo" << endl; 

	do{

		int vector[tamanyo];
	
		for (i = 0; i < tamanyo; i++)
		{
			num = rand()%70000;
			vector[i] = num;
		}

		for(j = 0; j < 30; j++){

			tiempoOrdenar = tiempo();
			quicksortCentral(vector, 0, tamanyo-1);
			tiempoOrdenar += tiempo();
			tiempoOrdenar2 += tiempoOrdenar;
		}
		cout << tamanyo << "   " << (tiempoOrdenar2/30) << endl;
		tamanyo *= 2;

	}while(tamanyo <= 65536);



}
















