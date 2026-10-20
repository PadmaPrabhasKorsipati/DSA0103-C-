#include <iostream>
#include <string>
using namespace std;

enum class Zone { Inner = 1, Middle = 2, Outer = 3 };
long long computeFare(int zone, int hour) {
    if (zone < 1 || zone > 3 || hour < 0 || hour > 23) return -1;
    long long fare = zone * 1000LL;
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    if (peak) fare += fare * 20 / 100;
    return fare;
}

int main() {
    struct Test { const char* name; int zone; int hour; long long expected; };
    Test tests[] = {
        {"Inner off-peak", 1, 11, 1000},
        {"Middle peak at 08:00", 2, 8, 2400},
        {"Outer peak at 17:00", 3, 17, 3600},
        {"Inner boundary 10:00", 1, 10, 1000},
        {"Outer boundary 20:00", 3, 20, 3000},
        {"Unknown zone", 4, 9, -1},
        {"Invalid hour", 1, 24, -1}
    };
    int count = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < count; ++i) {
        long long actual = computeFare(tests[i].zone, tests[i].hour);
        cout << tests[i].name << " | expected=" << tests[i].expected
             << " | actual=" << actual << " | "
             << (actual == tests[i].expected ? "PASS" : "FAIL") << '\n';
    }
    long long fiveJourneyTotal = computeFare(1, 11) + computeFare(2, 9)
        + computeFare(3, 14) + computeFare(1, 18) + computeFare(2, 20);
    cout << "Five-journey total (paise): " << fiveJourneyTotal << '\n';
    cout << "Leaves exactly Rs 50: " << (10000 - 5000 >= 5000 ? "yes" : "no") << '\n';
    return 0;
}