#pragma once
#include <string>
#include <vector>
#include "Transaction.h"

using std::string;
using std::vector;

class Account {
protected:
    string accountNumber;
    string holderName;
    double balance;
    vector<Transaction> transactionHistory;
public:
    Account(string num, string name, double initialBalance);
    virtual ~Account() = default;

    virtual bool deposit(double amount);
    virtual bool withdraw(double amount) = 0;
    virtual void displayInfo() const;
    virtual string getType() const = 0;

    void displayHistory() const;
    double getBalance() const;
    string getAccountNumber() const;
    string getHolderName() const;
    void logExternalTransaction(string type, double amount);
};
