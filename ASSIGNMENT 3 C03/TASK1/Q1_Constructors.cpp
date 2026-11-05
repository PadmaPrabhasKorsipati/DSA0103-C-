#include <iostream>
#include <string>
#include <stdexcept>

class Book {
    std::string title;
    int copies;
    std::string author;

    static int validate(int count) {
        if (count < 0) throw std::invalid_argument("Number of copies cannot be negative");
        return count;
    }

public:
    Book() : Book("Untitled", 0, "Unknown") {}
    explicit Book(const std::string& t) : Book(t, 1, "Unknown") {}
    Book(const std::string& t, int c) : Book(t, c, "Unknown") {}
    Book(const std::string& t, int c, const std::string& a)
        : title(t), copies(validate(c)), author(a) {}

    void print() const {
        std::cout << "Title: " << title << " | Copies: " << copies
                  << " | Author: " << author << '\n';
    }
};

int main() {
    try {
        Book empty;
        Book donated("The Alchemist");
        Book partial("Clean Code", 4);
        Book full("Computer Networks", 3, "Tanenbaum");

        std::cout << "Q1 - Constructor Overloading\n";
        empty.print();
        donated.print();
        partial.print();
        full.print();

        Book library[2];
        std::cout << "Book array created with default constructors.\n";

        try {
            Book invalid("Invalid Book", -2, "Unknown");
            invalid.print();
        } catch (const std::invalid_argument& e) {
            std::cout << "Negative-copy test: " << e.what() << '\n';
        }

        std::cout << "All valid objects constructed successfully.\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}