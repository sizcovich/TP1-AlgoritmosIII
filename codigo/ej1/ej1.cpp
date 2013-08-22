#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

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
typedef pair<int,int> Camion; //El camion se define por su capacidad
typedef vector<Paquete> Paquetes;


vector<int> algoritmoDePascual(int limite, int cantPaquetes, Paquetes ps) {
	vector<int> vectorCamionesOrdenados[cantPaquetes];
	pair<int,vector<int>> res;
	priority_queue<Camion, int> ca; //el entero representa el orden del camion
	int cantCamiones = 0; //contador de camiones

    for (int i=0;i<cantPaquetes;++i)
    {
        Camion c = ca.top();
        if (ps[i]+c <= limite)
        {
            c.second() += ps[i];
            ca.pop(); //elimina el camion menos cargado y en la siguiente linea lo vuelve a agregar
            ca.push(c);
        }else{
            ca.push(make_pair(ps[i], cantCamiones); //agrega un nuevo camion
            ++cantCamiones;
        }
    }
    //Guardo los resultados en el vector         
	while(!ca.empty()){
		Camion c = ca.top(); ca.pop();
		vectorCamionesOrdenados[c.first()] = c;
	}
	vectorCamionesOrdenados.resize(cantCamiones);
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
		vector<int> res;
		res = algoritmoDePascual(limite, cantPaquetes, ps);
		for (int i = 0; i < res.size(); ++i)
			cout << res[i] << " ";
        cout<<endl;
		termino = (cin >> ws).peek();
	}
	return 0;
}
