#include <iostream>
#include <string>
#include <algorithm>

class Prescription {
    int n;
    std::string* medicines;

public:
    explicit Prescription(int count)
        : n(count), medicines(count > 0 ? new std::string[count] : nullptr) {}

    Prescription(const Prescription& other)
        : n(other.n), medicines(n > 0 ? new std::string[n] : nullptr) {
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
        std::cout << "[Copy constructor] Deep copy of " << n << " medicines\n";
    }

    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            std::string* fresh = other.n > 0 ? new std::string[other.n] : nullptr;
            for (int i = 0; i < other.n; ++i) fresh[i] = other.medicines[i];
            delete[] medicines;
            medicines = fresh;
            n = other.n;
        }
        return *this;
    }

    ~Prescription() { delete[] medicines; }

    void set(int i, const std::string& m) {
        if (i >= 0 && i < n) medicines[i] = m;
    }
    std::string get(int i) const {
        return (i >= 0 && i < n) ? medicines[i] : "OUT_OF_RANGE";
    }
};

void inspectByValue(Prescription p) {
    std::cout << "Function received prescription by value.\n";
}
void inspectByReference(const Prescription& p) {
    std::cout << "Function received prescription by const reference.\n";
}

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;
    r = r;
    p.set(0, "Ibuprofen");

    std::cout << "Q2 - Deep Copy and Rule of Three\n";
    std::cout << p.get(0) << ' ' << p.get(1) << " | "
              << q.get(0) << ' ' << q.get(1) << " | "
              << r.get(0) << ' ' << r.get(1) << '\n';

    inspectByValue(p);
    inspectByReference(p);
    std::cout << "Self-assignment completed safely.\n";
}