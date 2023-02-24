#include "base.h"

enum fields {
    type, name, price, prod, cmpflag, quant, weight
};

void *getField(fields f) {
    switch (f) {
        case quant: {
            auto t = new int;
            std::cout << "Enter product quantity and press Enter: ";
            if (!(std::cin >> *t) || (*t < 0)) {
                delete t;
                t = nullptr;
            }
            return t;
        }

        case weight: {
            auto t = new double;
            std::cout << "Enter product weight and press Enter: ";
            if (!(std::cin >> *t) || (*t < 0)) {
                delete t;
                t = nullptr;
            }
            return t;
        }

        case type: {
            auto t = new int;
            std::cout << "Enter product type(1 - bun, 2 - pie, 3 - cake) and press Enter: ";
            if (!(std::cin >> *t) || (*t > 3 || *t < 1)) {
                delete t;
                t = nullptr;
            }
            return t;
        }
        case name: {
            auto t = new std::string;
            std::cout << "Enter product name (all symbols except ';') and press Enter: ";
            std::cin >> *t;
            if (t->find(';') != std::string::npos) {
                delete t;
                t = nullptr;
            }
            return t;
        }
        case price: {
            auto t = new double;
            std::cout << "Enter product price and press Enter: ";
            if (!(std::cin >> *t) || (*t < 0)) {
                delete t;
                t = nullptr;
            }
            return t;
        }
        case prod: {
            auto fam = (std::string *) getField(fields::name);
            if (!fam) {
                return nullptr;
            }
            auto t = (database::typeOfProduct *) getField(fields::type);
            if (!t) {
                delete fam;
                return nullptr;
            }
            auto pr = (double *) getField(fields::price);
            if (!pr) {
                delete fam;
                delete t;
                return nullptr;
            }
            auto weight = (double *) getField(fields::weight);
            if (!weight) {
                delete fam;
                delete t;
                delete pr;
                return nullptr;
            }
            auto quant = (int *) getField(fields::quant);
            if (!quant) {
                delete fam;
                delete t;
                delete pr;
                delete weight;
                return nullptr;
            }
            auto product = new database::item;
            product->fam = *fam;
            product->type = *t;
            product->price = *pr;
            product->weight = *weight;
            product->quant = *quant;
            delete t;
            delete fam;
            delete pr;
            delete weight;
            delete quant;
            return product;
        }

        case cmpflag: {
            int *t = new int;
            std::cout << "Enter filter type:\n"
                         "0 - more than chosen price\n"
                         "1 - less than chosen price\n"
                         "2 - equal to chosen price\n"
                         "and press Enter: ";
            if (!(std::cin >> *t) || (*t > 2 || *t < 0)) {
                delete t;
                t = nullptr;
            }
            return t;
        }
    }
}

int isNonValid(const void* pt){
    if(!pt){
        std::cout << "Wrong input!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    else return 0;
}
