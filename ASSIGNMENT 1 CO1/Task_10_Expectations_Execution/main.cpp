#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    const long long farePaise = 1234;
    const long long counts[] = {20000, 500000, 3000000};
    cout << fixed << setprecision(2);
    for (int i = 0; i < 3; ++i) {
        long long integerTotalPaise = counts[i] * farePaise;
        double doubleTotalRupees = counts[i] * (farePaise / 100.0);
        double integerTotalRupees = integerTotalPaise / 100.0;
        cout << counts[i] << " journeys: paise-total-Rs=" << integerTotalRupees
             << ", double-total-Rs=" << doubleTotalRupees
             << ", difference-Rs=" << (doubleTotalRupees - integerTotalRupees) << '\n';
    }
    int intTotal = 0;
    intTotal = 3000000 * 1234;
    cout << "32-bit int multiplication result is not reliable when overflow occurs: " << intTotal << '\n';
    return 0;
}