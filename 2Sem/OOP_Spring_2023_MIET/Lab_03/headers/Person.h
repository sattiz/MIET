#ifndef LAB_03_PERSON_H
#define LAB_03_PERSON_H

#include <iostream>
#include <string>
#include <iomanip>

class Person {
public:
    Person();

    Person(Person &item);

    Person(std::string name, std::string surname, std::string fatherName);

    bool toString(std::string& dest);

    bool fromString(std::string& source);

    friend std::ostream& operator<<(std::ostream& out, Person &item) {
        return out << std::left << std::setw(20) << item.name
                << std::left << std::setw(20) << item.fatherName
                << std::left << std::setw(20) << item.surname;
    }

    friend class Account;



private:
    std::string name;
    std::string surname;
    std::string fatherName;
};


#endif //LAB_03_PERSON_H
