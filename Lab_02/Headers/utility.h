#pragma once
#include <fstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <boost/algorithm/string.hpp>

#define FILEPATH "cakes.txt"
#define OPTION_NUMBER 7

enum typeOfProduct {
    BUN = 1, PIE, CAKE
};
enum error {
    NO_ERROR,
    CANT_OPEN_FILE,
    CANT_READ_FILE,
    OUT_OF_MEMORY,
    PRODUCT_ALREADY_IN_BASE,
    WRONG_INPUT,
    CANT_SAVE_CHANGES,
    PRODUCT_NOT_IN_BASE
};
enum compareDirection {
    MORE_THEN, LESS_THEN, EQUAL_TO
};
enum sortingDirection {
    ASCENDING, DESCENDING
};
enum itemField {
    NAME, TYPE, PRICE, QUANTITY, WEIGHT
};