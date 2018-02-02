#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

void burbuja(int vector[], int tamano)
{

	int i = 0;
	int j = tamano;
	int n = tamano;
	

	__asm
	{
		bucleExterior:
			mov eax, i;					//i
			mov ebx, n;					//n = tamano

			cmp eax, ebx - 1;			//si i < tam-1
			jnc fin;

			mov j, ebx - 1;				//j = tam - 1

		bucleInterior:
			mov ebx, j;					//j

			cmp i, ebx;					//si i < tam
			jnc incrementar;

			mov ecx, vector;			//ecx = vector
			mov eax, [ecx + 4 * ebx];	//eax = vector[j]
			dec ebx;
			mov edx, [ecx + 4 * ebx];	//edx = vector[j - 1]
			inc ebx;

			cmp eax, edx;				//si [j] < [j - 1]
			jnc decrementar;

			mov[ecx + 4 * ebx], edx;	//[j] = edx = [j - 1]
			dec ebx;
			mov[ecx + 4 * ebx], eax;	//[j - 1] = eax = [j]

			jmp bucleInterior;

		incrementar:
			inc i;						//i++
			jmp bucleExterior;

		decrementar:
			dec j;						//j--
			jmp bucleInterior;

		fin:
	}
}

void main()
{
	std::cout << "FASE-I PARTE INDIVIDUAL" << std::endl;
	std::cout << "ALIAGA HYDER ALEJANDRO JESÚS DNI:48765284V" << std::endl << std::endl;
	std::cout << "*** ALGORTIMO DE LA BURBUJA ***" << std::endl;

	int v[20],
		tamano,
		naleatorio,
		i;
	

	std::cout << "Cantidad de elementos a ordear(max 20)?: ";
	std::cin >> tamano;
	std::cout << "Elementos a ordenar: " << std::endl;

	srand(time(NULL));

	for (i = 0; i < tamano; i++)
	{
		naleatorio = rand() % 1000;
		v[i] = naleatorio;
		std::cout << v[i];
		if (i < tamano - 1)
			 std::cout << ", ";
	}
	std::cout << std::endl;

	burbuja(v, tamano);

	std::cout << "Elementos ordenados: " << std::endl;
	for (i = 0; i < tamano; i++)
	{
		std::cout << v[i];
		if (i < tamano - 1)
			std::cout << ", ";
	}
	std::cout << endl;
	getchar();
	getchar();
}