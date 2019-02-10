#include "include/Pizza.h"

int main(int argc, char const *argv[])
{
    if (argc <= 1){
        cout << "Please give me the Pizza." << endl;
        exit(0);
    }
    Pizza pizza(argv[1]);


        pizza.solveIt(0, 1);
        cout << endl;
        pizza.printMask();
    
    return 0;
}
