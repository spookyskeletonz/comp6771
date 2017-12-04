#include<iostream>
#include<string>
#include<fstream>

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

int main(){
    std::string filename;
    std::string line;
    std::cout << "enter file name of 3 numbers" << std::endl;
    std::cin >> filename;
    std::ifstream file;
    file.open(filename);
    unsigned num1, num2, num3;
    int counter = 0;
    while(std::getline(file, line)){
       if(counter == 0) num1 = std::stoi(line);
       if(counter == 1) num2 = std::stoi(line);
       if(counter == 2) num3 = std::stoi(line);
    }
    cs6771::order3(num1, num2, num3);
    std::cout << num1 << " " << num2 << " " << num3;
    return EXIT_SUCCESS;
}
