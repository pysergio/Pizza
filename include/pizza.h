
#include "sliceList.h"


class Pizza{
public:
// Pizza size
    int         row;
    int         col;
// Slice ingredients
    int         min;
    int         max;
// Pizza matrix
    int         **pizzaMatrix;
};

class RisingError{
public:
    void invalidPizzaShape(){
        cout << "Pizza shape don't correspond with description." << endl;
        exit(1);}
    void invalidPizzaSize(){
        cout << "Pizza size is to big (limit 1000 x 1000)." << endl;
        exit(1);}
    void invalidIngredient(){
        cout << "Found invalid ingredient (symbol)." << endl;
        exit(1);}
    void invalidMinMax(){
        cout << "Minimum ingredients limit per slice is bigest than Maximum" << endl;
        exit(1);}
    void invalidPizza(){
        cout << "Pizza could not be cut. Invalid Pizza." << endl;
        exit(1);}
    void invalidFileFormat(){
        cout << "Invalid file format. File should be (*.in)" << endl;
        exit(1);}
    void toMuchIngredients(){
        cout << "Found to much one type ingreditns." << endl;
        exit(1);}
    void invalidHeader(){
        cout << "File header not valid." << endl;
        exit(1);}
    void invalidMatrix(){
        cout << "File matrix not valid." << endl;
        exit(1);}
    void notOpened(){
        cout << "Error file open. Access denied." << endl;
        exit(1);}
};

class ReadingPizzaFile: public RisingError, public Pizza{
public:
    string      file;
    ReadingPizzaFile(string fpath);

    void    getHeader();
    void    getMatrix();
};
