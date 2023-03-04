#ifndef LAB_03_PERSON_H
#define LAB_03_PERSON_H

#include <iostream>
#include <string>

class Person {
public:
    Person();

    Person(Person &item);

    Person(std::string name, std::string surname, std::string fatherName);

    bool toString(std::string& dest);

    bool fromString(std::string& source);

    friend class Account;

private:
    std::string name;
    std::string surname;
    std::string fatherName;
};


#endif //LAB_03_PERSON_H
