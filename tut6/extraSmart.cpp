#include<iostream>
#include<memory>
template <typename T>
std::unique_ptr<T> make_unique(T t) {
	return std::unique_ptr<T>(new T(t));
}

template <typename T>
std::unique_ptr<T> make_unique(std::unique_ptr<T>& up){
    return std::unique_ptr<T>(new T(*up));
}

template <typename T>
T getBase(T t) {
	return t;
}

template <typename T>
auto getBase(T *t) -> decltype(*t) {
	return *t;
}

template <typename T>
auto getBase(std::unique_ptr<T>& up) -> decltype(*up) {
    return *up;
}

int main(){
    auto dptr = make_unique(3.14);
    std::cout << *dptr << std::endl;
    auto dptr2 = make_unique(dptr);
    std::cout << *dptr2 << std::endl;
    int i = 9;
    int* iptr = &i;
    std::cout << getBase(i) << std::endl;
    std::cout << getBase(iptr) << std::endl;
    std::cout << getBase(dptr) << std::endl;
}
