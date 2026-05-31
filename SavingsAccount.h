#pragma once
#include "Account.h"

using std::string;

class SavingsAccount : public Account {
private:
    double interestRate;
    double minimumBalance;

public:
    SavingsAccount(string num, string name, double bal, double rate, double minBal = 10.0);

    bool withdraw(double amount) override;
    void applyInterest();
    double getInterestRate() const;
    string getType() const override;
    void displayInfo() const override;
};
