#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {
private:
    std::string name;
    int id;
protected:
    Staff(const std::string& n, int staffId) : name(n), id(staffId) {}
public:
    virtual ~Staff() = default;
    std::string getName() const { return name; }
    int getId() const { return id; }
    virtual double pay() const = 0;
    virtual void print() const {
        std::cout << getName() << " (ID " << getId() << ") Pay: Rs "
                  << pay() << '\n';
    }
};

class Professor : public Staff {
private:
    double basic, research;
public:
    Professor(const std::string& n, int id, double b, double r)
        : Staff(n, id), basic(b), research(r) {}
    double pay() const override { return basic + basic * 0.42 + research; }
};

class LabAssistant : public Staff {
private:
    double basic;
public:
    LabAssistant(const std::string& n, int id, double b)
        : Staff(n, id), basic(b) {}
    double pay() const override { return basic + basic * 0.42; }
};

class GuestFaculty : public Staff {
private:
    double hours, rate;
public:
    GuestFaculty(const std::string& n, int id, double h, double r)
        : Staff(n, id), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};

int main() {
    std::vector<std::unique_ptr<Staff>> payroll;
    payroll.push_back(std::make_unique<Professor>("Anitha", 101, 50000, 8000));
    payroll.push_back(std::make_unique<LabAssistant>("Rahul", 102, 30000));
    payroll.push_back(std::make_unique<GuestFaculty>("Meera", 103, 40, 900));

    std::cout << "TASK 1 - CLASS DESIGN REVIEW\n";
    std::cout << "Polymorphic payroll report\n";
    for (const auto& member : payroll) member->print();
    std::cout << "Staff categories processed in one loop: " << payroll.size() << '\n';
    std::cout << "Base class is abstract: common identity + virtual pay().\n";
}