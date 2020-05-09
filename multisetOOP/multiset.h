#pragma once
#include<iostream>
#include "Comparator.h"
#include "node.h"
#include<queue>
using namespace std;

template<typename T, typename Comparator> class multiset
{
	node<T>* root;
	int noOfNodes;
	Comparator comp;
protected:
	//metode ce ma vor ajuta la realizarea insertiei si deletiei
	T maxim(T, T);	//facut
	node<T>* rotateRight(node<T>*);	//facut
	node<T>* rotateLeft(node<T>*);	//facut
	int getBalance(node<T>*);	//facut	
	node<T>* valMinNod(node<T>*);	//facut

public:
	multiset();	//facut
	multiset(multiset&);
	~multiset();
	node<T> getRoot() const { return this->root; }
	int getNoOfNodes() const { return this->noOfNodes; }
	void inserare(node<T>*, T);	//facut?
	T stergePrima(node<T>*, T);	//facut?
	int noOfAparitions(T);	//facut
	bool exista(T);
	void stergereToate(T);
	int distincte();
	friend ostream& operator << <> (ostream&, multiset&);
};


//constructor fara parametrii: initializeaza un multiset gol
template<typename T, typename Comparator>
multiset<T, Comparator>::multiset() { root = NULL; noOfNodes = 0; }
//constructor de copiere
template<class T, class Comparator>
multiset<T, Comparator>::multiset(multiset& M)
{

}
//destructor
template<typename T, typename Comparator>
multiset<T, Comparator>::~multiset()
{

}

//functii auxiliare pentru a realiza insertia si deletia

template<typename T, typename Comparator>
inline T multiset<T, Comparator>::maxim(T a, T b)
{
	if (comp(a, b) > 0)
		return a;
	else return b;
}

template<typename T, typename Comparator>
inline node<T>* multiset<T, Comparator>::rotateRight(node<T>* nod)
{
	node<T>* nodLeft = nod->left;
	node<T>* nodRight = nod->right;
	nodLeft->right = nod;
	nod->left = nodRight;
	nod->height = maxim(nod->left->getHeight(), nod->right->getHeight()) + 1;
	nodLeft = maxim(nodLeft->left->getHeight(), nodLeft->right->getHeight()) + 1;
	return nodLeft;
}

template<typename T, typename Comparator>
inline node<T>* multiset<T, Comparator>::rotateLeft(node<T>* nod)
{
	node<T>* nodRight = nod->right;
	node<T>* nodLeft = nod->left;
	nodRight->left = nod;
	nod->right = nodLeft;
	nod->height = maxim(nod->left->getHeight(), nod->right->getHeight()) + 1;
	nodRight->height = maxim(nodRight->left->getHeight(), nodRight->right->getHeight()) + 1;
	return nodRight;
}

template<typename T, typename Comparator>
inline int multiset<T, Comparator>::getBalance(node<T>* nod)
{
	if(nod==NULL)
		return 0;
	return nod->left->getHeight() - nod->right->getHeight();
}
template<typename T, typename Comparator>
inline node<T>* multiset<T, Comparator>::valMinNod(node<T>* nod)
{
	node<T>* nodCurent = nod;
	while (nodCurent->left != NULL)
		nodCurent = nodCurent->left;
	return nodCurent;
}
//inserarea propriu zisa
template<typename T, typename Comparator>
inline void multiset<T, Comparator>::inserare(node<T>* nod, T newKey)
{
	//initial facem insertia normala intr-un BST cu mentiunea ca pot exista duplicate
	if (nod== NULL)
	{
		node<T>* newNode(newKey);
		return newNode;
	}
	if (comp(newKey, nod->key) <= 0)
		nod->left = inserare(nod->left, newKey);
	else if (comp(newKey, nod->key) > 0)
		nod->right = inserare(nod->right, newKey);
	this->noOfNodes++;
	//verificam daca cumva arborele nu mai este echilibrat si verificam care dintre cele 4 cazuri de dezechilibru sunt
	int balance = getBalance(nod);

	//1) left left case
	if (balance > 1 && newKey < nod->left->key)
		return rotateRight(nod);
	//2)right right case

	if (balance<-1 && newKey>nod->right->key)
		return rotateLeft(nod);

	//3)left right case
	if (balance > 1 && newKey > nod->left->key)
	{
		nod->left = rotateLeft(nod->left);
		return rotateRight(nod);
	}

	//4)right left case
	if (balance < -1 && newKey < nod->right->key)
	{
		nod->right = rotateRight(nod->right);
		return rotateLeft(nod);
	}

	//daca nu este niciunul dintre cele 4 cazuri de mai sus
	//avl-ul este echilibrat deja si intoarcem doar nodul
	return nod;
}

template<typename T, typename Comparator>
inline T multiset<T, Comparator>::stergePrima(node<T>* root, T key)
{
	if (this->root == NULL)
		return;
	//initial verificam subarborele stang
	if (key < root->key)
		root->left = stergePrima(root->left, key);
	else if (key > root->key)
		root->right = stergePrima(root->right, key);
	else
	{
		if (root->left == NULL || root->right == NULL)
		{
			node<T>* aux;
			if (root->left = NULL)
				aux = root->left;
			else aux = root->right;
			if (aux == NULL)
			{
				aux = root;
				root = NULL;
			}
			else *root = *aux;

			delete aux;
		}
		else
		{
			node* aux = valMinNod(root->right);
			root->key = aux->key;
			root->right = stergePrima(root->right, aux->key);
		}
	}
	if (root == NULL)
		return root->key;
	root->height = 1 + maxim(root->left->getHeight(), root->right->getHeight());
	//dupa stergere exista riscul de a deveni dezechilibrat
	int balance = getBalance(root);
	//urmeaza testarea celor 4 cazuri:

	//1) left left case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rotateRight(root);

	//2) right right case
	if (balance < -1 && getBalance(root->right) <= 0)
		return rotateLeft(root);

	//3) left right case
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}

	//4) right left case
	if (balance < -1 && getBalance(root->right)>0)
	{
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	//daca nu era dezechilibru returnam direct radacina
	return root;

}

template<typename T, typename Comparator>
inline int multiset<T, Comparator>::noOfAparitions(T findKey)
{
	if (root == NULL)
		return 0;
	int nrAparitii = 0;
	queue<node<T>*> coada;
	coada.push(root);
	while (!coada.empty());
	{
		if (comp(coada.front()->key, findKey) == 0)
			nrAparitii++;
		coada.push(coada.front()->left);
		coada.push(coada.front()->right);
		coada.pop();
	}
	return nrAparitii;
}

template<typename T, typename Comparator>
inline bool multiset<T, Comparator>::exista(T findKey)
{
	int nrAparitii = noOfAparitions(findKey);
	if (nrAparitii)
		return true;
	return false;
}

