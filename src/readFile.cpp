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
	int			T;
	int			M;

	pizzaMatrix = new int*[row];
	for (int i = 0; i < row; i++) {
		pizzaMatrix[i] = new int[col];
	}
	cout << row << ' ' << col << endl;
	T = 0;
	M = 0;
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
					T++;
					pizzaMatrix[aux][i] = 1;
				} else if (line[i] == 'M') {
					M++;
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


	if (row * col / T > max && row * col / M > max){
		invalidIngredient();
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
