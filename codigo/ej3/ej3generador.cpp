#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;


int main() {
	srand(time(NULL));
	for (int i = 1; i <= 7 ; i++)
	{
		for (int j = 1; j <= 7; j++)
		{
			vector<int> matriz (i*j,1);
			
			int veinte = 20;
			veinte = veinte * i * j;
			veinte /= 100;
			
			if (veinte == 0)
			{
				veinte++;
			}
			
			int a = rand() % veinte;
			
			for (int k = 0; k < a; k++)
			{
				matriz[k] = 0;
			}
			
			int quince = 20;
			quince = quince * i * j;
			quince /= 100;
			
			if (quince == 0)
			{
				quince++;
			}
			
			int b = rand() % quince;
			
			for (int k = a; k < b+a; k++)
			{
				matriz[k] = 2;
			}
			
			random_shuffle(matriz.begin(), matriz.end());
			
			cout << i << " " << j << endl;
			
			for (int k = 0; k < i; k++)
			{
				for (int l = 0; l < j; l++)
				{
					cout << matriz[i*k + l] << " ";
				}
				cout << endl;
			}
			
			//~ b = rand() % 365;
			//~ if (a >= b)
				//~ cout << b << " " << a << " ";
			//~ else
				//~ cout << a << " " << b << " ";
		}
	}
	cout << "#";
	return 0;
}
