#include<iostream>
#include "multiset.h"
#include "Comparator.h"
#include<cassert>
using namespace std;
void testeMultiset()
{
    multiset<int, Comparator<int>> m, n;
    for (int i = 0; i < 6; i++)
        m.setRoot(m.inserare(m.getRoot(), i));
	assert(m.distincte(m.getRoot()) == 6);
	m.setRoot(m.inserare(m.getRoot(), 4));
	assert(m.exista(1) == true);
	assert(m.noOfAparitions(m.getRoot(), 4) == 2);
	m.stergereToate(4);
	assert(m.exista(4) == false);
	n = m;
	assert(m.getNoOfNodes() == m.getNoOfNodes());
	n.setRoot(n.inserare(n.getRoot(), 8));
	assert(n.distincte(n.getRoot()) == 6);
	n.setRoot(n.inserare(n.getRoot(), 8));
	assert(n.noOfAparitions(n.getRoot(), 8) == 2);

	multiset<double, Comparator<double>> p;
	p.setRoot(p.inserare(p.getRoot(), 2.7));
	p.setRoot(p.inserare(p.getRoot(), 3.7));
	assert(p.distincte(p.getRoot()) == 2);
	p.stergePrima(p.getRoot(), 2.7);
	assert(p.distincte(p.getRoot()) == 1);
}


int main()
{
	testeMultiset();
	cout << "Testele au trecut\n";
	return 0;
}