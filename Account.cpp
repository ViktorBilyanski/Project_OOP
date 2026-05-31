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

void Account::displayInfo() const {
    cout << fixed << setprecision(2);
    cout << "  Smetka #: " << setw(12) << accountNumber
         << " | Titular: " << setw(18) << holderName
         << " | Balans: " << setw(10) << balance << " lv.\n";
}

void Account::displayHistory() const {
    cout << "\n--- Istoriq na transakcii: smetka " << accountNumber << " ---\n";
    if (transactionHistory.empty()) {
        cout << "  Nqma izvresheni transakcii.\n";
        return;
    }
    cout << left << setw(22) << "Tip"
         << " | " << setw(10) << "Data"
         << " | Suma\n";
    cout << string(52, '-') << "\n";
    for (const auto& tx : transactionHistory) {
        tx.display();
    }
    cout << string(52, '-') << "\n";
}
