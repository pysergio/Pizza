#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#define FILE_FORMAT ".in"
#define HEADER_MAX  1000
#define INGR1 'T'
#define INGR2 'M'

class RisingError{
    public:
        static void invalidPizzaMatrix(){
            cout << "Pizza shape don't correspond with description." << endl;
            exit(1);}
        static void invalidIngredient(){
            cout << "Found invalid ingredient (symbol)." << endl;
            exit(1);}
        static void invalidMinMax(){
            cout << "Minimum ingredients limit per slice is bigest than Maximum" << endl;
            exit(1);}
        static void invalidPizza(){
            cout << "Pizza could not be cut. Invalid Pizza." << endl;
            exit(1);}
        static void invalidFileFormat(){
            cout << "Invalid file format. File should be (*.in)" << endl;
            exit(1);}
        static void toMuchIngredients(){
            cout << "Found to much one type ingredients.\nMake another Pizza;)" << endl;
            exit(1);}
        static void invalidHeader(){
            cout << "File header not valid." << endl;
            exit(1);}
        static void notOpened(){
            cout << "Error file open. Access denied." << endl;
            exit(1);}
        static void undefinedMinOrMax(){
            cout << "Can't set Divs, MIN or MAX are undefined!!!" << endl;
            exit(1);}
        static void undefinedXOrY(){
            cout << "Can't set Mask, X or Y are undefined!!!" << endl;
            exit(1);}
        static void pizzaHasNoSolution(){
            cout << "Given Pizza has no solution !!!\nMake another Pizza;)" << endl;
            exit(1);}
};