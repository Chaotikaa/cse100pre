#pragma once
#ifndef TS_H
#define TS_H

#include <algorithm>
#include <iostream>
#include <list>
#include <tuple>
#include <vector> // For freq. problem

using namespace std;

struct word;

typedef vector<word> completions;


// A container struct for the ternary search tree.
// Contains the data to be held and pointers for child nodes.
struct tsnode {
	tsnode * lo_kid, * hi_kid, * eq_kid;
	int is_end_of_string;
	int freq; // For freq. problem
	char data;
	completions c;
};


// A utility struct to contain data for determining predictions. 
struct word {
	word(int f, const char * k) : freq(f) {
		strcpy_s(key, k);
	}
	int freq;
	char key[BUFSIZ];
};


// Comparison function used to sort word structs. 
bool word_cmp(word w1, word w2) {
	return w1.freq > w2.freq;
}

// A ternary search tree that stores data based on the value of user-defined
// key strings. Upon initialization, the tree is empty (size 0). 
class ts {
	tsnode * root;
	int size;

	// Constructs and returns a tsnode object. All fields other than
	// data set to 0.
	tsnode * get_node(char c) {
		tsnode * tsn = new tsnode;
		tsn->data = c;
		tsn->is_end_of_string = 0;
		tsn->freq = -1;
		tsn->lo_kid = tsn->eq_kid = tsn->hi_kid = 0;
		return tsn;
	}

	// Inserts the specified data into the tree starting at this node.
	// If the node has all appropriate child nodes assigned, it will
	// defer the insertion to the appropriate child node. 
	void ins(tsnode ** root, const char * key, const char * whole = "", int freq = 0) {
		if (!(*root))
			(*root) = get_node(*key);
		if (*key < (*root)->data)
			ins(&((*root)->lo_kid), key, whole, freq);
		else if (*key > (*root)->data)
			ins(&((*root)->hi_kid), key, whole, freq);
		else if (*key == (*root)->data) {

			(*root)->c.push_back(word(freq, whole));

			if (*(key + 1)) 
				ins(&((*root)->eq_kid), key + 1, whole, freq);
			else
				(*root)->is_end_of_string = 1;
				
		}
	}

	// Searches for the specified string key. If the string key is not
	// in the tree, returns 0.
	int search(tsnode * root, const char * key) {
		if (!root) return 0;
		if (*key < root->data)
			return search(root->lo_kid, key);
		if (*key > root->data)
			return search(root->hi_kid, key);
		if (*key == root->data) {
			if (*(key + 1))
				return search(root->eq_kid, key + 1);
			else
				return root->is_end_of_string;
		}
	}

	// Returns the position of the node corresponding to the 
	// specified string key. If no such node exists, 0 is returned.
	tsnode * get_node_with(tsnode * root, const char * key) {
		if (!root) return 0;
		if (*key < root->data)
			return get_node_with(root->lo_kid, key);
		if (*key > root->data)
			return get_node_with(root->hi_kid, key);
		if (*key == root->data) {
			if (*(key + 1))
				return get_node_with(root->eq_kid, key + 1);
			else
				return root;
		}
	}

	// Deletes all children of the specified node.
	void delete_all(tsnode * root) {
		if (root) {
			if (root->lo_kid) {
				delete_all(root->lo_kid);
				delete root->lo_kid;
			}
			if (root->eq_kid) {
				delete_all(root->eq_kid);
				delete root->eq_kid;
			}
			if (root->hi_kid) {
				delete_all(root->hi_kid);
				delete root->hi_kid;
			}
		}
	}

public:
	
	// Constructs a new tree. Fields initialized to 0. 
	ts() : root(0), size(0) {}

	// Destructor. Deletes all nodes, starting at root.
	~ts() { delete_all(root); delete root; }

	// Inserts the specified key into the tree. 
	void insert(const char * key, int freq = 0) {
		ins(&root, key, key, freq);
	}

	// Searches for the specified key string in the tree. If found, 1 is
	// returned; otherwise, 0 is returned. 
	int search(const char * key) {
		if (!(*key)) return 0;
		return search(root, key);
	}

	// Returns a vector of the most likely string keys, based on the key
	// provided. The vector is of size n_completions. 
	vector<const char *> predict_completions(const char * keys, int n_completions = 5) {
		vector<const char *> predicted;
		tsnode * tsn = get_node_with(root, keys);
		if (!tsn) 
			return predicted;
		std::sort(tsn->c.begin(), tsn->c.end(), word_cmp);
		for (int i = 0; i < n_completions; i++) 
			if (i < tsn->c.size()) 
				predicted.push_back(tsn->c.at(i).key);
		
		return predicted;
	}

};

#endif
