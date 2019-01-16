#include "../include/pizza.h"

ReadingPizzaFile::ReadingPizzaFile(string fpath){
	
	if (fpath.substr(fpath.length() - 3) != ".in" ){
		invalidFileFormat();
	}

	cout << "Object is being created. " << fpath << endl;
	
	file = fpath;
}

int*	ReadingPizzaFile::getHeader(){

	string		line;
	int*		numbers;
	ifstream 	pizza(file);

	cout << file;
	if (pizza.is_open()){
		getline(pizza, line);
		pizza.close();
	} else { notOpened();}

	cout << line << endl;

	cout << numbers[1];
}



// void PizzaFile::readFile(string path){
// 	char    c;
// 	file.open("input.in");
// 	if (file.is_open()){
// 		for (int i = 0; i < 4; i++){
// 			file >> this->firstLine[i]; 
// 		}
// 		//Memory alloc
// 		this->pizzaMatrix = new int*[this->firstLine[0]];
// 		int i = -1;
// 		while (++i < this->firstLine[0]){
// 			this->pizzaMatrix = new int[this->firstLine[1]];
// 		}
// 		for (int i = 0; i <= this->firstLine[0]; i++){
// 			for (int j = 0; j <= this->firstLine[1]; j++){
// 				if (file >> c == 'T'){
// 					this->pizzaMatrix[i][j] = 0;
// 				} else if (file >> c == 'M') {
// 					this->pizzaMatrix[i][j] = 1;
// 				} else {
// 					this->pizzaMatrix[i][j] = fille >> c;
// 				}
// 			}
// 		}
// 	}
// }