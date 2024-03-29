#include "../headers/Account.h"

int Account::objNum = 0;

Account::Account(const Account &item) {
    this->client = item.client;
    this->accountNumber = item.accountNumber;
    this->deposit = item.deposit;
    objNum++;
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
        try {this->accountNumber = std::stoll(accNumSource); }
        catch (...) { throw std::runtime_error("Invalid source: cam not get account number"); }
        source.erase(0, sepIndex + 1);
    }

    if(sepIndex = source.find(';')) {
        std::string depositSource = source.substr(0,sepIndex);
        try {this->deposit = std::stold(depositSource); }
        catch (...) { throw std::runtime_error("Invalid source: cam not get account deposit"); }
    }
    objNum++;
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

Account& Account::operator=(Account const&right) {
    this->deposit = right.deposit;
    this->accountNumber = right.accountNumber;
    this->client = right.client;
    return *this;
}

Account& operator+(Account &item, long double money) {
    item.deposit += money;
    return item;
}

Account& Account::operator+=(long double right){
    return *this = *this + right;
}

std::ostream &operator<<(std::ostream &os, Account &item) {
    std::string str = std::to_string (item.deposit);
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
    return os << std::left << std::setw(20) << item.client
            << std::left << std::setw(20) << std::to_string(item.accountNumber)
            << std::left << std::setw(20) << str;
}

Account::~Account() {
    Account::objNum--;
}

Account::Account() {
    this->deposit = 0;
    this->accountNumber = 0;
    this->client = Person();
    objNum++;
}

