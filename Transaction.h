#pragma once
#include <string>

using std::string;

class Transaction {
private:
    string type;
    double amount;
    string date;

public:
    Transaction(string t, double a, string d = "");
    void display() const;
    string getType() const;
    double getAmount() const;
    string getDate() const;
};
