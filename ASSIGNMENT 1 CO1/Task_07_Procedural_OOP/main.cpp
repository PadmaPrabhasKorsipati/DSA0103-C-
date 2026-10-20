#include <iostream>
using namespace std;

const long long MIN_BALANCE = 5000;

bool proceduralCanTravel(long long balance, long long fare) {
    return fare >= 0 && balance - fare >= MIN_BALANCE;
}
bool proceduralDeduct(long long &balance, long long fare) {
    if (!proceduralCanTravel(balance, fare)) return false;
    balance -= fare;
    return true;
}

class SmartCard {
private:
    long long balancePaise;
public:
    SmartCard(long long initialBalance) : balancePaise(initialBalance) {}
    bool canTravel(long long fare) const {
        return fare >= 0 && balancePaise - fare >= MIN_BALANCE;
    }
    bool deduct(long long fare) {
        if (!canTravel(fare)) return false;
        balancePaise -= fare;
        return true;
    }
    long long balance() const { return balancePaise; }
};

int main() {
    long long proceduralBalance = 10000;
    cout << "Procedural deduction accepted: " << proceduralDeduct(proceduralBalance, 3000) << '\n';
    cout << "Procedural balance: " << proceduralBalance << '\n';

    SmartCard card(10000);
    cout << "OOP deduction accepted: " << card.deduct(3000) << '\n';
    cout << "OOP balance: " << card.balance() << '\n';
    cout << "Oversized deduction accepted: " << card.deduct(6000) << '\n';
    cout << "Final OOP balance: " << card.balance() << '\n';
    return 0;
}