#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class BillingError : public runtime_error {
public:
    using runtime_error::runtime_error;
};

class InvalidChargeError : public BillingError {
public:
    using BillingError::BillingError;
};

class ClaimError : public BillingError {
public:
    using BillingError::BillingError;
};

class UnknownPackageError : public BillingError {
public:
    using BillingError::BillingError;
};

class PatientNotFoundError : public BillingError {
public:
    using BillingError::BillingError;
};

double validateCharge(double amount) {
    if (amount < 0.0)
        throw InvalidChargeError("negative charge");
    return amount;
}

double approveClaim(double billed, double cover) {
    if (billed < 0.0 || cover < 0.0)
        throw InvalidChargeError("negative claim or cover");
    if (billed > cover)
        throw ClaimError("claim exceeds insurance cover");
    return billed;
}

double packageRate(const string& code) {
    if (code == "SURG-A") return 25000.0;
    if (code == "SURG-B") return 40000.0;
    throw UnknownPackageError("unknown package code: " + code);
}

void requirePatient(const string& patientId) {
    if (patientId.empty())
        throw PatientNotFoundError("patient record is missing");
}

int main() {
    try {
        cout << "Valid charge: Rs. " << validateCharge(1200) << '\n';
        cout << "Valid claim: Rs. " << approveClaim(40000, 50000) << '\n';
        cout << "Package rate: Rs. " << packageRate("SURG-A") << '\n';
        requirePatient("P1001");

        try {
            validateCharge(-50);
        } catch (const InvalidChargeError& e) {
            cout << "Charge error: " << e.what() << '\n';
        }

        try {
            approveClaim(60000, 50000);
        } catch (const ClaimError& e) {
            cout << "Claim error: " << e.what() << '\n';
        }

        try {
            packageRate("UNKNOWN");
        } catch (const UnknownPackageError& e) {
            cout << "Package error: " << e.what() << '\n';
        }

        try {
            requirePatient("");
        } catch (const PatientNotFoundError& e) {
            cout << "Patient error: " << e.what() << '\n';
        }

        try {
            throw bad_alloc();
        } catch (const bad_alloc&) {
            cout << "Allocation error: simulated std::bad_alloc\n";
        }
    } catch (const exception& e) {
        cout << "Top-level billing error: " << e.what() << '\n';
    }

    cout << "Program continues safely\n";
    return 0;
}
