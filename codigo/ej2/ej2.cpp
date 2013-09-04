#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

/* -----------------------------------------

Referencia: http://en.cppreference.com/w/cpp/algorithm/sort
Complejidad:
  -Sort : O(n.log(n))

--------------------------------------------*/

using namespace std;

typedef pair<int,pair<int, int> > Curso;
typedef vector<Curso> Cursos;

//VARIABLES IMPORTANTES
vector<bool> seleccionados;
int cantSeleccionados;
Cursos cs;

bool customLess (Curso i,Curso j)
{ return (i.second.second < j.second.second); }


void filtrarSolapamientos()
{
    Curso anterior;
    anterior = cs[0];
    seleccionados[0] = true;
    cantSeleccionados++;
    for(int i = 1; i < cs.size(); ++i) {
        if (cs[i].second.first > anterior.second.second) { //VEO SI EL INICIO DE UN CURSO ES DESPUES DEL TERMINO DEL ANTERIOR (DEL ANTERIOR AGREGADO).
    		anterior = cs[i];
    		seleccionados[cs[i].first] = true;
    		cantSeleccionados++;
    	}
    }
    return;
}


vector<int> ej2() {
	seleccionados.clear();
	cantSeleccionados = 0;
	vector<int> res;
	if (cs.size() == 0) {
		res.push_back(0);
		return res;
	} else {
		for(int i = 0; i < cs.size(); ++i)
			seleccionados.push_back(false);
			sort(cs.begin(), cs.end(),customLess);
			filtrarSolapamientos();
			res.push_back(cantSeleccionados);
			for (int i = 0; i < seleccionados.size(); ++i)
				if (seleccionados[i])
					res.push_back(i+1);
					return res;
	}
}

int main() {
    char termino = ' ';
	while (termino != '#') {
		int ci,cf;
		int cantCursos;
		cs.clear();
		cin >> cantCursos;
		for (int i = 0; i < cantCursos; ++i) {
			cin >> ci;
			cin >> cf;
			cs.push_back(make_pair(i, make_pair(ci, cf)));
		}


		auto t1 = chrono::high_resolution_clock::now();
		vector<int> res = ej2();
		auto t2 = chrono::high_resolution_clock::now();
		auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
		cerr << cantCursos << " " << x << endl;

		
		for (int i = 0; i < res.size(); ++i)
			cout << res[i] << " ";
		cout << endl;
		termino = (cin >> ws).peek();
	}
	return 0;
}
