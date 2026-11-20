#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
using namespace std;

class ClaimError : public runtime_error {
public:
    using runtime_error::runtime_error;
};

double approve(double billed, double cover) {
    if (billed < 0.0 || cover < 0.0)
        throw invalid_argument("negative amount");
    if (billed > cover)
        throw ClaimError("exceeds cover");
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& e) {
        cout << "audit: " << e.what() << '\n';
        throw;
    }
}

void validateAmount(double amount) {
    if (amount < 0.0)
        throw invalid_argument("negative");
    if (amount > 1e6)
        throw out_of_range("too large");
    cout << "ok ";
}

void processAmount(double amount) {
    try {
        validateAmount(amount);
    } catch (const out_of_range& e) {
        cout << "[log " << e.what() << "] ";
        throw;
    }
}

int main() {
    cout << "Validation and rethrow:\n";
    for (double amount : {100.0, -5.0, 2e6}) {
        try {
            processAmount(amount);
            cout << "done ";
        } catch (const exception& e) {
            cout << "caught " << e.what() << ' ';
        }
    }
    cout << "\n\nClaim settlement:\n";

    double cases[][2] = {{40000, 50000}, {60000, 50000}, {-1, 50000}};
    for (auto& c : cases) {
        try {
            cout << "approved " << settle(c[0], c[1]) << '\n';
        } catch (const ClaimError& e) {
            cout << "claim rejected: " << e.what() << '\n';
        } catch (const exception& e) {
            cout << "error: " << e.what() << '\n';
        }
    }

    cout << "\nAllocation failure demonstration:\n";
    try {
        throw bad_alloc();
    } catch (const bad_alloc&) {
        cout << "Allocation failed: simulated std::bad_alloc\n";
    }

    cout << "Program continues after handled errors\n";
    return 0;
}
