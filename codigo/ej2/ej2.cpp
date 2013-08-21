#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int> Curso;


vector<int> ej2(int cantCursos, vector<Curso> cs) {
	vector<int> res;
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
