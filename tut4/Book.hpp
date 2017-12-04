#include<iostream>
class Book {
public:
    //constructor
    Book(const std::string &n, const std::string &a, const int i, const double p) : name{n}, author{a}, isbn{i}, price{p} { }
    //overloaded operators
    bool operator==(const Book&);
    friend std::ostream& operator<<(std::ostream&, const Book&);
    operator std::string() const { return toString; }
    friend bool operator<(const Book&, const Book&);
    // getters
    int getIsbn() const { return isbn; }
    double getPrice() const  { return price; }
private:
    std::string name;
    std::string author;
    int isbn;
    double price;
    std::string toString = author + std::string(", ") + name;
};
