#include <iostream>
#include <iostream>
#include <string>
#include <fstream>

namespace cs6771 {
	void order3(unsigned int& a, unsigned int& b, unsigned int& c) {
		if (a > c) {
			int t = a;
			a = c;
			c = t;
		}
		if (b > c) {
			int t = b;
			b = c;
			c = t;
		}
		if (a > b) {
			int t = a;
			a = b;
			b = t;
		}
	}
}

int main() {
	unsigned int i, j, k;
	std::ifstream fin;
	fin.open("sorted.txt");
	fin >> i;
	fin >> j;
	fin >> k;
	fin.close();
	cs6771::order3(i, j, k);
	std::cout << i << " " << j << " " << k << std::endl;

}