#pragma once
template <typename T1>
class Array2d
{
public:
	Array2d();
	Array2d(int rows, int columns);
	~Array2d();
	
	T1 get(const unsigned int row, const unsigned int column);
	void set(const unsigned int row, const unsigned int column, T1 val);

	int get_rows();
	int get_cols();

private:
	unsigned int rows, columns; 
	T1** array; 

	// Выделение памяти для двумерного массива
	T1** malloc(int rows,int columns);

	// Очищение памяти после двумерного массива
	void mclear(T1** arr2d, int rows, int columns);
}; 

///////////////////////////////////////////////////////////////////////
// Реализация

template <typename T1>
Array2d <T1>::Array2d()
{
	this->rows = 1;
	this->columns = 1;
	array = malloc(rows, columns);
}

template <typename T1>
Array2d <T1>::Array2d(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;
	array = malloc(rows, columns);
}

template <typename T1>
Array2d <T1>::~Array2d()
{
	mclear(array, rows, columns);
	array = nullptr;
}

template <typename T1>
int Array2d <T1>::get_rows() { return rows; }

template <typename T1>
int Array2d <T1>::get_cols() { return columns; }

template <typename T1>
T1 Array2d <T1>::get(const unsigned int row, const unsigned int column)
{
	if (row >= this->rows && column >= this->columns)
		throw std::out_of_range("Request to an invalid memory location");
	return array[row][column];
}
// Добавить проверку на аргументы row, column

template <typename T1>
void Array2d <T1>::set(const unsigned int row, const unsigned int coloumn, T1 val)
{
	if (row >= this->rows || coloumn >= this->columns)
		throw std::out_of_range("Request to an invalid memory location");
	array[row][coloumn] = val;
}

template <typename T1>
T1** Array2d <T1>::malloc(int rows, int columns)
{
	if (rows <= 0 || columns <= 0)
		throw std::exception(" Need to (rows > 0 && columns > 0) ");
	T1** arr2d = new T1* [rows];
	for (int i = 0; i < rows; i++) arr2d[i] = new T1[columns];
	return arr2d;
}

template <typename T1>
void Array2d <T1>::mclear(T1** arr2d, int rows, int columns)
{
	if (rows <= 0 || columns <= 0)
		throw std::exception(" Need to (rows > 0 && columns > 0) ");
	for (int i = 0; i < rows; i++) delete[] arr2d[i];
	delete[] arr2d;
};