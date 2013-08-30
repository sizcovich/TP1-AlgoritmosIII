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

bool customLess (pair<Curso,int> i,pair<Curso,int> j)
{ return ((i.first).second < (j.first).second); }

vector<pair<Curso,int> > filtrarSolapamientos(vector<pair<Curso,int> >& cs)
{
    vector<pair<Curso,int> > res;
    res.reserve(cs.size()); //Sirve para reservar espacio y que agregar luego sea O(1)
    res.push_back(cs[0]);
    int ult = 0;
    for(int i=1;i<cs.size();++i)
    {
        if (cs[i].first.first >= res[ult].first.second) //VEO SI EL INICIO DE UN CURSO ES DESPUES DEL TERMINO DEL ANTERIOR (DEL ANTERIOR AGREGADO).
            {res.push_back(cs[i]);
            ++ult;}
    }
    return (res);
}


vector<int> ej2(vector<pair<Curso,int> > cs) {
	vector<int> res;
	res.reserve(cs.size()); //Sirve para reservar espacio y que agregar luego sea O(1)
 	sort(cs.begin(), cs.end(),customLess); //ORDENA SEGUN LA SEGUNDA TUPLA
	vector<pair<Curso,int> > salida;
	salida = filtrarSolapamientos(cs); //Quita los cursos que se solapan de izquierda a derecha

	//PREPARO LA SALIDA
	res.push_back(salida.size());
	for(int i=0;i<salida.size();++i){
        res.push_back(salida[i].second);
	}

	return res;
}

int main() {
    	char termino = ' ';
	while (termino != '#') {
		int c,ci,cf;
		int cantCursos;
		vector<pair<Curso,int> > cs;

		cin >> cantCursos;

        cs.reserve(cantCursos); //Sirve para reservar espacio y que agregar luego sea O(1)
		for (int i = 0; i < cantCursos; ++i)
		{
			cin >> ci;
			cin >> cf;
			Curso cur (ci, cf);
			cs.push_back(make_pair(cur, i++));
		}

		vector<int> res;

		res = ej2(cs);

		for (int i = 0; i < res.size(); ++i)
			cout << res[i] << " ";
        cout<<endl;
		termino = (cin >> ws).peek();
	}
	return 0;
}
