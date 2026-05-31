#include <iostream>
#include <iomanip>
#include <memory>
#include <limits>
#include "BankSystem.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"

using namespace std;

void printMenu() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "         OOP BANK BULGARIA - GLAVNO MENU\n";
    cout << string(60, '=') << "\n";
    cout << "  1.  Dobavi spestovna smetka\n";
    cout << "  2.  Dobavi razplashtatelna smetka\n";
    cout << "  3.  Depozit\n";
    cout << "  4.  Teglene\n";
    cout << "  5.  Prevod mezhdu smetki\n";
    cout << "  6.  Nachisli lihva (vsichki spestovni)\n";
    cout << "  7.  Istoriq na transakcii\n";
    cout << "  8.  Vsichki smetki po balans\n";
    cout << "  9.  Statistika na bankata\n";
    cout << "  10. Iztrii smetka\n";
    cout << "  11. Vsichki smetki\n";
    cout << "  12. Tarsene po titular\n";
    cout << "  13. Export na otchet vav fail\n";
    cout << "  0.  Izhod\n";
    cout << string(60, '-') << "\n";
    cout << "  Izbor: ";
}

// Helper: чете double и чисти буфера при грешка
double readDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [GRESHKA] Vuvedi validno chislo!\n";
    }
}

// Helper: чете цял ред (за имена с интервали)
string readLine(const string& prompt) {
    string val;
    cout << prompt;
    getline(cin, val);
    return val;
}

// Helper: чете string без интервали
string readWord(const string& prompt) {
    string val;
    cout << prompt;
    cin >> val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}

int main() {
    BankSystem bank("OOP Bank Bulgaria");
    int choice = -1;

    while (choice != 0) {
        printMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [GRESHKA] Vuvedi число!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n";

        if (choice == 1) {
            // Добави спестовна сметка
            cout << "--- Nova spestovna smetka ---\n";
            string num  = readWord("  Nomer na smetka (npr. BG01SAV): ");
            string name = readLine("  Ime na titular: ");
            double bal  = readDouble("  Nachalen balans (lv.): ");
            double rate = readDouble("  Lihven procent (npr. 0.03 za 3%): ");
            double minb = readDouble("  Minimalen balans (lv., default 10): ");
            bank.addAccount(make_shared<SavingsAccount>(num, name, bal, rate, minb));

        } else if (choice == 2) {
            // Добави разплащателна сметка
            cout << "--- Nova razplashtatelna smetka ---\n";
            string num  = readWord("  Nomer na smetka (npr. BG02CHK): ");
            string name = readLine("  Ime na titular: ");
            double bal  = readDouble("  Nachalen balans (lv.): ");
            double fee  = readDouble("  Taksa za teglene (lv.): ");
            double ovr  = readDouble("  Overdraft limit (lv., 0 za bez): ");
            bank.addAccount(make_shared<CheckingAccount>(num, name, bal, fee, ovr));

        } else if (choice == 3) {
            // Депозит
            cout << "--- Depozit ---\n";
            string num = readWord("  Nomer na smetka: ");
            double amt = readDouble("  Suma za depozit (lv.): ");
            auto acc = bank.findAccount(num);
            if (!acc) {
                cout << "  [GRESHKA] Smetka " << num << " ne e nameren.\n";
            } else {
                bool ok = acc->deposit(amt);
                cout << "  Rezultat: " << (ok ? "[USPESHNO]" : "[NEUSPESHNO]") << "\n";
                if (ok) cout << "  Nov balans: " << fixed << setprecision(2) << acc->getBalance() << " lv.\n";
            }
} else if (choice == 4) {
            // Теглене
            cout << "--- Teglene ---\n";
            string num = readWord("  Nomer na smetka: ");
            double amt = readDouble("  Suma za teglene (lv.): ");
            auto acc = bank.findAccount(num);
            if (!acc) {
                cout << "  [GRESHKA] Smetka " << num << " ne e nameren.\n";
            } else {
                bool ok = acc->withdraw(amt);
                cout << "  Rezultat: " << (ok ? "[USPESHNO]" : "[NEUSPESHNO]") << "\n";
                if (ok) cout << "  Nov balans: " << fixed << setprecision(2) << acc->getBalance() << " lv.\n";
            }

        } else if (choice == 5) {
            // Превод
            cout << "--- Prevod mezhdu smetki ---\n";
            string from = readWord("  Ot smetka (nomer): ");
            string to   = readWord("  Kam smetka (nomer): ");
            double amt  = readDouble("  Suma za prevod (lv.): ");
            bank.transfer(from, to, amt);

        } else if (choice == 6) {
            // Начисли лихва
            bank.applyInterestToAll();

        } else if (choice == 7) {
            // История
            cout << "--- Istoriq na transakcii ---\n";
            string num = readWord("  Nomer na smetka: ");
            bank.showAccountHistory(num);

        } else if (choice == 8) {
            // По баланс
            bank.showAccountsByBalance();

        } else if (choice == 9) {
            // Статистика
            bank.showBankStats();

        } else if (choice == 10) {
            // Изтрий
            cout << "--- Iztrivane na smetka ---\n";
            string num = readWord("  Nomer na smetka za iztrivane: ");
            bank.removeAccount(num);

        } else if (choice == 11) {
            // Всички сметки
            bank.showAllAccounts();

        } else if (choice == 12) {
            // Търсене по титуляр
            cout << "--- Tarsene po titular ---\n";
            string name = readLine("  Ime (ili chast ot ime): ");
            bank.showAccountsByHolder(name);

        } else if (choice == 13) {
            // Експорт
            cout << "--- Export na otchet ---\n";
            string filename = readWord("  Ime na fail (npr. report.txt): ");
            bank.exportReport(filename);

        } else if (choice == 0) {
            cout << "  Dovizhdane!\n";

        } else {
            cout << "  [GRESHKA] Nevalidna opciq. Opitai otnovo.\n";
        }
    }

    return 0;
}
