#include <iostream>
using namespace std;

class Bill {
public:
    virtual double total() const = 0;

    void show() const {
        cout << total() << ' ';
    }

    virtual ~Bill() {
        cout << "~Bill ";
    }
};

class OPBill : public Bill {
public:
    double total() const override { return 500.0; }

    ~OPBill() override {
        cout << "~OPBill ";
    }
};

class IPBill : public Bill {
public:
    double total() const override { return 1200.0; }

    ~IPBill() override {
        cout << "~IPBill ";
    }
};

int main() {
    Bill* b = new OPBill;
    b->show();
    delete b;
    cout << '\n';

    Bill* second = new IPBill;
    second->show();
    delete second;
    cout << '\n';
    return 0;
}
