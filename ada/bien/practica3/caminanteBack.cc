#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;


bool leerFichero(string nombreFichero, int &f, int &c, vector<vector<int> > &m){
	bool leido = false;
	string linea;
	fstream fich;

	fich.open(nombreFichero.c_str(), ios::in);
	if(fich.is_open()){
		fich >> f >> c;
		vector<vector<int> > ma(f, vector<int>(c));
		for(int i = 0; i < f; i++){
			for(int j = 0; j < c; j++){
				fich >> ma[i][j];			
			}
		}
		leido = true;
		m = ma;
		fich.close();
	}	
	return leido;
}


bool procesarArgumentos(int argc, char *argv[], string &nf, bool &p){
	bool correcto;
	correcto = true;
	// comprobar que las opcion no se repiten
	p = false;
	if(argc >= 3 && argc <= 4){
		for(int i = 1; i < argc && correcto; i++){
			if(!strcmp(argv[i], "-p")){
				p = true;
			}
			else{
				if(!strcmp(argv[i], "-f")){
					if(i + 1 <= argc - 1){
						nf = argv[i + 1];
						i++;
					}
					else{
						correcto = false;					
					}
				}
				else{
					correcto = false;
				}
			}
		}
	}
	else{
		correcto = false;
	}
	return correcto;

}

int valor_solucion(vector<vector<int> > &m, vector<pair<int, int> > &sol, int k){
	int total, i;
	total = 0;
	for(i = 0; i < k; i++){
		total = total + m[sol[i].first][sol[i].second];
	}
	return total;
}

// m => matriz con el camino
// kf, kc => posicion actual
// k paso actual. (tendremos rellenadas del vector k posiciones)
// x => solucion hasta el momento. (tamaño filas + columnas)
// f, c => ultima celda de la matriz
// sol_mejor => mejor solucion encontrada hasta el momento
// v_mejor mejor_valor encontrado hasta el momento

// primera llamada
// back(m, 0, 0, x, 0, f, c, sol_mejor, INT_MIN);
void back(vector<vector<int> > &m, int kf, int kc, vector<pair<int, int> > &x, int k, int f, int c, vector<pair<int, int> > &sol_mejor, int &v_mejor){
	int v_actual;
	// miramos si llegamos a solucion
		// y si la solucion mejora la solucion encontrada hasta el momento.
		// entonces se actualiza la mejor solucion con esa solucion.
	
	x[k] = pair<int,int>(kf, kc);
	k++;
	// llamada recursiva con todas las opciones.
	if(kf == f - 1 && kc == c - 1){
		v_actual = valor_solucion(m, x, k); 
		// estamos en solucion y la comparamos con la solucion actual.
		if(v_actual < v_mejor){
			v_mejor = v_actual;
			sol_mejor = x;
		}
	}
	else{
		if(kc == c - 1){
			back(m, kf + 1, kc, x, k, f, c, sol_mejor, v_mejor);
		}
		else{
			if(kf == f - 1){
				back(m, kf, kc + 1, x, k, f, c, sol_mejor, v_mejor);
			}
			else{
				back(m, kf + 1, kc, x, k, f, c, sol_mejor, v_mejor);
				back(m, kf, kc + 1, x, k, f, c, sol_mejor, v_mejor);
				back(m, kf + 1, kc + 1, x, k, f, c, sol_mejor, v_mejor);
			}
		}
	}
}

void imprimirCamino(vector<pair<int, int> > &camino, int f, int c){
	unsigned i, j;
//	vector<vector<char> > ma(f, vector<char>(c));

//	for(i = 0; i < f; i++){
//		for(j = 0; j < c; j++){
//			ma[i][j] = '.';
//		}
//	}
	for(i = 0; i < camino.size(); i++){
		cout << "(" << camino[i].first << "," << camino[i].second << ")";
//		m[camino[i].first()][camino[i].second()] = 'x';			
	}
//	cout << endl;
//	for(i = 0; i < f; i++){
//		for(j = 0; j < c; j++){
//			cout << m[i][j] << " ";
//		}
//		cout << endl;
//	}
	cout << endl;
	int k = 0;
	for(i = 0; i < f; i++){
		for(j = 0; j < c; j++){
			if(i == camino[k].first && j == camino[k].second){
				cout << "x";
				k++;
			}
			else{
				cout << ".";
			}
		}
		cout << endl;
	}

}
/*
	1 3 3
	1 2 2
	1 1 1

	k = 0
	x = {(0, 0), -, -, -, -}
*/
int main(int argc, char *argv[]){
	int  f, c, coste_menor;
	string nf;	
	bool leido, correcto, p;		
	vector<pair<int, int> > sol_mejor;
	vector<vector<int> > m;
	

	correcto = procesarArgumentos(argc, argv, nf, p);
	if(correcto == false){
		cout << "Error en argumentos. " << endl;
	}
	else{
		leido = leerFichero(nf, f, c, m);
		if(leido){
			coste_menor = INT_MAX; 
			vector<pair<int, int> > x(f + c - 1); // vector con la solucion actual.
			// back(m, 0, 0, x, 0, f, c, sol_mejor, INT_MIN);
			back(m, 0, 0, x, 0, f, c, sol_mejor, coste_menor);
			cout << "bASTRAK: " << coste_menor << endl;
			if(p){
				imprimirCamino(sol_mejor, f, c);	
			}
		}
		else{
			cout << "eat my cock!" << endl;
		}
	}
	return 0;
}


