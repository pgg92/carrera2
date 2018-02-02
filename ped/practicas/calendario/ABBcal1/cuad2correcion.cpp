#include <iostream>

using namespace std;

#include "tabbcalendario.h"

void tad01() {

  TABBCalendario a;
  TCalendario c1(1, 1,2000,(char *)"fecha"), c2(1, 1,2000,(char *)"fecha1"), c3(3, 3,2000,(char *)"fecha");

  a.Insertar(c1);
  a.Insertar(c2);
  if(a.Insertar(c3)==true) {
	cout<<"insertado"<<endl;
  }
  
  cout<<"hola"<<endl;
  cout<<"Inorden="<<a.Inorden()<<endl;
  cout<<"Preorden="<<a.Preorden()<<endl;
  cout<<"Postorden="<<a.Postorden()<<endl;
  
}

void tad02() {
  
  TABBCalendario a;
  TCalendario c1(1, 1,2000,(char *)"fecha"), c2(2, 2,2000,(char *)"fecha"), c3(3, 3,2000,(char *)"fecha");
  TCalendario c4(4,4,2000,(char *)"fecha");

  a.Insertar(c1);
  a.Insertar(c2);
  a.Insertar(c3);
  a.Insertar(c1);
  a.Insertar(c4);
  a.Insertar(c2);
  a.Insertar(c3);
  
  cout<<"Inorden="<<a.Inorden()<<endl;
  cout<<"Preorden="<<a.Preorden()<<endl;
  cout<<"Postorden="<<a.Postorden()<<endl;
}

void tad03() {

  TABBCalendario a;
  TCalendario c1(1, 1,2000,(char *)"fecha"), c2(2, 2,2000,(char *)"fecha"), c3(3, 3,2000,(char *)"fecha");
  TCalendario c4(4,4,2000,(char *)"fecha");

  a.Insertar(c1);
  a.Insertar(c2);
  a.Insertar(c3);

  if (a.Borrar(c4))
    cout<<"Borra algo" <<endl;
  else
    cout<<"No borra nada"<<endl;
    
  if (a.Borrar(c1))
    cout<<"Borra algo"<<endl;
  else
    cout<<"No borra nada"<<endl;

  if (a.Borrar(c1))
    cout<<"Borra algo"<<endl;
  else
    cout<<"No borra nada"<<endl;
}

void tad04() {

  TABBCalendario a;
  TCalendario c1(1, 1,2000,(char *)"fecha"), c2(2, 2,2000,(char *)"fecha"), c3(3, 3,2000,(char *)"fecha");
  TCalendario c4(4,4,2000,(char *)"fecha");

  a.Insertar(c1);
  a.Insertar(c2);
  a.Insertar(c3);

  if (a.Buscar(c3))
    cout<<"Esta" <<endl;
  else
    cout<<"No esta"<<endl;
    
  if (a.Buscar(c4))
    cout<<"Esta"<<endl;
  else
    cout<<"No esta"<<endl;
}

void tad05() {

  TABBCalendario a;

  cout<<"Inorden="<<a.Inorden()<<endl;
  
  cout<<"Preorden="<<a.Preorden()<<endl;
  
  cout<<"Postorden="<<a.Postorden()<<endl;
}

void tad06() {

  TABBCalendario a;
  TCalendario c1(1, 1,2000,(char *)"fecha"), c2(2, 2,2000,(char *)"fecha"), c3(3, 3,2000,(char *)"fecha");
  TCalendario c4(4,4,2000,(char *)"fecha");

  cout<<"Altura="<<a.Altura()<<endl;

  a.Insertar(c1);
  
  cout<<"Altura="<<a.Altura()<<endl;
  
  a.Insertar(c2);
  
  cout<<"Altura="<<a.Altura()<<endl;
  
  a.Insertar(c3);
  
  cout<<"Altura="<<a.Altura()<<endl;
  
  a.Insertar(c4);
  
  cout<<"Altura="<<a.Altura()<<endl;
}
  
