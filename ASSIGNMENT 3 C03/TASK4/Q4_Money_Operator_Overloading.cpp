#include <iomanip>
#include <iostream>
#include <sstream>

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        Money result;
        result.paise = paise + other.paise;
        return result;
    }

    Money operator-(const Money& other) const {
        Money result;
        result.paise = paise - other.paise;
        return result;
    }

    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const { return paise == other.paise; }
    bool operator<(const Money& other) const { return paise < other.paise; }

    friend std::ostream& operator<<(std::ostream& out, const Money& m) {
        long long absolute = m.paise < 0 ? -m.paise : m.paise;
        if (m.paise < 0) out << "-";
        out << "Rs " << absolute / 100 << '.' << std::setw(2)
            << std::setfill('0') << absolute % 100 << std::setfill(' ');
        return out;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << "Q4 - Money Operator Overloading\n";
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    Money x(0, 75), y(0, 50);
    std::cout << "Paise carry: " << x + y << '\n';
    std::cout << "Negative subtraction: " << Money(5) - Money(8) << '\n';

    Money bill(250);
    bill += Money(49, 50);
    std::cout << "Bill total: " << bill << '\n';
    std::cout << "Is bill less than Rs 300? " << (bill < Money(300)) << '\n';
}