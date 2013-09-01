#include <string>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <stdio.h>

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
	vector<int> restricciones;
	//0: horizontal, 1: vertical, 2: bidireccional.
	int i, j;
	Casilla () {
		laser = 0;
		ocupado = false;
		tipoSensor = -1;
		restricciones.push_back(1);
		restricciones.push_back(1);
		restricciones.push_back(1);		
		i = 0;
		j = 0;
	}
};
bool haySolucion;
typedef vector< vector <Casilla> > Grilla;
queue<Casilla*> casillasLibres;
Grilla g;
Grilla gMejor;
long int mejorCosto;
long int costoActual=0;
int cantSensores=0;
int mejorCantSensores=0;


void mostrar(Grilla g, string parametro) {
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			if (parametro=="tipo") {
				cout << g[i][j].tipo << " ";
			}
			if (parametro=="laser") {
				if (g[i][j].laser == 1)
					cout << "-" << " ";
				else if (g[i][j].laser == 2)
					cout << "|" << " ";
				else if (g[i][j].laser == 3)
					cout << "+" << " ";
				else
					cout << "O" << " ";
			}
			if (parametro=="restricciones") {
				if (g[i][j].ocupado)
					cout << "[X,X,X]" << " ";
				else
					printf("[%i,%i,%i] ", g[i][j].restricciones[0], g[i][j].restricciones[1], g[i][j].restricciones[2]);
			}
		}
		cout << endl;
	}
	if (parametro=="casillasLibres") {
		queue<Casilla*> tmp;
		while(!casillasLibres.empty()) {
			Casilla* c = casillasLibres.front(); casillasLibres.pop();
			tmp.push(c);
			printf("(%i, %i) ", c->i, c->j);
		}
		casillasLibres = tmp;
		cout << endl;
	}
	cout << endl;
}

bool chequearSolucion() {
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) { //Por cada casilla 
			if (g[i][j].tipo == 1)  //Si es piso
				if (g[i][j].laser == 0 && !g[i][j].ocupado)
					return false;					
			if (g[i][j].tipo == 2)  //Si es importante
				if (g[i][j].laser != 3)
					return false;
		}
	}
		
	return true;
}

void laserVertical(int i, int j, string sacarOPoner) {
	int iAnterior=i, jAnterior=j; //Me guardo los valores anteriores por que voy a tener q restaurarlos
	int ancho=g.size(); //Obtengo el ancho y alto del la matriz
	while (i<ancho && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia la derecho
		if (sacarOPoner=="SACAR") { //Si tengo que sacarlo
			if (g[i][j].laser == 3) //Me fijo si tiene dos lasers al mismo tiempo
				g[i][j].laser = 1; //DEJO EL QUE NO ES EL QUE QUIERO SACAR
			else
				g[i][j].laser = 0; //NO DEJO NINGUNO
		}
		else if (sacarOPoner=="PONER") {
			if (g[i][j].laser == 1)
				g[i][j].laser = 3;
			else
				g[i][j].laser = 2;
		}
		i++;
	}
	i = iAnterior;
	while(i>=0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia la izquierda
		if (sacarOPoner=="SACAR") {
			if (g[i][j].laser == 3)
				g[i][j].laser = 1;
			else
				g[i][j].laser = 0;
		}
		else if (sacarOPoner=="PONER") {
			if (g[i][j].laser == 1)
				g[i][j].laser = 3;
			else
				g[i][j].laser = 2;
		}
		i--;
	}
	return;
}

void laserHorizontal(int i, int j, string sacarOPoner) {
	int iAnterior=i, jAnterior=j; //Me guardo los valores anteriores por que voy a tener q restaurarlos
	int alto=g[i].size(); //Obtendo el ancho y alto del la matriz
	while(j<alto && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia abajo
		if (sacarOPoner=="SACAR") {
			if (g[i][j].laser == 3)
				g[i][j].laser = 2;
			else
				g[i][j].laser = 0;
		}
		else if (sacarOPoner=="PONER") {
			if (g[i][j].laser == 2)
				g[i][j].laser = 3;
			else
				g[i][j].laser = 1;
		}
		j++;
	}
	j = jAnterior;
	while(j>=0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia arriba
		if (sacarOPoner=="SACAR") {
			if (g[i][j].laser == 3)
				g[i][j].laser = 2;
			else
				g[i][j].laser = 0;
		}
		else if (sacarOPoner=="PONER") {
			if (g[i][j].laser == 2)
				g[i][j].laser = 3;
			else
				g[i][j].laser = 1;
		}
		j--;
	}
	return;
}

