#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <variant>
#include <vector>
using namespace std;
using Clock = chrono::steady_clock;

class Bill {
public:
    virtual double total() const = 0;
    virtual ~Bill() = default;
};

class OPBill : public Bill {
    double a, b;
public:
    OPBill(double x, double y) : a(x), b(y) {}
    double total() const override { return a + b; }
};

class IPBill : public Bill {
    double days, rate;
public:
    IPBill(double d, double r) : days(d), rate(r) {}
    double total() const override { return days * rate; }
};

struct SimpleBill {
    int type;
    double a, b;
    double total() const {
        switch (type) {
            case 0: return a + b;
            case 1: return a * b;
            default: return 0.0;
        }
    }
};

struct VariantOP {
    double a, b;
    double total() const { return a + b; }
};

struct VariantIP {
    double days, rate;
    double total() const { return days * rate; }
};

using VariantBill = variant<VariantOP, VariantIP>;

template<class Function>
double measureMilliseconds(Function function) {
    auto start = Clock::now();
    volatile double result = function();
    auto finish = Clock::now();
    (void)result;
    return chrono::duration<double, milli>(finish - start).count();
}

void runBillBenchmark(size_t n) {
    OPBill op(500, 1200);
    IPBill ip(3, 2500);
    vector<const Bill*> virtualBills;
    vector<SimpleBill> switchBills;
    vector<VariantBill> variantBills;
    virtualBills.reserve(n);
    switchBills.reserve(n);
    variantBills.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            virtualBills.push_back(&op);
            switchBills.push_back({0, 500, 1200});
            variantBills.push_back(VariantOP{500, 1200});
        } else {
            virtualBills.push_back(&ip);
            switchBills.push_back({1, 3, 2500});
            variantBills.push_back(VariantIP{3, 2500});
        }
    }

    double virtualMs = measureMilliseconds([&]() {
        double sum = 0;
        for (const Bill* b : virtualBills) sum += b->total();
        return sum;
    });

    double switchMs = measureMilliseconds([&]() {
        double sum = 0;
        for (const auto& b : switchBills) sum += b.total();
        return sum;
    });

    double variantMs = measureMilliseconds([&]() {
        double sum = 0;
        for (const auto& b : variantBills) {
            sum += visit([](const auto& item) { return item.total(); }, b);
        }
        return sum;
    });

    cout << "Bills: " << n << '\n'
         << "  Virtual: " << virtualMs << " ms\n"
         << "  Switch:  " << switchMs << " ms\n"
         << "  Variant: " << variantMs << " ms\n";
}

bool validateReturn(double amount) {
    return amount >= 0.0 && amount <= 100000.0;
}

bool validateException(double amount) {
    try {
        if (amount < 0.0 || amount > 100000.0)
            throw runtime_error("invalid claim");
        return true;
    } catch (const runtime_error&) {
        return false;
    }
}

void runExceptionBenchmark(size_t n, int invalidPercent) {
    vector<double> claims(n, 50000.0);
    size_t invalidCount = n * static_cast<size_t>(invalidPercent) / 100;
    for (size_t i = 0; i < invalidCount; ++i)
        claims[i] = -1.0;

    double returnMs = measureMilliseconds([&]() {
        size_t accepted = 0;
        for (double amount : claims)
            accepted += validateReturn(amount);
        return static_cast<double>(accepted);
    });

    double exceptionMs = measureMilliseconds([&]() {
        size_t accepted = 0;
        for (double amount : claims)
            accepted += validateException(amount);
        return static_cast<double>(accepted);
    });

    cout << "Invalid claims: " << invalidPercent << "% of " << n << '\n'
         << "  Return-code validation: " << returnMs << " ms\n"
         << "  Exception validation:   " << exceptionMs << " ms\n";
}

int main() {
    cout << fixed << setprecision(3);
    cout << "Virtual vs switch vs variant\n";
    for (size_t n : {1000u, 1000000u, 10000000u})
        runBillBenchmark(n);

    cout << "\nReturn-code vs exception validation (1,000,000 claims)\n";
    for (int rate : {0, 1, 50})
        runExceptionBenchmark(1000000, rate);

    cout << "\nTimings depend on CPU, compiler, OS and system load.\n";
    return 0;
}
