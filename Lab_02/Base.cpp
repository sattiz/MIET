#include "Headers/Base.h"
#include "Headers/Food.h"

Base::Base(const std::string &filename) {
    this->length = 0;
    this->itemsArr = nullptr;
    this->filename = filename;


    std::fstream fp(filename, std::ios::in);
    if (!fp.is_open()) {
        std::ofstream newFile(filename);
        if (!newFile.is_open())
            throw std::runtime_error("Can not open file!");
        newFile.close();
    } else {
        std::string buf;
        while (std::getline(fp, buf)) {
            if (buf.empty()) break;
            Food newItem;
            try {
                newItem = Food(buf);
            }
            catch (...) {
                this->~Base();
                throw std::runtime_error("Can not read file!");
            }
            switch (this->addItem(newItem)) {
                case NO_ERROR:
                    break;
                case PRODUCT_ALREADY_IN_BASE:
                    this->~Base();
                    throw std::runtime_error("Can not read file!");
                case OUT_OF_MEMORY:
                    this->~Base();
                    throw std::runtime_error("Out of memory!");
            }
        }
    }

    this->saveState = true;
}

Base::~Base() {
    for (int i = 0; i < length; i++) {
        this->itemsArr[i].~Food();
    }
    operator delete[](this->itemsArr);
}

error Base::addItem(const Food &item) {
    std::string buf;
    item.getFam(buf);
    if (this->getItem(buf) != -1) {
        return error::PRODUCT_ALREADY_IN_BASE;
    }
    Food *tmp;
    try {
        tmp = static_cast<Food *>(operator new[]((this->length + 1) * sizeof(Food)));
    }
    catch (...) {
        return OUT_OF_MEMORY;
    }

    for (int i = 0; i < (this->length + 1); i++) {
        if (i < this->length) {
            try {
                new(tmp + i) Food(this->itemsArr[i]);
            }
            catch (...) {
                for (int j = 0; j < i; j++)
                    tmp[j].~Food();
                operator delete[](tmp);
                return OUT_OF_MEMORY;
            }
        } else {
            try {
                new(tmp + i) Food(item);
            }
            catch (...) {
                for (int j = 0; j < i; j++)
                    tmp[j].~Food();
                operator delete[](tmp);
                return OUT_OF_MEMORY;
            }
        }
    }


    for (int j = 0; j < length; j++) {
        this->itemsArr[j].~Food();
    }
    operator delete[](this->itemsArr);

    this->itemsArr = tmp;
    this->length++;
    this->saveState = false;

    return error::NO_ERROR;
}

error Base::removeItem(const std::string &name) {
    int index = this->getItem(name);
    if (index == -1)
        return PRODUCT_NOT_IN_BASE;

    Food *tmp;
    try {
        tmp = static_cast<Food *>(operator new[]((this->length - 1) * sizeof(Food)));
    }
    catch (...) {
        return OUT_OF_MEMORY;
    }
    for (int i = 0, j = 0; i < this->length; i++) {
        if (i != index) {
            try {
                new(tmp + j++) Food(this->itemsArr[i]);
            }
            catch (...) {
                for (int k = 0; k < j; k++)
                    tmp[k].~Food();
                operator delete[](tmp);
                return OUT_OF_MEMORY;
            }
        }
    }

    for (int j = 0; j < length; j++) {
        this->itemsArr[j].~Food();
    }
    operator delete[](this->itemsArr);

    this->itemsArr = tmp;
    this->length--;
    this->saveState = false;

    return NO_ERROR;
}

void Base::sort(sortingDirection sortDirection, itemField sortingField) {
    for (int i = 0; i < this->length - 1; i++) {
        for (int j = 0; j < this->length - i - 1; j++) {
            int difference = this->itemsArr[j].moreThen(sortingField, this->itemsArr[j + 1]);
            if (sortDirection == ASCENDING) {
                if (difference > 0)
                    Food::swap(this->itemsArr[j], this->itemsArr[j + 1]);
            } else {
                if (difference < 0)
                    Food::swap(this->itemsArr[j], this->itemsArr[j + 1]);
            }
        }
    }
    this->saveState = false;
}

error Base::saveTofFile() {
    std::ofstream fp(filename, std::ios::trunc | std::ios::out);
    if (!fp.is_open()) {
        std::ofstream newFile(filename, std::ios::trunc | std::ios::out);
        if (!newFile.is_open())
            return CANT_SAVE_CHANGES;
        newFile.close();
        fp.open(filename, std::ios::trunc | std::ios::out);
        if (!fp.is_open())
            return CANT_SAVE_CHANGES;
    }

    for (int i = 0; i < this->length; i++) {
        fp << *this->itemsArr[i].parseToString() << "\n";
    }
    this->saveState = true;
    return NO_ERROR;
}

int Base::getItem(const std::string &name) {
    for (int i = 0; i < this->length; i++) {
        std::string l;
        this->itemsArr[i].getFam(l);
        std::string r = name;
        boost::algorithm::to_lower(l);
        boost::algorithm::to_lower(r);
        if (l == r)
            return i;
    }
    return -1;
}




