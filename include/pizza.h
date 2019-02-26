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
	int		**matrix;
	int		**mask;
	// Shapes list
	int		**divs;
	int		dCount;
	int		free_spaces_counter;

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
	// Slice list
	class   Slice {
	public:
		int x;
		int y;
		int dx;
		int dy;
		int shapeId;

		Slice();
	};
	List<Slice*> list;

	Pizza(string fpath);
	int     **getMatrix();
	int     **getDivs();
	int		getShapesC() { return this->dCount; }
	void	printHeader();
	void	printMatrix();
	void	printMask();
	void	printList();
	void	printFSC();
	void	solveIt(bool free_spaces_allowed);
};
Pizza::Slice::Slice() {
	this->x = 0;
	this->y = 0;
	this->dx = 0;
	this->dy = 0;
	this->shapeId = 0;
}
void	Pizza::setX(int X) {
	if (X < 1 || X > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->X = X;
}
void	Pizza::setY(int Y) {
	if (Y < 1 || Y > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->Y = Y;
}
void	Pizza::setMin(int min) {
	if (min < 1 || min > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->min = min;
}
void	Pizza::setMax(int max) {
	if (max < 1 || max > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->max = max;
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
		if (DIVS_ASCENDING)
			dc = 0;
		for (int i = this->min * 2; i <= max; i++)
			for (int j = 1; j <= i; j++)
				if (!(i % j)) {
					if (!DIVS_ASCENDING)
						dc--;
					this->divs[dc][0] = j;
					this->divs[dc][1] = i / j;
					if (DIVS_ASCENDING)
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
	int	fill = 1;
	int aux = 1;
	while (this->list.getSize() / (aux *= 10))
		fill++;
	for (int i = 0; i < this->Y; i++) {
		cout << "[ ";
		for (int j = 0; j < this->X; j++)
			if (this->mask[i][j] >= 0)
				cout << setfill('0') << setw(fill) << this->mask[i][j] << ' ';
			else if (this->mask[i][j] < 0)
				cout << setfill('-') << setw(fill) << this->mask[i][j] << ' ';
		cout << ']' << endl;
	}
}
void	Pizza::printFSC() {
		cout << "Free spaces = " << this->free_spaces_counter << endl;
}
void	Pizza::printList() {
	cout << this->list.getSize() << endl;
	for (int i = 0; i < this->list.getSize(); i++) {
		cout << list[i]->y << ' ' << list[i]->x << ' ' << list[i]->dy - 1
			<< ' ' << list[i]->dx - 1 << endl;
	}
}
void    Pizza::fileInit(string fpath) {
	if (fpath.substr(fpath.length() - FILE_FORMAT_LEN) == FILE_FORMAT) {
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
	free_spaces_counter = 0;
}
bool	Pizza::getCurrentPoint(int* x, int* y) {
	//Set current possition using (int* x, int* y) and return false if mask was filled(pizza was solved)
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
	//Try if shape => divs[shapeId] can be applied
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
void	Pizza::solveIt(bool free_spaces_allowed = true) {
	Slice* sl = nullptr;
	int sliceId = 1;
	if (free_spaces_allowed){
		int x = 0;
		int y = 0;
		while (this->getCurrentPoint(&x, &y)) {
			sl = new Slice;
			this->list.pushBack(sl);
			sl->x = x;
			sl->y = y;
			// Try to apply shape 
			while (sl->shapeId < this->getShapesC()) {
				if (this->tryShape(sl->x, sl->y, &sl->dx, &sl->dy, sl->shapeId)) {
					this->drawMask(sl->x, sl->y, sl->dx, sl->dy, sliceId);
					sliceId++;
					break;
				}
				sl->shapeId++;
			}
			// Skip this point if can't apply any shape
			if (sl->shapeId == this->getShapesC()) {
				if (this->matrix[sl->y][sl->x])
					this->mask[sl->y][sl->x] = -1;
				else
					this->mask[sl->y][sl->x] = -2;
				this->list.delBack();
				this->free_spaces_counter++;
			}
		}
	} else {
		// Backtrack algorithm
		while (sliceId) {
			if (sliceId > this->list.getSize()) {
				sl = new Slice;
				if (!this->getCurrentPoint(&sl->x, &sl->y)) {
					delete sl;
					return;
				}
				this->list.pushBack(sl);
			}
			else if (sliceId == this->list.getSize()) {
				sl = this->list.getBack();
				this->drawMask(sl->x, sl->y, sl->dx, sl->dy, 0);
				sl->shapeId++;
			}
			else if (sliceId < this->list.getSize()) {
				this->list.delBack();
				sl = this->list.getBack();
				this->drawMask(sl->x, sl->y, sl->dx, sl->dy, 0);
				sl->shapeId++;
			}
			// Try to apply shape 
			while (sl->shapeId < this->getShapesC()) {
				if (this->tryShape(sl->x, sl->y, &sl->dx, &sl->dy, sl->shapeId)) {
					this->drawMask(sl->x, sl->y, sl->dx, sl->dy, sliceId);
					sliceId++;
					break;
				}
				sl->shapeId++;
			}
			// Return back to apply another shape if can't apply any shape at this steep
			if (sl->shapeId == this->getShapesC())
				sliceId--;
		}
		RisingError::pizzaHasNoSolution();
	}
}