#include "Base.h"


class BaseInterface {
public:

    static void print(Base &base);

    template<typename T>
    static void printBaseByFilter(Base &base, itemField field, T fieldValue, compareDirection cd) {
        printTablesTop();
        double totalPrice = 0;
        int totalPos = 0;
        for (int i = 0; i < base.length; i++) {
            int compRes = base.itemsArr[i].moreThen(field, fieldValue);
            compRes *= cd == LESS_THEN ? -1 : 1;
            if (cd == EQUAL_TO && !compRes ||
                cd == LESS_THEN && compRes < 0 ||
                cd == MORE_THEN && compRes < 0) {
                printItem(base.itemsArr[i]);
                totalPrice += base.itemsArr[i].getPrice() * base.itemsArr[i].getQuant();
                totalPos++;
            }
        }
        printTablesBot(totalPrice, totalPos);
    }

private:
    static void printTablesTop();

    static void printItem(Food &item);

    static void printTablesBot(double totalPrice, unsigned int totalPos);
};

