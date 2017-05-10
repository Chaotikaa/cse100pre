#pragma once
#ifndef HCTREE_H
#define HCTREE_H

#include <iostream>
#include <string>
#include <map>

typedef std::map<char, std::string> bit_rep_keys;

class hcnode {

	friend class hctree;
	
	int weight;
	char c;
	std::string bit_string;
	
	hcnode * left;
	hcnode * right;

	void update_bit_rep(std::string bit, bit_rep_keys & keys) {
		bit_string = bit + bit_string;
		if (c != '\0') keys[c] = bit_string;
		if (left) left->update_bit_rep(bit, keys);
		if (right) right->update_bit_rep(bit, keys);
	}
	
public:
	

	void print(std::ostream & os) {
		if (left) left->print(os);
		if(c != '\0')
			os << "'" << c << "': " << weight << ", bit_str: " << bit_string << "\n";
		if (right) right->print(os);

	}
};


// A tree data structure used for generating Huffman compressions.
// Provides functionality for combining with other trees, according to
// the combination rules of the Huffman compression algorithm. 
class hctree {

	// Allows comparison struct comparetree to access this tree's attributes.
	friend struct comparetree;

	// The overall weight of the tree.
	int weight;

	// The root node of the tree.
	hcnode * root;

	// Map holding the values of the bit strings, mapped by the character
	// to which they correspond. 
	bit_rep_keys keys;

	// Utility function for constructing and initializing
	// hcnode objects. All fields are set according to the
	// specified data; by default, all fields will be set
	// to 0.
	hcnode * get_hc_node(char c = '\0', int weight = 0) {
		hcnode * hn = new hcnode;
		hn->weight = weight;
		hn->left = hn->right = 0;
		hn->c = c;
		hn->bit_string = "";
		return hn;
	}

	
	
public:

	// Constructs a new Huffman tree of size 1, with that 
	// node holding the character and weight data. 
	hctree(char c, int weight) {
		this->weight = weight;
		root = get_hc_node(c, weight);
	}

	/*hctree(hcnode *, hctree *);
	hctree(hcnode *, hcnode *);*/

	void combine_as_left(hctree *);
	//void combine_as_left(hcnode *);

	// Prints a string representation of this tree, with characters and weights.
	void print(std::ostream & os) {
		os << "[hctree: " << weight << "\n";
		root->print(os);
		os << "weight: " << weight << "]\n";
	}

	// Returns the map that holds the bit string representations, mapped by
	// character. 
	bit_rep_keys get_bin_keys() {
		return keys;
	}


};


// A utility structure that provides a comparison function for comparing
// hctree pointers. For use with std::priorityqueue.
struct comparetree {
	bool operator()(hctree * h1, hctree * h2) const {
		return h1->weight > h2->weight;
	}
};



#endif