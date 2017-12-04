#include "Book.hpp"

bool operator==(const Book& lhs, const Book& rhs){
    return(lhs.name == rhs.name && lhs.author == rhs.author && lhs.isbn == rhs.isbn && lhs.price == rhs.price);
}

std::ostream& operator<<(std::ostream& out, const Book& rhs){
    return out << "name: " << rhs.name << " author: " << rhs.author << " isbn: " << rhs.isbn << " price: " << rhs.price;
}

bool operator<(const Book& lhs, const Book& rhs){
    return(lhs.isbn < rhs.isbn);
}

