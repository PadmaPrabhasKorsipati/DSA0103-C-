#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Bill {
public:
    virtual double total() const = 0;
    virtual string type() const = 0;
    virtual ~Bill() = default;
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(double c, double t) : consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    string type() const override { return "OutPatient"; }
};

class InPatientBill : public Bill {
    int days;
    double rate, procedures, medicines;
public:
    InPatientBill(int d, double r, double p, double m)
        : days(d), rate(r), procedures(p), medicines(m) {}
    double total() const override { return days * rate + procedures + medicines; }
    string type() const override { return "InPatient"; }
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
    double coverLimit;
    double coPaymentPercent;
public:
    Insurance(double limit, double copay)
        : coverLimit(limit), coPaymentPercent(copay) {}
    double amountCovered(const Bill& bill) const override {
        double eligible = min(bill.total(), coverLimit);
        return eligible * (1.0 - coPaymentPercent / 100.0);
    }
    string name() const override { return "Insurance"; }
};

class GovernmentScheme : public Payer {
    double fixedPackageRate;
public:
    explicit GovernmentScheme(double rate) : fixedPackageRate(rate) {}
    double amountCovered(const Bill& bill) const override {
        return min(bill.total(), fixedPackageRate);
    }
    string name() const override { return "GovernmentScheme"; }
};

class CorporatePayer : public Payer {
    double coveragePercent;
public:
    explicit CorporatePayer(double percent) : coveragePercent(percent) {}
    double amountCovered(const Bill& bill) const override {
        return bill.total() * coveragePercent / 100.0;
    }
    string name() const override { return "CorporatePayer"; }
};

int main() {
    OutPatientBill op(500, 1200);
    InPatientBill ip(3, 2500, 30000, 2500);

    SelfPay self;
    Insurance insurance(50000, 20);
    GovernmentScheme government(30000);
    CorporatePayer corporate(50);

    vector<const Payer*> payers = {&self, &insurance, &government, &corporate};
    vector<const Bill*> bills = {&op, &ip};

    for (const Bill* bill : bills) {
        cout << bill->type() << " total: Rs. " << bill->total() << '\n';
        for (const Payer* payer : payers) {
            cout << "  " << payer->name() << " covers Rs. "
                 << payer->amountCovered(*bill) << '\n';
        }
    }
    return 0;
}
