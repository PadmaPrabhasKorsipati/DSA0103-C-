#include <iostream>
#include <string>

class Address {
    std::string city;
    int pin;
public:
    Address(const std::string& c, int p) : city(c), pin(p) {
        std::cout << "Address+ ";
    }
    ~Address() { std::cout << "~Address "; }
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class Course {
    std::string title;
public:
    explicit Course(const std::string& t) : title(t) {
        std::cout << "Course+ ";
    }
    ~Course() { std::cout << "~Course "; }
};

class Person {
protected:
    std::string name;
    int age;
    Address home;
public:
    Person(const std::string& n, int a, const std::string& city, int pin)
        : name(n), age(a), home(city, pin) {
        std::cout << "Person+ ";
    }
    virtual ~Person() { std::cout << "~Person "; }
};

class Student : virtual public Person {
protected:
    long long regNo;
    Course course;
public:
    Student(const std::string& n, int a, long long reg,
            const std::string& city, int pin, const std::string& c)
        : Person(n, a, city, pin), regNo(reg), course(c) {
        std::cout << "Student+ ";
    }
    ~Student() override { std::cout << "~Student "; }
    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") "
                  << home.str() << '\n';
    }
};

class Staff : virtual public Person {
protected:
    std::string department;
public:
    Staff(const std::string& n, int a, const std::string& city, int pin,
          const std::string& dept)
        : Person(n, a, city, pin), department(dept) {
        std::cout << "Staff+ ";
    }
    ~Staff() override { std::cout << "~Staff "; }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int a, long long reg,
                      const std::string& city, int pin, const std::string& courseName,
                      const std::string& dept)
        : Person(n, a, city, pin),
          Student(n, a, reg, city, pin, courseName),
          Staff(n, a, city, pin, dept) {
        std::cout << "TA+ ";
    }
    ~TeachingAssistant() override { std::cout << "~TA "; }
};

int main() {
    std::cout << "TASK 3 - CONSTRUCTION AND DESTRUCTION ORDER\n";
    std::cout << "Student object:\n";
    {
        Student s("Kavya", 19, 192311001, "Salem", 636001, "C++ OOP");
        s.print();
    }
    std::cout << "\nStaff object:\n";
    {
        Staff staff("Ravi", 38, "Chennai", 600001, "IT");
    }
    std::cout << "\nTeachingAssistant object:\n";
    {
        TeachingAssistant ta("Meena", 22, 192311010, "Vellore", 632001,
                             "Inheritance", "CSE");
    }
    std::cout << "\nMember initializer-list example:\n";
    Student completed("Kavya", 19, 192311001, "Salem", 636001, "C++ OOP");
    completed.print();
}