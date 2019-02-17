#include "include/Pizza.h"

int main(int argc, char const *argv[])
{

    if (argc <= 1){
        cout << "Please give me the Pizza." << endl;
        exit(0);
    }
    Pizza pizza(argv[1]);


        cout << endl;
        // pizza.printMatrix();
        pizza.solveIt();
        cout << endl;
        pizza.printMask();
        cout << endl;
        // pizza.printList();
    
    return 0;
}
