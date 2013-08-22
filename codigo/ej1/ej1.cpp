#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

/* -------------------------------------------------------------

Ejercicio 1

Referencia de la estructura priority_queue en http://www.cplusplus.com/reference/queue/priority_queue/
Complejidades:
 -insertar O(log(n))
 -borrar O(log(n))

El algoritmo esta basado en el pseudocodigo del informe.

---------------------------------------------------------------- */

using namespace std;

typedef int Paquete;
typedef pair<int,int> Camion; //El camion se define por su orden y su capacidad
typedef vector<Paquete> Paquetes;


pair<int,vector<int> > algoritmoDePascual(int limite, int cantPaquetes, Paquetes ps) {
	vector<int> vectorCamionesOrdenados(cantPaquetes);
	pair<int,vector<int> > res;
	priority_queue<Camion, vector<Camion>, greater<Camion> > ca;
	int cantCamiones = 0; //contador de camiones

	if (ps.empty()) //Si NO HAY PAQUETES, entonces devuelve el resultado vacio
		return make_pair(0, vector<int>());
	else { //Si hay paquetes, agrego el primer paquete al heap.
		ca.push(make_pair(cantCamiones, ps[0])); 
		cantCamiones++;
	}

    for (int i=1;i<cantPaquetes;++i)
    {
        Camion c = ca.top();
        if ((ps[i]+c.second) <= limite)
        {
            c.second += ps[i];
            ca.pop(); //elimina el camion menos cargado y en la siguiente linea lo vuelve a agregar
            ca.push(c);
        }else{
            ca.push(make_pair(cantCamiones, ps[i])); //agrega un nuevo camion
            ++cantCamiones;
        }
    }
    //Guardo los resultados en el vector         
	while(!ca.empty()){
		Camion c = ca.top();
		vectorCamionesOrdenados[c.first] = c.second;
		ca.pop();
	}
	vectorCamionesOrdenados.resize(cantCamiones);
    res.first = cantCamiones; //como empieza en 0 le sumo 1
    res.second = vectorCamionesOrdenados;
	return res; //devuelvo la tupla (cantCamiones,[c1 c2 ... cn])
}

int main() {
	char termino = ' ';
	while (termino != '#') {
		int limite;
		int cantPaquetes;
		cin >> limite;
		cin >> cantPaquetes;
		Paquetes ps;
		Paquete p;
		for (int i = 0; i < cantPaquetes; ++i)
		{
			cin >> p;
			ps.push_back(p);
		}
		pair<int,vector<int> > res;
		res = algoritmoDePascual(limite, cantPaquetes, ps);
		res.second.resize(res.first);
		cout << res.first << " ";
		for (int i = 0; i < res.first; ++i)
			cout << res.second[i] << " ";
        cout<<endl;
		termino = (cin >> ws).peek();
	}
	return 0;
}
