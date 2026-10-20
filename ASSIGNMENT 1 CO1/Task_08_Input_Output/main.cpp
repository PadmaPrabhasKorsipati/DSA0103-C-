#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

int main() {
    int hour;
    cout << "Enter journey hour (0-23): ";
    while (!(cin >> hour) || hour < 0 || hour > 23) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Invalid hour. Enter an integer from 0 to 23: ";
    }
    long long farePaise = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20) ? 1200 : 1000;
    cout << fixed << setprecision(2);
    cout << "Journey report\n";
    cout << "Hour: " << hour << '\n';
    cout << "Fare: Rs " << farePaise / 100.0 << '\n';
    return 0;
}