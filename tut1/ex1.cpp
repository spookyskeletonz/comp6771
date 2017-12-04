#include <iostream>
#include <iostream>
#include <string>
#include <fstream>

namespace cs6771 {
	void order3(int *a, int *b, int *c) {
		if (*a < *c) {
			int t = *a;
			*a = *c;
			*c = t;
		}
		if (*a < *b) {
			int t = *a;
			*a = *b;
			*b = t;
		}
		if (*b < *c) {
			int t = *b;
			*b = *c;
			*c = t;
		}
	}
}

int main(int argc, char* argv[]) {
	std::cout << "Enter integer one: " << std::endl;
	int one;
	std::cin >> one;
	std::cout << "Enter integer two: " << std::endl;
	int two;
	std::cin >> two;
	std::cout << "Enter integer three: " << std::endl;
	int three;
	std::cin >> three;
	std::cout << one + two + three << std::endl;
	cs6771::order3(&one, &two, &three);
	std::cout << one << " " << two << " " << three << std::endl;
	std::ofstream fout;
	fout.open("sorted.txt");
	fout << one << " " << two << " " << three;
	fout.close();
}