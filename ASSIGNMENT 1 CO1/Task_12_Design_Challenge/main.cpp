#include <iomanip>
#include <iostream>
using namespace std;

enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };
constexpr long long FARE_PAISE[] = {1000, 2000, 3000, 6000};
constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;

class MonthlyPass {
private:
    bool enabled;
    Zone first;
    Zone second;
public:
    MonthlyPass() : enabled(false), first(Zone::Inner), second(Zone::Inner) {}
    MonthlyPass(Zone a, Zone b) : enabled(true), first(a), second(b) {}
    bool covers(Zone z) const {
        return enabled && (z == first || z == second);
    }
};

class SmartCard {
private:
    long long balancePaise;
    MonthlyPass pass;
public:
    SmartCard(long long balance, MonthlyPass p) : balancePaise(balance), pass(p) {}
    bool hasPassFor(Zone z) const { return pass.covers(z); }
    bool pay(long long farePaise) {
        if (farePaise < 0 || balancePaise - farePaise < MIN_BALANCE_PAISE) return false;
        balancePaise -= farePaise;
        return true;
    }
    long long balance() const { return balancePaise; }
};

long long calculateFare(Zone zone, int hour, bool weekend) {
    int index = static_cast<int>(zone);
    if (index < 0 || index > 3 || hour < 0 || hour > 23) return -1;
    long long fare = FARE_PAISE[index];
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    if (weekend) {
        fare = fare * (100 - WEEKEND_DISCOUNT_PERCENT) / 100;
    } else if (peak) {
        fare += fare * PEAK_PERCENT / 100;
    }
    return fare;
}

int main() {
    SmartCard card(20000, MonthlyPass(Zone::Inner, Zone::Airport));
    struct Example { Zone zone; int hour; bool weekend; const char* label; };
    Example examples[] = {
        {Zone::Airport, 18, false, "Airport peak weekday"},
        {Zone::Airport, 18, true, "Airport weekend peak hour"},
        {Zone::Middle, 9, false, "Middle peak weekday"},
        {Zone::Inner, 14, false, "Inner covered by monthly pass"}
    };
    for (const Example& e : examples) {
        if (card.hasPassFor(e.zone)) {
            cout << e.label << ": Rs 0.00 (monthly pass)\n";
            continue;
        }
        long long fare = calculateFare(e.zone, e.hour, e.weekend);
        bool accepted = card.pay(fare);
        cout << e.label << ": ";
        if (accepted) {
            cout << "Rs " << fare / 100 << '.' << setw(2) << setfill('0') << fare % 100 << setfill(' ');
        } else {
            cout << "Denied (low balance)";
        }
        cout << ", balance Rs " << card.balance() / 100 << '\n';
    }
    return 0;
}