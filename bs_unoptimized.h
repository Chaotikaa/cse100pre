#pragma once
#ifndef BS_UNOPTIMIZED_H
#define BS_UNOPTIMIZED_H

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// Implmentation of the binary search tree data structure. Unoptimized
// (no re-balancing, etc.); therefore will run slower in comparison to
// other binary tree implmentations. 
template<class T>
class bs_unoptimized {

	// Representation of a node in the binary tree. 
	struct bsnode {
		bsnode * left;
		bsnode * right;
		bsnode * par;
		int height;
		T data;

		bsnode(T& dat) : data(dat) {}
	};

	int siz;
	int height;
	bsnode * root;
	int(*cmp)(T, T);


	bsnode * get_bsnode(T& data) {
		bsnode * b = new bsnode(data);
		b->left = b->right = b->par = 0;
		b->height = 0;
		return b;
	}

	void insert(bsnode *& b, T& data) {
		if (!b) { b = get_bsnode(data); siz++; return; }
		else if (cmp(data, b->data) == -1) insert(b->left, data);
		else if (cmp(data, b->data) == 1) insert(b->right, data);
		else if (cmp(data, b->data) == 0) b->data = data;
		int lh = (b->left) ? b->left->height : -1;
		int rh = (b->right) ? b->right->height : -1;
		b->height = max(lh, rh) + 1;
	}

	
	bool search(bsnode *& b, T& data) {
		if (!b) { return 0; }
		else if (cmp(data, b->data) == -1) return search(b->left, data);
		else if (cmp(data, b->data) == 1) return search(b->right, data);
		else if (cmp(data, b->data) == 0) return 1;
	}

	void print_all_n(bsnode * b, ostream &os) const {
		if (b) {
			print_all_n(b->left, os);
			os << b->data << " ";
			print_all_n(b->right, os);
		}
	}

	void delete_all_n(bsnode * b) {
		if (b) {
			delete_all_n(b->left);
			delete_all_n(b->right);
			delete b;
		}
	}

public:

	bs_unoptimized(int(*cmp)(T, T)) : siz(0), 
		root(0), height(0) { this->cmp = cmp; }

	~bs_unoptimized() { delete root; }

	void insert(T data) { 
		insert(root, data);
		height = root->height;
	}

	bool search(T data) { return search(root, data);  }

	int size() { return siz; }

	bool empty() { return siz == 0; }

	friend ostream& operator<< (ostream &os, const bs_unoptimized<T>& b) {
		os << "[ ";
		b.print_all_n(b.root, os);
		os << "| h: " << b.height << ", s: " << b.siz << " ]";
		return os;
	}

};


#endif