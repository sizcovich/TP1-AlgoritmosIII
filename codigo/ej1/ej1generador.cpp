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
	for (int i = 1000; i <= 100000 ; i=i+1000)
	{
		cout << 120 << " " << i << " " ;
		for (int j = 0; j < i; j++)
		{
			cout << rand() % 100 << " ";
		}
		cout << endl;
	}
	cout << "#";
	return 0;
}
