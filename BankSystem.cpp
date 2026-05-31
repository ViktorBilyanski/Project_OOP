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
