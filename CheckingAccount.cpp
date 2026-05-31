#include "CheckingAccount.h"
#include <iostream>
#include <iomanip>

using namespace std;

CheckingAccount::CheckingAccount(string num, string name, double bal, double fee, double overdraft)
    : Account(num, name, bal), transactionFee(fee), overdraftLimit(overdraft) {}

bool CheckingAccount::withdraw(double amount) {
    if (amount <= 0) {
        cout << "  [GRESHKA] Sumata za teglene trqbva da e polozhitelna!\n";
        return false;
    }
    double totalDeduction = amount + transactionFee;
    // Allow overdraft up to the overdraftLimit
    if ((balance + overdraftLimit) < totalDeduction) {
        cout << "  [GRESHKA] Nedostatachno sredstva (vkl. taksa "
             << fixed << setprecision(2) << transactionFee << " lv.)!\n";
        return false;
    }
    balance -= totalDeduction;
    transactionHistory.push_back(Transaction("Teglene (Razpl.)", amount));
    if (transactionFee > 0) {
        transactionHistory.push_back(Transaction("Taksa teglene", transactionFee));
    }
    return true;
}

double CheckingAccount::getTransactionFee() const { return transactionFee; }
double CheckingAccount::getOverdraftLimit() const { return overdraftLimit; }
string CheckingAccount::getType() const { return "Razplashtatelna"; }

void CheckingAccount::displayInfo() const {
    cout << "  [RAZPLASHTATELNA]";
    Account::displayInfo();
    cout << "                   Taksa teglene: "
         << fixed << setprecision(2) << transactionFee
         << " lv. | Overdraft limit: " << overdraftLimit << " lv.\n";
}
