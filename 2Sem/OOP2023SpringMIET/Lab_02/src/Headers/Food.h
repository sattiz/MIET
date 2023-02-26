#pragma once
#include "utility.h"

class Food {
public:

    Food(std::string fam, typeOfProduct type, double weight, int quant, double price);
    explicit Food(std::string s);
    [[nodiscard]] std::string* parseToString() const;
    int moreThen(itemField f, Food& item);

    // if (this->field > fieldValue) then return > 0
    int moreThen(itemField f, double fieldValue);
    int moreThen(itemField f, int fieldValue);
    int moreThen(itemField f, std::string fieldValue);
    int moreThen(itemField f, typeOfProduct fieldValue);

    static void swap(Food &a, Food&b){
        auto tmp = a;
        a = b;
        b = tmp;
    }

    Food(){
        objNum++;
    }

    Food(const Food &item) {
        fam = item.fam;
        type = item.type;
        price = item.price;
        weight = item.weight;
        quant = item.quant;
        objNum++;
    }

    static int getObjNum() {return objNum; }
    void getFam(std::string &dest) const { dest = this->fam; }
    typeOfProduct getType() const { return this->type; }
    double getWeight() const { return this->weight; }
    int getQuant() const { return this->quant; }
    double getPrice() const { return this->price; }
    void setFam(std::string fieldVal){ this->fam = fieldVal; }
    void setType(typeOfProduct fieldVal){ this->type = fieldVal; }
    void setQuant(int fieldVal){ this->quant = fieldVal; }
    void setPrice(double fieldVal){ this->price = fieldVal; }
    void setWeight(double fieldVal){ this->weight = fieldVal; }

    ~Food() {
        objNum--;
    }

private:
    std::string fam;
    typeOfProduct type;
    double weight;
    int quant;
    double price;
    static int objNum;

};

