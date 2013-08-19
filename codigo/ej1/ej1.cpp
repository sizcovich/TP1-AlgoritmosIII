#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef int Paquete;
typedef vector<Paquete> Paquetes;

vector<int> ej1(int limite, int cantPaquetes, Paquetes ps) {
	vector<int> res;
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
