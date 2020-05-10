#include<iostream>
#include "multiset.h"
#include "Comparator.h"
using namespace std;

int main()
{
	multiset<int, Comparator<int>> M;
	for (int i = 0; i < 6; i++)
		M.setRoot(M.inserare(M.getRoot(), i));

	M.stergePrima(M.getRoot(), 5);
	cout << M;
	return 0;
}