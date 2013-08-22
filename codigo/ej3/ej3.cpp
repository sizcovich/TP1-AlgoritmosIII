#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Casilla {
	int tipo;
	// 0: pared, 1: piso, 2: importante.
	int laser;
	// 0: libre, 1: laser horizontal, 2: laser vertical, 3: ambos.
	bool ocupado;
	// Si hay un sensor ahi.
	int tipoSensor;
	// 1: bidireccional, 2: horizontal, 3: vertical.
	int restricciones;
	//1: horizontal, 2: vertical, 3: ambos.
	Casilla () {
		laser = 0;
		ocupado = false;
		tipoSensor = -1;
		restricciones = 0;
	}
};

typedef vector< vector <Casilla> > Grilla;

void restringirCasillasPorImportante(int i, int j, Grilla &g) {
	/*
	Basicamente lo que hace esto es recorrer todas las casillas desde la casilla importante
	hacia las casillas izquierda, derecha, arriba y abajo para marcar las restricciones.
	Se termina de recorrer las casillas cuando toque el borde o cuando me choque con una pared.
	*/
	int iAnterior=i, jAnterior=j; //Me guardo los valores anteriores por que voy a tener q restaurarlos
	int ancho=g.size(), alto=g[i].size(); //Obtendo el ancho y alto del la matriz
	while (i<ancho && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia la derecho
		if (g[i][j].restricciones == 2 || g[i][j].restricciones == 3)
			g[i][j].restricciones = 3;
		else
			g[i][j].restricciones = 1;
		i++;
	}
	i = iAnterior;
	while(i>0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia la izquierda
		if (g[i][j].restricciones == 2 || g[i][j].restricciones == 3)
			g[i][j].restricciones = 3;
		else
			g[i][j].restricciones = 1;
		i--;
	}
	i = iAnterior;
	while(j<alto && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia abajo
		if (g[i][j].restricciones == 1 || g[i][j].restricciones == 3)
			g[i][j].restricciones = 3;
		else
			g[i][j].restricciones = 2;
		j++;
	}
	j = jAnterior;
	while(j>0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia arriba
		if (g[i][j].restricciones == 1 || g[i][j].restricciones == 3)
			g[i][j].restricciones = 3;
		else
			g[i][j].restricciones = 2;
		j--;
	}
}

void mostrar(Grilla g, string parametro) {
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			if (parametro=="tipo") {
				cout << g[i][j].tipo << " ";
			}
			if (parametro=="laser") {
				cout << g[i][j].laser << " ";
			}
			if (parametro=="restricciones") {
				if (g[i][j].tipo == 2)
					cout << "X" << " ";
				else
					cout << g[i][j].restricciones << " ";
			}
		}
		cout << endl;
	}
}


vector< vector< int > > ej3(Grilla g) {
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) { //Por cada casilla 
			if (g[i][j].tipo == 2) { //Si es importante
				restringirCasillasPorImportante(i, j, g); //Restringo sus casillas horizontales y verticales.
			}
		}
	}
	mostrar(g, "restricciones");











	vector < vector <int > > res;
	return res;
}

int main() {
	char termino = ' ';
	while (termino != '#') {
		int n, m;
		cin >> n;
		cin >> m;

		vector<Casilla> filaC;
		Casilla c;
		Grilla g;

		for (int i = 0; i < n; ++i) {
			g.push_back(filaC);
			for (int j = 0; j < m; ++j) {
				cin >> c.tipo;
				g[i].push_back(c);
			}
		}
		vector<vector<int> > res;
		res = ej3(g);
		for (int i = 0; i < res.size(); ++i) {
			for(int j = 0; j < res[i].size(); ++j) {
				cout << res[i][j] << " ";
			}
			cout << endl;
		}
		termino = (cin >> ws).peek();
	}
	return 0;
}
