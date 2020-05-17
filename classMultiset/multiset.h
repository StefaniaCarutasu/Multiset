#pragma once
#include<iostream>
#include "Comparator.h"
#include "node.h"
#include<vector>
using namespace std;

template<typename T, typename Comparator> class multiset
{
	node<T>* root;
	int noOfNodes;
	Comparator comp;
protected:
	//metode ce ma vor ajuta la realizarea insertiei si deletiei
	T maxim(T, T);
	node<T>* rotateRight(node<T>*);
	node<T>* rotateLeft(node<T>*);
	int getBalance(node<T>*);
	node<T>* valMinNod(node<T>*);

public:
	multiset();	
	multiset(multiset&);
	~multiset();
	void setRoot(node<T>* r) { this->root = r; }
	node<T>* getRoot() const { return this->root; }
	int getNoOfNodes() const { return this->noOfNodes; }
	node<T>* inserare(node<T>*, T);	
	node<T>* stergePrima(node<T>*, T);
	int noOfAparitions(node<T>*, T);
	bool exista(T);
	void stergereToate(T);
	int distincte(node<T>*);
	void operator = (multiset<T, Comparator>&);
	friend ostream& operator << <>(ostream&, multiset<T, Comparator>&);

};
//testare exceptii:
class multisetVid : public exception
{
	const char* what() const throw ()
	{
		return "Multisetul este vid";
	}
};
class nuExista : public exception
{
	const char* what() const throw ()
	{
		return "Nu exista aceasta cheie in multiset";
	}
};

//constructor fara parametrii: initializeaza un multiset gol
template<typename T, typename Comparator>
multiset<T, Comparator>::multiset(): root(NULL), noOfNodes(0) {}
//constructor de copiere
template<class T, class Comparator>
multiset<T, Comparator>::multiset(multiset& M)
{
	if (this->noOfNodes)
		this->~multiset();
	vector<node<T>*> coada;
	coada.push_back(M.root);
	while (coada.size() > 0)
	{
		node<T>* aux = coada[0];
		if (aux->getLeft() != NULL) coada.push_back(aux->getLeft());
		if (aux->getRight() != NULL) coada.push_back(aux->getRight());
		int i = 0;
		while (i < aux->aparitions)
		{
			this->setRoot(this->inserare(this->getRoot(), aux->getKey()));
			i++;
		}
		coada.erase(coada.begin());
	}


}
//destructor
template<typename T, typename Comparator>
multiset<T, Comparator>::~multiset()
{
	vector<node<T>*> coada;
	vector<T> auxSterg;
	coada.push_back(this->root);
	while (coada.size() > 0)
	{
		node<T>* aux = coada[0];
		auxSterg.push_back(aux->getKey());
		if (aux->getLeft() != NULL) coada.push_back(aux->getLeft());
		if (aux->getRight() != NULL) coada.push_back(aux->getRight());
		coada.erase(coada.begin());	
	}
	for (auto i : auxSterg)
		this->stergereToate(i);
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
	node<T>* nodRight = nodLeft->right;
	nodLeft->right = nod;
	nod->left = nodRight;
	nod->height = maxim(nod->left->getHeight(nod->left), nod->right->getHeight(nod->right)) + 1;
	nodLeft->height = maxim(nodLeft->left->getHeight(nodLeft->left), nodLeft->right->getHeight(nodLeft->right)) + 1;
	return nodLeft;
}

template<typename T, typename Comparator>
inline node<T>* multiset<T, Comparator>::rotateLeft(node<T>* nod)
{
	node<T>* nodRight = nod->right;
	node<T>* nodLeft = nodRight->left;
	nodRight->left = nod;
	nod->right = nodLeft;
	nod->height = maxim(nod->left->getHeight(nod->left), nod->right->getHeight(nod->right)) + 1;
	nodRight->height = maxim(nodRight->left->getHeight(nodRight->left), nodRight->right->getHeight(nodRight->right)) + 1;
	return nodRight;
}

