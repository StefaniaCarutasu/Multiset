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
	cout << "Testele au trecut\n";
	multiset<int, Comparator<int>> m;
	for (int i = 0; i < 6; i++)
		m.setRoot(m.inserare(m.getRoot(), i));
	vector<node<int>*> coada;
	coada.push_back(m.getRoot());
	node<int>* aux;
	while (coada.size() > 0)
	{
		aux = coada[0];
		if (aux->getLeft() != NULL) coada.push_back(aux->getLeft());
		if (aux->getRight() != NULL) coada.push_back(aux->getRight());
		int i = 0;
		while (aux->getAparitions() > i)
		{
			i++;
			cout << aux->getAparitions();
			cout << " ";
		}
		coada.erase(coada.begin());
	}
	cout << m;

	return 0;
}