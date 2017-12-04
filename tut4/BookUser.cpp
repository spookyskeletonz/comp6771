#include<iostream>
#include "Book.hpp"
#include<vector>
int main(){
    std::vector<Book> books = {Book("book1", "author1", 111, 10.5), 
        Book("book2", "author2", 112, 3.5), 
        Book("book3", "author3", 121, 20.5), 
        Book("book4", "author4", 211, 19.5), 
        Book("book5", "author5", 113, 11.5)};
    std::sort(books.begin(), books.end());
    for(std::vector<Book>::iterator it = books.begin(); it != books.end(); ++it)
        std::cout << ' ' << *it << '\n';
    std::cout << '\n';
    std::sort(books.begin(), books.end(), [] (Book b, Book c) { return b.getPrice() < c.getPrice(); });
    for(std::vector<Book>::iterator it = books.begin(); it != books.end(); ++it)
        std::cout << ' ' << *it << '\n';
    std::cout << '\n';
}
