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
typedef vector< vector <Casilla> > Grilla;
queue<Casilla*> casillasLibres;
Grilla g;
Grilla gMejor;
long int mejorCosto;
long int costoActual=0;

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
	while(i>0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia la izquierda
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
	while(j>0 && g[i][j].tipo != 0) { //Aca voy desde el lugar importante hacia arriba
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
	return;
}

void restringHorizontal(int i, int j) {
	int iAnterior=i, jAnterior=j; //Me guardo los valores anteriores por que voy a tener q restaurarlos
	int ancho=g.size(), alto=g[i].size(); //Obtendo el ancho y alto del la matriz
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
	return;
}

void restringirCasillasPorImportante(int i, int j) {
	/*	Basicamente lo que hace esto es recorrer todas las casillas desde la casilla importante
	hacia las casillas izquierda, derecha, arriba y abajo para marcar las restricciones.
	Se termina de recorrer las casillas cuando toque el borde o cuando me choque con una pared.	*/
	restringVertical(i, j);
	restringHorizontal(i, j);
	return;
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

void backtrack() {
	//SI NO TENGO MAS CASILLAS QUE ASIGNAR ENTONCES QUEIRE DECIR QUE TERMINE Y DEBERIA SER UNA SOLUCION
	if (costoActual >= mejorCosto)
		return;
	if (casillasLibres.empty()) {
		if (chequearSolucion()) { //CHEQUEO SI ES UNA SOLUCION
			if (costoActual < mejorCosto) {
				mejorCosto = costoActual;
				gMejor = g;				
			}
		}
		return;
	}

	queue<Casilla*> ignorados;	//ACA VAN LOS ELEMENTOS QUE TIENEN UN LASER PASANDO POR EL Y NO LO USO PARA EL BACKTRACK
	while(casillasLibres.front()->laser > 0) {
		ignorados.push(casillasLibres.front()); 
		casillasLibres.pop();
	}
	Casilla* casillaActual = casillasLibres.front();  //SACO DE LA LISTA LA CASILLA EN LA CUAL VOY A INTENTAR METER COSAS
	Casilla* recuperarCasillaActual = casillaActual;
	casillasLibres.pop();

	//LLAMADA A BACKTRACKING CON VACIO
	backtrack();
	
	//LLAMADA A BACKTRACKING CON UNIDIRECCIONAL
	if (casillaActual->restricciones != 3) {
		if (casillaActual->restricciones != 1){ //LLAMADA A BACKTRACKING CON HORIZONTAL
			//LA ACCION DE ASIGNARLE A LA CASILLA LA INFORMACION QUE DICE QUE HAY UN SENSOR
			casillaActual->ocupado = true;
			casillaActual->tipoSensor = 2;
			casillaActual->laser = 1;
			//LUEGO ME GUARDO EL ESTADO ANTERIOR DE LAS CASILLAS QUE VOY A RESTRINGIR
			vector<Casilla> cache = g[casillaActual->j];
			for (int i = 0; i < g[casillaActual->i].size(); ++i)
				cache.push_back(g[casillaActual->i][i]);
			restringVertical(casillaActual->i, casillaActual->j);
			//LUEGO TRAZO EL LASER QUE GENERA EL SENSOR QUE ACABO DE PONER
			laserHorizontal(casillaActual->i, casillaActual->j, "PONER");
			//ACTUALIZO MI COSTO ACTUAL PARA HACER LA PODA
			costoActual = costoActual + 4000;
			backtrack();
			costoActual = costoActual - 4000;
			//COMO NO DEVOLVIO CERO, ENTONCES RESTAURO EL TRAZADO DE LASER DE LAS CASILLAS QUE AFECTA EL SENSOR QUE PUSE
			laserHorizontal(casillaActual->i, casillaActual->j, "SACAR");
			//RESTAURO TAMBIEN LAS RESTRICCIONES DE LAS OTRAS CASILLAS.
			for (int i = 0; i < cache.size(); ++i)
				g[casillaActual->i][i] = cache[i];

		}
		if (casillaActual->restricciones != 2){ //LLAMADA A BACKTRACKING CON VERTICAL
			//LA ACCION DE ASIGNARLE A LA CASILLA LA INFORMACION QUE DICE QUE HAY UN SENSOR
			casillaActual->ocupado = true;
			casillaActual->tipoSensor = 3;
			casillaActual->laser = 2;
			//LUEGO ME GUARDO EL ESTADO ANTERIOR DE LAS CASILLAS QUE VOY A RESTRINGIR
			vector<Casilla> cache = g[casillaActual->i];
			restringHorizontal(casillaActual->i, casillaActual->j);
			//LUEGO TRAZO EL LASER QUE GENERA EL SENSOR QUE ACABO DE PONER
			laserVertical(casillaActual->i, casillaActual->j, "PONER"); 
			//ACTUALIZO MI COSTO ACTUAL PARA HACER LA PODA
			costoActual = costoActual + 4000;
			//HAGO LA LLAMADA RECURSIVA, SI DEVUELVE CERO ES POR QUE LLEGUE A UNA SOLUCION
			backtrack();
			costoActual = costoActual - 4000;
			//COMO NO DEVOLVIO CERO, ENTONCES RESTAURO EL TRAZADO DE LASER DE LAS CASILLAS QUE AFECTA EL SENSOR QUE PUSE
			laserVertical(casillaActual->i, casillaActual->j, "SACAR");
			//RESTAURO TAMBIEN LAS RESTRICCIONES DE LAS OTRAS CASILLAS.
			g[casillaActual->i] = cache;
		}
	}

	//LLAMADA A BACKTRACKING CON BIDIRECCIONAL
	casillaActual->ocupado = true;
	casillaActual->tipoSensor = 1;
	casillaActual->laser = 3;
	
	//LUEGO ME GUARDO EL ESTADO ANTERIOR DE LAS CASILLAS QUE VOY A RESTRINGIR HORIZONTALMENTE
	vector<Casilla> cache = g[casillaActual->i];
	restringHorizontal(casillaActual->i, casillaActual->j);
	//LUEGO TRAZO EL LASER QUE GENERA EL SENSOR QUE ACABO DE PONER 
	laserVertical(casillaActual->i, casillaActual->j, "PONER");
	
	//LUEGO ME GUARDO EL ESTADO ANTERIOR DE LAS CASILLAS QUE VOY A RESTRINGIR VERTICALMENTE
	vector<Casilla> cache2 = g[casillaActual->j];
	for (int i = 0; i < g[casillaActual->i].size(); ++i)
		cache2.push_back(g[casillaActual->i][i]);
	restringVertical(casillaActual->i, casillaActual->j);
	//LUEGO TRAZO EL LASER QUE GENERA EL SENSOR QUE ACABO DE PONER
	laserHorizontal(casillaActual->i, casillaActual->j, "PONER");
			 
	//ACTUALIZO MI COSTO ACTUAL PARA HACER LA PODA
	costoActual = costoActual + 6000;
	//HAGO LA LLAMADA RECURSIVA, SI DEVUELVE CERO ES POR QUE LLEGUE A UNA SOLUCION
	backtrack();
	costoActual = costoActual - 6000;
	//COMO NO DEVOLVIO CERO, ENTONCES RESTAURO EL TRAZADO DE LASER DE LAS CASILLAS QUE AFECTA EL SENSOR QUE PUSE
	laserVertical(casillaActual->i, casillaActual->j, "SACAR");
	//RESTAURO TAMBIEN LAS RESTRICCIONES DE LAS OTRAS CASILLAS.
	g[casillaActual->i] = cache;
	
	//COMO NO DEVOLVIO CERO, ENTONCES RESTAURO EL TRAZADO DE LASER DE LAS CASILLAS QUE AFECTA EL SENSOR QUE PUSE
	laserHorizontal(casillaActual->i, casillaActual->j, "SACAR");
	//RESTAURO TAMBIEN LAS RESTRICCIONES DE LAS OTRAS CASILLAS.
	for (int i = 0; i < cache2.size(); ++i)
		g[casillaActual->i][i] = cache2[i];
			
	/* 
	AHORA LO QUE PASO FUE QUE YA SE EJECUTARON TODOS LOS BACKTRACK Y LLEGUE ACA
	TENGO QUE RESTAURAR:
	1) casillaActual: PONERLA COMO ESTABA AL RPINCIPIO (hace una variable temporal para guardar el casillero como estaba antes).
	2) METERLA DE NUEVO EN casillerosLibres.
	3) SI HAY CASILLEROS EN "ignorados" TAMBIEN VOLVERLOS A METER.
	*/
	casillasLibres.push(recuperarCasillaActual);
	while(!ignorados.empty()) {
		Casilla* casillaIgnorada = ignorados.front();
		ignorados.pop();
		casillasLibres.push(casillaIgnorada);
	}
	return;

}

vector< vector< int > > ej3() {
	queue<Casilla*> casillasLibresEnLimpio; //RESTAURAR EL CASILLEROlIBRE POR UNO QUE ESTE EN LIMPIO.
	casillasLibres = casillasLibresEnLimpio;
	for (int i = 0; i < g.size(); ++i) {
		for (int j = 0; j < g[i].size(); ++j) { //Por cada casilla 
			if (g[i][j].tipo == 2) { //Si es importante
				restringirCasillasPorImportante(i, j); //Restringo sus casillas horizontales y verticales.
				if (g[i][j].tipo == 1) 
					casillasLibres.push(&(g[i][j]));
			}
		}
	}
	
	backtrack();
	vector < vector <int > > res;
	return res;
}

int main() {
	char termino = ' ';
	while (termino != '#') {
		int n, m;
		mejorCosto = n*m*6000; //NECESITO TENER UN COSTO MAXIMO PARA IR MEJORANDOLO EN CADA SOLUCION, EL INICIAL ES EL MAXIMO QUE SE PODRIA OBTENER.
		Grilla gEnLimpio; //A LA PRIMERA VUELTA ESTA TODO BIEN, PERO CUANDO SE EJECUTA POR SEGUNDA VEZ, HAY INFORMACION EN LA GRILLA DE LA VEZ ANTERIOR
		g = gEnLimpio; //ENTONCES CREO UNA GRILLA EN LIMPIO Y LA REEMPLAZO
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
		res = ej3();
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


/*
To-do list:

ARMAR TODA LA SOLUCION EN BASE A LA INFORMACION:
- mejorCosto (tiene el mejor Costo que se uso)
- gMejor (la grilla de la cual se obtuvo el mejor Costo)



FALTAN LAS FUNCIONES: 
chequearSolucion();

*/
