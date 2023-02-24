#include "Headers/Food.h"

int Food::objNum = 0;

Food::Food(std::string s) {
    std::string words[5];
    for(int i = 0, j = 0; i < s.length(); i++) {
        if(s[i] != ';')
            words[j].append(sizeof (char), s[i]);
        else{
            j++;
        }
    }
    fam.append(words[0]);
    try {
        type = (typeOfProduct)std::stoi(words[1]);
    }
    catch (...) {
        throw std::runtime_error("Can not read file!");
    }
    try {
        weight = std::stod(words[2]);
    }
    catch (...) {
        throw std::runtime_error("Can not read file!");
    }
    try {
        quant = std::stoi(words[3]);
    }
    catch (...) {
        throw std::runtime_error("Can not read file!");
    }
    try {
        price = std::stod(words[4]);
    }
    catch (...) {
        throw std::runtime_error("Can not read file!");
    }
    Food::objNum++;
}

std::string *Food::parseToString() const {
    std::string* s;
    try {
        s = new std::string;
    }
    catch (std::bad_alloc &e) {
        return nullptr;
    }
    s->append(fam); s->append(sizeof(char), ';');
    s->append(std::to_string(type)); s->append(sizeof(char), ';');
    s->append(std::to_string(weight)); s->append(sizeof(char), ';');
    s->append(std::to_string(quant)); s->append(sizeof(char), ';');
    s->append(std::to_string(price)); s->append(sizeof(char), ';');
    return s;
}

Food::Food(std::string fam, typeOfProduct type, double weight, int quant, double price) {
    this->fam = fam;
    this->type = type;
    this->weight = weight;
    this->quant = quant;
    this->price = price;
    Food::objNum++;
}

// if (*this > item||fieldValue) then return > 0
int Food::moreThen(itemField f, double fieldValue) {
    switch (f) {
        case itemField::PRICE:
            return fabs(this->price - fieldValue) < std::numeric_limits<double>::epsilon() ?
                   0 : (this->price - fieldValue > 0) ? 1 : -1;
        case itemField::WEIGHT:
            return fabs(this->weight - fieldValue) < std::numeric_limits<double>::epsilon() ?
                0 : (this->weight - fieldValue > 0) ? 1 : -1;
    }
    return 0;
}

int Food::moreThen(itemField f, int fieldValue) {
    return this->quant - fieldValue;
}
int Food::moreThen(itemField f, std::string fieldValue) {
    return this->fam.compare(fieldValue);
}
int Food::moreThen(itemField f, typeOfProduct fieldValue) {
    return static_cast<int>(this->type) - static_cast<int>(fieldValue);
}
int Food::moreThen(itemField f, Food& item) {
    switch (f) {
        case itemField::NAME:
            return this->fam.compare(item.fam);
        case itemField::TYPE:
            return this->type - item.type;
        case itemField::QUANTITY:
            return this->quant - item.quant;
        case itemField::WEIGHT:
            if(fabs(this->weight - item.weight) < std::numeric_limits<double>::epsilon())
                return 0;
            else
                return (this->weight - item.weight > 0) ? 1 : -1;
        case itemField::PRICE:
            if(fabs(this->price - item.price) < std::numeric_limits<double>::epsilon())
                return 0;
            else
                return (this->price - item.price > 0) ? 1 : -1;
    }
    return 0;
}








