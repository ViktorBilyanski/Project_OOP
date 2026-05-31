#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

static string getCurrentDate() {
    time_t now = time(nullptr);
    char buf[11];
    strftime(buf, sizeof(buf), "%d.%m.%Y", localtime(&now));
    return string(buf);
}

Transaction::Transaction(string t, double a, string d)
    : type(t), amount(a), date(d.empty() ? getCurrentDate() : d) {}

void Transaction::display() const {
    cout << left << setw(22) << type
         << " | " << setw(10) << date
         << " | Suma: " << fixed << setprecision(2) << setw(10) << amount << " lv.\n";
}

string Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
string Transaction::getDate() const { return date; }