void restringVertical(int i, int j) {
	int iAnterior=i, jAnterior=j; //Me guardo los valores anteriores por que voy a tener q restaurarlos
	int ancho=g.size(), alto=g[i].size(); //Obtendo el ancho y alto del la matriz
	i++;
	while (i<ancho && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia la derecho
		g[i][j].restricciones[1] = 0;
		g[i][j].restricciones[2] = 0;
		i++;
	}
	i = iAnterior;
	i--;
	while(i>=0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia la izquierda
		g[i][j].restricciones[1] = 0;
		g[i][j].restricciones[2] = 0;
		i--;
	}
	return;
}

void restringHorizontal(int i, int j) {
	int iAnterior=i, jAnterior=j; //Me guardo los valores anteriores por que voy a tener q restaurarlos
	int ancho=g.size(), alto=g[i].size(); //Obtendo el ancho y alto del la matriz
	j++;
	while(j<alto && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia abajo
		g[i][j].restricciones[0] = 0;
		g[i][j].restricciones[2] = 0;
		j++;
	}
	j = jAnterior-1;
	while(j>=0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia arriba
		g[i][j].restricciones[0] = 0;
		g[i][j].restricciones[2] = 0;
		j--;
	}
	return;
}

void restringirCasillasPorImportante(int i, int j) {
	int iAnterior=i, jAnterior=j; //Me guardo los valores anteriores por que voy a tener q restaurarlos
	int ancho=g.size(), alto=g[i].size(); //Obtendo el ancho y alto del la matriz
	j++;
	while(j<alto && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia abajo
		g[i][j].restricciones[1] = 0;
		j++;
	}
	j = jAnterior-1;
	while(j>=0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia arriba
		g[i][j].restricciones[1] = 0;
		j--;
	}
	j = jAnterior;
	i++;
	while (i<ancho && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia la derecho
		g[i][j].restricciones[0] = 0;
		i++;
	}
	i = iAnterior;
	i--;
	while(i>=0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia la izquierda
		g[i][j].restricciones[0] = 0;
		i--;
	}
	return;
}

