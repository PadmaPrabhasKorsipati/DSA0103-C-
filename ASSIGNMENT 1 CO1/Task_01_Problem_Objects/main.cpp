#include <iostream>
#include <string>
using namespace std;

class FareTable {
public:
    static int baseFarePaise(int zone) {
        if (zone == 1) return 1000;
        if (zone == 2) return 2000;
        if (zone == 3) return 3000;
        return -1;
    }
};

class Journey {
public:
    int zone;
    int hour;
    Journey(int z, int h) : zone(z), hour(h) {}
    bool isPeak() const { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }
};

class SmartCard {
private:
    long long balancePaise;
    static const long long MIN_BALANCE_PAISE = 5000;
public:
    SmartCard(long long balance) : balancePaise(balance) {}
    bool canTravel(long long fare) const { return fare >= 0 && balancePaise - fare >= MIN_BALANCE_PAISE; }
    bool deduct(long long fare) {
        if (!canTravel(fare)) return false;
        balancePaise -= fare;
        return true;
    }
    long long balance() const { return balancePaise; }
};

int main() {
    SmartCard card(10000);
    Journey trip(1, 9);
    int base = FareTable::baseFarePaise(trip.zone);
    long long fare = base;
    if (trip.isPeak()) fare += fare * 20 / 100;
    cout << "Objects: SmartCard, Journey, FareTable\n";
    cout << "Peak journey fare (paise): " << fare << '\n';
    cout << "Travel allowed: " << (card.deduct(fare) ? "yes" : "no") << '\n';
    cout << "Remaining balance (paise): " << card.balance() << '\n';
    cout << "Invariant: balance never falls below 5000 paise after a successful journey.\n";
    return 0;
}