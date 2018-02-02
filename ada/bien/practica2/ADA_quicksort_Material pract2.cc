#include <sys/resource.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
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

int *crearVector(int n){
	int *v, i;
	v = new int [n];
	for(i = 0; i < n; i++){
		v[i] = rand() % n;
	}
	return v;
}


int main(){
	int n, i;
	long double tantes, tdespues, media;
	int *v;
	fstream fich;
	const int inicio = pow(2, 12);
	const int fin = pow(2, 23);
	const int veces = 10;

	fich.open("nesquick.txt", ios::out);
	fich << "#talla\ttiempo" << endl; // quitar si no funciona.
	n = inicio;
	while(n <= fin){
		media = 0;
		for(i = 0; i < veces; i++){	
			v = crearVector(n);
			tantes = tiempo();
			quicksortCentral(v, 0, n - 1);
			tdespues = tiempo();
			media = media + tdespues - tantes;
			delete [] v;
		}			
		fich << n << "\t" << media/veces << endl;
		n = n * 2;	
	}
	fich.close();
}


