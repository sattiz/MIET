#include "Headers/Interactor.h"
#include "Headers/BaseInterface.h"

void Interactor::printInstruction(itemField field) {
    std::string explanation[] = {
            "Enter product name (all symbols except ';') and press Enter: ",
            "Enter product type(1 - bun, 2 - pie, 3 - cake) and press Enter: ",
            "Enter product price and press Enter: ",
            "Enter product quantity and press Enter: ",
            "Enter product weight and press Enter: ",
    };
    std::cout << explanation[static_cast<int>(field)];
}


bool Interactor::wrongInputWarning() {
    std::cout << "Wrong input!" << std::endl;
    return false;
}

bool Interactor::getItem(Food &dest) {
    int quant;
    typeOfProduct type;
    std::string name;
    double price, weight;
    if  (getItemFieldValue(NAME, &name) &&
            getItemFieldValue(TYPE, &type) &&
            getItemFieldValue<int>(QUANTITY, &quant) &&
            getItemFieldValue<double>(WEIGHT, &weight) &&
            getItemFieldValue<double>(PRICE, &price)) {
        dest.setFam(name);
        dest.setWeight(weight);
        dest.setType(type);
        dest.setQuant(quant);
        dest.setPrice(price);
        return true;
    }
    return false;
}

bool Interactor::getItemField(itemField &dest) {
    std::cout << "\nChoose product characteristic:\n"
                 "1 - Name\n"
                 "2 - Type\n"
                 "3 - Price\n"
                 "4 - Quantity\n"
                 "5 - Weight\n"
                 "and press Enter: ";
    int t;
    std::string buf;
    std::getline(std::cin, buf);
    if(!buf.length()) return wrongInputWarning();
    if(buf.find_first_not_of("12345") != std::string::npos)
        return wrongInputWarning();
    t = std::stoi(buf);
    if ((t < 6 && t > 0)) {
        dest = static_cast<itemField>(t - 1);
        return true;
    }
    return wrongInputWarning();
}

bool Interactor::getSortingDirection(sortingDirection &dest) {
    std::cout << "\nChoose sort direction:\n"
                 "1 - Ascending\n"
                 "2 - Descending\n"
                 "and press Enter: ";
    int t;
    std::string buf;
    std::getline(std::cin, buf);
    if(!buf.length()) return wrongInputWarning();
    if(buf.find_first_not_of("12") != std::string::npos)
        return wrongInputWarning();
    t = std::stoi(buf);
    if (t < 3 && t > 0) {
        dest = static_cast<sortingDirection>(t - 1);
        return true;
    }
    return wrongInputWarning();
}

bool Interactor::getFilterDirection(compareDirection &dest) {
    std::cout << "\nChoose sort direction:\n"
                 "1 - Less then entered value\n"
                 "2 - More then entered value\n"
                 "3 - Equal to entered value\n"
                 "and press Enter: ";
    int t;
    std::string buf;
    std::getline(std::cin, buf);
    if(!buf.length()) return wrongInputWarning();
    if(buf.find_first_not_of("123") != std::string::npos)
        return wrongInputWarning();
    t = std::stoi(buf);
    if (t < 4 && t > 0) {
        dest = static_cast<compareDirection>(t - 1);
        return true;
    }
    return wrongInputWarning();
}

int Interactor::getOption() {
    int t;
    std::string buf;
    std::getline(std::cin, buf);
    if(!buf.length()) return 8;
    if(buf.find_first_not_of("1234567") != std::string::npos)
        return OPTION_NUMBER + 1;
    t = std::stoi(buf);
    if (t < 8 && t > 0) {
        return t;
    }
    return OPTION_NUMBER + 1;
}

template<typename T>
bool Interactor::getItemFieldValue(itemField field, T *fieldValue) {
    printInstruction(field);
    std::string buf;
    std::getline(std::cin,buf);
    if(!buf.length()) return wrongInputWarning();
    int pointIndex;

    switch (field) {
        case PRICE:
        case WEIGHT:
            if(buf.find_first_not_of("0123456789.") != std::string::npos)
                return wrongInputWarning();

            pointIndex = static_cast<int>(buf.find_first_not_of("0123456789"));

            if(pointIndex == buf.length() - 1)
                return wrongInputWarning();


            if(pointIndex != std::string::npos)
                if(buf.find_first_not_of("0123456789", pointIndex + 1) != std::string::npos)
                    return wrongInputWarning();

            *(double*)fieldValue = std::stod(buf);
            return (*(double *)fieldValue) > std::numeric_limits<double>::epsilon() || wrongInputWarning();
        case QUANTITY:
            if(buf.find_first_not_of("0123456789") != std::string::npos)
                return wrongInputWarning();
            *(int*)fieldValue = std::stoi(buf);
            return (*(int*)fieldValue) > 0 || wrongInputWarning();
    }
    return wrongInputWarning();
}
bool Interactor::getItemFieldValue(itemField field, std::string *fieldValue){
    printInstruction(field);
    std::getline(std::cin, *fieldValue);
    if(!fieldValue->length()) return wrongInputWarning();
    return fieldValue->find(';') == std::string::npos || wrongInputWarning();
}
bool Interactor::getItemFieldValue(itemField field, typeOfProduct *fieldValue) {
    printInstruction(field);
    std::string buf;

    std::getline(std::cin, buf);
    if(!buf.length()) return wrongInputWarning();
    if(buf.find_first_not_of("123") != std::string::npos)
        return wrongInputWarning();
    int in = std::stoi(buf);

    if((in) < 4 && (in) > 0) {
        *fieldValue = static_cast<typeOfProduct>(in);
        return true;
    }
    return wrongInputWarning();
}

bool Interactor::saveChanges(Base &base) {
    if(base.isSaved()) {
        std::cout << "All changes already saved!" << std::endl;
    }

    std::cout << "Press enter to SAVE, enter any other character to CANCEL changes:";
    std::string buf;
    std::getline(std::cin, buf);

    if(!buf.length()){
        if(base.saveTofFile()){
            std::cout << "Changes can not be saved!" << std::endl;
            return false;
        }
        std::cout << "Changes are successfully saved!" << std::endl;
        return true;
    }
    std::cout << "Saving cancelled." << std::endl;
    return true;
}

bool Interactor::exitProgram(Base &base) {
    std::string buf;

    if(!base.isSaved()) {
        std::cout << "Would you like to save changes?" << std::endl;
        Interactor::saveChanges(base);
    }

    std::cout << "Press enter to EXIT, "
        "enter any other character to continue work with program:";

    getline(std::cin, buf);
    if(!buf.length())
        return true;

    return false;
}
