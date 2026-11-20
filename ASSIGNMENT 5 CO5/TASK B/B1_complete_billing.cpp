#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Bill {
protected:
    string patient;
public:
    explicit Bill(string p) : patient(move(p)) {}
    virtual double total() const = 0;
    virtual string type() const = 0;
    virtual void print() const {
        cout << type() << " " << patient << ": Rs. " << total() << '\n';
    }
    virtual ~Bill() = default;
};

class OutPatient : public Bill {
    double consultation, tests;
public:
    OutPatient(string p, double c, double t)
        : Bill(move(p)), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    string type() const override { return "OP"; }
};

class InPatient : public Bill {
    int days;
    double perDay, surgery, medicines;
public:
    InPatient(string p, int d, double rate, double s, double m)
        : Bill(move(p)), days(d), perDay(rate), surgery(s), medicines(m) {}
    double total() const override { return days * perDay + surgery + medicines; }
    string type() const override { return "IP"; }
};

class DayCare : public Bill {
    double packagePrice;
public:
    DayCare(string p, double price) : Bill(move(p)), packagePrice(price) {}
    double total() const override { return packagePrice; }
    string type() const override { return "DayCare"; }
};

class Emergency : public Bill {
    double baseCharge, hourlyRate, hours;
public:
    Emergency(string p, double base, double rate, double h)
        : Bill(move(p)), baseCharge(base), hourlyRate(rate), hours(h) {}
    double total() const override { return baseCharge + hourlyRate * hours; }
    string type() const override { return "Emergency"; }
};

class Payer {
public:
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual string name() const = 0;
    virtual ~Payer() = default;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill&) const override { return 0.0; }
    string name() const override { return "SelfPay"; }
};

class Insurance : public Payer {
    double limit, copay;
public:
    Insurance(double l, double c) : limit(l), copay(c) {}
    double amountCovered(const Bill& b) const override {
        return min(b.total(), limit) * (1.0 - copay / 100.0);
    }
    string name() const override { return "Insurance"; }
};

class GovernmentScheme : public Payer {
    double packageRate;
public:
    explicit GovernmentScheme(double r) : packageRate(r) {}
    double amountCovered(const Bill& b) const override {
        return min(b.total(), packageRate);
    }
    string name() const override { return "GovernmentScheme"; }
};

int main() {
    cout << fixed << setprecision(2);
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatient>("Ravi", 500, 1200));
    bills.push_back(make_unique<InPatient>("Meena", 3, 2500, 30000, 2500));
    bills.push_back(make_unique<DayCare>("Arun", 25000));
    bills.push_back(make_unique<Emergency>("Kiran", 2000, 1000, 3));

    SelfPay self;
    Insurance insurance(50000, 20);
    GovernmentScheme government(30000);
    vector<const Payer*> payers = {&self, &insurance, &government};

    double grandTotal = 0.0;
    for (const auto& bill : bills) {
        bill->print();
        grandTotal += bill->total();
        for (const Payer* payer : payers) {
            cout << "  " << payer->name() << " covers Rs. "
                 << payer->amountCovered(*bill) << '\n';
        }
    }
    cout << "Hospital Total: Rs. " << grandTotal << '\n';
    return 0;
}
