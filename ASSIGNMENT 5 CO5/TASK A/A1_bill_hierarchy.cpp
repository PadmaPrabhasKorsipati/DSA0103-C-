#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Bill {
protected:
    string patient;
    int billId;

public:
    Bill(string name, int id) : patient(name), billId(id) {}
    virtual double total() const = 0;
    virtual string type() const = 0;

    virtual void print() const {
        cout << type() << " | Bill " << billId << " | " << patient
             << " | Rs. " << total() << '\n';
    }

    virtual ~Bill() = default;
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(string p, int id, double c, double t)
        : Bill(p, id), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    string type() const override { return "OutPatient"; }
};

class InPatientBill : public Bill {
    int days;
    double roomRate, procedures, medicines;
public:
    InPatientBill(string p, int id, int d, double rate, double proc, double med)
        : Bill(p, id), days(d), roomRate(rate), procedures(proc), medicines(med) {}
    double total() const override {
        return days * roomRate + procedures + medicines;
    }
    string type() const override { return "InPatient"; }
};

class DayCareBill : public Bill {
    double packagePrice;
public:
    DayCareBill(string p, int id, double price)
        : Bill(p, id), packagePrice(price) {}
    double total() const override { return packagePrice; }
    string type() const override { return "DayCare"; }
};

class EmergencyBill : public Bill {
    double baseCharge, hourlyRate, hours;
public:
    EmergencyBill(string p, int id, double base, double rate, double h)
        : Bill(p, id), baseCharge(base), hourlyRate(rate), hours(h) {}
    double total() const override { return baseCharge + hourlyRate * hours; }
    string type() const override { return "Emergency"; }
};

int main() {
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatientBill>("Ravi", 101, 500, 1200));
    bills.push_back(make_unique<InPatientBill>("Meena", 102, 3, 2500, 30000, 2500));
    bills.push_back(make_unique<DayCareBill>("Arun", 103, 25000));
    bills.push_back(make_unique<EmergencyBill>("Kiran", 104, 2000, 1000, 3));

    double dayTotal = 0.0;
    for (const auto& bill : bills) {
        bill->print();
        dayTotal += bill->total();
    }
    cout << "Day total: Rs. " << dayTotal << '\n';
    return 0;
}
