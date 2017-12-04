#include<iostream>
#include "Book.hpp"
bool Book::operator==(const Book& b){
    return name == b.name 
           && author == b.author
           && isbn == b.isbn
           && price == b.price;
}

std::ostream& operator<<(std::ostream &os, const Book& b){
    os << "name: " << b.name << "author: " << b.author 
    << "isbn: " << b.isbn << "price: " << b.price;
    return os;
}

bool operator<(const Book& lhs, const Book& rhs){
    return lhs.getIsbn() < rhs.getIsbn();
}


