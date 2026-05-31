#include "SavingsAccount.h"
#include <iostream>
#include <iomanip>

using namespace std;

SavingsAccount::SavingsAccount(string num, string name, double bal, double rate, double minBal)
    : Account(num, name, bal), interestRate(rate), minimumBalance(minBal) {}

bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0) {
        cout << "  [GRESHKA] Sumata za teglene trqbva da e polozhitelna!\n";
        return false;
    }
    if ((balance - amount) < minimumBalance) {
        cout << "  [GRESHKA] Tegleneto bi namalilo balansa pod minimuma ("
             << fixed << setprecision(2) << minimumBalance << " lv.)!\n";
        return false;
    }
    balance -= amount;
    transactionHistory.push_back(Transaction("Teglene (Spest.)", amount));
    return true;
}

void SavingsAccount::applyInterest() {
    double interest = balance * interestRate;
    balance += interest;
    transactionHistory.push_back(Transaction("Lihva", interest));
    cout << "  Nachislena e lihva (" << fixed << setprecision(1) << (interestRate * 100)
         << "%): " << fixed << setprecision(2) << interest << " lv. -> Nov balans: "
         << balance << " lv.\n";
}

double SavingsAccount::getInterestRate() const { return interestRate; }
string SavingsAccount::getType() const { return "Spestovna"; }

void SavingsAccount::displayInfo() const {
    cout << "  [SPESTOVNA]     ";
    Account::displayInfo();
    cout << "                   Lihven % : "
         << fixed << setprecision(2) << (interestRate * 100) << "% | Min. balans: "
         << minimumBalance << " lv.\n";
}
