#include "include/pizza.h"

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
    SliceList<int> lst;

    cout << "Before object created adr = " << lst.head << endl;
    lst.push_back(5);

    cout << "After object created adr = " << lst.head << endl;

    return 0;
}
