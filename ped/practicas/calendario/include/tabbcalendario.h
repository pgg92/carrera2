#ifndef __TABBCALEDARIO__
#define __TABBCALEDARIO__

#include <iostream>
#include "tcalendario.h"
#include "tlistacalendario.h"
#include "tvectorcalendario.h"

using namespace std;

class TNodoABB;

class TABBCalendario {

	friend ostream & operator<< (ostream &, const TABBCalendario &);

private:

	TNodoABB *raiz;
	void InordenAux(TVectorCalendario &, int &) const;
	void PreordenAux(TVectorCalendario &, int &) const;
	void PostordenAux(TVectorCalendario &, int &) const;

public:

	TABBCalendario();
	TABBCalendario(const TABBCalendario &);
	void Copiar_arbol(const TABBCalendario &);
	~TABBCalendario();
	TABBCalendario & operator=(const TABBCalendario &);

	bool operator==(const TABBCalendario &) const;
	TABBCalendario operator+(const TABBCalendario &) const ;
	TABBCalendario operator-(const TABBCalendario &) const ;


	bool EsVacio() const;
	bool Insertar(TCalendario &);
	TNodoABB * Nuevo_Nodo(TCalendario &);
	TNodoABB * obtenerNodo(const TCalendario &);
	TNodoABB * obtenerNodoaux(const TNodoABB *);
	void eliminarNodo(TNodoABB *);
	bool Borrar(const TCalendario &);
	bool Buscar(TCalendario &) const;
	TCalendario Raiz() const;
	int Altura() const;
	int Nodos() const;
	int NodosHoja() const;
	TVectorCalendario Inorden() const;
	TVectorCalendario Preorden() const;
	TVectorCalendario Postorden() const;
	TVectorCalendario Niveles();

	int* lista_hijos(const TListaCalendario &);

};

class TNodoABB {

	friend class TABBCalendario;

private:

	TCalendario item;
	TABBCalendario iz, de;

public:

	TNodoABB();
	TNodoABB(const TNodoABB &);
	~TNodoABB();
	TNodoABB & operator=(const TNodoABB &);

};

#endif
