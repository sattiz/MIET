#pragma once


#include "utility.h"
#include "Base.h"

class Interactor {
public:
    static bool exitProgram(Base &base);

    static bool saveChanges(Base &base);

    static bool wrongInputWarning();

    static bool getItem(Food &dest);

    static bool getItemField(itemField &dest);

    static bool getFilterDirection(compareDirection &dest);

    static bool getSortingDirection(sortingDirection &dest);

    static int getOption();

    template<typename T>
    static bool getItemFieldValue(itemField field, T *fieldValue);
    static bool getItemFieldValue(itemField field, std::string *fieldValue);
    static bool getItemFieldValue(itemField field, typeOfProduct *fieldValue);

private:
    static void printInstruction(itemField field);
};
