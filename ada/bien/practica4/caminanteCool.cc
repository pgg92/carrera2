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
int voraz(vector<vector<int> > &m, int f, int c, vector<pair<int, int> > &a){
	int i, j, peso;

	i = 0;
	j = 0;
	peso = m[0][0];
	while(i != f - 1 || j != c - 1){
		a.push_back(pair<int, int>(i, j));
		if(i == f - 1){		// utlima fila, siempre a la derecha.
			j++;
		}
		else{
			if(j == c - 1){ // utlima columna, siempre a la izquierda.
				i++;
			}
			else{
				if(m[i+1][j+1] <= m[i+1][j] && m[i+1][j+1] <= m[i][j+1]){
					i++;
					j++;
				}
				else{
					if(m[i][j + 1] <= m[i + 1][j] && m[i][j + 1] <= m[i + 1][j + 1]){
						j++;
					}
					else{
						i++;
					}
				}
			}
		}
		peso = peso + m[i][j];
	}
	a.push_back(pair<int, int>(f-1, c-1));
	return peso;
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
int main(int argc, char *argv[]){
	int  f, c, peso;
	string nf;	
	bool leido, correcto, p;		
	vector<pair<int, int> > camino;
	vector<vector<int> > m;

	correcto = procesarArgumentos(argc, argv, nf, p);
	if(correcto == false){
		cout << "Error en argumentos. " << endl;
	}
	else{
		leido = leerFichero(nf, f, c, m);
		if(leido){
			peso = voraz(m, f, c, camino);
			cout << "Greedy: " << peso << endl;
			if(p){
				imprimirCamino(camino, f, c);	
			}
		}
		else{
			cout << "eat my cock!" << endl;
		}
	}
	return 0;
}


