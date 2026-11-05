#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0;

public:
    Cart& add(const std::string& item, double price) {
        if (n < 10 && price >= 0) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    double total() const {
        double sum = 0;
        for (int i = 0; i < n; ++i) sum += prices[i];
        return sum * (100 - discount) / 100;
    }

    void print() const {
        std::cout << "Items: " << n << " Total: Rs "
                  << std::fixed << std::setprecision(2) << total() << '\n';
    }
};

int main() {
    std::cout << "TASK 5 - OBJECT POINTERS AND THIS POINTER\n";

    Cart direct;
    direct.add("Rice", 60).add("Dal", 120).setDiscount(10);
    std::cout << "Direct object: ";
    direct.print();

    Cart* pointer = &direct;
    pointer->add("Oil", 180);
    std::cout << "Pointer with ->: ";
    pointer->print();

    Cart& reference = direct;
    reference.add("Milk", 40);
    std::cout << "Reference: ";
    reference.print();

    Cart* dynamicCart = new Cart;
    dynamicCart->add("Bread", 50).setDiscount(5);
    std::cout << "Dynamic object: ";
    dynamicCart->print();
    delete dynamicCart;

    Cart customerA, customerB, customerC;
    customerA.add("A", 100);
    customerB.add("B", 250).setDiscount(10);
    customerC.add("C", 180);
    Cart* activeCarts[] = {&customerA, &customerB, &customerC};

    Cart* highest = activeCarts[0];
    for (Cart* current : activeCarts)
        if (current->total() > highest->total()) highest = current;

    std::cout << "Highest cart total: Rs " << highest->total() << '\n';
}