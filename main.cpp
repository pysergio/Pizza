#include "include/Pizza.h"

int main(int argc, char const *argv[])
{

    if (argc <= 1){
        cout << "Please give me the Pizza." << endl;
        exit(0);
    }
    Pizza pizza(argv[1]);

    cout << pizza.getY() << ' ' << pizza.getX() << ' ' << pizza.getMin() << ' ' << pizza.getMax() << endl;

    pizza.printMatrix();
    cout << endl;
    pizza.printMask();
    
    return 0;
}
