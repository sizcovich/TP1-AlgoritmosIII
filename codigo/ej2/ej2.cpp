#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

/* -----------------------------------------

Referencia: http://en.cppreference.com/w/cpp/algorithm/sort
Complejidad:
  -Sort : O(n.log(n))

--------------------------------------------*/

using namespace std;

typedef pair<int,pair<int, int> > Curso;
typedef vector<Curso> Cursos;

//VARIABLES IMPORTANTES
vector<bool> seleccionados;
int cantSeleccionados;
Cursos cs;

bool customLess (Curso i,Curso j)
{ return (i.second.second < j.second.second); }

// int busquedaBinaria(vector<pair<Curso,int> >& entrada, Curso& elem)
// {
// 	int i = 0;
// 	int m;
// 	int j = entrada.size();
// 	while (i<j)
// 	{
// 		m = (i+j) / 2;
// 		if (entrada[i].first == elem)
// 			return (entrada[i].second);
// 		if (entrada[j].first == elem)
// 			return (entrada[j].second);
// 		if (entrada[m].first < elem )
// 		{
// 			i = m;
// 		}else{
// 			j = m;
// 		}
// 	}
// 	return (entrada[m].second);
// }


void filtrarSolapamientos()
{
    // res.reserve(cs.size()); //Sirve para reservar espacio y que agregar luego sea O(1)
    Curso anterior;
    anterior = cs[0];
    seleccionados[0] = true;
    cantSeleccionados++;
    for(int i = 1; i < cs.size(); ++i) {
        if (cs[i].second.first > anterior.second.second) { //VEO SI EL INICIO DE UN CURSO ES DESPUES DEL TERMINO DEL ANTERIOR (DEL ANTERIOR AGREGADO).
    		anterior = cs[i];
    		seleccionados[cs[i].first] = true;
    		cantSeleccionados++;
    	}
    }
    return;
}


vector<int> ej2() {
	vector<bool> sLimpio;
	seleccionados = sLimpio;
	cantSeleccionados = 0;
	vector<int> res;
	if (cs.size() == 0) {
		res.push_back(0);
		return res;
	} else {
		for (int i = 0; i < cs.size(); ++i)
			seleccionados.push_back(false);
		sort(cs.begin(), cs.end(),customLess);
		filtrarSolapamientos();
		res.push_back(cantSeleccionados);
		for (int i = 0; i < seleccionados.size(); ++i)
			if (seleccionados[i])
				res.push_back(i+1);
		return res;
	}
	// res.reserve(cs.size()); //Sirve para reservar espacio y que agregar luego sea O(1)
 	// sort(cs.begin(), cs.end(),customLess); //ORDENA SEGUN LA SEGUNDA TUPLA
	// Cursos filtrados = filtrarSolapamientos(cs); //Quita los cursos que se solapan de izquierda a derecha

	//PREPARO LA SALIDA
	// sort(cs.begin(), cs.end()); //ordena para encontrar los intervalos en tiempo logaritmico
	// res.push_back(salida.size());
	// for(int i=0;i<salida.size();++i){
 	// 		res.push_back(busquedaBinaria(apariciones,salida[i]));
	// }


}

int main() {
    char termino = ' ';
	while (termino != '#') {
		int ci,cf;
		int cantCursos;
		Cursos csLimpio; cs = csLimpio;
		cin >> cantCursos;
		for (int i = 0; i < cantCursos; ++i) {
			cin >> ci;
			cin >> cf;
			cs.push_back(make_pair(i, make_pair(ci, cf)));
		}
		vector<int> res = ej2();
		for (int i = 0; i < res.size(); ++i)
			cout << res[i] << " ";
		cout << endl;







		// if (cantCursos > 0)
		// {
			
		// 	vector< pair<Curso,int> > apariciones; //Guarda el orden de llegada (aparicion) de los cursos 
			
		// 	cs.reserve(cantCursos); //Sirve para reservar espacio y que agregar luego sea O(1)
		// 	apariciones.reserve(cantCursos);
		// 	for (int i = 0; i < cantCursos; ++i)
		// 	{
		// 		cin >> ci;
		// 		cin >> cf;
		// 		cs.push_back(pair<int,int>(int(ci), int(cf)));
		// 		pair<Curso,int> val(pair<int,int>(int(ci), int(cf)),posicion);
		// 		apariciones.push_back(val);
		// 		++posicion;
		// 	}

		// 	vector<int> res;

		// 	res = ej2(cs,apariciones);

		// 	for (int i = 0; i < res.size(); ++i)
		// 		cout << res[i] << " ";
		// 	cout<<endl;
		// }else{
		// 	cout<<"0"<<endl;
		// }
		termino = (cin >> ws).peek();
	}
	return 0;
}
