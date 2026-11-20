#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;

class Guard {
    string name;
public:
    explicit Guard(string n) : name(move(n)) {}
    ~Guard() noexcept {
        cout << "~" << name << ' ';
    }
};

void functionF() {
    Guard local("f");
    throw 42;
}

void auditAndRethrow() {
    try {
        throw runtime_error("claim rejected");
    } catch (const exception& e) {
        cout << "audit: " << e.what() << '\n';
        throw;
    }
}

int main() {
    cout << "Stack unwinding demonstration: ";
    try {
        Guard mainGuard("main");
        functionF();
        cout << "not printed ";
    } catch (int value) {
        cout << "caught " << value << '\n';
    }

    cout << "Rethrow demonstration:\n";
    try {
        auditAndRethrow();
    } catch (const exception& e) {
        cout << "top-level handler: " << e.what() << '\n';
    }

    cout << "RAII demonstration:\n";
    try {
        unique_ptr<int> resource = make_unique<int>(100);
        cout << "resource value: " << *resource << '\n';
        throw runtime_error("simulated failure");
    } catch (const exception& e) {
        cout << "caught: " << e.what() << '\n';
    }

    return 0;
}
