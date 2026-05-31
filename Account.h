#pragma once
#include <string>
#include <vector>
#include "Transaction.h"

using std::string;
using std::vector;

class Account {
protected:
    string accountNumber;
    string holderName;
    double balance;
    vector<Transaction> transactionHistory;
