#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#include "hctree.h"

namespace hc {
	int main(int argc, char * argv[]) {
		if (argc != 2) {
			std::cerr << "Please provide an input file and an output file name.\n";
		}

		std::map<char, int> chars;
		std::priority_queue<hctree *, std::vector<hctree *>, comparetree> pri;

		std::ifstream file;

		file.open(argv[0]);

		char c;

		while (!file.eof()) {
			file.get(c);

			// first instance of this character
			if (chars.count(c) == 0)
				chars[c] = 1;
			else chars[c] = chars[c] + 1;
		}

		file.close();

		for (std::map<char, int>::iterator it = chars.begin(); 
			it != chars.end(); ++it) {
			pri.push(new hctree(it->first, it->second));
		}

		while (pri.size() != 0) {
			
		}


		

		return 0;
	}
}

