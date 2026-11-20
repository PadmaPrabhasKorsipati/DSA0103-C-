#include <iostream>
#include <memory>
#include <stdexcept>
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
    virtual ~Bill() = default;
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(string p, double c, double t)
        : Bill(move(p)), consultation(c), tests(t) {}
    double total() const override {
        if (consultation < 0 || tests < 0)
            throw invalid_argument("negative outpatient charge");
        return consultation + tests;
    }
    string type() const override { return "OutPatient"; }
};

class TelemedicineBill : public Bill {
    double consultationFee, platformFee;
public:
    TelemedicineBill(string p, double c, double f)
        : Bill(move(p)), consultationFee(c), platformFee(f) {}
    double total() const override {
        if (consultationFee < 0 || platformFee < 0)
            throw invalid_argument("negative telemedicine charge");
        return consultationFee + platformFee;
    }
    string type() const override { return "Telemedicine"; }
};

class Payer {
public:
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual ~Payer() = default;
};

class Insurance : public Payer {
    double limit, copay;
public:
    Insurance(double l, double c) : limit(l), copay(c) {}
    double amountCovered(const Bill& bill) const override {
        if (limit < 0 || copay < 0 || copay > 100)
            throw invalid_argument("invalid insurance policy");
        double eligible = bill.total() < limit ? bill.total() : limit;
        return eligible * (1.0 - copay / 100.0);
    }
};

class CorporatePayer : public Payer {
    double coveragePercent;
public:
    explicit CorporatePayer(double p) : coveragePercent(p) {}
    double amountCovered(const Bill& bill) const override {
        if (coveragePercent < 0 || coveragePercent > 100)
            throw invalid_argument("invalid corporate coverage");
        return bill.total() * coveragePercent / 100.0;
    }
};

int main() {
    try {
        vector<unique_ptr<Bill>> bills;
        bills.push_back(make_unique<OutPatientBill>("Ravi", 500, 1200));
        bills.push_back(make_unique<TelemedicineBill>("Anu", 800, 200));

        Insurance insurance(50000, 20);
        CorporatePayer corporate(50);

        for (const auto& bill : bills) {
            cout << bill->type() << " total: Rs. " << bill->total() << '\n';
            cout << "Insurance covers: Rs. "
                 << insurance.amountCovered(*bill) << '\n';
            cout << "Corporate covers: Rs. "
                 << corporate.amountCovered(*bill) << '\n';
        }

        try {
            OutPatientBill invalid("Test", -10, 100);
            cout << invalid.total() << '\n';
        } catch (const exception& e) {
            cout << "Handled billing exception: " << e.what() << '\n';
        }
    } catch (const exception& e) {
        cout << "Top-level error: " << e.what() << '\n';
    }

    cout << "All managed objects leave scope safely\n";
    return 0;
}
