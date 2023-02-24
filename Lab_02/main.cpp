#include "Headers/utility.h"
#include "Headers/BaseInterface.h"
#include "Headers/Interactor.h"

using namespace std;

int main() {
    int option = 1;
    Base *cakes;
    try {
        cakes = new Base(FILEPATH);
    }
    catch (const std::runtime_error e) {
        cerr << e.what() << endl << "Exiting program!" << endl;
        return 0;
    }

    while (true) {
        std::cout << std::endl << std::setfill('-') << std::setw(134) << "-";
        cout << "\n"
                "Print............................1\n"
                "Add new product..................2\n"
                "Delete product by name...........3\n"
                "Print filtered by field..........4\n"
                "Sort.............................5\n"
                "Save changes.....................6\n"
                "Exit program.....................7\n"
                "\nEnter option: ";

        option = Interactor::getOption();
        switch (option) {
            case 1: {
                BaseInterface::print(*cakes);
                break;
            }
            case 2: {
                Food tmp = Food();
                if (Interactor::getItem(tmp)) {
                    switch (cakes->addItem(tmp)) {
                        case OUT_OF_MEMORY:
                            cout << "Can not add product: Computer memory is out!" << endl;
                            break;
                        case PRODUCT_ALREADY_IN_BASE:
                            cout << "Can not add product: product already in base!" << endl;
                            break;
                        case NO_ERROR:
                            cout << "Item added." << endl;
                            break;
                    }
                }
                break;
            }
            case 3: {
                string name;
                if (Interactor::getItemFieldValue(NAME, &name)) {
                    switch (cakes->removeItem(name)) {
                        case OUT_OF_MEMORY:
                            cout << "Can not remove product: Computer memory is out!" << endl;
                            break;
                        case PRODUCT_NOT_IN_BASE:
                            cout << "Can not remove product: product is not in the base!" << endl;
                            break;
                        case NO_ERROR:
                            cout << "Item removed." << endl;
                            break;
                    }
                }
                break;
            }
            case 4: {
                itemField field;
                compareDirection cd;
                string name;
                typeOfProduct type;
                double price, weight;
                int quant;
                if (Interactor::getItemField(field)) {
                    switch (field) {
                        case NAME:
                            if (Interactor::getItemFieldValue(field, &name))
                                BaseInterface::printBaseByFilter(*cakes, NAME, name, EQUAL_TO);
                            break;
                        case TYPE:
                            if (Interactor::getItemFieldValue(field, &type))
                                BaseInterface::printBaseByFilter(*cakes, TYPE, type, EQUAL_TO);
                            break;
                        case PRICE:
                            if (Interactor::getFilterDirection(cd) &&
                                Interactor::getItemFieldValue(field, &price))
                                    BaseInterface::printBaseByFilter(*cakes, field, price, cd);
                            break;
                        case QUANTITY:
                            if (Interactor::getFilterDirection(cd) &&
                                Interactor::getItemFieldValue(field, &quant))
                                    BaseInterface::printBaseByFilter(*cakes, field, quant, cd);
                            break;
                        case WEIGHT:
                            if (Interactor::getFilterDirection(cd) &&
                                Interactor::getItemFieldValue(field, &weight))
                                    BaseInterface::printBaseByFilter(*cakes, field, weight, cd);
                            break;
                    }
                }
                break;
            }
            case 5: {
                itemField field;
                sortingDirection direction;
                if(!Interactor::getItemField(field))
                    break;
                if(!Interactor::getSortingDirection(direction))
                    break;

                cakes->sort(direction, field);
                std::cout << "Base sorted!" << endl;
                break;
            }
            case 6: {
                Interactor::saveChanges(*cakes);
                break;
            }
            case 7: {
                if(!Interactor::exitProgram(*cakes))
                    break;
                delete cakes;
                cout << "See ya!" << endl;
                return 0;
            }
            default: {
                Interactor::wrongInputWarning();
                break;
            }
        }
    }
}