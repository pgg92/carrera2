#ifndef __TLISTACALENDARIO__
#define __TLISTACALENDARIO__

#include <iostream>
#include "tcalendario.h"
#include "tvectorcalendario.h"

using namespace std;

//---------------------TNODOCALENDARIO-----------------
class TNodoCalendario {

	friend class TListaCalendario;
	friend class TListaPos;

private:

	TCalendario c; //New Calendario
	TNodoCalendario *siguiente; //Puede ser un vector de nodos

public:

	TNodoCalendario();
	TNodoCalendario(const TNodoCalendario &);
	~TNodoCalendario();
	TNodoCalendario & operator=(const TNodoCalendario &);
	
};

//------------------------TLISTAPOS--------------------

class TListaPos {

	friend class TListaCalendario;

private:

	TNodoCalendario *pos;

public:

	TListaPos(); //Constructor Por Defecto
	TListaPos(const TListaPos &p); //Constructor de Copia
	~TListaPos(); //Destructor
	TListaPos& operator=(const TListaPos &);

	bool operator==(const TListaPos &) const;
	bool operator!=(const TListaPos &) const;
	TListaPos Siguiente() const;
	bool EsVacia() const;

};

//--------------------TLISTACALENDARIO--------------

class TListaCalendario {

	friend ostream & operator<<(ostream &, const TListaCalendario &);

private:

	TNodoCalendario *primero; //Primer item de la lista

public:

	TListaCalendario(); //Constructor por Defecto
	TListaCalendario(const TListaCalendario &); //Constructor de Copia
	~TListaCalendario(); //Destructor
	TListaCalendario & operator=(const TListaCalendario &); //Sobrecarga del operador Asignación

	bool operator==(const TListaCalendario &);
	TListaCalendario operator+(const TListaCalendario &);
	TListaCalendario operator-(const TListaCalendario &);
	bool Insertar(const TCalendario &);
	bool Borrar(const TCalendario &);
	bool Borrar(const TListaPos &);
	bool Borrar(const int,const int,const int);
	bool EsVacia() const;
	TCalendario Obtener(const TListaPos &) const;
	bool Buscar(const TCalendario &) const;
	int Longitud() const;
	TListaPos Primera() const;
	TListaPos Ultima() const;
	TListaCalendario SumarSubl (const int I_L1, const int F_L1,  const TListaCalendario &L2, const int I_L2, const int F_l2);
	TListaCalendario ExtraerRango(const int n1, const int n2);

};

#endif