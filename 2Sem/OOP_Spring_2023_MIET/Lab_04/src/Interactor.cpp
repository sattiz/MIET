#include <limits>
#include "../headers/Interactor.h"

void Interactor::printMenu() {
    std::cout << std::endl << std::setfill('-') << std::setw(134) << "-";
    std::cout << "\n"
                 "Print Base.......................1\n"
                 "Add new account..................2\n"
                 "Sort Base........................3\n"
                 "Find account by number...........4\n"
                 "Save changes.....................5\n"
                 "Print menu.......................6\n"
                 "Exit program.....................7\n\n";
}

int Interactor::getOption() {
    std::cout << std::endl << "Enter option(6 to print menu): ";
    int t;
    std::string buf;
    std::getline(std::cin, buf);
    if(!buf.length())
        return -1;

    if(buf.find_first_not_of("1234567") != std::string::npos)
        return -1;

    t = std::stoi(buf);
    if (t < 8 && t > 0)
        return t;

    return -1;
}

void Interactor::clearAndWarn() {
    std::cin.clear ();    // Restore input stream to working state
    std::cout << "Wrong input!" << std::endl;
}

std::string Interactor::getAccount() {
    std::string dest;
    for(int i = 0; i < 3; i++){
        auto tmp = getField<std::string>(i);
        if(!tmp){
            return "";
        }
        dest += *tmp + ";";
        delete tmp;
    }
    dest += "=";
    auto pInt = getField<long long>(3);
    if(!pInt) return "";
    dest += std::to_string(*pInt) + ";";
    delete pInt;

    auto pDouble = getField<long double>(4);
    if(!pDouble) return "";
    dest += std::to_string(*pDouble) + ";";
    delete pDouble;

    return dest;
}
