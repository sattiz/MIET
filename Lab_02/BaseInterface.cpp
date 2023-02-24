#include "Headers/BaseInterface.h"

void BaseInterface::print(Base &base) {
    int totalPos = 0;
    double totalPrice = 0;
    printTablesTop();
    int i = 0;
    for (; i < base.length; i++, totalPos++) {
        printItem(base.itemsArr[i]);
        totalPrice += base.itemsArr[i].getPrice() * base.itemsArr[i].getQuant();
    }
    if (!i) std::cout << "Empty List!" << std::endl;
    printTablesBot(totalPrice, totalPos);
}

void BaseInterface::printTablesTop() {
    std::cout << std::endl << std::left << std::setfill(' ')
              << std::setw(40) << "Name of product"
              << std::setw(10) << "Type"
              << std::setw(20) << "Weight"
              << std::setw(20) << "Quantity"
              << std::setw(20) << "Price(rub)"
              << std::setw(20) << "Total Price" << std::endl;
    std::cout << std::setfill('-') << std::setw(134) << "-" << std::endl;
}

void BaseInterface::printTablesBot(double totalPrice, unsigned int totalPos) {
    std::cout << std::setfill('-') << std::setw(134) << "-" << std::endl;
    std::cout << std::setfill('.') << std::setw(110) << "Total PRICE of all products:" << totalPrice << std::endl;
    std::cout << std::setfill('.') << std::setw(110) << "Total positions:" << totalPos << std::endl;
}

void BaseInterface::printItem(Food &item) {
    std::string typeArr[] = {"BUN", "PIE", "CAKE"};
    std::string buf;
    item.getFam(buf);
    std::cout << std::left << std::setfill(' ') << std::setw(40) << buf
              << std::setw(10) << typeArr[item.getType() - 1]
              << std::setw(20) << item.getWeight()
              << std::setw(20) << item.getQuant()
              << std::setw(20) << item.getPrice()
              << std::setw(20) << item.getPrice() * item.getQuant() << std::endl;
}