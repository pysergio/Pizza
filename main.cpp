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
    lst.push_back("str");

    cout << "After object created adr = " << lst[-1] << endl;
    cout << "After object created adr = " << typeid(lst).name() << endl;

    return 0;
}
