#include <iostream>
#include "tlistaporo.h"
#include "tvectorporo.h"
#include "tavlporo.h"

using namespace std;

int
main(void)
{
	TAVLPoro a;
	TVectorPoro e,s;
  
	TPoro p;
	TPoro p68(1,1,68,(char *) "rojo");
	TPoro p56(1,1,56,(char *) "rojo");
	TPoro p84(1,1,84,(char *) "rojo");
	TPoro p35(1,1,35,(char *) "rojo");
	TPoro p60(1,1,60,(char *) "rojo");
	TPoro p80(1,1,80,(char *) "rojo");
	TPoro p98(1,1,98,(char *) "rojo");
	TPoro p11(1,1,11,(char *) "rojo");
	TPoro p55(1,1,55,(char *) "rojo");
	TPoro p64(1,1,64,(char *) "rojo");
	TPoro p70(1,1,70,(char *) "rojo");
	TPoro p82(1,1,82,(char *) "rojo");
	TPoro p92(1,1,92,(char *) "rojo");
	TPoro p40(1,1,40,(char *) "rojo");
	TPoro p83(1,1,83,(char *) "rojo");

	a.Insertar(p68);
	a.Insertar(p56);
	a.Insertar(p84);
	a.Insertar(p35);
	a.Insertar(p60);
	a.Insertar(p80);
	a.Insertar(p98);
	a.Insertar(p11);
	a.Insertar(p55);
	a.Insertar(p64);
	a.Insertar(p70);
	a.Insertar(p82);
	a.Insertar(p92);
	a.Insertar(p40);
	a.Insertar(p83);

	s = a.BuscaHermano(e);

	cout << s << endl;
  
	return 0;
}

/* SALIDA : 
[]
*/
