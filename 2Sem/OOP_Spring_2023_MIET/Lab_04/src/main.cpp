#include <iostream>

#include "../headers/Account.h"
#include "../headers/Bank.h"
#include "../headers/Interactor.h"


using namespace std;

int main() {
    std::string filename = "Bank.txt";
    Bank bank(filename);

    int option = 1;
    Interactor::printMenu();

    while(option != 7){
        option = Interactor::getOption();
        switch (option) {
            case 1:{
                cout << endl;
                bank.print();
                cout << endl;
                break;
            }
            case 2:{
                std::string tmp = Interactor::getAccount();
                if(tmp.length()) {
                    if(!bank.addAccount(tmp)) {
                        cout << "Account already exists!" << endl;
                        break;
                    }
                    cout << endl << "Account added!" << endl;
                }
                else Interactor::clearAndWarn();
                break;
            }
            case 3:{
                bank.sort();
                cout << endl << "Base sorted!" << endl;
                break;
            }
            case 4:{
                cout << endl;
                long long *accNum = Interactor::getField<long long>(3);
                if (accNum) {
                    bank.print(*accNum);
                } else Interactor::clearAndWarn();
                delete accNum;
                cout << endl;
                break;
            }
            case 5:{
                bank.saveChanges();
                cout << endl << "Changes saved!" << endl;
                break;
            }
            case 6:{
                cout << endl;
                Interactor::printMenu();
                cout << endl;
                break;
            }
            case 7:{
                bank.saveChanges();
                cout << endl << "See ya!" << endl;
                break;
            }
            default:
                Interactor::clearAndWarn();
        }
    }
    return 0;
}
