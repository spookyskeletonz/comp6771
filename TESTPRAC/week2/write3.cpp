#include <iostream>
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

int main(){
    int num1, num2, num3;
    std::ofstream file;
    file.open("write3.txt");
    std::cout << "enter 1st num" << std::endl;
    std::cin >> num1;
    std::cout<< "enter 2nd num" << std::endl;
    std::cin >> num2;
    std::cout << "enter 3rd num" << std::endl;
    std::cin >> num3;
    cs6771::order3(&num1, &num2, &num3);
    std::cout << "ordered: " << num1 << " " << num2 << " " << num3 << std::endl;
    file << num1 << "\n" << num2 << "\n" << num3 << std::endl;
    return EXIT_SUCCESS;
}
