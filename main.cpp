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
