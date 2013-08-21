#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
// MAS QUE HEAP
#include <map>

/* -------------------------------------------------------------

Ejercicio 1

Referencia de la estructura map en http://en.cppreference.com/w/cpp/container/map
ejemplos en http://www.cplusplus.com/reference/map/map/

El algoritmo esta basado en el pseudocodigo del informe.

---------------------------------------------------------------- */

using namespace std;

typedef int Paquete;
typedef int Camion; //El camion se define por su capacidad
typedef vector<Paquete> Paquetes;

Camion camionMenosCargado(map<Camion, int> ca)
{
    map<int,int>::iterator it = ca.begin();
    return (it->first);
}

vector<int> ej1(int limite, int cantPaquetes, Paquetes ps) {
	vector<int> res;
	//estructura
	map<Camion, int> ca; //El segundo int es al cuete basicamente
	int cantCamiones = 1;

    for (int i=0;i<cantPaquetes;++i)
    {
        Camion c = camionMenosCargado(ca);
        if (Paquetes[i]<= c)
        {
            c -= Paquetes[i];
            map<int,int>::iterator it = ca.begin();
            ca.erase(it); //elimina el camion menos cargado y en la siguiente linea lo vuelve a agregar
            ca.emplace(make_pair(std::int(c), std::int(0))); //agrega el valor c
        }else{
            ca.emplace(make_pair(std::int(limite-Paquetes[i]), std::int(0)));
            ++cantCamiones;
        }
    }

    //Guardo los resultados en el vector
    res.push_back(cantCamiones);
    for (map<int,int>::iterator it2=mymap.begin(); it2!=mymap.end(); ++it2)
        res.push_back(it2->first);

	return res;
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
		cin >> p;

		for (int i = 0; i < cantPaquetes; ++i)
		{
			cin >> p;
			ps.push_back(p);
		}
		vector<int> res;
		res = ej1(limite, cantPaquetes, ps);
		for (int i = 0; i < res.size(); ++i)
			cout << res[i] << " ";
		termino = (cin >> ws).peek();
	}
	return 0;
}
