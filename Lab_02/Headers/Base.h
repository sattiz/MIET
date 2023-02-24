#pragma once
#include "utility.h"
#include "Food.h"

class Base {
public:

    Base() = default;
    explicit Base(const std::string& file);

    ~Base();

    error addItem(const Food &item);

    error removeItem(const std::string &name);

    void sort(sortingDirection sortDirection, itemField sortingField);

    error saveTofFile();

    bool isSaved() const{
        return this->saveState;
    }

    friend class BaseInterface;

private:
    bool saveState{};
    std::string filename;
    Food* itemsArr{};
    unsigned int length{};

    int getItem(const std::string &name);
};
