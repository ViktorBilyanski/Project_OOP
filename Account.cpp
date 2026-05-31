#include "Account.h"
#include <iostream>
#include <iomanip>

using namespace std;

Account::Account(string num, string name, double initialBalance)
    : accountNumber(num), holderName(name), balance(initialBalance) {
    if (initialBalance > 0) {
        transactionHistory.push_back(Transaction("Nachalen depozit", initialBalance));
    }
}

bool Account::deposit(double amount) {
    if (amount <= 0) {
        cout << "  [GRESHKA] Sumata za depozit trqbva da e polozhitelna!\n";
        return false;
    }
    balance += amount;
    transactionHistory.push_back(Transaction("Depozit", amount));
    return true;
}
