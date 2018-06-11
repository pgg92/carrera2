#ifndef __TAVLCALENDARIO__
#define __TAVLCALENDARIO__

#include <iostream>
#include "tcalendario.h"
#include "tvectorcalendario.h"
#include "tlistacalendario.h"

using namespace std;

class TNodoAVL;

class TAVLCalendario {

	friend ostream & operator<<(ostream &, TAVLCalendario &);

private:

	TNodoAVL *raiz;
	void InordenAux(TVectorCalendario &, int &);
	void PreordenAux(TVectorCalendario &, int &);
	void PostordenAux(TVectorCalendario &, int &);

public:

	//FORMA CANPNOCA DE LA CLASE
	TAVLCalendario();								//Constructor por defecto
	TAVLCalendario(TAVLCalendario &);				//Constructor de copia
	void copiar_arbol(TAVLCalendario &avl);
	~TAVLCalendario();								//Destructor
	TAVLCalendario & operator=(TAVLCalendario &);	//Sobrecarga del operador asignacoon

	//METODOS DE LA CLASE
	bool operator==(TAVLCalendario &);
	bool operator!=(TAVLCalendario &);
	bool EsVacio();
	bool Insertar(TCalendario &);
	void InsertarAux(TNodoAVL *, bool &, TCalendario &);
	void Equilibrar();
	TNodoAVL * Nuevo_Nodo(TCalendario &);
	void Balancear(TCalendario &);
	bool Buscar(TCalendario &);
	int Altura();
	int Nodos();
	int NodosHoja();
	TVectorCalendario Inorden();
	TVectorCalendario Preorden();
	TVectorCalendario Postorden();
	bool Borrar(TCalendario &);
	TCalendario Raiz();

};

class TNodoAVL {

	friend class TAVLCalendario;

private:

	TCalendario item;							//Elemento Etiqueta del nodo
	TAVLCalendario iz, de;						//Subárbol izquierdo y derecho
	int fe;										//Factor de Equilibrio

public:

	//FORMA CANÓNICA DE LA CLASE
	TNodoAVL();									//Constructor Por Defecto
	TNodoAVL(TNodoAVL &);						//Constructor De Copia
	~TNodoAVL();								//Destructor
	TNodoAVL & operator=(TNodoAVL &);			//Sobrecarga del Operador Asignacion

};

#endif