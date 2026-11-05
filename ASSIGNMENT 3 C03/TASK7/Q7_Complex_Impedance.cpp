#include <cmath>
#include <iostream>
#include <stdexcept>
#include <iomanip>

class Complex {
    double real, imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(double r) : real(r), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& z) const {
        return Complex(real + z.real, imag + z.imag);
    }
    Complex operator-(const Complex& z) const {
        return Complex(real - z.real, imag - z.imag);
    }
    Complex operator*(const Complex& z) const {
        return Complex(real * z.real - imag * z.imag,
                       real * z.imag + imag * z.real);
    }
    Complex operator/(const Complex& z) const {
        double denominator = z.real * z.real + z.imag * z.imag;
        if (denominator == 0.0) throw std::domain_error("Division by zero impedance");
        return Complex((real * z.real + imag * z.imag) / denominator,
                       (imag * z.real - real * z.imag) / denominator);
    }
    bool operator==(const Complex& z) const {
        const double eps = 1e-9;
        return std::abs(real - z.real) < eps && std::abs(imag - z.imag) < eps;
    }
    double magnitude() const { return std::sqrt(real * real + imag * imag); }

    friend std::ostream& operator<<(std::ostream& out, const Complex& z) {
        out << std::fixed << std::setprecision(2) << z.real;
        if (z.imag >= 0) out << " + j" << z.imag;
        else out << " - j" << -z.imag;
        return out;
    }
};

int main() {
    const double pi = std::acos(-1.0);
    const double frequency = 50.0;
    const double omega = 2.0 * pi * frequency;
    const double R = 100.0, L = 0.1, C = 100e-6;

    Complex resistor(R, 0);
    Complex inductor(0, omega * L);
    Complex capacitor(0, -1.0 / (omega * C));

    Complex series = resistor + inductor + capacitor;
    Complex parallel = (resistor * inductor) / (resistor + inductor);

    std::cout << "Q7 - AC Circuit Complex Impedance\n";
    std::cout << "Resistor: " << resistor << '\n';
    std::cout << "Inductor: " << inductor << '\n';
    std::cout << "Capacitor: " << capacitor << '\n';
    std::cout << "Series RLC impedance: " << series << '\n';
    std::cout << "Series magnitude: " << series.magnitude() << " ohms\n";
    std::cout << "Parallel R-L impedance: " << parallel << '\n';
    std::cout << "Parallel magnitude: " << parallel.magnitude() << " ohms\n";

    try {
        Complex invalid = resistor / Complex(0, 0);
        std::cout << invalid << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "Zero-division test: " << e.what() << '\n';
    }
}