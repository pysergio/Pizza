#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

class RisingError{
public:
    void invalidPizzaShape(){
        cout << "Pizza shape don't correspond with description." << endl;
        exit(0);}
    void invalidPizzaSize(){
        cout << "Pizza size is to big (limit 1000 x 1000)." << endl;
        exit(0);}
    void invalidIngredient(){
        cout << "Found invalid ingredient (symbol)." << endl;
        exit(0);}
    void invalidMinMax(){
        cout << "Minimum ingredients limit per slice is bigest than Maximum" << endl;
        exit(0);}
    void invalidPizza(){
        cout << "Pizza could not be cut. Invalid Pizza." << endl;
        exit(0);}
    void invalidFileFormat(){
        cout << "Invalid file format. File should be (*.in)" << endl;
        exit(0);}
    void toMuchIngredients(){
        cout << "Found to much one type ingreditns." << endl;
        exit(0);}
    void notOpened(){
        cout << "Error file open. Access denied." << endl;
        exit(0);}
};

class ReadingPizzaFile: public RisingError{
public:
    string      file;
    ReadingPizzaFile(string fpath);

    int*    getHeader();
    int**   getMatrix();
};

class Pizza{
public:
// Pizza size
    int         x;
    int         y;
// Slice ingredients
    int         min;
    int         max;
// Pizza matrix
    int         **pizzaMatrix;
};