#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

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
	int i, j;
	Casilla () {
		laser = 0;
		ocupado = false;
		tipoSensor = -1;
		restricciones = 0;
		i = 0;
		j = 0;
	}
};
queue<Casilla*> casillasLibres;
typedef vector< vector <Casilla> > Grilla;
Grilla g;

void restringirCasillasPorImportante(int i, int j) {
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

void mostrar(string parametro) {
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

void backtrack(queue<Casilla*> casillasLibres) {
	
	queue<Casilla*> ignorados;
	while(casillasLibres.front()->laser > 0) {
		ignorados.push(casillasLibres.front()); 
		casillasLibres.pop();
	}
	Casilla* casillaActual = casillasLibres.front(); 
	casillasLibres.pop();

	//LLAMADA A BACKTRACKING CON VACIO
	backtrack()

	if (casillaActual->restricciones != 3) {
		if (casillaActual->restricciones != 1){
			//LLAMADA A BACKTRACKING CON HORIZONTAL
			casillaActual.ocupado = true;
			casillaActual.tipoSensor = 3;
			casillaActual.laser = 2;
			//LLENA TODA COLUMNA
			restringVertical(casillaActual.i, casillaActual.j);
		}
		if (casillaActual->restricciones != 2){
			//LLAMADA A BACKTRACKING CON VERTICAL
			casillaActual.ocupado = true;
			casillaActual.tipoSensor = 3;
			casillaActual.laser = 2;
			//LLENA TODA COLUMNA
			restringHorizontal(casillaActual.i, casillaActual.j);
		}
	}

	//LLAMADA A BACKTRACKING CON BIDIRECCIONAL



	if (casillasLibres.empty()) {


	}





}




vector< vector< int > > ej3(Grilla g) {
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) { //Por cada casilla 
			if (g[i][j].tipo == 2) { //Si es importante
				if (g[i][j].tipo == 1) 
					casillasLibres.push(&(g[i][j]));
				restringirCasillasPorImportante(i, j); //Restringo sus casillas horizontales y verticales.
			}
		}
	}
	
	backtrack(casillasLibres);
	



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
				c.i = i;
				c.j = j;
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
