#include <iostream>

#include "../headers/Person.h"

int main() {
    Person client;
    std::string source = "Vladimir;Getmantsev;Michailovich;";
    client.fromString(source);
    client.toString(source);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