void tad07() {

  TABBCalendario a,b,c;
  TCalendario c1(1, 1,2000,(char *)"fecha"),c2;
  int i;
  
  for (i=1; i<=300; i++)
  {
      c1.ModFecha(1,1,2000+i);
      a.Insertar(c1);
      b.Insertar(c1);
      c.Insertar(c1);
  }
      
  cout<<"Altura="<<a.Altura()<<endl;
  cout<<"Altura="<<b.Altura()<<endl;
  cout<<"Altura="<<c.Altura()<<endl;
  
  cout<<"Nodos="<<a.Nodos()<<endl;
  cout<<"NodosHoja="<<a.NodosHoja()<<endl; 
  cout<<"Nodos="<<b.Nodos()<<endl;
  cout<<"NodosHoja="<<c.NodosHoja()<<endl; 
  cout<<"Nodos="<<c.Nodos()<<endl;
  cout<<"NodosHoja="<<c.NodosHoja()<<endl; 
}

void tad08() {

  TABBCalendario a;
  TCalendario c1(1, 1,2000,(char *)"fecha"),c2(2,2,2000,(char *)"fecha"),c3(3,3,2000,(char *)"fecha");

  a.Insertar(c1);
  a.Insertar(c2);
  a.Insertar(c3);
  
  TABBCalendario b(a);
  
  cout<<"Inorden="<<b.Inorden()<<endl;

  TABBCalendario c,d(c);
  
  cout<<"Inorden="<<d.Inorden()<<endl;
}

void tad09() {

  TABBCalendario a;
  TCalendario c1(1, 1,2000,(char *)"fecha"),c2(2,2,2000,(char *)"fecha"),c3(3,3,2000,(char *)"fecha");

  a.Insertar(c1);
  a.Insertar(c2);
  a.Insertar(c3);
  
  a.~TABBCalendario();
  
  cout<<"Inorden="<<a.Inorden()<<endl;
}

void tad10() {

  TABBCalendario a;
  TCalendario c7(7, 7,2000,(char *)"fecha"),c4(4,4,2000,(char *)"fecha"),c10(10,10,2000,(char *)"fecha");
  TCalendario c2(2,2,2000,(char *)"fecha"),c5(5,5,2000,(char *)"fecha"),c8(8,8,2000,(char *)"fecha"),c9(9,9,2000,(char *)"fecha");
  
  //Comprobar sustitucion mayor izquierda
  a.Insertar(c7);
  a.Insertar(c4);
  a.Insertar(c10);
  a.Insertar(c8);
  a.Insertar(c9);
  a.Insertar(c5);
  a.Insertar(c2);
  
  a.Borrar(c7);
  
  cout<<"Preorden="<<a.Preorden()<<endl;
  
  //Comprobar sustitucion unico hijo
  
  TABBCalendario b;
  
  b.Insertar(c2);
  b.Insertar(c4);
  b.Insertar(c5);
  b.Insertar(c7);
  b.Insertar(c8);
  b.Insertar(c9);
  b.Insertar(c10);
  
  b.Borrar(c2);
  
  cout<<"Preorden="<<b.Preorden()<<endl;
}

void tad11() {

  TABBCalendario a;
  TCalendario c7(7, 7,2000,(char *)"fecha"),c4(4,4,2000,(char *)"fecha"),c10(10,10,2000,(char *)"fecha");
  TCalendario c2(2,2,2000,(char *)"fecha"),c5(5,5,2000,(char *)"fecha"),c8(8,8,2000,(char *)"fecha"),c9(9,9,2000,(char *)"fecha");
  TCalendario c1(1,1,2000,(char *)"fecha");
  
  a.Insertar(c7);
  a.Insertar(c4);
  a.Insertar(c10);
  a.Insertar(c8);
  a.Insertar(c9);
  a.Insertar(c5);
  a.Insertar(c2);
  
  a.Borrar(c1);
  
  cout<<"Preorden="<<a.Preorden()<<endl;
}

void tad12() {

  //Comprobar sustitucion unico hijo no es la raiz
  
  TABBCalendario b;
  TCalendario c7(7, 7,2000,(char *)"fecha"),c4(4,4,2000,(char *)"fecha"),c10(10,10,2000,(char *)"fecha");
  TCalendario c2(2,2,2000,(char *)"fecha"),c5(5,5,2000,(char *)"fecha"),c8(8,8,2000,(char *)"fecha"),c9(9,9,2000,(char *)"fecha");
  
  b.Insertar(c2);
  b.Insertar(c4);
  b.Insertar(c5);
  b.Insertar(c7);
  b.Insertar(c8);
  b.Insertar(c9);
  b.Insertar(c10);
  
  b.Borrar(c5);
  
  cout<<"Preorden="<<b.Preorden()<<endl;
}

