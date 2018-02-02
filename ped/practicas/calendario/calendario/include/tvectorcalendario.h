#ifndef __TVECTORCALENDARIO__
#define __TVECTORCALENDARIO__

#include <iostream>
#include "tcalendario.h" 

using namespace std;

class TVectorCalendario {

	friend ostream & operator<<(ostream &, const TVectorCalendario &);

private:

	TCalendario *c;
	int tamano;
	TCalendario error;
	void Copiar_Datos (const TVectorCalendario &);
	bool Comprueba_Rango(const int index) const;

public:

	TVectorCalendario();
	TVectorCalendario(const int);
	TVectorCalendario(const TVectorCalendario &);
	~TVectorCalendario();
	TVectorCalendario & operator=(const TVectorCalendario &);

	bool operator==(const TVectorCalendario &);
	bool operator!=(const TVectorCalendario &);
	TCalendario & operator[](int);
	TCalendario operator[](int) const;
	int Tamano();
	int Ocupadas();
	bool ExisteCal(const TCalendario &);
	void MostrarMensajes(const int,const int,const int);
	bool Redimensionar(const int);

};

#endif
