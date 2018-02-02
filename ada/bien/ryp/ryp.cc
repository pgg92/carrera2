#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include "time.h"
#include <climits>
using namespace std;

int **m;

class Node;
class Caminante{
friend istream &operator>>(istream &is, Caminante &a);
friend ostream &operator<<(ostream &os, const Caminante &a);
	friend class Node;
	private:
		vector<vector<int> > m;
		int f, c;
		int generados, podados;
	public:
		int getGenerados() const{ return generados;}
		int getPodados() const { return podados; }
		void incPodados() {podados++;}
		void incGenerados() {generados++;}
		void clear(){
			f = 0;
			c = 0;
			generados = 0;
			podados = 0;
			m.clear();
		}
		int getFilas() const { return f;}
		int getColumnas() const { return c;}
};
istream &operator>>(istream &fich, Caminante &a){
	string linea;
	fich >> a.f >> a.c;
	vector<vector<int> > ma(a.f, vector<int>(a.c));
	for(int i = 0; i < a.f; i++){
		for(int j = 0; j < a.c; j++){
			fich >> ma[i][j];			
		}
	}
	a.m = ma;
	return fich;
}
ostream &operator<<(ostream &os, const Caminante &a){
	for(int i = 0; i < a.f; i++){
		for(int j = 0; j < a.c; j++){
			os << a.m[i][j] << " ";
		}
		os << endl;
	}
	os << "generados: " << a.generados << endl;
	os << "podados: " << a.podados << endl;
	return os;
}

