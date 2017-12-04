#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

class Book {
public:
    //cosntructor
    Book(std::string n, std::string a, int i, double p) : name(n), author(a), isbn(i), price(p) {}

    // getters
    int getIsbn() const { return isbn; }
    double getPrice() const  { return price; }

    //operator overload
    friend bool operator==(const Book& lhs, const Book& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Book& rhs);
    operator std::string() const { std::string result = author + "," + name; return result; }
    friend bool operator<(const Book& lhs, const Book& rhs);
private:
    std::string name;
    std::string author;
    int isbn;
    double price;

};

#endif
