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
	// Si hay un sensor ahi
	int tipoSensor;
	// 1: bidireccional, 2: horizontal, 3: vertical.
	Casilla () {
		laser = 0;
		ocupado = false;
		tipoSensor = -1;
	}
};

typedef vector< vector <Casilla> > Grilla;

vector< vector< int > > ej3(Grilla g) {
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
