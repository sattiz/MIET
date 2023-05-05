#ifndef LAB_03_ACCOUNT_H
#define LAB_03_ACCOUNT_H

#include "Person.h"
#include <stdexcept>

class Account {
public:
    Account();

    Account(const Account &item);

    Account(std::string &source);

    template<typename T>
    Account(T name, T surname, T fathername,
            long long int number, long double deposit) {
        this->client = Person(name, surname, fathername);
        this->accountNumber = number;
        this->deposit = deposit;
    }

    bool toString(std::string &dest);

    static void swap(Account &left, Account &right);

    friend Account& operator+(Account &item, long double money);

    Account& operator=(Account const&right);

    Account& operator+=(long double right);

    long long int getNum() const {
        return accountNumber;
    }

    static int getObjNum(){
        return objNum;
    }

    friend std::ostream& operator<<(std::ostream &os, Account &item);

    friend bool operator <(const Account&left, const Account &right){
        return left.deposit < right.deposit;
    }

    friend bool operator >(const Account&left, const Account &right){
        return left.deposit > right.deposit;
    }

    ~Account();

private:
    Person client;
    long long int accountNumber;
    long double deposit;
    static int objNum;
};


#endif //LAB_03_ACCOUNT_H
