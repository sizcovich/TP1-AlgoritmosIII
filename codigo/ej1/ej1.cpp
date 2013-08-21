#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>

/* -------------------------------------------------------------

Ejercicio 1

Referencia de la estructura map en http://en.cppreference.com/w/cpp/container/multimap
ejemplos en http://www.cplusplus.com/reference/map/multimap/
Complejidades:
 -iterador begin O(1)
 -insert O(log(n))
 -erase O(log(n)) en realidad es menos

El algoritmo esta basado en el pseudocodigo del informe.

---------------------------------------------------------------- */

using namespace std;

typedef int Paquete;
typedef int Camion; //El camion se define por su capacidad
typedef vector<Paquete> Paquetes;

Camion camionMenosCargado(int limite,multimap<Camion, int> ca)
{
    multimap<int,int>::iterator it = ca.begin();
    if (it==ca.end())
        return limite;
    return (it->first);
}

vector<int> ej1(int limite, int cantPaquetes, Paquetes ps) {
	vector<int> res;
	//estructura
	multimap<Camion, int> ca; //El segundo int es al cuete basicamente
	int cantCamiones = 0;

    for (int i=0;i<cantPaquetes;++i)
    {
        Camion c = camionMenosCargado(limite,ca);
        if (ps[i]+c <= limite )
        {
            c += ps[i];
            multimap<int,int>::iterator it = ca.begin();
            ca.erase(it); //elimina el camion menos cargado y en la siguiente linea lo vuelve a agregar
            ca.insert(pair<int,int>(int(c), int(0)));
        }else{
            ca.insert(pair<int,int>(int(ps[i]), int(0)));
            ++cantCamiones;
        }
    }
    //Guardo los resultados en el vector
    res.push_back(cantCamiones);
    for (multimap<int,int>::iterator it2=ca.begin(); it2!=ca.end(); ++it2)
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

		for (int i = 0; i < cantPaquetes; ++i)
		{
			cin >> p;
			ps.push_back(p);
		}
		vector<int> res;
		res = ej1(limite, cantPaquetes, ps);
		for (int i = 0; i < res.size(); ++i)
			cout << res[i] << " ";
        cout<<endl;
		termino = (cin >> ws).peek();
	}
	return 0;
}
