//
// Created by vladimir on 9.3.23..
//

#ifndef LAB_03_INTERACTOR_H
#define LAB_03_INTERACTOR_H

#include "Account.h"
#include <algorithm>

class Interactor {
public:

    static int getOption();

    static void clearAndWarn();

    static void printMenu();

    static std::string getAccount();

    template<typename T>
    [[nodiscard]] static T *getField(int fieldFlag) {
        std::string fieldNames[] = {"name", "surname", "fathername", "account number", "deposit"};
        std::string buf;
        std::cout << "Enter " << fieldNames[fieldFlag] << ": ";
        std::getline(std::cin, buf);
        if (!buf.length())
            return nullptr;

        switch (fieldFlag) {
            case 0:
            case 1:
            case 2: {
                if (buf.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-") != std::string::npos)
                    return nullptr;
                return (T *) new std::string(buf);
            }
            case 3: {
                if (buf.find_first_not_of("0123456789") != std::string::npos)
                    return nullptr;
                return (T *) new long long(std::stoll(buf));
            }
            case 4: {
                if (buf.find_first_not_of("0123456789.") != std::string::npos ||
                    std::count(buf.begin(), buf.end(), '.') > 1)
                    return nullptr;
                return (T *) new long double(std::stold(buf));
            }
            default:
                return nullptr;
        }
    }
};


#endif //LAB_03_INTERACTOR_H
