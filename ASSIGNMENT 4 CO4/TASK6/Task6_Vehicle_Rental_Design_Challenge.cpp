#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Vehicle {
private:
    std::string registration;
    double dailyRate;
    bool rented = false;
public:
    Vehicle(const std::string& reg, double rate)
        : registration(reg), dailyRate(rate) {}
    virtual ~Vehicle() = default;

    std::string getRegistration() const { return registration; }
    double getDailyRate() const { return dailyRate; }
    bool isRented() const { return rented; }

    bool rent() {
        if (rented) return false;
        rented = true;
        return true;
    }
    double returnVehicle(int lateDays) {
        if (!rented) return 0;
        rented = false;
        return rentalCharge(1) + (lateDays > 0 ? lateDays * dailyRate * 0.5 : 0);
    }

    virtual double rentalCharge(int days) const = 0;
    virtual void display() const = 0;
};

class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate) : Vehicle(reg, rate) {}
    double rentalCharge(int days) const override { return getDailyRate() * days; }
    void display() const override {
        std::cout << "Bicycle " << getRegistration() << " | daily Rs "
                  << getDailyRate() << '\n';
    }
};

class MotorVehicle : public Vehicle {
private:
    double fuelLevel;
    std::string serviceDue;
protected:
    MotorVehicle(const std::string& reg, double rate, double fuel,
                 const std::string& due)
        : Vehicle(reg, rate), fuelLevel(fuel), serviceDue(due) {}
    double fuel() const { return fuelLevel; }
    std::string dueDate() const { return serviceDue; }
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(const std::string& reg, double rate, double fuel,
               const std::string& due)
        : MotorVehicle(reg, rate, fuel, due) {}
    double rentalCharge(int days) const override { return getDailyRate() * days; }
    void display() const override {
        std::cout << "TwoWheeler " << getRegistration() << " | fuel "
                  << fuel() << "% | service " << dueDate() << '\n';
    }
};

class Car : public MotorVehicle {
private:
    int seats;
public:
    Car(const std::string& reg, double rate, double fuel,
        const std::string& due, int capacity)
        : MotorVehicle(reg, rate, fuel, due), seats(capacity) {}
    double rentalCharge(int days) const override { return getDailyRate() * days; }
    void display() const override {
        std::cout << "Car " << getRegistration() << " | seats " << seats
                  << " | fuel " << fuel() << "% | service " << dueDate() << '\n';
    }
};

class ElectricCar : public Vehicle {
private:
    double batteryKWh;
    double ratePerKWh;
public:
    ElectricCar(const std::string& reg, double daily, double battery, double kwhRate)
        : Vehicle(reg, daily), batteryKWh(battery), ratePerKWh(kwhRate) {}
    double rentalCharge(int days) const override {
        return getDailyRate() * days + batteryKWh * ratePerKWh;
    }
    void display() const override {
        std::cout << "ElectricCar " << getRegistration() << " | battery "
                  << batteryKWh << " kWh | charge rate Rs " << ratePerKWh << "/kWh\n";
    }
};

class ElectricBus : public Vehicle {
private:
    int seats;
    double batteryKWh;
    double ratePerKWh;
public:
    ElectricBus(const std::string& reg, double daily, int capacity,
                double battery, double kwhRate)
        : Vehicle(reg, daily), seats(capacity), batteryKWh(battery),
          ratePerKWh(kwhRate) {}
    double rentalCharge(int days) const override {
        return getDailyRate() * days + batteryKWh * ratePerKWh;
    }
    void display() const override {
        std::cout << "ElectricBus " << getRegistration() << " | seats " << seats
                  << " | battery " << batteryKWh << " kWh\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("BI-101", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("TW-202", 250, 75, "2026-12-01"));
    fleet.push_back(std::make_unique<Car>("CA-303", 1500, 60, "2026-11-20", 5));
    fleet.push_back(std::make_unique<ElectricCar>("EV-404", 1800, 45, 8));

    std::cout << "TASK 6 - VEHICLE RENTAL FLEET\n";
    std::cout << "Fleet listing:\n";
    for (const auto& vehicle : fleet) vehicle->display();

    std::cout << "Rent and return demonstration (one rental day):\n";
    for (const auto& vehicle : fleet) {
        if (vehicle->rent()) {
            double charge = vehicle->returnVehicle(1);
            std::cout << vehicle->getRegistration()
                      << " returned late; total charge Rs " << charge << '\n';
        }
    }

    std::cout << "Adding new vehicle type without changing existing classes:\n";
    fleet.push_back(std::make_unique<ElectricBus>("EB-505", 5000, 40, 180, 10));
    fleet.back()->display();
    std::cout << "Total vehicles: " << fleet.size() << '\n';
}