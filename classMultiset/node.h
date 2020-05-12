#pragma once
#include<iostream>
using namespace std;

//pentru a atinge complexitatea ceruta voi folosi un  AVL
template<typename T, typename Comparator> class multiset;
template<typename T> class node
{
	T key;
	node<T>* left, * right;
	int height; //inaltimea arborelui pana la nodul curent
	int aparitions; //pastrez nr de aparitii a unei chei ca sa pot pastra structura de BST
public:
	node() : left(NULL), right(NULL), height(0), aparitions(0) {}
	node(T key) : key(key), left(NULL), right(NULL), height(0), aparitions(1) {}
	int getHeight(node<T>* nod) const
	{
		if (nod == NULL)
			return 0;
		return nod->height;
	}
	T getKey() const { return this->key; }
	int getAparitions() const { return this->aparitions; }
	node<T>* getLeft() const { return this->left; }
	node<T>* getRight() const { return this->right; }
	friend class multiset<T, Comparator<T>>;
};
