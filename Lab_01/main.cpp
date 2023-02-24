#include "base.h"
#include "utility.h"

using namespace std;
int main() {
    int option = 1;
    std::string filepath = FILEPATH;
    database::base cakes;
    database::error errcheck = database::base_init(cakes);
    if(errcheck) {
        cout << "Can not run program!" << endl;
        return errcheck;
    }

    while(true){
        std::cout << std::endl << std::setfill('-') << std::setw(134) << "-" ;
        cout << "\nAdd new product..................1\n"
                "Print product database...........2\n"
                "Find product by name.............3\n"
                "Filter database by price.........4\n"
                "Sort database by lowering price..5\n"
                "Filter database by product type..6\n"
                "Exit program.....................7\n"
                "\nEnter option: ";
        cin >> option;

        switch (option) {
            case 1: {
                auto t = (database::item *)getField(prod);
                switch (database::base_addItem(cakes, t)) {
                    case database::WRONG_INPUT:
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Wrong input!" << endl;
                        break;
                    case database::OUT_OF_MEMORY:
                        cout << "Out of memory!" << endl;
                        break;
                    case database::PRODUCT_ALREADY_IN_BASE:
                        cout << "Base already contains product with this name!" << endl;
                        break;
                    default:
                        cout << "Item added!" << endl;
                }
                delete t;
                break;
            }
            case 2: {
                base_print(cakes);
                break;
            }
            case 3: {
                auto fam = (string*)getField(name);
                if(isNonValid(fam)) break;
                database::base_printFoundItem(cakes, *fam);
                delete fam;
                break;
            }
            case 4: {
                auto pr = (double*)getField(price);
                if(isNonValid(pr)) break;
                auto cmpf = (database::CMP*)getField(cmpflag);
                if(isNonValid(cmpf)) break;
                database::base_printPriceFilteredItems(cakes, *pr, *cmpf);
                delete pr; delete cmpf;
                break;
            }
            case 5: {
                base_sort(cakes);
                cout << "Base sorted!" << endl;
                break;
            }
            case 6: {
                auto t = (database::typeOfProduct*)getField(type);
                if(isNonValid(t)) break;
                database::base_printTypeFilteredItems(cakes, *t);
                delete t;
                break;
            }
            case 7:
                char t;
                cout << "Do you want to save changes? Press 'ENTER' to save, any other key to cancel changes.";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                t = cin.get();
                if(t == '\n') {
                    database::base_writeToFile(cakes);
                    cout << "Changes saved!" << endl;
                } else {
                    cout << "Changes cancelled!" << endl;
                }
                database::base_delete(cakes);
                return 0;
            default:
                isNonValid(nullptr);
        }
    }
}
