#ifndef LAB_03_BANK_H
#define LAB_03_BANK_H

#include "Account.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Bank {

public:
    Bank(std::string &filename);

    ~Bank() = default;

    template<typename T>
    bool addAccount(T source) {
        int AccNumBeginIndex = source.find('=') + 1;
        int AccNumLength = source.find(';', AccNumBeginIndex) - AccNumBeginIndex;
        if(!searchByAccountNum(stoll(source.substr(AccNumBeginIndex, AccNumLength))))
            list.emplace_back(Account(source));
        else return false;
        return true;
    }

    template<typename T>
    bool addAccount(T name, T surname, T fathername, long long int accNum, long double deposite) {
        if(!this->searchByAccountNum(accNum))
            list.emplace_back(Account(name, surname, fathername, accNum, deposite));
        else return false;
        return true;
    }

    void print();

    void print(long long accNum);

    void sort(int key = 0);

    void saveChanges();

private:
    Account* searchByAccountNum(long long int accountNumber);

    std::vector<Account> list;
    std::string filename;
};


#endif //LAB_03_BANK_H
