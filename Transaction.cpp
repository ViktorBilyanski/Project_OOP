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
