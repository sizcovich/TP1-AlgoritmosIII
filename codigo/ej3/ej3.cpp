#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct casilla {
	int tipo;
	// 0: pared, 1: piso, 2: importante.
	int laser;
	// 0: libre, 1: laser horizontal, 2: laser vertical, 3: ambos.
	bool ocupado;
	// Si hay un sensor ahi
	int tipoSensor;
	// 1: bidireccional, 2: horizontal, 3: vertical.
};

typedef vector< vector <casilla> > grilla;

int main() {
	
	return 0;
}
