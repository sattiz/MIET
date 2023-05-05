
#include "../headers/Bank.h"

Bank::Bank(std::string &filename) {
    std::ifstream fp(filename);
    if(fp.is_open()){ // exists
        std::string clientString;
        while(std::getline(fp, clientString)){
            this->list.emplace_back(clientString);
        }
        fp.close();
    } else { // does not exist
        std::ofstream newFile(filename);
        newFile.close();
    }
    this->filename = filename;
}

void Bank::saveChanges() {
    std::ofstream file(filename, std::ios::trunc);
    for(int i = 0; i < list.size(); i++){
        std::string tmp;
        list[i].toString(tmp);
        file << tmp << '\n';
    }
    file.close();
}

void Bank::sort(int key) {
    if(key)
        std::sort(list.begin(), list.end(), std::greater<Account>());
    else
        std::sort(list.begin(), list.end());
}

void Bank::print() {
    std::cout << std::setfill(' ') << std::left << std::setw(20) << "Name:"
            << std::setw(20) << "Fathername:"
            << std::setw(20) << "Surname:"
            << std::setw(20) << "Account Number:"
            << std::setw(20) << "Deposit:" << std::endl;
    std::cout << std::setfill('-') << std::setw(101)<< '-' << std::setfill(' ') << std::endl ;

    for (Account i : list) {
        std::cout << i << std::endl;
    }

    std::cout << std::setfill('-') << std::setw(101)<< '-' << std::setfill(' ') << std::endl ;
    std::cout << std::setfill('.') << "Total Accounts(objects):" << std::setw(77) << std::right << Account::getObjNum() << std::setfill(' ') << std::endl;
    std::cout << std::setfill('.') << "Accounts(objects) printed:" << std::setw(75) << std::right << Account::getObjNum() << std::setfill(' ') << std::endl;
}

void Bank::print(long long accNum) {
    auto tmp = this->searchByAccountNum(accNum);

    if(!tmp) {
        std::cout << "Account with this number not found!" << std::endl;
        return;
    }

    std::cout << std::setfill(' ') << std::left << std::setw(20) << "Name:"
              << std::setw(20) << "Fathername:"
              << std::setw(20) << "Surname:"
              << std::setw(20) << "Account Number:"
              << std::setw(20) << "Deposit:" << std::endl;
    std::cout << std::setfill('-') << std::setw(101)<< '-' << std::setfill(' ') << std::endl ;

    std::cout << *tmp << std::endl;

    std::cout << std::setfill('-') << std::setw(101)<< '-' << std::setfill(' ') << std::endl ;
    std::cout << std::setfill('.') << "Total Accounts(objects):" << std::setw(77) << std::right << Account::getObjNum() << std::setfill(' ') << std::endl;
    std::cout << std::setfill('.') << "Accounts(objects) printed:" << std::setw(75) << std::right << 1 << std::setfill(' ') << std::endl;
}

Account* Bank::searchByAccountNum(long long int accountNumber) {

    auto tmp = std::find_if(list.begin(), list.end(),
                           [accountNumber](const Account& acc){
       return acc.getNum() == accountNumber;
    });

    return tmp == list.end() ? static_cast<Account*>(nullptr) : &*tmp;
}








