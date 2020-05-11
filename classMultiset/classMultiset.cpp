#include<iostream>
#include "multiset.h"
#include "Comparator.h"
#include<cassert>
using namespace std;
void testeMultiset()
{
    multiset<int, Comparator<int>> m;
    for (int i = 0; i < 6; i++)
        m.setRoot(m.inserare(m.getRoot(), i));
	assert(m.distincte(m.getRoot()) == 6);
}

int main()
{
	testeMultiset();
	cout << "Testele au trecut";
	return 0;
}