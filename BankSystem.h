#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Account.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"

using std::string;
using std::vector;
using std::shared_ptr;

class BankSystem {
private:
    vector<shared_ptr<Account>> accounts;
    string bankName;
    double totalTransactions;
    int transactionCount;

public:
    BankSystem(string name = "OOP Bank");

    // Account management
    void addAccount(shared_ptr<Account> acc);
    bool removeAccount(const string& num);
    shared_ptr<Account> findAccount(const std::string& num);

    // Core operations
    bool transfer(const std::string& fromNum, const std::string& toNum, double amount);
    void applyInterestToAll();

    // Reporting / display
    void showAllAccounts() const;
    void showBankStats() const;
    void showAccountHistory(const string& num) const;
    void showAccountsByBalance() const;
    void showAccountsByHolder(const string& name) const;

    // Getters
    int getAccountCount() const;
    double getTotalDeposits() const;
    double getTotalByType(const string& type) const;

    // Export
    bool exportReport(const string& filename) const;
};
// already closed above - need to edit properly
