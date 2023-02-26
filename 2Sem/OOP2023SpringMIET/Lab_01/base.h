#ifndef LAB_01_BASE_H
#define LAB_01_BASE_H

#include <fstream> // работа с файлами
#include <iostream> // работа с потоками ввода-вывода
#include <iomanip>  // и его модификация
#include <string>                     // работа со строками
#include <boost/algorithm/string.hpp> // работа со строками
#include <cmath> // сравнение вещественных чисел

#define FILEPATH "cakes.txt"

namespace database{
    enum typeOfProduct {
        bun = 1, pie, cake};
    enum error {NO_ERROR, CAN_NOT_OPEN_FILE, OUT_OF_MEMORY, PRODUCT_ALREADY_IN_BASE, WRONG_INPUT};
    enum CMP {LEFT_MORE_THEN_RIGHT, LEFT_LESS_THEN_RIGHT, LEFT_EQUAL_TO_RIGHT};

    typedef struct {
        std::string fam; // название
        typeOfProduct type; // тип (1,2,3)
        double weight; // вес
        int quant; // количество
        double price; // стоимость за ед
    } item;

    typedef struct {
        std::string name; // название файла
        std::fstream file; // открыть файл
        item** itemsArr; // название массива
        unsigned int length;
    } base;

    error base_init(base &self);
    error base_addItem(base &self,item *product);
    void base_print(base &self);
    void base_printPriceFilteredItems(const base &self,double price, CMP cmpFlag);
    void base_printTypeFilteredItems(const base &self,typeOfProduct type);
    void base_printFoundItem(const base &self, const std::string &name);
    void base_sort(base &self);
    void base_writeToFile(base &self);
    void base_delete(base &self);
}

#endif