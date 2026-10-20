#include <iostream>
using namespace std;

enum class Zone { Inner, Middle, Outer };
constexpr long long INNER_FARE_PAISE = 1000;
constexpr long long MIDDLE_FARE_PAISE = 2000;
constexpr long long OUTER_FARE_PAISE = 3000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;

int main() {
    Zone zone = Zone::Outer;
    long long fare = OUTER_FARE_PAISE;
    bool peak = true;
    if (peak) fare += fare * PEAK_SURCHARGE_PERCENT / 100;
    cout << "Base fare (paise): " << OUTER_FARE_PAISE << '\n';
    cout << "Peak fare (paise): " << fare << '\n';
    cout << "Minimum balance (paise): " << MIN_BALANCE_PAISE << '\n';
    cout << "Zone enum value: " << static_cast<int>(zone) << '\n';
    return 0;
}