void tad13() {

  //Comprobar borrar hoja
  
  TABBCalendario b;
  TCalendario c7(7, 7,2000,(char *)"fecha"),c4(4,4,2000,(char *)"fecha"),c10(10,10,2000,(char *)"fecha");
  TCalendario c2(2,2,2000,(char *)"fecha"),c5(5,5,2000,(char *)"fecha"),c8(8,8,2000,(char *)"fecha"),c9(9,9,2000,(char *)"fecha");  
  
  b.Insertar(c2);
  b.Insertar(c4);
  b.Insertar(c5);
  b.Insertar(c7);
  b.Insertar(c8);
  b.Insertar(c9);
  b.Insertar(c10);
  
  b.Borrar(c10);
  
  cout<<"Preorden="<<b.Preorden()<<endl;
}

void tad14() {

  //Comprobar borrar hoja
  
  TABBCalendario a,b;
  TCalendario c7(7, 7,2000,(char *)"fecha"),c4(4,4,2000,(char *)"fecha"),c10(10,10,2000,(char *)"fecha");
  TCalendario c2(2,2,2000,(char *)"fecha"),c5(5,5,2000,(char *)"fecha"),c8(8,8,2000,(char *)"fecha"),c9(9,9,2000,(char *)"fecha");
  
  a.Insertar(c2);
  a.Insertar(c4);
  a.Insertar(c5);
  a.Insertar(c7);
  a.Insertar(c8);
  a.Insertar(c9);
  a.Insertar(c10);
  
  b=a;

  cout<<"Preorden="<<b.Preorden()<<endl;
  
  b.~TABBCalendario();
  
  cout<<"Preorden="<<a.Preorden()<<endl;
}

void tad15() {

  //Comprobar borrar hoja
  
  TABBCalendario a,b,c;
  TCalendario c7(7, 7,2000,(char *)"fecha"),c4(4,4,2000,(char *)"fecha"),c10(10,10,2000,(char *)"fecha");
  TCalendario c2(2,2,2000,(char *)"fecha"),c5(5,5,2000,(char *)"fecha"),c8(8,8,2000,(char *)"fecha"),c9(9,9,2000,(char *)"fecha");
  TCalendario c3(3,3,2000,(char *)"fecha"),c1(1,1,2000,(char *)"fecha"),c12(12,12,2000,(char *)"fecha"),c6(6,6,2000,(char *)"fecha");
  
  
  a.Insertar(c7);
  a.Insertar(c4);
  a.Insertar(c10);
  a.Insertar(c2);
  a.Insertar(c5);
  a.Insertar(c8);
  a.Insertar(c9);
  
  b.Insertar(c4);
  b.Insertar(c1);
  b.Insertar(c6);
  b.Insertar(c12);
  b.Insertar(c3);
  c=b;

  cout<<"Preorden="<<b.Preorden()<<endl;
  cout<<"Preorden="<<c.Preorden()<<endl;
  
  c=a+b;
  
  cout<<"Preorden="<<c.Preorden()<<endl;
  cout<<"Preorden="<<b.Preorden()<<endl;
  cout<<"Preorden="<<a.Preorden()<<endl;
}

void pruebasTad(){
	cout<<"EMPIEZA EL TAD01:\n";
	tad01();
	cout<<"EMPIEZA EL TAD02:\n";
	tad02();
	cout<<"EMPIEZA EL TAD03:\n";
	tad03();
	cout<<"EMPIEZA EL TAD04:\n";
	tad04();	
	cout<<"EMPIEZA EL TAD05:\n";
	tad05();	
	cout<<"EMPIEZA EL TAD06:\n";
	tad06();	
	cout<<"EMPIEZA EL TAD07:\n";
	tad07();	
	cout<<"EMPIEZA EL TAD08:\n";
	tad08();
	cout<<"EMPIEZA EL TAD09:\n";
	tad09();
	cout<<"EMPIEZA EL TAD10:\n";
	tad10();
	cout<<"EMPIEZA EL TAD11:\n";
	tad11();
	cout<<"EMPIEZA EL TAD12:\n";
	tad12();
	cout<<"EMPIEZA EL TAD13:\n";
	tad13();
	cout<<"EMPIEZA EL TAD14:\n";
	tad14();
	cout<<"EMPIEZA EL TAD15:\n";
	tad15();
}


int main(){

	pruebasTad();

	return 0;
}
