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

int recursiva(vector<vector<int> > &m, int i, int j){
	int s1, s2, s3;
	if(i == 0 && j == 0){
		return m[i][j];
	}
	else{
		if(i > 0 && j > 0)
			s1 = recursiva(m, i-1, j-1) + m[i][j];
		else
			s1 = INT_MAX;	
		if(j > 0)
			s2 = recursiva(m, i, j-1) + m[i][j];
		else
			s2 = INT_MAX;  
		if(i > 0)
			s3 = recursiva(m, i-1, j) + m[i][j];
		else
			s3 = INT_MAX;
		return min(min(s1, s2), s3);	
	}
}

/*
	ra(5, 5) -> ra(4, 4) -> ra(4, 5) -> ra(5, 4)
	ra(4, 5) -> ra(3, 4) -> ra(4, 4) *
*/
int recursivaAlmacen(vector<vector<int> > &m, int i, int j, vector<vector<int> > &a){
	int s1, s2, s3;

	if(a[i][j] == -1){
		if(i == 0 && j == 0){
			return a[i][j] = m[i][j];
		}
		else{
			if(i > 0 && j > 0)
				s1 = recursiva(m, i-1, j-1) + m[i][j];
			else
				s1 = INT_MAX;	
			if(j > 0)
				s2 = recursiva(m, i, j-1) + m[i][j];
			else
				s2 = INT_MAX;  
			if(i > 0)
				s3 = recursiva(m, i-1, j) + m[i][j];
			else
				s3 = INT_MAX;
			return a[i][j] = min(min(s1, s2), s3);	
		}
	}
	else{
		return a[i][j];
	}
}

bool procesarArgumentos(int argc, char *argv[], bool &ign, string &nf, bool &t, bool &p){
	bool correcto;
	correcto = true;
	// comprobar que las opcion no se repiten
	ign = t = p = false;
	if(argc >= 3 && argc <= 6){
		for(int i = 1; i < argc && correcto; i++){
			if(!strcmp(argv[i], "-t")){
				t = true;
			}
			else{
				if(!strcmp(argv[i], "-p")){
					p = true;
				}
				else{
					if(!strcmp(argv[i], "--ignore-recursive")){
						ign = true;
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
		}
	}
	else{
		correcto = false;
	}
	return correcto;
}
void inicializar(vector<vector<int> > &m){
	for(int i = 0; i < m.size(); i++){
		for(int j = 0; j < m[i].size(); j++){
			m[i][j] = -1;
		}
	}
}


/*
		m	0 1 2 3 4 
	  	0	7 2 3 1 1	
		1   2
		2	4
		3	2
		4	4

		a	0 	1 	2  	3 	4
		0	7. 	9.	12	13	14
		1	9.  x
		2 	13
		3	15
		4	19


*/
int iterative(vector<vector<int> > &m, int filas, int columnas, vector<pair<int, int> > &camino){
	int i, j;	
	vector<vector<int> > a(filas, vector<int>(columnas));
		
	a[0][0] = m[0][0];
	for(i = 1; i < m.size(); i++){
		a[i][0] = m[i][0] + a[i-1][0]; 
	}
	for(i = 1; i < m[0].size(); i++){
		a[0][i] = m[0][i] + a[0][i-1];
	}
	for(i = 1; i < m.size(); i++){
		for(j = 1; j < m[0].size(); j++){
			a[i][j] = min(a[i-1][j-1], min(a[i-1][j], a[i][j-1])) + m[i][j];
		}	
	}
	
	i = filas - 1;
	j = columnas - 1;
	while(i != 0 || j != 0){ // no regreso a la primera celda.
		camino.push_back(pair<int,int>(i, j));		
		if(i == 0){
			j--;
		}
		else{
			if(j == 0){
				i--;
			}
			else{
				if(a[i-1][j-1] < a[i-1][j] && a[i-1][j-1] < a[i][j-1]){
					i--; j--;
				}
				else{
					if(a[i-1][j] < a[i-1][j-1] && a[i-1][j] < a[i-1][j-1]){
						i--;
					}
					else{
						j--;
					}
				}
			}
		}
	}
	camino.push_back(pair<int,int>(0,0));
	return a[filas-1][columnas-1];
}

// dos vectores sin swap y dos variables.
int iterative2vectores(vector<vector<int> > &m, int filas, int columnas){
	int i, j, f_ant, f_act;	
	vector<vector<int> > a(2, vector<int>(columnas));
		
	a[0][0] = m[0][0];
	for(i = 1; i < columnas; i++){
		a[0][i] = m[0][i] + a[0][i-1];
	}
	f_ant = 0;
	f_act = 1;
	for(i = 1; i < filas; i++){
		for(j = 0; j < columnas; j++){
			if(j == 0){
				a[f_act][j] = a[f_ant][j] + m[i][j];
			}
			else{
				a[f_act][j] = min(a[f_act][j-1], min(a[f_ant][j], a[f_ant][j-1])) + m[i][j];
			}		
		}
		f_act = (f_act + 1) % 2;
		f_ant = (f_ant + 1) % 2;
	}	
	return a[f_act][columnas-1];
}

int iterative2vectoresSwap(vector<vector<int> > &m, int filas, int columnas){
	int i, j;	
	vector<vector<int> > a(2, vector<int>(columnas));
		
	a[0][0] = m[0][0];
	for(i = 1; i < columnas; i++){
		a[0][i] = m[0][i] + a[0][i-1];
	}
	for(i = 1; i < filas; i++){
		for(j = 0; j < columnas; j++){
			if(j == 0){
				a[1][j] = a[0][j] + m[i][j];
			}
			else{
				a[1][j] = min(a[1][j-1], min(a[0][j], a[0][j-1])) + m[i][j];
			}		
		}
		a[0].swap(a[1]);
	}	
	return a[0][columnas-1];
}

/*
int interative1vector(vector<vector<int> > &m, int filas, int columnas){
	int i, j;
	int diagonal; // guardo en diagonal el valor
					// actual no perderlo.
	vector<int> a(columnas);

	// el vector lo tenemos que rellenar tantas
	// veces como filas tengo.
	for(i = 0; i < columnas; i++){
		a[i] = INT_MAX;
	}
	for(j = 0; j < filas; j++){
		for(j = 0; j < columnas; j++){
			
		}
	}

	return a[a.size() - 1];	
}
*/

int main(int argc, char *argv[]){
	int  f, c;
	string nf;	
	bool leido, correcto, ign, t, p;		
	vector<pair<int, int> > camino;
	vector<vector<int> > m;
	correcto = procesarArgumentos(argc, argv, ign, nf, t, p);
	if(correcto == false){
		cout << "Error en argumentos. " << endl;
	}
	else{
		leido = leerFichero(nf, f, c, m);
		if(leido){
			cout << "Recursive: " << recursiva(m, f-1, c-1) << endl;
			vector<vector<int> > a(f, vector<int>(c));
			inicializar(a);
			cout << "Memoization: " << recursivaAlmacen(m, f - 1, c - 1, a) << endl;
			cout << "Iterative: " << iterative(m, f, c, camino) << endl;
			cout << "Iterative vector: " << iterative2vectoresSwap(m, f, c) << endl;
			cout << "A possible path: " << endl;
			for(int i = camino.size() - 1; i >= 0; i--){
				cout << "(" << camino[i].first << "," << camino[i].second << ")";
			}
			cout << endl;
		}
		else{
			cout << "Error. no se ha podido abrir el fichero " << nf << endl;
		}
	}	
	return 0;
}


