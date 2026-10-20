#include <iostream>
#include <climits>
#include <limits>
using namespace std;

int main() {
    bool valid = true;
    char zoneCode = 'A';
    int hour = 9;
    long long balancePaise = 123456789012LL;
    unsigned int journeyCount = 500;
    double example = 0.1 + 0.2;
    auto inferred = 42;
    cout << "sizeof(bool)=" << sizeof(bool) << '\n';
    cout << "sizeof(char)=" << sizeof(char) << '\n';
    cout << "sizeof(int)=" << sizeof(int) << '\n';
    cout << "sizeof(long long)=" << sizeof(long long) << '\n';
    cout << "sizeof(unsigned int)=" << sizeof(unsigned int) << '\n';
    cout << "sizeof(double)=" << sizeof(double) << '\n';
    cout << "sizeof(auto-inferred int)=" << sizeof(inferred) << '\n';
    cout << "INT_MAX=" << INT_MAX << '\n';
    cout << "LLONG_MAX=" << LLONG_MAX << '\n';
    cout << "valid=" << valid << ", zoneCode=" << zoneCode << ", hour=" << hour << '\n';
    cout.precision(17);
    cout << "0.1 + 0.2 as double = " << example << '\n';
    cout << "balance paise=" << balancePaise << ", journey count=" << journeyCount << '\n';
    return 0;
}