class Node{
	private:
		static Caminante datos; // cada nodo tiene los datos del problema.
		vector<pair<int, int> > x; // camino recorrido hasta el momento.
		int f, c; // fila y columna actual
		int valor; // coste acumulado
	public:
		int getValor() const{
			return valor;
		}
		int getFilaActual() const{
			return f;
		}
		int getColumnaActual() const{
			return c;
		}
		Node(){
			f = 0;
			c = 0;
			valor = datos.m[0][0];
			x.push_back(pair<int, int>(0, 0));		
		}
		static Node initialNode(const Caminante &_d){
			datos = _d;
			return Node();
		}
		// comprueba si he tomado las decisiones
		bool isTerminal() const{
			return f == datos.f - 1 && c == datos.c - 1;
		}
		// comprobamos si estoy dentro de la matriz
		bool isFeasible() const{
			return f >= 0 && f < datos.f && c >= 0 && c < datos.c;
		}
		// valor de la solucion acumulada hasta el 
		// momento, cuando sea terminal sera el 
		// valor de la solucion.
		int value() const{
			return valor;
		}
		// devuelve el conjunto de nodos resultado de avanzar desde el nodo actual
		// en las 3 direcciones
		// mi expand solo genera nodos factibles puedo quitar la comprobacion de si
		// es factible del bucle principal!!
		vector<Node> expand() const{
			vector<Node> hijos;			
			int i;
			Node nuevo1(*this);
			nuevo1.f++;
			nuevo1.c++;
			nuevo1.x.push_back(pair<int, int>(nuevo1.f, nuevo1.c));		
			if(nuevo1.isFeasible()){
				nuevo1.valor += datos.m[nuevo1.f][nuevo1.c];
				hijos.push_back(nuevo1);
			}
			Node nuevo2(*this);
			nuevo2.f++;
			nuevo2.x.push_back(pair<int, int>(nuevo2.f, nuevo2.c));		
			if(nuevo2.isFeasible()){			
				nuevo2.valor += datos.m[nuevo2.f][nuevo2.c];
				hijos.push_back(nuevo2);
			}
			Node nuevo3(*this);
			nuevo3.c++;
			nuevo3.x.push_back(pair<int, int>(nuevo3.f, nuevo3.c));		
			if(nuevo3.isFeasible()){			
				nuevo3.valor += datos.m[nuevo3.f][nuevo3.c];
				hijos.push_back(nuevo3);
			}
			return hijos;
		}
		// estimacion optimista para este nodo, una solucion que es mejor
		// que la solucion optima de este nodo, poda este nodo.
		// estimacion trivial:
		//		- suponer que el coste de todas las casillas hasta el
		int optimistic_b() const{			
			int value, d;
			if(c > f){
				d = datos.c - 1 - c;
				d = d + datos.f - 1 - (f + d);
			}
			else{
				d = datos.f - 1 - f;
				d = d + datos.c - 1 - (c + d);
			}
			value = d + valor;
			return value;
		}
		// estimacion pesimista, una solucion que esta por encima o igual
		// de la solucion optima, poda otros nodos.
		double pessimistic_b() const{
			int i, j, peso;
			i = f;	// fila y columna por la que voy.
			j = c;
			peso = valor;	// valor acumulado hasta el momento.
			while(i != datos.f - 1 || j != datos.c - 1){
				if(i == datos.f - 1){	// utlima fila, siempre a la derecha.
					j++;
				}
				else{
					if(j == datos.c - 1){ // utlima columna, siempre a la izquierda.
						i++;
					}
					else{
						if(datos.m[i+1][j+1] <= datos.m[i+1][j] && datos.m[i+1][j+1] <= datos.m[i][j+1]){
							i++;
							j++;
						}
						else{
							if(datos.m[i][j + 1] <= datos.m[i + 1][j] && datos.m[i][j + 1] <= datos.m[i + 1][j + 1]){
								j++;
							}
							else{
								i++;
							}
						}
					}
				}
				peso = peso + datos.m[i][j];
			}
			return peso;
		}
		void imprimir() const{
			unsigned i, j, k;
			cout << "valor: " << valor << endl;
			for(i = 0; i < x.size(); i++){
				cout << "(" << x[i].first << "," << x[i].second << ")";
			}
			cout << endl;
			k = 0;
			for(i = 0; i < datos.f; i++){
				for(j = 0; j < datos.c; j++){
					if(k < x.size() && i == x[k].first && j == x[k].second){
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
};


Caminante Node::datos; 

class mycomp{
	public:
		bool operator()(const Node &n1, const Node &n2) const{
			return n1.optimistic_b() > n2.optimistic_b();
		}
};

typedef Node Solution;
typedef Caminante Problem;
typedef double Value;
typedef priority_queue<Node, vector<Node>, mycomp> myqueue;

// Node BB(Alfarero a)
Solution BB(Problem &p){
	Node init = Node::initialNode(p);
	Node best; // inicializar la variable estatica con el problema despues de leero.
	Value pb = init.pessimistic_b();
	myqueue q;

	const int x = p.getFilas();
	const int y = p.getColumnas();
	m = new int * [x];
	for(int i = 0; i < x; i++){
		m[i] = new int [y];
		for(int j = 0; j < y; j++){
			m[i][j] = INT_MAX;
		}
	}
	q.push(init);
	while(!q.empty()){
		Node n = q.top(); // cojemos el mejor
		q.pop(); // quito el mejor de la cola
		// compruebo si cota superior puedo mejorar pb.
		// si lo mejor que me puede pasar es menor que el 
		// camino actual, es que a lo mejor lo puedo mejorar.		
		if(n.getValor() < m[n.getFilaActual()][n.getColumnaActual()]){		
			m[n.getFilaActual()][n.getColumnaActual()] = n.getValor();
			if(n.optimistic_b() <= pb){
				pb = min(pb, n.pessimistic_b()); // a ver si mejoro la solucion con una solucion real de este nodo (aunque no la mejor)
				if(n.isTerminal())
					best = n;
				else{
					for(Node sel : n.expand()){
						//if(sel.isFeasible()){ // cuando generamos
						p.incGenerados();				
						q.push(sel);
						//}
					}
				}
			}
			else{
				p.incPodados();
			}
		}
	}
	return best;
}

int main(int argc, char *argv[]){
	ifstream fich;
	Caminante a;
	string vacia;

	int n = 1;
	double inicio, fin, time;
	int rcalls;
	if(argc == 2){
		fich.open(argv[1]);
		if(fich.is_open()){
			//while(!fich.eof()){
				a.clear();
				fich >> a;
				cout << "Problem " << n << ": " << endl;  	
				inicio = clock();
				Solution s = BB(a);
				fin = clock();	
				s.imprimir();
				time = (fin-inicio)/((double)CLOCKS_PER_SEC);				
				cout << "CPU elapsed time in seconds: " << time << endl;
				cout << "Generados: " << a.getGenerados() << endl;
				cout << "Podados: " << a.getPodados() << endl;
				// cout << a << endl;
				fich.get(); // lee el salto de linea
				fich.get(); // le la linea vacia
				n++;
			//}			
			fich.close();
		}
	}
	return 0;	
}







