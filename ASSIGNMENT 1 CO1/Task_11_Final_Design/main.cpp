#include <iomanip>
#include <iostream>
using namespace std;

enum class Zone { Inner, Middle, Outer };
constexpr long long FARES_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_PERCENT = 20;
constexpr long long MIN_REMAINING_PAISE = 5000;

class SmartCard {
    long long balancePaise;
public:
    explicit SmartCard(long long initial) : balancePaise(initial) {}
    long long balance() const { return balancePaise; }
    bool pay(long long farePaise) {
        if (farePaise < 0 || balancePaise - farePaise < MIN_REMAINING_PAISE) return false;
        balancePaise -= farePaise;
        return true;
    }
};

long long calculateFare(Zone zone, bool peak) {
    int index = static_cast<int>(zone);
    long long fare = FARES_PAISE[index];
    if (peak) fare += fare * PEAK_PERCENT / 100;
    return fare;
}

int main() {
    SmartCard card(10000);
    long long fare = calculateFare(Zone::Outer, true);
    cout << "Calculated fare Rs " << fare / 100 << '.' << setw(2) << setfill('0') << fare % 100 << setfill(' ') << '\n';
    cout << "Accepted: " << (card.pay(fare) ? "yes" : "no") << '\n';
    cout << "Balance paise: " << card.balance() << '\n';
    cout << "Design: enum class + constexpr fare table + private SmartCard balance\n";
    return 0;
}