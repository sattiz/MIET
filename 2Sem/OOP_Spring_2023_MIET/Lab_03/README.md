[<назад>](https://github.com/xXxINFARKTxXx/MIET/tree/main/2Sem/OOP_Spring_2023_MIET)
# Лабораторная работа №3 (Вариант 1)
## Цель работы
Получить практические навыки работы с перегруженными операторами и методами класса.

## Техническое задание

### Общие требования 

1. Для подготовки к лабораторной работе используйте данные из папок «Справочная информация» и «Теория»  
2. Вы начинаете работу над проектом, который будет развиваться в последующих лабораторных работах.  
3. В каждой информационной системе должна быть статическая переменная для учета числа существующих элементов в базе данных. 
4. Данные размещаются в динамической памяти. 
5. Для выполнения функций, указанных в задании, написать диалоговый интерфейс, позволяющий выполнять функции в произвольном порядке многократно
6. При выполнении функции «выход из программы» нужно сохранить информацию на диске 
7. Первичный ввод данных проводить с клавиатуры 
8. Если программа уже запускалась, то данные загружаются из файла перед выходом на диалог. Иными словами вносятся изменения и дополнения в уже существующую базу данных.  
9. Обязательные функции для всех вариантов: 
    + добавить новый элемент  
    + распечатка данных в табличном виде 
    + выход из программы 
10. Остальные реализуемые функции указаны в задании индивидуально. 
11. Примеры диалогового интерфейса и табличного вывода смотрите в лабораторной работе №1 
12. Перегруженные операторы реализовывать как с помощью дружественной функции (ДФ), так и с помощью метода класса (МК). Если в задании не указан метод реализации – решаете по своему усмотрению. 
13. Кроме перечисленных, вы  можете добавить дополнительные элементы в класс по своему усмотрению, должны быть реализованы все необходимые элементы для работы тестовой программы. 

### Требования по варианту

При выполнении задания используйте общие требования
 + Создайте проект информационной системы: Банк (депозит). 
 + Создать класс fio, состоящий из 3-х текстовых строк (фамилия, имя и отчество) 
 + Создать класс bank со следующими элементами:  
	+ **Элементы-данные класса bank:** 
	  1. Характеристики депозита (все данные pri):  
		    + Клиент: объект класса fio  
		    + Номер счета: целое число  
		    + Сумма на счете (сумма депозита ) : дробное число  
	  2. Cчетчик созданных объектов класса bank (СД)   
	+ **Элементы-функции класса bank:**  
		1. Создать обязательные функции, указанные в общих требованиях (МК).    
		2.  Создать функции для данного варианта:   
			  + Ввод данных с клавиатуры   
			  + Поиск объекта класса bank по заданному fio   
	+ **Перегрузить следующие операторы (для класса bank):**
		1. << вывод объекта класса bank в выходной поток cout   
		2.  Добавить число к полю «сумма на счете»   
 
**Тестовая программа (функция main):**
1. Массив объектов класса bank (MBank) располагать в динамической памяти 
2. При запуске программы данные ввести с клавиатуры (первый запуск программы) или загрузить с диска (все последующие запуски) 
3. Добавить несколько новых элементов в массив MBank (ввод с клавиатуры) 
4. Вывести массив MBank  в табличном виде (использовать перегруженный оператор <<) 
5. С клавиатуры ввести данные в переменную find (тип fio),  по введенному значению найти клиента банка и увеличить «сумму на счете» (использовать перегруженный оператор +) 
6. При выходе из программы измененные данные на диске
    
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
  - ```class Account{...}``` - элемент базы хранит в себе данные о учетной записи пользователя банка,  
  - ```class Bank{...}``` - база данных,  
  - ```class Person{...}``` - элемент класса `Account`, который содержит персональные данные о пользователе,  
  - ```class Interactor{...}``` - интерфейс для взаимодействия с пользователем,также служит для валидации данных  
  
#### Сигнатуры классов

##### Account
```c++
class Account {  
public:  
//конструкторы
	Account();  
	Account(const Account &item);  
	Account(std::string &source);  
	template<typename T>  
	Account(T name, T surname, T fathername,  
	long long int number, long double deposit) {...}  
	  

	bool toString(std::string &dest);  
	static void swap(Account &left, Account &right);  

//операторы
	friend Account& operator+(Account &item, long double money);  
	Account& operator=(Account const&right);  
	Account& operator+=(long double right);  
	friend std::ostream& operator<<(std::ostream &os, Account &item);  
	friend bool operator <(const Account&left, const Account &right);
	friend bool operator >(const Account&left, const Account &right);

// геттеры
	long long int getNum() const;
	static int getObjNum();
	
	~Account();  
  
private:  
	Person client;  
	long long int accountNumber;  
	long double deposit;  
	static int objNum;  
};
```
##### Bank
```c++
class Bank {  
  
public:  
	Bank(std::string &filename);  
	  
	~Bank() = default;  
	  
	template<typename T>  
	bool addAccount(T source) {...}  
	  
	template<typename T>  
	bool addAccount(T name, T surname, T fathername, long long int accNum, long double deposite){...}  
  
	void print();  
	void print(long long accNum);  
	void sort(int key = 0);  
	void saveChanges();  
  
private:  
	Account* searchByAccountNum(long long int accountNumber);  
  
	std::vector<Account> list;  
	std::string filename;  
};
```

##### Person
```c++
class Person {  
public:  
	Person();  
	  
	Person(Person &item);  
	  
	Person(std::string name, std::string surname, std::string fatherName);  
	  
	bool toString(std::string& dest);  
	  
	bool fromString(std::string& source);  
	  
	friend std::ostream& operator<<(std::ostream& out, Person &item) {...}  
	  
	friend class Account;  
	  
private:  
	std::string name;  
	std::string surname;  
	std::string fatherName;  
};
```

##### Interactor
```c++
class Interactor {  
public:  
	  
	static int getOption();  
	  
	static void clearAndWarn();  
	  
	static void printMenu();  
	  
	static std::string getAccount();  
	  
	template<typename T>  
	[[nodiscard]] static T *getField(int fieldFlag) {...}  
  
};

```
#### Листинг исходного кода

| Account | Bank | Interactor | Person |
|:---:|:---:|:---:|:---:|
| [Account.cpp](https://github.com/xXxINFARKTxXx/MIET/blob/main/2Sem/OOP_Spring_2023_MIET/Lab_03/src/Account.cpp) | [Bank.cpp](https://github.com/xXxINFARKTxXx/MIET/blob/main/2Sem/OOP_Spring_2023_MIET/Lab_03/src/Bank.cpp) | [Interactor.cpp](https://github.com/xXxINFARKTxXx/MIET/blob/main/2Sem/OOP_Spring_2023_MIET/Lab_03/src/Interactor.cpp) | [Person.cpp](https://github.com/xXxINFARKTxXx/MIET/blob/main/2Sem/OOP_Spring_2023_MIET/Lab_03/src/Person.cpp) |
| [Account.h](https://github.com/xXxINFARKTxXx/MIET/blob/main/2Sem/OOP_Spring_2023_MIET/Lab_03/headers/Account.h) | [Bank.h](https://github.com/xXxINFARKTxXx/MIET/blob/main/2Sem/OOP_Spring_2023_MIET/Lab_03/headers/Bank.h) | [Interactor.h](https://github.com/xXxINFARKTxXx/MIET/blob/main/2Sem/OOP_Spring_2023_MIET/Lab_03/headers/Interactor.h) | [Person.h](https://github.com/xXxINFARKTxXx/MIET/blob/main/2Sem/OOP_Spring_2023_MIET/Lab_03/headers/Person.h) |

[main.cpp](https://github.com/xXxINFARKTxXx/MIET/blob/main/2Sem/OOP_Spring_2023_MIET/Lab_03/src/main.cpp)

#### Пример работы программы

##### Начало работы (меню программы)
```
--------------------------------------------------------------------------------------------------------------------------------------
Print Base.......................1
Add new account..................2
Sort Base........................3
Find account by number...........4
Save changes.....................5
Print menu.......................6
Exit program.....................7

Enter option: 
```
> На любой невалидный ввод программа регирует следующим образом: ``` Wrong input!```.
> Кроме того программа прекращает взаимодействовать с пользователем в районе данной опции программы и выводит меню.
> Например:
```
Enter option: 2
Enter product name (all symbols except ';') and press Enter: Name 
Enter product type(1 - bun, 2 - pie, 3 - cake) and press Enter: 1 asd qwe
Wrong input!

...
\\\ Menu
...
```

##### Вывод занесенной базы на экран 
```
...
Enter option(6 to print menu): 1

Name:               Fathername:         Surname:            Account Number:     Deposit:            
-----------------------------------------------------------------------------------------------------
vladimir            voyakin             vladimirovich       4443234             56754               
qwe                 qwe                 asd                 123                 333333              
clad                arzanovich          ponmev              7                   16000               
-----------------------------------------------------------------------------------------------------
Total Accounts(objects):............................................................................3
Accounts(objects) printed:..........................................................................3


Enter option(6 to print menu): 
```

>В академических целях добавлен вывод на экран количества созданных объектов класса Food: ```Object number: ......11```, который в свою очередь меняется в зависимости от количесвтва объектов в базе. Форматированный вывод меняет количество итогов таблицы, за исключением последнего(количество объектов меняется только функциями (2) и (3) вышеописанного меню) 

##### Добавление пользователя
```
Enter option(6 to print menu): 2
Enter name: name
Enter surname: surname
Enter fathername: fathername
Enter account number: 12345678910
Enter deposit: 123

Account added!

Enter option(6 to print menu): 1

Name:               Fathername:         Surname:            Account Number:     Deposit:            
-----------------------------------------------------------------------------------------------------
vladimir            voyakin             vladimirovich       4443234             56754               
qwe                 qwe                 asd                 123                 333333              
clad                arzanovich          ponmev              7                   16000               
name                fathername          surname             12345678910         123                 
-----------------------------------------------------------------------------------------------------
Total Accounts(objects):............................................................................4
Accounts(objects) printed:..........................................................................4


Enter option(6 to print menu): 
```

#####  Сортировка
```
Enter option(6 to print menu): 3

Base sorted!

Enter option(6 to print menu): 1

Name:               Fathername:         Surname:            Account Number:     Deposit:            
-----------------------------------------------------------------------------------------------------
name                fathername          surname             12345678910         123                 
clad                arzanovich          ponmev              7                   16000               
vladimir            voyakin             vladimirovich       4443234             56754               
qwe                 qwe                 asd                 123                 333333              
-----------------------------------------------------------------------------------------------------
Total Accounts(objects):............................................................................4
Accounts(objects) printed:..........................................................................4


Enter option(6 to print menu): 

```

##### Вывод занесенной базы с фильтром
```
Enter option(6 to print menu): 4

Enter account number: 7
Name:               Fathername:         Surname:            Account Number:     Deposit:            
-----------------------------------------------------------------------------------------------------
clad                arzanovich          ponmev              7                   16000               
-----------------------------------------------------------------------------------------------------
Total Accounts(objects):............................................................................4
Accounts(objects) printed:..........................................................................1


Enter option(6 to print menu): 
```

##### Импорт данных из базы в файл
```
Enter option(6 to print menu): 5

Changes saved!

Enter option(6 to print menu):
```

##### Завершение работы
```
Enter option(6 to print menu): 7
Would you like to save changes?
Press enter to SAVE, enter any other character to CANCEL changes:d
Saving cancelled.
Press enter to EXIT, enter any other character to continue work with program:d

Enter option(6 to print menu): 7
Would you like to save changes?
Press enter to SAVE, enter any other character to CANCEL changes:
Changes are successfully saved!
Press enter to EXIT, enter any other character to continue work with program:
See ya!

...
```

## Ответы на контрольные вопросы

### 1.  Какие классы и функции называются дружественными?
Дружественные функции и классы - это функции и классы, которые не являются членами класса, однако имеют доступ к его закрытым членам - переменным и функциям, которые имеют спецификатор private.
    
### 2.  Как осуществляется перегрузка операций? 
Существует два основных способа перегрузки операторов: глобальные функции, дружественные для класса, или подставляемые функции самого класса
    
### 3.  Сколько аргументов требуется для определения перегруженной унарной (бинарной) операции?
С помощью ключевого слова friend - один аргумент
Без ключевого слова friend ни одного
Пример:
```c++
struct A{  
	A() = default;  
	  
	A& operator++(){  
		a++;  
		return *this;  
	}  
	  
	friend A& operator++(A& obj) {  
		obj.a++;  
		return obj;  
	}  
	  
	private:  
		int a{};  
}
```
    
### 4.  Чем отличается действие перегруженной операции ++ при ее использовании в префиксной форме от использовании в постфиксной форме?
Операторы `++` и  `--` возвращают в постфиксной форме копию объекта до произведения операции, в то время как в префиксной  форме сначала производится операция над объектом, затем возвращается сам объект.
Пример:
```c++
struct A {  
	A() = default;  

	A& operator++ () {  // префиксный оператор  
		value += 1;  
		return *this;  
	}  
	  
	A operator++ (int) {  // постфиксный оператор
		A copy {*this};  
		++(*this);  
		return copy;  
	}  
private:  
	int value{};  
};
```
    
### 5.  Какие ограничения существуют при перегрузке операторов?
Некоторые операторы обязаны быть перегружены как члены класса ( например operator=, operator() и некоторые другие ). Создать новые операторы нельзя. Также нельзя изменить количество операндов, их ассоциативность, приоритет. Также существуют рекомендации по перегрузки операторов исходя из семантики самих операторов, например правила перегрузки operator= для различных конструкторов (переноса, копирования). 

    
### 6.  Какую роль играет указатель this при перегрузке операторов?
Не используется при перегрузке операторов с помощью ключевого слова friend. При вызове методы класса получают:
-   список параметров
-   неявный константный указатель this  c адресом объекта, вызвавшего метод
`void set (int k){this->i=k;}`
Указатель this константный, то есть всегда указывает на один и тот же объект, адресные операции с ним запрещены.
    
### 7.  Какую роль играет указатель this при вызове метода класса?
Аналогично пункту 6.
    
### 8.  Приведите примеры повторных объявлений функций (ошибок перегрузки).
```c++
void foo(int a, int b) // пример объявленной функции
void foo(int c, int d) // ошибка
int foo(int a, int b) // ошибка
void foo(int a=5, int b=6) // ошибка
void foo(int a, int b, ...) // ошибка
```
[<назад>](https://github.com/xXxINFARKTxXx/MIET/tree/main/2Sem/OOP_Spring_2023_MIET)
