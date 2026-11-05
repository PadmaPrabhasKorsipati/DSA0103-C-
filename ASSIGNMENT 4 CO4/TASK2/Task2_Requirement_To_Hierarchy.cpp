#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;
public:
    Person(const std::string& n = "Unknown", int i = 0,
           const std::string& p = "Not set")
        : name(n), id(i), phone(p) {
        std::cout << "Person ";
    }
    void showPerson() const {
        std::cout << name << " ID:" << id << " Phone:" << phone;
    }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;
public:
    Student(const std::string& n, int i, const std::string& p,
            const std::string& prog, double g)
        : Person(n, i, p), programme(prog), cgpa(g) {
        std::cout << "Student ";
    }
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;
public:
    Staff(const std::string& n, int i, const std::string& p,
          const std::string& dept, double s)
        : Person(n, i, p), department(dept), salary(s) {
        std::cout << "Staff ";
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double g,
                      const std::string& dept, double s)
        : Person(n, i, p), Student(n, i, p, prog, g),
          Staff(n, i, p, dept, s) {
        std::cout << "TA ";
    }
    void display() const {
        showPerson();
        std::cout << " Programme:" << programme << " CGPA:" << cgpa
                  << " Department:" << department << " Salary:" << salary << '\n';
    }
};

class ResearchScholar : public Student {
private:
    double fellowship;
public:
    ResearchScholar(const std::string& n, int i, const std::string& p,
                    const std::string& prog, double g, double f)
        : Person(n, i, p), Student(n, i, p, prog, g), fellowship(f) {}
    void display() const {
        showPerson();
        std::cout << " Fellowship:Rs " << fellowship << '\n';
    }
};

int main() {
    std::cout << "TASK 2 - FROM REQUIREMENT TO HIERARCHY\n";
    std::cout << "Virtual diamond construction: ";
    TeachingAssistant ta("Kavya", 201, "9876543210", "CSE", 8.7,
                         "Computer Science", 35000);
    std::cout << '\n';
    std::cout << "Teaching assistant: ";
    ta.display();

    ResearchScholar scholar("Arun", 202, "9123456780", "ECE", 9.1, 18000);
    std::cout << "Research scholar: ";
    scholar.display();
}