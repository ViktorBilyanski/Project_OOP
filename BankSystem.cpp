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

void BankSystem::applyInterestToAll() {
    cout << "\n  -- Nachislqvane na lihva na vsichki spestovni smetki --\n";
    int count = 0;
    for (auto& acc : accounts) {
        auto* sa = dynamic_cast<SavingsAccount*>(acc.get());
        if (sa) {
            sa->applyInterest();
            count++;
        }
    }
    if (count == 0) cout << "  Nqma spestovni smetki v sistemata.\n";
}

void BankSystem::showAllAccounts() const {
    cout << "\n=== " << bankName << " - VSICHKI SMETKI (" << accounts.size() << ") ===\n";
    if (accounts.empty()) {
        cout << "  Nqma registrirani smetki.\n";
        return;
    }
    for (const auto& acc : accounts) {
        acc->displayInfo();
        cout << "\n";
    }
}

void BankSystem::showBankStats() const {
    cout << "\n=== STATISTIKA: " << bankName << " ===\n";
    cout << "  Broi smetki:                " << accounts.size() << "\n";
    cout << "  Broi prevodi:               " << transactionCount << "\n";
    cout << "  Obshta suma prevodi:        " << fixed << setprecision(2) << totalTransactions << " lv.\n";

    double total = 0;
    for (const auto& acc : accounts) total += acc->getBalance();
    cout << "  Obshto pod upravlenie:      " << total << " lv.\n";
    cout << "  -> Spestovni smetki:        " << getTotalByType("Spestovna") << " lv.\n";
    cout << "  -> Razplashtatelni smetki:  " << getTotalByType("Razplashtatelna") << " lv.\n";
}

void BankSystem::showAccountHistory(const string& num) const {
    for (const auto& acc : accounts) {
        if (acc->getAccountNumber() == num) {
            acc->displayHistory();
            return;
        }
    }
    cout << "  [GRESHKA] Smetka " << num << " ne e nameren.\n";
}

void BankSystem::showAccountsByBalance() const {
    cout << "\n=== SMETKI NAREDITBI PO BALANS (namalavasht) ===\n";
    vector<shared_ptr<Account>> sorted = accounts;
    sort(sorted.begin(), sorted.end(),
         [](const shared_ptr<Account>& a, const shared_ptr<Account>& b) {
             return a->getBalance() > b->getBalance();
         });
    int rank = 1;
    for (const auto& acc : sorted) {
        cout << "  #" << rank++ << " ";
        acc->displayInfo();
    }
}

int BankSystem::getAccountCount() const { return (int)accounts.size(); }

double BankSystem::getTotalDeposits() const {
    double total = 0;
    for (const auto& acc : accounts) total += acc->getBalance();
    return total;
}

bool BankSystem::exportReport(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "  [GRESHKA] Ne moga da otvorq fail: " << filename << "\n";
        return false;
    }
    file << "=== " << bankName << " - OTCHET ===\n";
    file << "Broi smetki: " << accounts.size() << "\n";
    file << fixed << setprecision(2);
    double total = 0;
    for (const auto& acc : accounts) {
        file << acc->getAccountNumber() << " | "
             << acc->getHolderName() << " | "
             << acc->getType() << " | "
             << acc->getBalance() << " lv.\n";
        total += acc->getBalance();
    }
    file << "OBSHTO: " << total << " lv.\n";
    file.close();
    cout << "  [OK] Otcheta e zapisan v: " << filename << "\n";
    return true;
}

void BankSystem::showAccountsByHolder(const string& name) const {
    cout << "\n=== TARSENE PO TITULAR: \"" << name << "\" ===\n";
    bool found = false;
    for (const auto& acc : accounts) {
        if (acc->getHolderName().find(name) != string::npos) {
            acc->displayInfo();
            found = true;
        }
    }
    if (!found) cout << "  Nqma smetki za titular: " << name << "\n";
}

// Utility: total balance for a specific account type
double BankSystem::getTotalByType(const string& type) const {
    double total = 0;
    for (const auto& acc : accounts) {
        if (acc->getType() == type) total += acc->getBalance();
    }
    return total;
}
