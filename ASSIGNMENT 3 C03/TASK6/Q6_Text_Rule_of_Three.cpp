#include <iostream>
#include <cstring>

class Text {
    char* data;

public:
    Text(const char* s = "") {
        std::size_t len = std::strlen(s);
        data = new char[len + 1];
        std::memcpy(data, s, len + 1);
    }

    Text(const Text& other) {
        std::size_t len = std::strlen(other.data);
        data = new char[len + 1];
        std::memcpy(data, other.data, len + 1);
        std::cout << "[copy] ";
    }

    Text& operator=(const Text& other) {
        if (this != &other) {
            std::size_t len = std::strlen(other.data);
            char* fresh = new char[len + 1];
            std::memcpy(fresh, other.data, len + 1);
            delete[] data;
            data = fresh;
        }
        return *this;
    }

    ~Text() { delete[] data; }

    Text operator+(const Text& other) const {
        std::size_t a = std::strlen(data), b = std::strlen(other.data);
        char* joined = new char[a + b + 1];
        std::memcpy(joined, data, a);
        std::memcpy(joined + a, other.data, b + 1);
        Text result(joined);
        delete[] joined;
        return result;
    }

    bool operator==(const Text& other) const {
        return std::strcmp(data, other.data) == 0;
    }
    bool operator!=(const Text& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& out, const Text& t) {
        return out << t.data;
    }
};

int main() {
    std::cout << "Q6 - Text Class and Rule of Three\n";
    Text first("Hello ");
    Text second("World");
    Text third("!");
    Text combined = first + second + third;
    std::cout << "\nCombined: " << combined << '\n';

    Text copy = combined;
    std::cout << "Copied: " << copy << '\n';
    copy = copy;
    std::cout << "Self assignment: " << copy << '\n';

    Text empty;
    std::cout << "Empty text: [" << empty << "]\n";
    std::cout << std::boolalpha << "Equal? " << (copy == combined)
              << " | Not equal? " << (copy != first) << '\n';
}