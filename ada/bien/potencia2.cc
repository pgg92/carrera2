#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

unsigned long calls_pow2_1, calls_pow2_2, calls_pow2_3, calls_pow2_4;

unsigned long pow2_1(unsigned n){
	calls_pow2_1++;
	if(n == 0)
		return 1;
	else
		return 2 * pow2_1(n-1);	
	
}

unsigned long pow2_2(unsigned n){
	calls_pow2_2++;
	unsigned long resultado;

	if(n == 0){
		return 1;
	}
	else{
		if(n % 2 == 0){
			resultado = pow2_2(n/2) * pow2_2(n/2);
		}
		else{
			resultado = 2*pow2_2(n/2) * pow2_2(n/2);
		}
	}
	return resultado;
}

unsigned long pow2_3(unsigned n){
	calls_pow2_3++;
	unsigned long resultado;
	
	if(n == 0){
		return 1;
	}
	else{
		resultado = pow2_3(n/2);
		if(n % 2 == 0){
			resultado = resultado*resultado;
		}
		else{
			resultado = 2*resultado*resultado;
		}
	}
	return resultado;
}

unsigned long pow2_4(unsigned n){
	calls_pow2_4++;
	unsigned long resultado;
	
	if(n == 0){
		resultado = 1;
	}
	else{
		resultado = pow2_4(n - 1) + pow2_4(n - 1);
	}
	return resultado;
}

int main(void){
    unsigned long sol,res;

    cout << "n     pow2_1  pow2_2  pow2_3  pow2_4" << endl;

    for (unsigned i=0; i<= 500; i+=2){
        
        sol = (unsigned long) powl(2,i);
        cout << i << "\t";
    
        calls_pow2_1=0;
        calls_pow2_2=0;
        calls_pow2_3=0;
        calls_pow2_4=0;

        res=pow2_1(i);
        if (res!=sol){cout << "Error in pow2_1(n): incorrect result"; exit(1);}

        res=pow2_2(i);
        if (res!=sol){cout << "Error in pow2_2(n): incorrect result"; exit(1);}

        res=pow2_3(i);
        if (res!=sol){cout << "Error in pow2_3(n): incorrect result"; exit(1);}

        /* pow2_4 can not be computed with (not so) big values of n...*/  
        if (i<=32){	
          res=pow2_4(i);
          if (res!=sol){cout << "Error in pow2_4(n): incorrect result"; exit(1);}
        }

        cout << calls_pow2_1 << "\t"; 
        cout << calls_pow2_2 << "\t"; 
        cout << calls_pow2_3 << "\t";
        if (calls_pow2_4) 
		cout  << calls_pow2_4;
        cout  << endl;
    }
}

