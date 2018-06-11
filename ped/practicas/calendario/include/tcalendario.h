#ifndef __TCALENDARIO__
#define __TCALENDARIO__

#include <iostream>
using namespace std;

class TCalendario {
  
  friend ostream & operator<<(ostream &, const TCalendario &);
  
private:
  
  int dia;
  int mes;
  int anyo;
  char* mensaje;
  
  bool esBisiesto(int);
  bool Mes_impar(int);
  bool Mes_par(int);
  
public:
  
  bool esCorrecto(int, int, int);
  
  TCalendario();				//Constructor por defecto
  TCalendario(const int, const int,const int,const char *);		//Constructor que inicializa calendario con parámetros pasados
  TCalendario(const TCalendario &);			//Constructor de copia
  ~TCalendario();				//Destructor
  TCalendario& operator=(const TCalendario &);	//Sobrecarga del operador asignación
  
  TCalendario operator+(const int); //Consejo (Parámetros de funciones como const)
  TCalendario operator-(const int);
  TCalendario operator++(const int); //Postincremento
  TCalendario & operator++(); //Preincremento
  TCalendario operator--(const int); //Postdescremento
  TCalendario & operator--(); //Predecremento
  
  bool ModFecha(const int,const int,const int);
  bool ModMensaje(const char *);
  bool operator ==(const TCalendario &);
  bool operator !=(const TCalendario &);
  bool operator>(const TCalendario &);
  bool operator<(const TCalendario &);
  bool EsVacio();
  int Dia() { return dia; };
  int Mes() { return mes; };
  int Anyo() { return anyo; };
  char *Mensaje() { return mensaje; };

};

#endif
  
  
  

