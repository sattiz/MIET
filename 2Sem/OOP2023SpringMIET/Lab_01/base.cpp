#include "base.h"

using namespace database;

void base__printTablesTop() {
    std::cout << std::endl << std::left << std::setfill(' ')
              << std::setw(40) <<  "Name of product"
              << std::setw(10) << "Type"
              << std::setw(20) << "Weight"
              << std::setw(20) << "Quantity"
              << std::setw(20) << "Price(rub)"
              << std::setw(20) << "Total Price" << std::endl;
    std::cout << std::setfill('-') << std::setw(134) << "-" << std::endl;
}
void base__printTablesBot(const double totalPrice, const unsigned int totalPos){
    std::cout << std::setfill('-') << std::setw(134) << "-" << std::endl;
    std::cout << std::setfill('.') << std::setw(110) << "Total price of all products:" << totalPrice << std::endl;
    std::cout << std::setfill('.') << std::setw(110) << "Total positions:" << totalPos << std::endl;
}
void base__printItem(const item* item){
    std::string typeArr[] = {"bun", "pie", "cake"};
    std::cout << std::left << std::setfill(' ') << std::setw(40) << item->fam
              << std::setw(10) << typeArr[item->type-1]
              << std::setw(20) << item->weight
              << std::setw(20) << item->quant
              << std::setw(20) << item->price
              << std::setw(20) << item->price * item->quant << std::endl;
}
item* item__parseToItem(std::string s) {
    item* product = new item;
    std::string words[5];
    for(int i = 0, j = 0; i < s.length(); i++) {
        if(s[i] != ';')
            words[j].append(sizeof (char), s[i]);
        else{
            j++;
        }
    }
    product->fam.append(words[0]);
    product->type = (typeOfProduct)std::stoi(words[1]);
    product->weight = std::stod(words[2]);
    product->quant = std::stoi(words[3]);
    product->price = std::stod(words[4]);
    return product;
}
std::string* item__parseToString(database::item &item) {
    auto s = new std::string;
    s->append(item.fam); s->append(sizeof(char), ';');
    s->append(std::to_string(item.type)); s->append(sizeof(char), ';');
    s->append(std::to_string(item.weight)); s->append(sizeof(char), ';');
    s->append(std::to_string(item.quant)); s->append(sizeof(char), ';');
    s->append(std::to_string(item.price)); s->append(sizeof(char), ';');
    return s;
}
int base__compare (const void* l, const void* r) {
    return (*((item**)l))->price > (*((item**)r))->price ? -1 : 1;
}
int base__findItemByName(const base &self, const std::string &name){
    for(int i = 0; i < self.length; i++) {
        std::string l = self.itemsArr[i]->fam;
        std::string r = name;
        boost::algorithm::to_lower(l);
        boost::algorithm::to_lower(r);
        if (l == r)
            return i;
    }
    return 0;
}

error database::base_init(base &self) {
    self.length = 0;
    self.itemsArr = nullptr;
    self.name = FILEPATH;
    self.file.open(self.name, std::ios::in);
    if(!self.file.is_open()) {
        std::ofstream newFile;
        newFile.open(FILEPATH);
        if (!newFile.is_open())
            return CAN_NOT_OPEN_FILE;
        newFile.close();
        self.file.open(self.name);
        if(!self.file.is_open())
            return CAN_NOT_OPEN_FILE;
    }

    std::string s;
    while(std::getline(self.file, s)) {
        item *tmp = item__parseToItem(s);
        if (base_addItem(self, tmp) == OUT_OF_MEMORY)
            return OUT_OF_MEMORY;
    }
    self.file.close();

    return NO_ERROR;
}

error database::base_addItem(base &self,item *product) {
    if(!product)
        return WRONG_INPUT;
    if(base__findItemByName(self, product->fam))
        return PRODUCT_ALREADY_IN_BASE;
    item **tmp;
    try {
        tmp = new item* [self.length + 1];
    }
    catch (std::bad_alloc& ba) {
        return OUT_OF_MEMORY;
    }

    if(self.itemsArr) {
        std::memcpy(tmp, self.itemsArr, self.length * sizeof(item*));
        delete[] self.itemsArr;
    }

    self.itemsArr = tmp;
    self.itemsArr[self.length] = new item;
    *self.itemsArr[self.length] = *product;
    self.length++;
    return NO_ERROR;
}

void database::base_print(base &self) {
    if(self.length) {
        double totalPrice = 0;
        base__printTablesTop();

        unsigned int i;
        for (i = 0; i < self.length; i++) {
            base__printItem(self.itemsArr[i]);
            totalPrice += self.itemsArr[i]->price * self.itemsArr[i]->quant;
        }
        base__printTablesBot(totalPrice, i);
    } else {
        std::cout << "Base is empty!" << std::endl;
    }
}

void database::base_printPriceFilteredItems(const base &self,const double price, const CMP cmpFlag) {
    double totalPrice = 0;
    base__printTablesTop();

    bool (*compare) (double, double);
    switch (cmpFlag) {
        case LEFT_MORE_THEN_RIGHT: {
            compare = [](double l, double r) { return l > r; };
            break;
        }
        case LEFT_EQUAL_TO_RIGHT: {
            compare = [](double l, double r) { return std::fabs(l - r) < std::numeric_limits<double>::epsilon(); };
            break;
        }
        case LEFT_LESS_THEN_RIGHT: {
            compare = [](double l, double r) { return l < r; };
            break;
        }
    }

    unsigned int i, totalPos = 0;
    for(i = 0; i < self.length; i++) {
        if(compare(price, self.itemsArr[i]->price)) {
            base__printItem(self.itemsArr[i]);
            totalPrice += self.itemsArr[i]->price;
            totalPos++;
        }
    }

    base__printTablesBot(totalPrice, totalPos);
}

void database::base_printTypeFilteredItems(const base &self,const typeOfProduct type) {
    double totalPrice = 0;
    base__printTablesTop();

    unsigned int i, totalPos = 0;
    for(i = 0; i < self.length; i++) {
        if(self.itemsArr[i]->type == type) {
            base__printItem(self.itemsArr[i]);
            totalPrice += self.itemsArr[i]->price;
            totalPos++;
        }
    }

    base__printTablesBot(totalPrice, totalPos);
}

void database::base_printFoundItem(const base &self, const std::string &name) {
    int i = base__findItemByName(self, name);
    if(i) {
        base__printTablesTop();
        base__printItem(self.itemsArr[i]);
        base__printTablesBot(self.itemsArr[i]->price * self.itemsArr[i]->quant , 1);
    } else {
        std::cout << "Product is not found!" << std::endl;
    }
}

void database::base_sort(base &self) {
    std::qsort((void *) self.itemsArr, (size_t) self.length, (size_t) sizeof(self.itemsArr), base__compare);
}

void database::base_writeToFile(base &self){
    self.file.open(FILEPATH, std::ios::trunc | std::ios::out);
    for(int i = 0; i < self.length; i++) {
        self.file << *item__parseToString(*(self.itemsArr[i])) << "\n";
    }
    self.file.close();
}

void database::base_delete(base &self) {
    for(int i = 0; i < self.length; i++)
        delete self.itemsArr[i];
    delete[] self.itemsArr;
    self.itemsArr = nullptr;
}

