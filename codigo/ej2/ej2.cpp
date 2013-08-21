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

typedef pair<int> Curso;

struct {
        bool operator()(Curso a, Curso b)
        {
            return a.second < b.second;
        }
    } customLess;


vector<int> ej2(int cantCursos, vector<Curso> cs) {
	vector<int> res;
	sort(cs.begin()+1, cs.end(),customLess); //ORDENA SEGUN LA SEGUNDA TUPLA Y A PARTIR DEL SEGUNDO ELEMENTO, PORQUE EL PRIMERO ES LA CANTIDAD DE ELEMENTOS
	return res;
}

int main() {
    	char termino = ' ';
	while (termino != '#') {
		int c,ci,cf;
		int cantCursos;
		vector<Curso> cs;

		cin >> cantCursos;

		for (int i = 0; i < cantCursos; ++i)
		{
			cin >> ci;
			cin >> cf;
			cs.push_back(pair<int,int>(int(ci), int(cf)));
		}

		vector<int> res;
		res = ej2(cantCursos,cs);
		for (int i = 0; i < res.size(); ++i)
			cout << res[i] << " ";
        cout<<endl;
		termino = (cin >> ws).peek();
	}
	return 0;
}
