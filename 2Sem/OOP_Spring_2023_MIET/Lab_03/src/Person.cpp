#include "../headers/Person.h"


Person::Person() {
    name = "";
    surname = "";
    fatherName = "";
}

Person::Person(Person &item) {
    name = item.name;
    surname = item.surname;
    fatherName = item.fatherName;
}

Person::Person(std::string name, std::string surname, std::string fatherName) {
    this->name = name;
    this->surname = surname;
    this->fatherName = fatherName;
}

bool Person::toString(std::string& dest) {
    if(!(name.length() && surname.length() && fatherName.length()))
        return false;
    dest = name + ';' + surname + ';' + fatherName + ';';
    return true;
}

bool Person::fromString(std::string &source) {
    size_t sepIndex;
    if (!source.length())
        return false;

    if(sepIndex = source.find(';')){
        name = source.substr(0, sepIndex);
        source.erase(0, sepIndex + 1);
    } else return false;

    if(sepIndex = source.find(';')){
        surname = source.substr(0, sepIndex);
        source.erase(0, sepIndex + 1);
    } else return false;

    if(sepIndex = source.find(';')){
        fatherName = source.substr(0, sepIndex);
        source.erase(0, sepIndex + 1);
    } else return false;
    return true;
}