void backtrack() {
	//SI NO TENGO MAS CASILLAS QUE ASIGNAR ENTONCES QUEIRE DECIR QUE TERMINE Y DEBERIA SER UNA SOLUCION
	if (costoActual >= mejorCosto)
		return;
	if (casillasLibres.empty()) {
		if (chequearSolucion()) { //CHEQUEO SI ES UNA SOLUCION
			if (costoActual < mejorCosto) {
				haySolucion = true;
				mejorCosto = costoActual;
				gMejor = g;	
				mejorCantSensores = cantSensores;
			}
		}
		return;
	}
	Casilla* casillaActual = casillasLibres.front();  //SACO DE LA LISTA LA CASILLA EN LA CUAL VOY A INTENTAR METER COSAS
	casillasLibres.pop();
	if (casillaActual->laser > 0) {
		backtrack();
		casillasLibres.push(casillaActual);
		return;
	} else {
		//LLAMADA A BACKTRACKING CON BIDIRECCIONAL
		if (casillaActual->restricciones[2]){ //LLAMADA A BACKTRACKING CON BIDIRECCIONAL
			//LA ACCION DE ASIGNARLE A LA CASILLA LA INFORMACION QUE DICE QUE HAY UN SENSOR
			casillaActual->ocupado = true;
			casillaActual->tipoSensor = 1;
			casillaActual->laser = 3;
			//LUEGO TRAZO EL LASER QUE GENERA EL SENSOR QUE ACABO DE PONER 
			laserVertical(casillaActual->i, casillaActual->j, "PONER");
			laserHorizontal(casillaActual->i, casillaActual->j, "PONER");
			//ACTUALIZO MI COSTO ACTUAL PARA HACER LA PODA
			costoActual = costoActual + 6000;
			cantSensores++;
			//HAGO LA LLAMADA RECURSIVA, SI DEVUELVE CERO ES POR QUE LLEGUE A UNA SOLUCION
			backtrack();
			cantSensores--;
			costoActual = costoActual - 6000;
			//COMO NO DEVOLVIO CERO, ENTONCES RESTAURO EL TRAZADO DE LASER DE LAS CASILLAS QUE AFECTA EL SENSOR QUE PUSE
			laserVertical(casillaActual->i, casillaActual->j, "SACAR");
			laserHorizontal(casillaActual->i, casillaActual->j, "SACAR");
		}
		//LLAMADA A BACKTRACKING CON UNIDIRECCIONAL
		if (casillaActual->restricciones[0]){ //LLAMADA A BACKTRACKING CON HORIZONTAL
			//LA ACCION DE ASIGNARLE A LA CASILLA LA INFORMACION QUE DICE QUE HAY UN SENSOR
			casillaActual->ocupado = true;
			casillaActual->tipoSensor = 2;
			casillaActual->laser = 1;
			//LUEGO ME GUARDO EL ESTADO ANTERIOR DE LAS CASILLAS QUE VOY A RESTRINGIR
			vector< vector <int> >cache;
			for (int i = 0; i < g.size(); ++i)
				cache.push_back(g[i][casillaActual->j].restricciones);
			restringVertical(casillaActual->i, casillaActual->j);
			//LUEGO TRAZO EL LASER QUE GENERA EL SENSOR QUE ACABO DE PONER
			laserHorizontal(casillaActual->i, casillaActual->j, "PONER");
			//ACTUALIZO MI COSTO ACTUAL PARA HACER LA PODA2
			costoActual = costoActual + 4000;
			cantSensores++;
			backtrack();
			cantSensores--;
			costoActual = costoActual - 4000;
			//COMO NO DEVOLVIO CERO, ENTONCES RESTAURO EL TRAZADO DE LASER DE LAS CASILLAS QUE AFECTA EL SENSOR QUE PUSE
			laserHorizontal(casillaActual->i, casillaActual->j, "SACAR");
			//RESTAURO TAMBIEN LAS RESTRICCIONES DE LAS OTRAS CASILLAS.
			for (int i = 0; i < cache.size(); ++i)
				g[i][casillaActual->j].restricciones = cache[i];
		}
		if (casillaActual->restricciones[1]){ //LLAMADA A BACKTRACKING CON VERTICAL
			//LA ACCION DE ASIGNARLE A LA CASILLA LA INFORMACION QUE DICE QUE HAY UN SENSOR
			casillaActual->ocupado = true;
			casillaActual->tipoSensor = 3;
			casillaActual->laser = 2;
			//LUEGO ME GUARDO EL ESTADO ANTERIOR DE LAS CASILLAS QUE VOY A RESTRINGIR
			vector< vector <int> >cache;			
			for (int i = 0; i < g[casillaActual->i].size(); ++i)
				cache.push_back(g[casillaActual->i][i].restricciones);
			restringHorizontal(casillaActual->i, casillaActual->j);
			//LUEGO TRAZO EL LASER QUE GENERA EL SENSOR QUE ACABO DE PONER
			laserVertical(casillaActual->i, casillaActual->j, "PONER"); 
			//ACTUALIZO MI COSTO ACTUAL PARA HACER LA PODA
			costoActual = costoActual + 4000;
			cantSensores++;
			//HAGO LA LLAMADA RECURSIVA, SI DEVUELVE CERO ES POR QUE LLEGUE A UNA SOLUCION
			backtrack();
			cantSensores--;
			costoActual = costoActual - 4000;
			//COMO NO DEVOLVIO CERO, ENTONCES RESTAURO EL TRAZADO DE LASER DE LAS CASILLAS QUE AFECTA EL SENSOR QUE PUSE
			laserVertical(casillaActual->i, casillaActual->j, "SACAR");
			//RESTAURO TAMBIEN LAS RESTRICCIONES DE LAS OTRAS CASILLAS.
			for (int i = 0; i < cache.size(); ++i)
				g[casillaActual->i][i].restricciones = cache[i];

		}

		//LLAMADA A BACKTRACKING CON VACIO
		casillaActual->ocupado = false;
		casillaActual->tipoSensor = -1;
		casillaActual->laser = 0;
		backtrack();
		//RECUPERO LA CASILLA QUE QUEDO IGUAL QUE HACER LA LLAMADA SIN TOCAR NADA DE ARRIBA
		casillasLibres.push(casillaActual);
		return;
	}
}

