#pragma once
#ifndef TST_H
#define TST_H

#include <string>

// A ternary search tree that stores data based on the value of user-defined
// key strings. Upon initialization, the tree will be set to size 0. 
template <typename T>
class tst {

	// A container class for the ternary search tree. It also includes
	// functionality for inserting additional nodes. 
	class tstnode {
	
		friend class tst;

		// All fields are initialized to nullptr.
		tstnode * eq_kid;
		tstnode * lo_kid;
		tstnode * hi_kid;
		T * data;
		char c_key;

		// Constructs a tstnode object based on the given parameters.
		// Also initializes all child node pointers to nullptr.
		tstnode(T * data, char key) : data(data), c_key(key){
			eq_kid = nullptr;
			lo_kid = nullptr;
			hi_kid = nullptr;
		}

		// Inserts the specified data into the tree starting at this node.
		// If this node has all appropriate child nodes assigned, it will
		// defer the insertion to the appropriate child.
		//
		// Returns true if the data was successfully inserted; false is
		// returned when duplicate data with the same key is passed.
		int insert(T * dat, std::string key) {
			if (key.at(0) == c_key && key.length() <= 1) {
				if (data == nullptr) {
					data = dat;
					return 0;
				}
				return 1;
			}
			if (key.at(0) == c_key && key.length() > 1) {
				
				if (eq_kid == nullptr) {
					//std::cerr << "writing " << key.length() << key.at(1);
					eq_kid = new tstnode(key.length() > 2 ? nullptr : dat, key.at(1));
					if (key.length() > 2)
						return eq_kid->insert(dat, key.substr(1));

				}
				else return eq_kid->insert(dat, key.substr(1));
			}
			else if (key.at(0) < c_key) {
				//std::cerr << "go left";
				if (lo_kid == nullptr) {
					//std::cerr << "writing " << key.length() << key.at(0);
					lo_kid = new tstnode(key.length() > 1 ? nullptr : dat, key.at(0));

					if (key.length() > 1)
						return lo_kid->insert(dat, key);
				}
				else return lo_kid->insert(dat, key);
			}
			else if (key.at(0) > c_key) {
				if (hi_kid == nullptr) {
					//std::cerr << "writing " << key.length() << key.at(0);
					hi_kid = new tstnode(key.length() > 1 ? nullptr : dat, key.at(0));

					if (key.length() > 1)
						return hi_kid->insert(dat, key);
				}
				else return hi_kid->insert(dat, key);
			}
			return 0;
		}

		// Returns the data associated with the specified string key. If there
		// is no data associated with the key, nullptr is returned. 
		T * get(std::string key) {
			//std::cerr << "At " << c_key << "\n";
			if (key.at(0) == c_key) {
				if (key.length() == 1) return data;
				else if (eq_kid == nullptr) return nullptr;
				else return eq_kid->get(key.substr(1));
			}
			else if (key.at(0) < c_key) {
				if (lo_kid == nullptr) return nullptr;
				else return lo_kid->get(key);
			}
			else {
				if (hi_kid == nullptr) return nullptr;
				else return hi_kid->get(key);
			}
		}
	};

	int size;
	tstnode * root;
	
public:

	// Constructs a new ternary search tree and initializes fields. 
	tst() {
		root = nullptr;
		size = 0;
	}


	// Inserts the specified data into the tree.
	void insert(T * data, std::string key) {
		if (root == nullptr) {
			root = new tstnode(key.length() > 1 ? nullptr : data, key.at(0));
			//std::cerr << "Inserting";
			if (key.length() == 1) size = size + 1;
			else if (key.length() > 1)
				if (root->insert(data, key)) size = size + 1;
		}
		else
			if (root->insert(data, key)) size++;
	}

	// Returns the data associated with the specified string key.
	// Returns nullptr if there exists no associated data. 
	T * get(std::string key) {
		return (root == nullptr) ? nullptr : root->get(key);
	}

	
};
#endif
