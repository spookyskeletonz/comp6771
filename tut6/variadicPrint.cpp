#include<iostream>
#include<vector>
template <typename T>
bool printIfWholeNumber(const T&) {
	return false;
}

template <>
bool printIfWholeNumber<int>(const int& i) {
	std::cout << i;
	return true;
}

template <typename T>
unsigned int printAndCountWholeNumbers(const T& d) {
	if (printIfWholeNumber(d)) {
		std::cout << " ";
		return 1;
	}
	return 0;
}

template <typename T, typename... U>
unsigned int printAndCountWholeNumbers(T head, U... tail) {
    int num = printAndCountWholeNumbers(head);
    num += printAndCountWholeNumbers(tail...);
    return num;
}

template <typename T>
unsigned int printAndCountWholeNumbers(const std::vector<T>& vd){
    unsigned int count = 0;
    for(auto d : vd){
        auto dCopy = d;
        dCopy -= static_cast<int>(d);
        if(dCopy == 0){
            printIfWholeNumber(static_cast<int>(d));
            std::cout << " ";
            count++;
        }
    }
    return count;
}

int main(){
    auto c = printAndCountWholeNumbers(1, 2.5, 3, 4.5, 5.5, 6, 7.0, -5, "2" );
    std::cout << "count = " << c << std::endl;

    std::vector<double> d = {1.2, 32.0, 3.2, 5.30, 5.4, 6, -5};
    auto dc = printAndCountWholeNumbers(d);
    std::cout << "count = " << dc << std::endl;

    std::vector<unsigned int> vui = {65, 343, 21, 3};
    dc = printAndCountWholeNumbers(vui);
    std::cout << "count = " << dc << std::endl;
}


