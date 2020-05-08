#pragma once
#include<iostream>
using namespace std;

//pentru a atinge complexitatea ceruta voi folosi un  AVL
template<typename T, typename Comparator> class multiset;
template<typename T> class node
{
	T key;
	node* left, * right;
	int height; //inaltimea arborelui pana la nodul curent
public:
	node() : left(NULL), right(NULL), height(0) {}
	node(T key): key(key), left(NULL), right(NULL), height(0) {}
	int getHeight(node* nod)
	{
		if (nod == NULL)
			return 0;
		return nod->height;
	}
	friend class multiset<T, Comparator<T>>; 
};