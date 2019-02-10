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
		void	drawMask(int x, int y, int shapeId, int sliceId);
		bool	getDeltas(int* dx, int* dy, int x, int y, int shapeId);
		bool	getCurrentPoint(int* x, int* y);
		bool	tryShape(int x, int y, int shapeId);

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

				Slice(int x, int y, int dx, int dy, int shapeId, int sliceId);
		};
		List<Slice*> list;

		Pizza(string fpath);
		int     getX();
		int     getY();
		int     getMin();
		int     getMax();
		int     **getMatrix();
		int     **getDivs();
		void	printHeader();
		void	printMatrix();
		void	printMask();
		void	solveIt(int shapeId = 0, int sliceId = 1);
};
Pizza::Slice::Slice(int x, int y, int dx, int dy, int shapeId, int sliceId){
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->shapeId = shapeId;
	this->sliceId = sliceId;
}
void	Pizza::setX(int X){
	if (X < 1 || X > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->X = X;
}
int		Pizza::getX(){
	return this->X;
}
void	Pizza::setY(int Y){
	if (Y < 1 || Y > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->Y = Y;
}
int		Pizza::getY(){
	return this->Y;
}
void	Pizza::setMin(int min){
	if (min < 1 || min > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->min = min;
}
int		Pizza::getMin(){
	return this->min;
}
void	Pizza::setMax(int max){
	if (max < 1 || max > HEADER_MAX)
		RisingError::invalidHeader();
	else
		this->max = max;
}
int		Pizza::getMax(){
	return this->max;
}
int**	Pizza::getMatrix(){
	return this->matrix;
}
int**	Pizza::getDivs(){
	return this->divs;
}
void 	Pizza::setClearMask(){
	if (this->X && this->Y){
		if (this->X * this->Y < min * 2)
			RisingError::pizzaHasNoSolution();
		this->mask = new int*[Y];
		for (int i = 0; i < Y; i++)
			this->mask[i] = new int[X];
		for (int i = 0; i < this->Y; i++)
			for (int j = 0; j < this->X; j++)
				this->mask[i][j] = 0;
	} else {
	}
}
void 	Pizza::setDivs(){
	if (this->min && this->max){
		int dc = 0;

		if (this->min * 2 > this->max)
			RisingError::invalidMinMax();
		for (int i = this->min; i <= max; i++)
			for (int j = 1; j <= i; j++)
				if (!(i % j))
					dc++;
		this->divs = new int*[dc];
		for (int i = 0; i < dc; i++)
			this->divs[i] = new int[2];
		this->dCount = dc;
		dc = 0;
		for (int i = this->min; i <= max; i++)
			for (int j = 1; j <= i; j++)
				if (!(i % j)){
					this->divs[dc][0] = j;
					this->divs[dc][1] = i / j;
					dc++;
				}
	} else 
		RisingError::undefinedMinOrMax();
}
void	Pizza::printHeader(){
    cout << this->Y << ' ' << this->X << ' ' << this->min << ' ' << this->max << endl;
}
void	Pizza::printMatrix(){
	for (int i = 0; i < this->Y; i++){
		cout << "[ ";
		for (int j = 0; j < this->X; j++)
			cout << this->matrix[i][j] << ' ';
		cout << ']' << endl;
	}
}
void	Pizza::printMask(){
	for (int i = 0; i < this->Y; i++){
		cout << "[ ";
		for (int j = 0; j < this->X; j++)
			cout << this->mask[i][j] << ' ';
		cout << ']' << endl;
	}
}
void    Pizza::fileInit(string fpath){
	if (fpath.substr(fpath.length() - 3) == FILE_FORMAT){
		this->fpath = fpath;
	} else {
		RisingError::invalidFileFormat();
	}
}
void    Pizza::readHeader(){
	ifstream	pfile(this->fpath);
	string		header;
	int			counter = 0;
	int			aux = 0;

	if (pfile.is_open()){
		getline(pfile, header);
		pfile.close();
	} else
		RisingError::notOpened();
	for (int i = 0; header[i]; i++){
		if (header[i] == ' ')
			i++;
		if (header[i] < '0' && header[i] > '9')
			RisingError::invalidHeader();
	}
	for (int i = 0; header[i]; i++){
		if (header[i] == ' ') {
			if (counter == 0){
				setY(aux);
			}
			else if (counter == 1){
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
void    Pizza::readMatrix(){
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
	while(getline(pfile, line)){
		if (line.length() != this->X)
			RisingError::invalidPizzaMatrix();
		for (int j = 0; line[j]; j++) {
			if (line[j] != INGR1 && line[j] != INGR2)
				RisingError::invalidIngredient();
			else if (line[j] == INGR1) {
				ingr1++;
				this->matrix[i][j] = 1;
			} else if (line[j] == INGR2) {
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
Pizza::Pizza(string fpath){
	fileInit(fpath);
	readHeader();
	readMatrix();
	setDivs();
	setClearMask();
}


bool	Pizza::getCurrentPoint(int* x, int* y){
	for (int i = 0; i < this->Y; i++)
		for (int j = 0; j < this->X; j++)
			if (!this->mask[i][j]){
				*x = j;
				*y = i;
				return true;
			}
	return false;
}
bool	Pizza::getDeltas(int* dx, int* dy, int x, int y, int shapeId){
	if (shapeId >= this->dCount)
		return false;

	*dx = this->divs[shapeId][0] + x;
	*dy = this->divs[shapeId][1] + y;

	if (*dx > this->X || *dy > this->Y)
		return false;

	return true;
}
void	Pizza::drawMask(int x, int y, int shapeId, int sliceId){
	int		dx;
	int		dy;
	getDeltas(&dx, &dy, x, y, sliceId);
		for (int i = y; i < dy; i++)
			for (int j = x; j < dx; j++)
				this->mask[i][j] = sliceId;
}
bool	Pizza::tryShape(int x, int y, int shapeId){
	int		dx;
	int		dy;
	int		sum = 0;

	if (getDeltas(&dx, &dy, x, y, shapeId))
		for (int i = y; i < dy; i++)
			for (int j = x; j < dx; j++){
				if (this->mask[i][j])
					return false;
				if (this->matrix[i][j])
					sum++;
			}
	else
		return false;
	if (this->max - sum < this->min || this->min < sum)
		return false;
	return true;
}	
void	Pizza::solveIt(int shapeId, int sliceId){
	int 	x;
	int		y;
	int		dx;
	int		dy;

	if (!getCurrentPoint(&x, &y))
		return;
	cout << endl;
	printMask();
	while (shapeId < this->dCount){
		if (tryShape(x, y, shapeId)){
			getDeltas(&dx, &dy, x, y, sliceId);
			drawMask(x, y, shapeId, sliceId);
			Slice newSlice(x, y, dx, dy, shapeId, sliceId);
			this->list.push_back(&newSlice);
			solveIt(0, sliceId + 1);
			return;
		}
		shapeId++;
	}
	return;
	
}