void ej3() {
	queue<Casilla*> casillasLibresEnLimpio; //RESTAURAR EL CASILLEROlIBRE POR UNO QUE ESTE EN LIMPIO.
	casillasLibres = casillasLibresEnLimpio;
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) { //Por cada casilla 
			if (g[i][j].tipo == 2)
				restringirCasillasPorImportante(i, j); //Restringo sus casillas horizontales y verticales.
			if (g[i][j].tipo == 1) 
				casillasLibres.push(&(g[i][j]));
		}
	}

	backtrack();
	return;
}

int main() {
	// stdin = freopen("./ej3.in", "r", stdin);
	char termino = ' ';
	while (termino != '#') {
		haySolucion = false;
		int n, m;
		Grilla gEnLimpio; //A LA PRIMERA VUELTA ESTA TODO BIEN, PERO CUANDO SE EJECUTA POR SEGUNDA VEZ, HAY INFORMACION EN LA GRILLA DE LA VEZ ANTERIOR
		g = gEnLimpio; //ENTONCES CREO UNA GRILLA EN LIMPIO Y LA REEMPLAZO
		gMejor = gEnLimpio;
		cin >> n;
		cin >> m;
		mejorCosto = n*m*6000; //NECESITO TENER UN COSTO MAXIMO PARA IR MEJORANDOLO EN CADA SOLUCION, EL INICIAL ES EL MAXIMO QUE SE PODRIA OBTENER.
		cantSensores = 0;
		costoActual = 0;
		mejorCantSensores = 0;
		
		vector<Casilla> filaC;
		Casilla c;

		for (int i = 0; i < n; ++i) {
			g.push_back(filaC);
			for (int j = 0; j < m; ++j) {
				cin >> c.tipo;
				c.i = i;
				c.j = j;
				g[i].push_back(c);
			}
		}
		auto t1 = chrono::high_resolution_clock::now();

		ej3();
		
		auto t2 = chrono::high_resolution_clock::now();
		auto x = chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();

		cerr << n+m << " " << x << endl;

		if (mejorCosto == n*m*6000 && !haySolucion)
			cout << "-1" << endl;
		else {
			// mostrar(gMejor, "laser");
			// mostrar(gMejor, "restricciones");
			cout << mejorCantSensores << " " << mejorCosto;
			cout << endl;
			for (int i = 0; i < gMejor.size(); ++i) {
				for(int j = 0; j < gMejor[i].size(); ++j) {
					if (gMejor[i][j].ocupado) {
						cout << gMejor[i][j].tipoSensor << " " << i << " " << j << endl;
						// if (gMejor[i][j].tipoSensor == 1) {
						// 	cout << "bidireccional (" << i << "," << j << ")";
						// 	cout << endl;
						// }
						// if (gMejor[i][j].tipoSensor == 2) {
						// 	cout << "horizontal (" << i << "," << j << ")";
						// 	cout << endl;
						// }
						// if (gMejor[i][j].tipoSensor == 3) {
						// 	cout << "vertical (" << i << "," << j << ")";
						// 	cout << endl;
						// }
					}
				}
			}
		}
		termino = (cin >> ws).peek();
		cout << endl;
	}
	return 0;
}
