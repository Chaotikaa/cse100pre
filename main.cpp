//#define USING_MAIN_1
//#define USING_MAIN_2
#define USING_MAIN_3
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>

#include "bs_unoptimized.h"
#include "hctree.h"
#include "tst.h"
#include "ts.h"

using namespace std;

#ifdef USING_MAIN_1
int main (int argc, char * argv[]) {
	char opt;
	int dat;
	std::string key;
	tst<int> t;
	ts tst = ts();

	

	
	/*t.insert(new int(1), "as");
	t.insert(new int(2), "at");
	t.insert(new int(3), "ca");
	t.insert(new int(4), "cut");
	t.insert(new int(5), "cup");
	t.insert(new int(6), "cute");
	t.insert(new int(7), "he");
	t.insert(new int(8), "us");
	t.insert(new int(9), "i");*/
	/*std::ifstream in;
	char str[BUFSIZ];
	int i = 0;
	in.open("dict.txt");
	int * data = new int(0);
	std::string nul;
	while (!in.eof()) {
		
		in.getline(str, BUFSIZ);
		tst.insert(str);
		i++;
	}
	//std::string str; std::getline(in, str);
	//std::cout << ((str == "") ? "none" : str);
	std::cout << "Choose one of the following options: (i)nsert, (s)earch, (p)redict completions: ";
	while (std::cin >> opt) {
		
		switch (opt) {
		case 'i': {
			std::getline(std::cin, key);
			std::cout << "Type the string key: ";
			std::getline(std::cin, key);
			std::cout << "Type the frequency of the string key: ";
			std::cin >> dat;
			std::getline(std::cin, nul);
		    tst.insert((char*)key.c_str(), dat);
			
			
			break;
		}
		case 's': {
			std::getline(std::cin, key);

			std::cout << "Type the key: ";
			std::cin.getline(str, BUFSIZ);
			std::cout << (tst.search(str) ? "Found" : "not found") << "\n";
			/*int * get = t.get(key);
			if (get != nullptr) std::cout << "Data: " << *get << "\n";
			else std::cout << "No element found";
			break;
		}
		case 'p': {
			std::getline(std::cin, key);
			std::cout << "Type the string to predict for: ";
			std::getline(std::cin, key);
			vector<const char *> l = tst.predict_completions(key.c_str());
			cerr << "Predictions (up to 5): ";
			for (int i = 0; i < l.size(); i++) {
				cerr << l.at(i) << " ";
			}
			cerr << "\n";
		}
		default:
			std::cout << "Invalid option";
		}
		std::cout << "Choose one of the following options: (i)nsert, (s)earch: ";


	}*/
}

#endif
#ifdef USING_MAIN_2

int main(int argc, char * argv[]) {
	std::cerr << argc - 1 << " arguments passed:\n";
	std::cerr << argv[1] << " " << argv[2] << "\n";
	if (argc != 3) {

		std::cerr << "Please provide an input file and an output file name.\n";
		//return 1;
	}



	std::map<char, int> chars;
	std::priority_queue<hctree *, std::vector<hctree *>, comparetree> pri;

	std::ifstream file;

	file.open(argv[1]);

	

	char c;

	while (!file.eof()) {
		file.get(c);

		// first instance of this character
		if (chars.count(c) == 0)
			chars[c] = 1;
		else chars[c] = chars[c] + 1;
	}


	for (std::map<char, int>::iterator it = chars.begin();
		it != chars.end(); ++it) {
		std::cerr << "[Got character: " << it->first << ", weight : " << it->second << "\n";
		pri.push(new hctree(it->first, it->second));
	}

	/*hctree * h1 = pri.top();
	h1->print(std::cerr);
	pri.pop();
	hctree * h2 = pri.top();
	h2->print(std::cerr);
	h1->combine_as_left(h2);

	h1->print(std::cerr);*/





	while (pri.size() != 1) {
		/*hctree * hl = pri.top();
		pri.pop();

		hl->print(std::cerr);*/
		hctree * hr = pri.top();
		pri.pop();
		hctree * hl = pri.top();
		pri.pop();
		std::cerr << "\n[Before:]\n";
		std::cerr << "Right:\n";
		hr->print(std::cerr);
		std::cerr << "Left:\n";
		hl->print(std::cerr);
		hl->combine_as_left(hr);
		std::cerr << "\n[After:]\n";
		hl->print(std::cerr);
		pri.push(hl);

	}

	hctree * final = pri.top();
	pri.pop();

	cerr << "Final:\n";
	bit_rep_keys k = final->get_bin_keys();
	for (bit_rep_keys::iterator it = k.begin(); it != k.end(); ++it) {
		cerr << it->first << ": \"" << it->second << "\"\n";
	}


	std::ofstream of;
	of.open(argv[2]);
	char line[BUFSIZ];
	file.clear();
	file.seekg(0, ios::beg);
	file.getline(line, BUFSIZ);
	char * ptr = line;
	cerr << line << "\n";
	while (*ptr) {
		
		std::cout << k[*ptr];
		++ptr;
	}


	std::cin.get();


	return 0;
}
#endif
#ifdef USING_MAIN_3

int cmp(int i1, int i2) {
	if (i1 < i2) return -1;
	if (i1 > i2) return 1;
	else return 0;
}
int main(int argc, char * argv[]) {

	int a = 1;
	int b = 2;
	const int * p = &a;
	a = 3;
	//*p = 4;
	p = &b;


	bs_unoptimized<int> b = bs_unoptimized<int>(cmp);
	/*b.insert(5);
	b.insert(3);
	b.insert(4);
	b.insert(2);
	b.insert(1);
	b.insert(7);*/
	cout << b;

	cin.get();
}
#endif
