#include "List.h"


class Pizza {
protected:
	// File
	string  fpath;;
	// Pizza matrix size
	int		X;
	int		Y;
	// Ingredients limit per slice
	int		min;
	int		max;
	// Pizza matrix
	int**	matrix;
	// Shapes list
	int**	divs;
	int		dCount;

	void    fileInit(string fpath);
	void    readHeader();
	void    readMatrix();
	void    setClearMask();
	void    setDivs();
	void    setX(int X);
	void    setY(int Y);
	void    setMin(int min);
	void    setMax(int max);
	void	drawMask(int x, int y, int dx, int dy, int sliceId);
	bool	getCurrentPoint(int* x, int* y);
	bool	tryShape(int x, int y, int* dx, int* dy, int shapeId);

public:
	int         **mask;
	// Slice list
	class   Slice {
	public:
		int x;
		int y;
		int dx;
		int dy;
		int shapeId;
		int sliceId;

		Slice();
	};
	List<Slice*> list;

	Pizza(string fpath);
	int     getX();
	int     getY();
	int     getMin();
	int     getMax();
	int     **getMatrix();
	int     **getDivs();
	int		getDivsC() { return this->dCount; }
	void	printHeader();
	void	printMatrix();
	void	printMask();
	void	printList();
	void	solveIt();
};
Pizza::Slice::Slice() {
	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;
	this->shapeId = 0;
	this->sliceId = 0;
}
void	Pizza::setX(int X) {
	if (X < 1 || X > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->X = X;
}
int		Pizza::getX() {
	return this->X;
}
void	Pizza::setY(int Y) {
	if (Y < 1 || Y > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->Y = Y;
}
int		Pizza::getY() {
	return this->Y;
}
void	Pizza::setMin(int min) {
	if (min < 1 || min > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->min = min;
}
int		Pizza::getMin() {
	return this->min;
}
void	Pizza::setMax(int max) {
	if (max < 1 || max > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->max = max;
}
int		Pizza::getMax() {
	return this->max;
}
int**	Pizza::getMatrix() {
	return this->matrix;
}
int**	Pizza::getDivs() {
	return this->divs;
}
void 	Pizza::setClearMask() {
	if (this->X && this->Y) {
		if (this->X * this->Y < min * 2)
			RisingError::pizzaHasNoSolution();
		this->mask = new int*[Y];
		for (int i = 0; i < Y; i++)
			this->mask[i] = new int[X];
		for (int i = 0; i < this->Y; i++)
			for (int j = 0; j < this->X; j++)
				this->mask[i][j] = 0;
	}
	else {
	}
}
void 	Pizza::setDivs() {
	if (this->min && this->max) {
		int dc = 0;

		if (this->min * 2 > this->max)
			RisingError::invalidMinMax();
		for (int i = this->min * 2; i <= max; i++)
			for (int j = 1; j <= i; j++)
				if (!(i % j))
					dc++;
		this->divs = new int*[dc];
		for (int i = 0; i < dc; i++)
			this->divs[i] = new int[2];
		this->dCount = dc;
		dc = 0;
		for (int i = this->min * 2; i <= max; i++)
			for (int j = 1; j <= i; j++)
				if (!(i % j)) {
					// dc--;
					this->divs[dc][0] = j;
					this->divs[dc][1] = i / j;
					dc++;
				}
	}
	else
		RisingError::undefinedMinOrMax();
}
void	Pizza::printHeader() {
	cout << this->Y << ' ' << this->X << ' ' << this->min << ' ' << this->max << endl;
}
void	Pizza::printMatrix() {
	for (int i = 0; i < this->Y; i++) {
		cout << "[ ";
		for (int j = 0; j < this->X; j++)
			cout << this->matrix[i][j] << ' ';
		cout << ']' << endl;
	}
}
void	Pizza::printMask() {
	for (int i = 0; i < this->Y; i++) {
		cout << "[ ";
		for (int j = 0; j < this->X; j++)
			cout << this->mask[i][j] << ' ';
		cout << ']' << endl;
	}
}
void	Pizza::printList() {
	for (int i = 0; i < this->list.getSize(); i++) {
		cout << " x=" << list[i]->x;
		cout << " y=" << list[i]->y;
		cout << " dx=" << list[i]->dx;
		cout << " dy=" << list[i]->dy;
		cout << " shapeId=" << list[i]->shapeId;
		cout << " sliceId=" << list[i]->sliceId << endl;
	}
}
void    Pizza::fileInit(string fpath) {
	if (fpath.substr(fpath.length() - 3) == FILE_FORMAT) {
		this->fpath = fpath;
	}
	else {
		RisingError::invalidFileFormat();
	}
}
void    Pizza::readHeader() {
	ifstream	pfile(this->fpath);
	string		header;
	int			counter = 0;
	int			aux = 0;

	if (pfile.is_open()) {
		getline(pfile, header);
		pfile.close();
	}
	else
		RisingError::notOpened();
	for (int i = 0; header[i]; i++) {
		if (header[i] == ' ')
			i++;
		if (header[i] < '0' && header[i] > '9')
			RisingError::invalidHeader();
	}
	for (int i = 0; header[i]; i++) {
		if (header[i] == ' ') {
			if (counter == 0) {
				setY(aux);
			}
			else if (counter == 1) {
				setX(aux);
			}
			else if (counter == 2)
				setMin(aux);
			i++;
			aux = 0;
			counter++;
		}
		aux *= 10;
		aux += header[i] - 48;
	}
	if (counter == 3)
		setMax(aux);
	else
		RisingError::invalidHeader();
}
void    Pizza::readMatrix() {
	ifstream	pfile(fpath);
	string		line;
	int			ingr1 = 0;
	int			ingr2 = 0;
	int			i = 0;

	this->matrix = new int*[this->Y];
	for (int i = 0; i < this->Y; i++)
		this->matrix[i] = new int[this->X];
	if (pfile.is_open())
		getline(pfile, line);
	else
		RisingError::notOpened();
	while (getline(pfile, line)) {
		if (line.length() != this->X)
			RisingError::invalidPizzaMatrix();
		for (int j = 0; line[j]; j++) {
			if (line[j] != INGR1 && line[j] != INGR2)
				RisingError::invalidIngredient();
			else if (line[j] == INGR1) {
				ingr1++;
				this->matrix[i][j] = 1;
			}
			else if (line[j] == INGR2) {
				ingr2++;
				this->matrix[i][j] = 0;
			}
		}
		i++;
	}
	if (i != this->Y)
		RisingError::invalidPizzaMatrix();
	if (this->X * this->Y / ingr1 > this->max && this->X * this->Y / ingr2 > this->max)
		RisingError::toMuchIngredients();

	pfile.close();
}
Pizza::Pizza(string fpath) {
	fileInit(fpath);
	readHeader();
	readMatrix();
	setDivs();
	setClearMask();
}
bool	Pizza::getCurrentPoint(int* x, int* y) {
	for (int i = 0; i < this->Y; i++)
		for (int j = 0; j < this->X; j++)
			if (!this->mask[i][j]) {
				*x = j;
				*y = i;
				return true;
			}
	return false;
}
void	Pizza::drawMask(int x, int y, int dx, int dy, int sliceId) {
	for (int i = y; i < dy; i++)
		for (int j = x; j < dx; j++)
			this->mask[i][j] = sliceId;
}
bool	Pizza::tryShape(int x, int y, int* dx, int* dy, int shapeId) {
	int		sum = 0;
	*dx = this->divs[shapeId][0] + x;
	*dy = this->divs[shapeId][1] + y;
	if (*dx > this->X || *dy > this->Y)
		return false;
	for (int i = y; i < *dy; i++)
		for (int j = x; j < *dx; j++) {
			if (this->mask[i][j])
				return false;
			if (this->matrix[i][j])
				sum++;
		}
	if (this->min > this->divs[shapeId][0] * this->divs[shapeId][1] - sum || this->min > sum)
		return false;
	return true;
}
void	Pizza::solveIt() {
	Slice* sl = nullptr;
	int sliceId = 1;
	int success = this->X * this->Y; // 
	int percentage = 0;

	while (sliceId) {
		if (!(sliceId % 20)) {
			int progress = success;
			for (int i = 0; i < this->Y; i++) {
				for (int j = 0; j < this->X; j++) {
					if (!this->mask[i][j])
						progress--;
				}
			}
			if (percentage != (int)(((float)progress / (float)success) * 100)){
				percentage = (int)(((float)progress / (float)success) * 100);
				cout << percentage << "%%" << endl;
			}
		}
		// printMask();
		if (sliceId < this->list.getSize()){
			sl = this->list[-1];
			delete sl;
			this->list.del_back();
			sl = this->list[-1];
			sl->shapeId++;
			drawMask(sl->x, sl->y, sl->dx, sl->dy, 0);	// Remove slice from mask when go back
		}
		else if (sliceId > this->list.getSize()) {
			sl = new Slice();
			sl->sliceId = sliceId;
			sl->shapeId = 0;
			if (!getCurrentPoint(&sl->x, &sl->y)) {
				return;
			}
			this->list.push_back(sl);
		}
		else {
			sl = this->list[-1];
			sl->shapeId++;
			drawMask(sl->x, sl->y, sl->dx, sl->dy, 0);	// Remove slice from mask when go back
		}
		while (sl->shapeId < this->dCount) {
			if (tryShape(sl->x, sl->y, &sl->dx, &sl->dy, sl->shapeId)) {
				drawMask(sl->x, sl->y, sl->dx, sl->dy, sl->sliceId);
				sliceId++;
				break;
			}
			sl->shapeId++;
		}
		if (sl->shapeId >= this->dCount)
			sliceId--;
	}

	RisingError::pizzaHasNoSolution();
}
