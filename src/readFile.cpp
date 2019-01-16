#include "../include/pizza.h"

ReadingPizzaFile::ReadingPizzaFile(string fpath){
	
	if (fpath.substr(fpath.length() - 3) != ".in" ){
		invalidFileFormat();
	}

	cout << "Object is being created. " << fpath << endl;
	
	file = fpath;
}

void	ReadingPizzaFile::getHeader(){

	string		line;
	int			numbers;
	ifstream 	pizza(file);
	int			i;
	int			aux;

	if (pizza.is_open()){
		getline(pizza, line);
		pizza.close();
	} else {
		notOpened();
	}
	i = -1;
	while (line[++i] != '\0'){
		if (line[i] == ' ')
			i++;
		if (line[i] < '0' && line[i] > '9' )
			invalidHeader();
	}
	i = -1;
	numbers = 0;
	aux = 0;
	while (line[++i] != '\0'){
		if (line[i] == ' ') {
			if (numbers < 1 || numbers > 1000)
				invalidHeader();
			if (aux == 0) {
				row = numbers;
			} else if (aux == 1) {
				col = numbers;
			} else if (aux == 2) {
				min = numbers;
			}
			numbers = 0;
			aux++;
			i++;
		}
		numbers *= 10;
		numbers += line[i] - 48;
	}
	max = numbers;
	if (min * 2 > max){
		invalidMinMax();
	}
}

void	ReadingPizzaFile::getMatrix() {
	ifstream 	pizza(file);
	string		line;
	int			aux;

	pizzaMatrix = new int*[row];
	for (int i = 0; i < row; i++) {
		pizzaMatrix[i] = new int[col];
	}
	cout << row << ' ' << col << endl;
	if (pizza.is_open()) {
		getline(pizza, line);
		aux = 0;
		while (!pizza.eof()){
			getline(pizza, line);
			if (line.length() != col)
				invalidMatrix();
			for (int i = 0; line[i] != '\0'; i++) {
				if (line[i] != 'T' && line[i] != 'M')
					invalidIngredient();
				else if (line[i] == 'T') {
					pizzaMatrix[aux][i] = 1;
				} else if (line[i] == 'M') {
					pizzaMatrix[aux][i] = 0;
				}
			}
			aux++;
			cout << line << endl;
		}
		if (aux != row)
			invalidPizzaShape();
	} else {
		notOpened();
	}
	cout << endl;
	pizza.close();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << pizzaMatrix[i][j] << " ";
		}
		cout << endl;
	}
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