#include "include/pizza.h"
#define MACRO_VARIABLE_TO_STRING(Variable) (void(Variable),#Variable)

int main(int argc, char const *argv[])
{
    if (argc <= 1){
        cout << "Please give me the Pizza." << endl;
        exit(0);
    }

    ReadingPizzaFile PizzaFile(argv[1]);
    PizzaFile.getHeader();
    PizzaFile.getMatrix();

    // RisingError RisingError;
    // RisingError.invalidPizza();
    SliceList<string> lst;

    // cout << "Before object created data = " << lst[0] << endl;
    lst.push_back("str");  // index = 0
    lst.push_back("str2"); // index = 1
    lst.push_back("str3"); // index = 2

    cout << "Check list index operator " << lst[0] << endl;
    cout << "Check list index operator " << lst[1] << endl;
    cout << "Check list index operator " << lst[2] << endl;
    cout << "Check list index operator " << lst[-1] << endl;
    cout << "Check list index operator " << lst[4] << endl;
    
    return 0;
}
