#ifndef LAB_03_BANK_H
#define LAB_03_BANK_H

#include "Account.h"
#include <vector>

class Bank {

public:
    Bank(std::string filename);

    void addAccount();

    int searchByAccountNum(long long int accountNumber);

    void print();

    void descendingSortByDeposit();

    void saveChanges();


private:
    std::vector<Account> list;
};


#endif //LAB_03_BANK_H
