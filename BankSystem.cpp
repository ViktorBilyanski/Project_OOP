#include "BankSystem.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;

BankSystem::BankSystem(string name)
    : bankName(name), totalTransactions(0.0), transactionCount(0) {}

void BankSystem::addAccount(shared_ptr<Account> acc) {
    // Check for duplicate account number
    if (findAccount(acc->getAccountNumber())) {
        cout << "  [GRESHKA] Smetka " << acc->getAccountNumber() << " veche sashtestvuva!\n";
        return;
    }
    accounts.push_back(acc);
    cout << "  [OK] Smetka " << acc->getAccountNumber()
         << " za " << acc->getHolderName() << " e dobavena uspeshno.\n";
}

bool BankSystem::removeAccount(const string& num) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if ((*it)->getAccountNumber() == num) {
            cout << "  [OK] Smetka " << num << " e izlichena.\n";
            accounts.erase(it);
            return true;
        }
    }
    cout << "  [GRESHKA] Smetka " << num << " ne e nameren.\n";
    return false;
}

shared_ptr<Account> BankSystem::findAccount(const string& num) {
    for (auto& acc : accounts) {
        if (acc->getAccountNumber() == num) return acc;
    }
    return nullptr;
}

bool BankSystem::transfer(const string& fromNum, const string& toNum, double amount) {
    auto fromAcc = findAccount(fromNum);
    auto toAcc   = findAccount(toNum);

    if (fromNum == toNum) {
        cout << "  [GRESHKA] Ne moga da pravq prevod kam sashtata smetka!\n";
        return false;
    }
    if (!fromAcc) {
        cout << "  [GRESHKA] Izprashtacha smetka " << fromNum << " ne e nameren!\n";
        return false;
    }
    if (!toAcc) {
        cout << "  [GRESHKA] Poluchatelskata smetka " << toNum << " ne e nameren!\n";
        return false;
    }
    if (amount <= 0) {
        cout << "  [GRESHKA] Sumata za prevod trqbva da e polozhitelna!\n";
        return false;
    }

    if (fromAcc->withdraw(amount)) {
        toAcc->deposit(amount);
        // Log the transfer as a distinct transaction type for clarity
        fromAcc->logExternalTransaction("Prevod -> " + toNum, amount);
        toAcc->logExternalTransaction("Prevod <- " + fromNum, amount);
        totalTransactions += amount;
        transactionCount++;
        cout << "  [OK] Prevod " << fixed << setprecision(2) << amount
             << " lv. ot " << fromNum << " kam " << toNum << " e uspeshen.\n";
        return true;
    }
    return false;
}
