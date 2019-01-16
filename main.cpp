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
    return 0;
}
