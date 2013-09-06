#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <random>
#include <iterator>

using namespace std;

#define PORCENTAJE_PAREDES 20
#define PORCENTAJE_IMPORTANTES 10

int main() {
	random_device rd;
    mt19937 g(rd());
	vector<vector<int > > matriz;
	vector<int> linea;


	for (int i = 1; i <= 7 ; i++)
	{
		for (int j = 1; j <= 7; j++)
		{
			vector<int> matriz (i*j,1);

			float tam = i*j;

			int limP = static_cast<int>((tam/100)*PORCENTAJE_PAREDES);
			int limI = static_cast<int>((tam/100)*PORCENTAJE_IMPORTANTES);

			//cout << limP << " " << limI << endl;

			for (int k = 0; k < limP; k++)
				matriz[k] = 0;
			
			for (int k = limP; k < (limP+limI); k++)
				matriz[k] = 2;
			
			shuffle(matriz.begin(), matriz.end(), g);

			cout << i << " " << j << endl;
			if (j>1) {
				matriz[j-2] = 0;
				matriz[j-1] = 2;
				matriz[j] = 0;
			}

			for (int k = 0; k < matriz.size(); ++k) {
				if (k % j == 0 && k!=0)
					cout << endl;

				cout << matriz[k] << " ";
			}
			cout << endl;
		}
	}
	cout << "#";
	return 0;
}
