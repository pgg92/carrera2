/* SALIDA:
4
3
3
*/

#include <iostream>
#include "tabbcom.h"
#include "tcomplejo.h"
#include "tvectorcom.h"
using namespace std;

int
main(void)
{
  
  TABBCom a1;
  TABBCom a2;
  int val;

  TComplejo c1(1, 0);
  TComplejo c2(2, 0);
  TComplejo c3(3, 0);
  TComplejo c4(4, 0);

  val = a1.examen(a2);
  cout << val << endl;

  a1.Insertar(c1);
  a2.Insertar(c2);
  val = a1.examen(a2);
  cout << val << endl;

  a1.Insertar(c2);
  a2.Insertar(c3);  
  val = a1.examen(a2);
  cout << val << endl;

  return 1;
}


