#include "../headers/Account.h"

int Account::objNum = 0;

Account::Account(Account &item) {
    this->client = item.client;
    this->accountNumber = item.accountNumber;
    this->deposit = item.deposit;
    Account::objNum++;
}

Account::Account(std::string &source) {
    size_t sepIndex;
    if(!source.length())
        throw std::runtime_error("Empty string");

    if(sepIndex = source.find('=')) {
        std::string personSource = source.substr(0, sepIndex);
        if(!this->client.fromString(personSource))
            throw std::runtime_error("Invalid source: can not parse client info");
        source.erase(0,sepIndex+1);
    } else throw std::runtime_error("Invalid source: client sep not found");

    if(sepIndex = source.find(';')) {
        std::string accNumSource = source.substr(0,sepIndex);
        try {this->accountNumber = std::stoi(accNumSource); }
        catch (...) { throw std::runtime_error("Invalid source: cam not get account number"); }
        accNumSource.erase(0, sepIndex + 1);
    }

    if(sepIndex = source.find(';')) {
        std::string depositSource = source.substr(0,sepIndex);
        try {this->deposit = std::stod(depositSource); }
        catch (...) { throw std::runtime_error("Invalid source: cam not get account deposit"); }
    }
}

bool Account::toString(std::string &dest) {
    if(!this->client.toString(dest)) return false;
    dest += '=' + std::to_string(this->accountNumber) + ';' + std::to_string(this->deposit) + ';';
    return true;
}

void Account::swap(Account &left, Account &right) {
    Account tmp;
    tmp = right;
    right = left;
    left = tmp;
}

int Account::compareByDeposit(Account &left, Account *right) {
    return left.deposit - right->deposit > 0 ? 1 : -1;
}

long double operator+(Account &item, long double money) {
    return item.deposit += money;
}

std::ostream &operator<<(std::ostream &os, Account &item) {
    return os;
}

Account::~Account() {
    Account::objNum--;
}

