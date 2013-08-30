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

typedef pair<int,int> Curso;

bool customLess (Curso i,Curso j)
{ return (i.second < j.second); }

int busquedaBinaria(vector<pair<Curso,int> >& entrada, Curso& elem)
{
	int i = 0;
	int m;
	int j = entrada.size();
	while (i<j)
	{
		m = (i+j) / 2;
		if (entrada[i].first == elem)
			return (entrada[i].second);
		if (entrada[j].first == elem)
			return (entrada[j].second);
		if (entrada[m].first < elem )
		{
			i = m;
		}else{
			j = m;
		}
	}
	return (entrada[m].second);
}


vector<Curso> filtrarSolapamientos(vector<Curso>& cs)
{
    vector<Curso> res;
    res.reserve(cs.size()); //Sirve para reservar espacio y que agregar luego sea O(1)
    res.push_back(cs[0]);
    int ult = 0;
    for(int i=1;i<cs.size();++i)
    {
        if (cs[i].first >= res[ult].second) //VEO SI EL INICIO DE UN CURSO ES DESPUES DEL TERMINO DEL ANTERIOR (DEL ANTERIOR AGREGADO).
            {res.push_back(cs[i]);
            ++ult;}
    }
    return (res);
}


vector<int> ej2(vector<Curso>& cs, vector< pair<Curso,int> >& apariciones) {
	vector<int> res;
	res.reserve(cs.size()); //Sirve para reservar espacio y que agregar luego sea O(1)
 	sort(cs.begin(), cs.end(),customLess); //ORDENA SEGUN LA SEGUNDA TUPLA
	vector<Curso> salida = filtrarSolapamientos(cs); //Quita los cursos que se solapan de izquierda a derecha

	//PREPARO LA SALIDA
	sort(cs.begin(), cs.end()); //ordena para encontrar los intervalos en tiempo logaritmico
	res.push_back(salida.size());
	for(int i=0;i<salida.size();++i){
        res.push_back(busquedaBinaria(apariciones,salida[i]));
	}

	return res;
}

int main() {
    	char termino = ' ';
	while (termino != '#') {
		int c,ci,cf;
		int cantCursos;
		vector<Curso> cs;
		int posicion = 1;

		cin >> cantCursos;
		
		vector< pair<Curso,int> > apariciones; //Guarda el orden de llegada (aparicion) de los cursos 
		
        cs.reserve(cantCursos); //Sirve para reservar espacio y que agregar luego sea O(1)
        apariciones.reserve(cantCursos);
		for (int i = 0; i < cantCursos; ++i)
		{
			cin >> ci;
			cin >> cf;
			cs.push_back(pair<int,int>(int(ci), int(cf)));
			pair<Curso,int> val(pair<int,int>(int(ci), int(cf)),posicion);
			apariciones.push_back(val);
			++posicion;
		}

		vector<int> res;

		res = ej2(cs,apariciones);

		for (int i = 0; i < res.size(); ++i)
			cout << res[i] << " ";
        cout<<endl;
		termino = (cin >> ws).peek();
	}
	return 0;
}