template<typename T, typename Comparator>
inline int multiset<T, Comparator>::getBalance(node<T>* nod)
{
	if (nod == NULL)
		return 0;
	return (nod->left->getHeight(nod->left) - nod->right->getHeight(nod->right));
}
template<typename T, typename Comparator>
inline node<T>* multiset<T, Comparator>::valMinNod(node<T>* nod)
{
	node<T>* nodCurent = nod;
	while (nodCurent && nodCurent->left != NULL)
		nodCurent = nodCurent->left;
	return nodCurent;
}
//inserarea propriu zisa
template<typename T, typename Comparator>
inline node<T>* multiset<T, Comparator>::inserare(node<T>* root, T newKey)
{
	//initial facem o insertie normala in BST
	if (root == NULL)
	{
		node<T>* aux = new node<T>(newKey);
		root = aux;
		this->noOfNodes++;
		return root;
	}
	else
	{
		if (comp(newKey, root->key) == 0)
		{
			root->aparitions++; //daca cheia ce trebuie inserata mai apare in multiset atunci doar incrementez nr de aparitii
			noOfNodes++;
		}
		else if (comp(newKey , root->key) == -1)
			root->left = inserare(root->left, newKey);
		else if (comp(newKey , root->key) == 1)
			root->right = inserare(root->right, newKey);
	}

	root->height = 1 + maxim(root->left->getHeight(root->left), root->right->getHeight(root->right));

	//verificam daca cumva arborele nu mai este echilibrat si verificam care dintre cele 4 cazuri de dezechilibru sunt
	int balance = getBalance(root);

	//1) left left case
	if (balance > 1 && newKey < root->left->key)
		return rotateRight(root);
	//2)right right case

	if (balance<-1 && newKey>root->right->key)
		return rotateLeft(root);

	//3)left right case
	if (balance > 1 && newKey > root->left->key)
	{
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}

	//4)right left case
	if (balance < -1 && newKey < root->right->key)
	{
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	//daca nu este niciunul dintre cele 4 cazuri de mai sus
	//avl-ul este echilibrat deja si intoarcem radacina
	
	return root;
}

template<typename T, typename Comparator>
inline node<T>* multiset<T, Comparator>::stergePrima(node<T>* root, T delKey)
{
	//verific daca valoarea exista deja in multiset sau daca multisetul este vid
	if (root == NULL) throw multisetVid();
	if (noOfAparitions(root, delKey) == 0) throw nuExista();
	
	//initial fac o stergere clasica dintr-un BST
	if (delKey < root->key)
		root->left = stergePrima(root->left, delKey);
	else if (delKey > root->key)
		root->right = stergePrima(root->right, delKey);
	else
	{
		root->aparitions--;
		this->noOfNodes--;
		if (root->aparitions == 0)
		{
			if (root->left == NULL)
			{
				node<T>* aux = root->right;
				delete root;
				return aux;
			}
			else if (root == NULL)
			{
				node<T>* aux = root->left;
				delete root;
				return root;
			}
			node<T>* aux = valMinNod(root->right);
			root->key = aux->key;
			root->right = stergePrima(root->right, aux->key);
		}
	}
	if (root == NULL)
		return root;
	root->height = 1 + maxim(root->left->getHeight(root->left), root->right->getHeight(root->right));
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
inline int multiset<T, Comparator>::noOfAparitions(node<T>* root, T findKey)
{
	if (root == NULL) return 0;
	else
	{
		vector<node<T>*> coada;
		coada.push_back(root);
		node<T>* aux;
		while (coada.size() > 0)
		{
			aux = coada[0];
			if (comp(aux->getKey(), findKey) == 0)
				return aux->getAparitions();
			else
			{
				if (aux->getLeft() != NULL) coada.push_back(aux->getLeft());
				if (aux->getRight() != NULL) coada.push_back(aux->getRight());
				coada.erase(coada.begin());
			}
			
		}
		if (coada.size() == 0)
			return 0;
	}
}

template<typename T, typename Comparator>
inline bool multiset<T, Comparator>::exista(T findKey)
{
	int nrAparitii = noOfAparitions(this->root, findKey);
	if (nrAparitii)
		return true;
	return false;
}

template<typename T, typename Comparator>
inline void multiset<T, Comparator>::stergereToate(T deleteKey)
{
	while (noOfAparitions(this->root, deleteKey))
	{
		this->root = stergePrima(this->root, deleteKey);
	}
}

template<typename T, typename Comparator>
inline int multiset<T, Comparator>::distincte(node<T>* root)
{
	//avand in vedere ca pt fiecare nod pastrez numarul de aparitii in multiset numarul de noduri din avl imi va da nr de valori distincte
	return noOfNodes;	
}

template<typename T, typename Comparator>
inline void multiset<T, Comparator>::operator = (multiset<T, Comparator>& M)
{

	if (this->getNoOfNodes())
		this->~multiset();
	vector<node<T>*> coada;
	coada.push_back(M.root);
	while (coada.size() > 0)
	{
		node<T>* aux = coada[0];
		if (aux->getLeft() != NULL) coada.push_back(aux->getLeft());
		if (aux->getRight() != NULL) coada.push_back(aux->getRight());
		int i = 0;
		while (i < aux->aparitions)
		{
			this->setRoot(this->inserare(this->getRoot(), aux->getKey()));
			i++;
		}
		coada.erase(coada.begin());
	}

}


template<typename T, typename Comparator>
ostream& operator<< <>(ostream& out, multiset<T, Comparator>& M)
{
	if (M.getRoot() == NULL)
		throw multisetVid();
	vector<node<T>*> coada;
	coada.push_back(M.root);
	node<T>* aux;
	while (coada.size() > 0)
	{
		aux = coada[0];
		if (aux->getLeft() != NULL) coada.push_back(aux->getLeft());
		if (aux->getRight() != NULL) coada.push_back(aux->getRight());
		int i = 0;
		while (aux->getAparitions() > i)
		{
			i++;
			out << aux->getKey();
			out << " ";
		}
		coada.erase(coada.begin());
	}
	out << '\n';
	return out;
}