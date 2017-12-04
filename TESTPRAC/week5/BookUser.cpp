#include "Book.hpp"
#include <vector>

int main(){
    std::cout << "creating Books and adding to vector\n";
    std::vector<Book> books;
    books.push_back(Book("Harry Potter and the Applet of Fire", "JK Rowling", 1, 25));
    books.push_back(Book("Lord of the Pings", "JRR Tolkien", 4, 19));
    books.push_back(Book("Pride and Predicate", "Jane Austen", 2, 31));
    books.push_back(Book("Cracking the Coding Interview", "Gayle Laakman", 6, 20));
    for(auto it = books.begin(); it != books.end(); ++it){
        std::cout << *it << "\n";
    }
    std::cout << "sorting books now without lambda. shoudl sort based on isbn due to '<' operator overload\n";
    std::sort(books.begin(), books.end());
    for(auto it = books.begin(); it != books.end(); ++it){
         std::cout << *it << "\n";
    }
    std::cout << "sorting books now with lambda to sort by price\n";
    std::sort(books.begin(), books.end(), [](Book a, Book b){
            return a.getPrice() < b.getPrice();
    });
    for(auto it = books.begin(); it != books.end(); ++it){
        std::cout << *it << "\n";
    }

}
