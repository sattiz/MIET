# Лабораторная работа №2 (Вариант 1)
## Цель работы
Закрепить практические навыки, полученные при изучении дисциплины «Основы программирования».  Решение задач с использованием динамических структур, работа с файлами.
## Техническое задание
### Общие требования 
1. Во всех вариантах нужно создать базу данных, согласно варианту задания
2. В каждой базе должна быть статическая переменная для учета общего числа элементов в базе данных.
3. Данные размещаются в динамической памяти.
4. Обязательные функции для всех вариантов:
    + добавить новый элемент в базу
    + распечатка данных в табличном виде
    + выход из программы
5. Остальные функции для работы с базой указаны в задании индивидуально.
6. Для выполнения функций, указанных в задании, написать диалоговый интерфейс, позволяющий выполнять функции в произвольном порядке многократно
7. При выполнении функции «выход из программы» нужно сохранить базу на диске
8. Первичное создание базы – ввод данных с клавиатуры
9. Если программа уже запускалась, то данные загружаются из файла перед выходом на диалог. Иными словами вносятся изменения и дополнения в уже существующую базу данных.
10.  При реализации функций в параметрах и возвращаемых значениях использовать указатели и ссылки
11. Выполнить задание лабораторной работы №1 в стиле ООП. Для этого видоизменить программу, разработанную ранее.
12. Дополнить проект в соответствии с вашим вариантом задания.
13. В заданиях используются следующие сокращения:
  pub– открытые данные (public),  
  pri – закрытые данные (private),  
  СД – статические данные (в единственном экземпляре, общие для всего класса),  
  НСД – нестатические данные тиражируются для каждого объекта,  
  КК – конструктор копирования,  
  ДФ – дружественная функция,  
  МК- метод класса.  
  Например поле, помеченное СД, pri означает статическую переменную, размещенную в закрытой области.  
14. Если поле никак не отмечено, то считать его открытым
15. Для текстовых данных в классе создавать указатели на строки, а в конструкторах динамически выделять память под строки, в деструкторах – возвращать в кучу.
16. В задании указаны методы, которые создаются обязательно, но вы не должны этим ограничиваться. Как правило, для работы требуются и другие методы, какие – решать вам.
17. Оценка лабораторной работы проходит по 2 критериям:  
    • оценка проекта (элементы класса: данные, методы и т.п.)	- 50%  
    • оценка реализации (сама программа) – 50%  
### Требования по варианту
+ База данных: Пищевое производство (расчеты).
+ Создать класс food (видоизменить программу) со следующими элементами:
  + данные-члены класса:
    ```c++
    char* fam ; (pri)	  //Название изделия
    int   type;   (pri)         //тип изделия (1- булочка, 2-пирожок, 3-пирожное)
    double weight; (pri)   // вес
    int quant;		// количество
    double cost;		//стоимость
    static int count;        // счетчик существующих объектов класса
    ```
  + функции-члены класса:
    1. Создать обязательные функции, указанные в общих требованиях (МК).
    2. Создать функции для данного варианта: 
      + Поиск изделий по названию (МК),
      + Фильтр по типу (найти изделия заданного типа) (ДФ),
      + Сортировать по уменьшению стоимости (сначала более дорогие) (ДФ).
+ Тестовая программа №1:  
    • Базу данных (массив объектов) располагать в динамической памяти.  
    • При запуске программы данные ввести с клавиатуры (первый запуск программы) или загрузить с диска (все последующие запуски).  
    • Добавить несколько новых элементов (ввод с клавиатуры).  
    • Выполнить все реализованные функции (поиск, фильтр, сортировка).  
    • При выходе из программы запомнить измененную базу на диске.  

