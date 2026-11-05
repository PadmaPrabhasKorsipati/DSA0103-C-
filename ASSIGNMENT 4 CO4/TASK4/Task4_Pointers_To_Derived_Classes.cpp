#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    virtual double rate() const { return 3.5; }
    double nonVirtualRate() const { return 3.5; }
    virtual ~Account() { std::cout << "Account destructor\n"; }
};

class SeniorAccount : public Account {
private:
    double* history;
public:
    SeniorAccount() : history(new double[100]{}) {}
    double rate() const override { return 4.0; }
    double nonVirtualRate() const { return 4.0; }
    ~SeniorAccount() override {
        delete[] history;
        std::cout << "SeniorAccount destructor\n";
    }
};

int main() {
    std::cout << "TASK 4 - POLYMORPHISM AND SAFE DESTRUCTION\n";
    SeniorAccount senior;
    Account* basePointer = &senior;

    Account slicedCopy = senior;

    std::cout << "Non-virtual call through base pointer: "
              << basePointer->nonVirtualRate() << '\n';
    std::cout << "Virtual call through base pointer: "
              << basePointer->rate() << '\n';
    std::cout << "Virtual call on sliced base copy: "
              << slicedCopy.rate() << '\n';

    std::cout << "Unique pointer collection:\n";
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for (const auto& account : accounts)
        std::cout << "Interest rate: " << account->rate() << "%\n";

    std::cout << "End of main; derived and base destructors run safely.\n";
}