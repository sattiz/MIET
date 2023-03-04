#ifndef LAB_03_ACCOUNT_H
#define LAB_03_ACCOUNT_H

#include "Person.h"
#include <stdexcept>

class Account {

    Account() = default;

    Account(Account &item);

    Account(std::string &source);

    bool toString(std::string &dest);

    static void swap(Account &left, Account &right);

    static int compareByDeposit(Account& left, Account *right);

    friend long double operator+(Account &item, long double money);

    friend std::ostream& operator<<(std::ostream &os, Account &item);

    ~Account();

private:
    Person client;
    long long int accountNumber;
    long double deposit;
    static int objNum;
};


#endif //LAB_03_ACCOUNT_H