### Пример диалогового интерфейса (База данных «Склад товаров»)
![image](https://user-images.githubusercontent.com/57076699/221278362-82021063-f4c1-428b-9342-7202cbf5acd8.png)

### Пример распечатки данных в табличном виде (База данных «Склад товаров»)
![image](https://user-images.githubusercontent.com/57076699/221285525-babe4c51-90ee-4f44-bf6c-b5434ff33de8.png)

## Реализация технического задания

### Сторонние возможности
При реализации программы были использованы следующие возможности из библиотек:
```c++
#include <fstream> // работа с файлами
#include <iostream> // работа с потоками ввода-вывода
#include <iomanip>  // и его модификация 
#include <string>                     // работа со строками
#include <boost/algorithm/string.hpp> // работа со строками
#include <cmath> // сравнение вещественных чисел
```
### Архитектура приложения

Приложение состоит из следующих сущностей:  
  - ```class Food{...}``` - элемет базы хранит в себе данные о записи,  
  - ```class Base{...}``` - база данных,  
  - ```class BaseInterface{...}``` - интерфейс форматированного вывода базы данных,  
  - ```class Interactor{...}``` - интерфейс для взаимодействия с пользователем,также слежит для валидации данных  

Кроме того используются следующие перечисления:
```c++
enum typeOfProduct { // тип продукта
    BUN = 1, PIE, CAKE
};
```
```c++
enum error { // обработка ошибок
    NO_ERROR,
    OUT_OF_MEMORY,
    PRODUCT_ALREADY_IN_BASE,
    CANT_SAVE_CHANGES,
    PRODUCT_NOT_IN_BASE
};
```
```c++
enum compareDirection { // определение направления для фильтрации ввода
    MORE_THEN, LESS_THEN, EQUAL_TO
};
```
```c++
enum sortingDirection { // определение для направления сортировки
    ASCENDING, DESCENDING
};
```
  
#### Сигнатуры классов

##### Food
```c++
class Food {
public:

//конструкторы
    Food();
    Food(const Food &item);
    explicit Food(std::string s);
    Food(std::string fam, typeOfProduct type, double weight, int quant, double price);

//преобразование записи в базе в строку
    [[nodiscard]] std::string* parseToString() const;
    
//сравненение записи по полю
    // if (this->field > fieldValue) then return > 0
    int moreThen(itemField f, Food& item);
    int moreThen(itemField f, double fieldValue);
    int moreThen(itemField f, int fieldValue);
    int moreThen(itemField f, std::string fieldValue);
    int moreThen(itemField f, typeOfProduct fieldValue);

//меняется значения записей местами
    static void swap(Food &a, Food&b);

//геттеры
    static int getObjNum();
    void getFam(std::string &dest) const;
    typeOfProduct getType() const;
    double getWeight() const;
    int getQuant() const;
    double getPrice() const;
 
 //сеттеры
    void setFam(std::string fieldVal);
    void setType(typeOfProduct fieldVal);
    void setQuant(int fieldVal);
    void setPrice(double fieldVal);
    void setWeight(double fieldVal);

//деконструктор
    ~Food();

private:
    std::string fam; // название продукта
    typeOfProduct type; // тип продукта
    double weight; //вес продукта
    int quant; //количество единиц продукта
    double price; //цена продукта
    static int objNum; //количество объектов в программе(динамически меняется во время работы программы)
};
```
##### Base
```c++
class Base {
public:

// конструторы
    Base() = default;
    explicit Base(const std::string& file); // по совместительству импорт базы из файла

// добавление продукта в базу (возвращает !NO_ERROR если добавить не удалось
    error addItem(const Food &item);
     
// удаление продукта из базу (возвращает !NO_ERROR если добавить не удалось
    error removeItem(const std::string &name);
    
// сортирует элементы в базе
    void sort(sortingDirection sortDirection, itemField sortingField);

// экспортирует базу в файл
    error saveTofFile();
    
// проверяет последний экспорт базы в файл
    bool isSaved() const;

// BaseInterface объявлен другом этого класса
    friend class BaseInterface;
    
// деструктор
    ~Base();

private:
    bool saveState{}; // есть ли различия между базой в файле и в динамической памяти
    std::string filename; // название файла из которого открывалась база
    Food* itemsArr{}; // массив элементов базы
    unsigned int length{}; // длина массива
    
    int getItem(const std::string &name); // взять
};
```

##### BaseInterface
```c++
class BaseInterface {
public:

// форматированный нефильтрованный вывод
    static void print(Base &base); 

// фильтрованный вывод базы
    template<typename T>
    static void printBaseByFilter(Base &base, itemField field, T fieldValue, compareDirection cd); 

private:

// печать заголовка таблицы
    static void printTablesTop(); 

// печать ячейки таблицы
    static void printItem(Food &item); 

// печать итогов таблицы
    static void printTablesBot(double totalPrice, unsigned int totalPos);
};
```

##### Interactor
```c++
class Interactor {
public:
// обработка выхода из программы
    static bool exitProgram(Base &base);

// сохранение изменений
    static bool saveChanges(Base &base);

// уведомляет пользователя о неправильном вводе
    static bool wrongInputWarning();

// получение данных продуктов от пользователя
    static bool getItem(Food &dest);

// получение типа поля от пользователя
    static bool getItemField(itemField &dest);

// получение направления фильтрации от пользователя
    static bool getFilterDirection(compareDirection &dest);

// получение направления сортировки от пользователя
    static bool getSortingDirection(sortingDirection &dest);

// получение опции взаимодействия с базой от пользователя
    static int getOption();

// получение значения поля от пользователя
    template<typename T>
    static bool getItemFieldValue(itemField field, T *fieldValue);
    static bool getItemFieldValue(itemField field, std::string *fieldValue);
    static bool getItemFieldValue(itemField field, typeOfProduct *fieldValue);

private:

// печать инструкции в зависимости от ввода пользователя
    static void printInstruction(itemField field);
};

```
#### Реализация методов

| BaseInterface | Base | Interactor | Food |
|:---:|:---:|:---:|:---:|
| [BaseInterface.cpp](https://github.com/xXxINFARKTxXx/OOP2023SpringMIET/blob/main/Lab_02/BaseInterface.cpp) | [Base.cpp](https://github.com/xXxINFARKTxXx/OOP2023SpringMIET/blob/main/Lab_02/Base.cpp) | [Interactor.cpp](https://github.com/xXxINFARKTxXx/OOP2023SpringMIET/blob/main/Lab_02/Interactor.cpp) | [Food.cpp](https://github.com/xXxINFARKTxXx/OOP2023SpringMIET/blob/main/Lab_02/Food.cpp) |
| [BaseInterface.h](https://github.com/xXxINFARKTxXx/OOP2023SpringMIET/blob/main/Lab_02/BaseInterface.h) | [Base.h](https://github.com/xXxINFARKTxXx/OOP2023SpringMIET/blob/main/Lab_02/Base.h) | [Interactor.h](https://github.com/xXxINFARKTxXx/OOP2023SpringMIET/blob/main/Lab_02/Interactor.h) | [Food.h](https://github.com/xXxINFARKTxXx/OOP2023SpringMIET/blob/main/Lab_02/Food.h) |

#### Схематическое описание взаимодействия элементов программы и пользователя

![image](https://github.com/xXxINFARKTxXx/OOP2023SpringMIET/blob/main/Lab_02/Project.drawio.svg)

#### Пример работы программы






