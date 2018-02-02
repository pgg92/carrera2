#include <iostream>
#include "tlistaporo.h"
#include "tvectorporo.h"
#include "tavlporo.h"

using namespace std;

int
main(void)
{
	TAVLPoro a;
	TVectorPoro e(5),s;
  
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
	TPoro p71(1,1,71,(char *) "rojo");
	TPoro p82(1,1,82,(char *) "rojo");
	TPoro p92(1,1,92,(char *) "rojo");
	TPoro p40(1,1,40,(char *) "rojo");
	TPoro p83(1,1,83,(char *) "rojo");

  	e[1] = p68;
  	e[2] = p71;
  	e[3] = p82;
  	e[4] = p92;
  	e[5] = p98;


	s = a.BuscaHermano(e);

	cout << s << endl;
  
	return 0;
}

/* SALIDA : 
[1 () 2 () 3 () 4 () 5 ()]
*/
