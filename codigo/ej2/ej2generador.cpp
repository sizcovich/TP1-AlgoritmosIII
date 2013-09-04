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
	for (int i = 5000; i <= 100000 ; i=i+5000)
	{
		cout << i << " " ;
		for (int j = 0; j < i; j++)
		{
			a = rand() % 365;
			b = rand() % 365;
			if (a >= b)
				cout << b << " " << a << " ";
			else
				cout << a << " " << b << " ";
		}
		cout << endl;
	}
	cout << "#";
	return 0;
}
