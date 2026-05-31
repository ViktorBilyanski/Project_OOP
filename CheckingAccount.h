#pragma once
#include "Account.h"

using namespace std;
class CheckingAccount : public Account {
private:
    double transactionFee;
    double overdraftLimit;

public:
    CheckingAccount(string num, string name, double bal, double fee, double overdraft = 0.0);

    bool withdraw(double amount) override;
    double getTransactionFee() const;
    double getOverdraftLimit() const;
    string getType() const override;
    void displayInfo() const override;
};
