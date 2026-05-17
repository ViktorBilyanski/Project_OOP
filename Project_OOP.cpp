#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <clocale>

using namespace std;

// 1. Клас за история на транзакциите
class Transaction {
private:
    string type;
    double amount;
public:
    Transaction(string t, double a) : type(t), amount(a) {}
    
    void display() const {
        cout << left << setw(15) << type 
             << " | Сума: " << fixed << setprecision(2) << amount << " лв.\n";
    }
};

// 2. Базов абстрактен клас за Сметка
class Account {
protected:
    string accountNumber;
    string holderName;
    double balance;
    vector<Transaction> transactionHistory;

public:
    Account(string num, string name, double initialBalance)
        : accountNumber(num), holderName(name), balance(initialBalance) {
        if (initialBalance > 0) {
            transactionHistory.push_back(Transaction("Първоначален деп.", initialBalance));
        }
    }

    virtual ~Account() = default; // Виртуален деструктор - задължителен за полиморфизъм

    // Споделена функционалност за депозиране
    virtual bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        transactionHistory.push_back(Transaction("Депозит", amount));
        return true;
    }

    // Чисто виртуална функция за теглене (абстрактен метод)
    virtual bool withdraw(double amount) = 0;

    // Справка за баланс и детайли
    virtual void displayInfo() const {
        cout << "Сметка #: " << accountNumber << " | Титуляр: " << holderName 
             << " | Баланс: " << balance << " лв.\n";
    }

    void displayHistory() const {
        cout << "\n--- История на транзакциите за сметка " << accountNumber << " ---\n";
        if (transactionHistory.empty()) {
            cout << "Няма извършени транзакции.\n";
            return;
        }
        for (const auto& tx : transactionHistory) {
            tx.display();
        }
    }

    // Гетери за трансферите
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
    
    // Помощна функция за добавяне на външна транзакция (напр. при превод)
    void logExternalTransaction(string type, double amount) {
        transactionHistory.push_back(Transaction(type, amount));
    }
    
    // Директна промяна на баланса само при вътрешен превод
    void forceUpdateBalance(double amount) {
        balance += amount;
    }
};

// 3. Производен клас: Спестовна сметка
class SavingsAccount : public Account {
private:
    double interestRate; // напр. 0.02 за 2%

public:
    SavingsAccount(string num, string name, double bal, double rate)
        : Account(num, name, bal), interestRate(rate) {}

    bool withdraw(double amount) override {
        // Примерно правило: Не може да се тегли, ако балансът пада под 10 лв.
        if (amount <= 0 || (balance - amount) < 10.0) {
            return false;
        }
        balance -= amount;
        transactionHistory.push_back(Transaction("Теглене (Спест.)", amount));
        return true;
    }

    void applyInterest() {
        double interest = balance * interestRate;
        balance += interest;
        transactionHistory.push_back(Transaction("Лихва", interest));
        cout << "Начислена е лихва: " << interest << " лв.\n";
    }

    void displayInfo() const override {
        cout << "[Спестовна] ";
        Account::displayInfo();
    }
};

// 4. Производен клас: Разплащателна сметка
class CheckingAccount : public Account {
private:
    double transactionFee; // Такса за теглене

public:
    CheckingAccount(string num, string name, double bal, double fee)
        : Account(num, name, bal), transactionFee(fee) {}

    bool withdraw(double amount) override {
        // Трябва да има достатъчно пари за сумата + таксата
        double totalDeduction = amount + transactionFee;
        if (amount <= 0 || balance < totalDeduction) {
            return false;
        }
        balance -= totalDeduction;
        transactionHistory.push_back(Transaction("Теглене (Разпл.)", amount));
        transactionHistory.push_back(Transaction("Такса теглене", transactionFee));
        return true;
    }

    void displayInfo() const override {
        cout << "[Разплащателна] ";
        Account::displayInfo();
    }
};

// 5. Клас за управление на Банковата Система
class BankSystem {
private:
    vector<shared_ptr<Account>> accounts;

public:
    void addAccount(shared_ptr<Account> acc) {
        accounts.push_back(acc);
    }

    shared_ptr<Account> findAccount(const string& num) {
        for (auto& acc : accounts) {
            if (acc->getAccountNumber() == num) return acc;
        }
        return nullptr;
    }

    // Функционалност: Справка за всички баланси (Полиморфизъм в действие)
    void showAllAccounts() const {
        cout << "\n=== ВСИЧКИ СМЕТКИ В СИСТЕМАТА ===\n";
        for (const auto& acc : accounts) {
            acc->displayInfo();
        }
    }

    // Функционалност: Превод между сметки
    bool transfer(const string& fromNum, const string& toNum, double amount) {
        auto fromAcc = findAccount(fromNum);
        auto toAcc = findAccount(toNum);

        if (!fromAcc || !toAcc || amount <= 0) {
            cout << "Грешка: Невалидни сметки или сума!\n";
            return false;
        }

        // Опит за теглене от изпращача
        if (fromAcc->withdraw(amount)) {
            // Депозиране при получателя
            toAcc->deposit(amount);
            
            // Корекция на логването за по-яснота в историята
            fromAcc->logExternalTransaction("Превод към " + toNum, amount);
            return true;
        }
        
        cout << "Грешка: Недостиг на средства в сметка " << fromNum << "\n";
        return false;
    }
};

// Главна функция за демонстрация на работещите функционалности
int main() {
    // Настройка на локализация за правилно изписване на български в конзолата
    setlocale(LC_ALL, "bg_BG.UTF-8");

    BankSystem bank;

    // 1. Инициализиране на сметки (Класова йерархия със смарт указатели)
    auto sa = make_shared<SavingsAccount>("BG01SAV", "Иван Иванов", 1000.0, 0.02);
    auto ca = make_shared<CheckingAccount>("BG02CHK", "Петър Петров", 500.0, 1.50);

    bank.addAccount(sa);
    bank.addAccount(ca);

    cout << "--- Демонстрация на Функционалностите (Чекпойнт 2) ---\n";

    // Функционалност 1: Справка за баланс
    bank.showAllAccounts();

    // Функционалност 2: Операции Депозиране и Теглене (със специфични правила)
    cout << "\n* Извършване на операции депозиране и теглене... *\n";
    sa->deposit(200);   // Баланс: 1200
    ca->withdraw(100);  // Баланс: 500 - 100 - 1.50 (такса) = 398.50
    
    bank.showAllAccounts();

    // Функционалност 3: Превод между сметки
    cout << "\n* Извършване на превод от Спестовна към Разплащателна сметка... *\n";
    if (bank.transfer("BG01SAV", "BG02CHK", 300.0)) {
        cout << "Преводът е успешен!\n";
    }
    
    bank.showAllAccounts();

    // Функционалност 4: История на транзакциите
    sa->displayHistory();
    ca->displayHistory();

    return 0;
}