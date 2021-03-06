/* assignmnet 6.cpp
Joe Longman
C++ class for matrices

Matrix data is stored in a 1D array, location of element A_ij given by (j-1) + (i-1)*n
Requirements:
- Parametrized constructor (utlizing new) - done
- Destructor using delete - done
- Member function to overload assignment operator that perfomrs a deep copy of data -done
-Also handles self assignment - done
- A copy constructor and copy assignment operator that perform a deep copy of the class data -done
- Move constructor and move assignment
- Friend fucntion to overload << and >> for io of matrix data -done
- Overloaded +, - * for matrix arithmetic-  done
- A function to return a matrix with the ith row and jth column deleted - done
- A recursive function to calculate the determinant of a square matrix - done
*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

//create enum for row or column (used in delete row/column function)
enum rowcolumn{row, column};
bool declare;

//MATRIX CLASS DECLARATION
class matrix
{
private:
	int rows, columns;//integers for the number of rows and the number of column
	int size = rows * columns;
	double *marray;

public:
	matrix() { if(declare)cout << "default constructor called" << endl; rows = 0; columns = 0; size = 0; marray = 0; }		//default constructor
	matrix(int r, int c);			//parametrized constructor

	matrix(const matrix& mat);		//copy constructor
	matrix(matrix&& mat);			//move constructor
	matrix & operator =(const matrix& mat); //assignment operator
	matrix & operator =(matrix&& mat);	//move assignmet operator

	~matrix() { delete marray; if(declare)cout << "Destructor called" << endl; }	//destructor

	//get and set functions 
	int row_num() const { return rows; }		// member function outputs number of rows
	int column_num() const { return columns; }	//member function outputs number of columns

	void set_row_num(const int number) { rows = number; }	//set the number of rows and columns
	void set_column_num(const int number) { columns = number; }

	double & operator()(const int i, const int j);	//overloaded element operator for accessing matrix elements
	double & operator[](const int i)const; //overloaded element operator for accessing matrix elements by 1D array value
	
	//declare functions for matrix iostream 
	friend ostream &operator <<(ostream &os, const matrix &mat);
	friend istream &operator >> (istream &is, matrix &mat);

	friend double determinant(matrix &mat);	//function to calculate determinant of matrix
	friend matrix deleterc(rowcolumn choice, int index, matrix &mat);		//function to delete row or column

	void populate(const double number) {			//populates the matrix with the value specified in the argument 
		for (int i = 0; i < size; i++) marray[i] = number;
		return;
	}
	//arithmetic operators
	matrix operator+(const matrix &mat);
	matrix operator-(const matrix &mat);
	matrix operator*(const matrix &mat);
};

					////END OF CLASS DECLARATION/////

//parametrized constructor
matrix::matrix(int r, int c) {
	if (declare) {
		cout << "parametrized constructor called" << endl; //constructors can declare when they are called for helpful error checking
	}	
	if (r < 1 || c < 1) {							//check for negative entries
		cerr << "Fatal Error: row and column size must be a positive integer, closing program..." << endl;
		exit(1);			//improper entries kills program
	}
	size = r * c;			//assign parameter values
	rows = r;
	columns = c;
	marray = new double[size];		//store matrix elements in marray
	for (int i = 0; i < size; i++) marray[i] = 0;	//initially populate with 0
}

//copy constructor
matrix::matrix(const matrix &mat) {		//argument in copy constructor must be a const reference to the class
	if (declare) cout << "called copy constructor" << endl;
	marray = 0; columns = mat.columns; rows = mat.rows; size = rows * columns;	//set values
	if (size > 0)	//copy values over if matrix has size
	{
		marray = new double[size];
		for (int i = 0; i < size; i++) marray[i] = mat[i];
	}
}
//move constructor
matrix::matrix(matrix&& mat) {
	if(declare) cout << "called move constructor" << endl;
	rows = mat.rows;
	columns = mat.columns;
	size = rows * columns;
	marray = mat.marray;
	mat.rows = 0;
	mat.columns = 0;
	mat.size = 0;
	mat.marray = 0;
}

//assignment operator
matrix &matrix::operator=(const matrix &mat){		//argument in assignment operator must be a const reference to the class
	if(declare) cout << "assignment operator called" << endl;
	if (&mat == this) return *this;					//check for self assignment
	delete[] marray;			//delete the old array and set values
	columns = mat.column_num(); rows = mat.row_num(); size = rows * columns;
	if (size > 0)
	{
		marray = new double[size];
		for (int i = 0; i < size; i++) marray[i] = mat[i];
	}
	return *this;
}

//move assignment operator
matrix & matrix::operator=(matrix&& mat) {
	if (declare) cout << "called move assignment operator" << endl;
	swap(rows, mat.rows);
	swap(columns, mat.columns);
	swap(size, mat.size);
	swap(marray, mat.marray);
	return *this;
}

//overloaded () operator to access matrix elements, elements accessed as matrix(i,j)
double & matrix::operator()(const int i, const int j) {
	if (i<0 || j<0 || i >= rows + 1 || j >= columns + 1) {		//check elements exist in the matrix
		cerr << "Fatal Error: matrix index out of range, closing program..." << endl;
		exit(1);
	}
	int index = (j - 1) + (i - 1)*columns;	//conversion from 2D matrix to 1D array
	return marray[index];
}

//overloaded [] operator for accessing matrix elements by 1D array value, with error checking
double & matrix::operator[](const int i)const {
	if (i<0 || i >= size) {		//check elements exist in the matrix
		cerr << "Fatal Error: array index out of range, closing program..." << endl;
		exit(1);
	}
	return marray[i];
}

//function for matrix addition
matrix matrix::operator+(const matrix &mat){
	
	if (rows != mat.row_num() || columns != mat.column_num()) {
		cerr << "Error: Addition requires same size of row and column" << endl;
		matrix temp(1, 1);
		return temp; //check that rows and columns are equal size
	}
	matrix temp(rows, columns);
	for (int i = 0; i < size; i++) temp[i] = marray[i] + mat[i];
	return temp;
}

//function for matrix subtraction
matrix matrix::operator-(const matrix &mat) {
	if (rows != mat.row_num() || columns != mat.column_num()) {
		cerr << "Error: Subtraction requires same size of row and column" << endl;
		matrix temp(1, 1);
		return temp; //check that rows and columns are equal size
	}
	matrix temp(rows, columns);
	for (int i = 0; i < size; i++) {

		temp[i] = marray[i] - mat[i];
	}
	return temp;
}

//function for matrix multiplication
matrix matrix::operator*(const matrix &mat) {
	if (columns != mat.row_num()) {
		cerr << "Error: Multiplication of matrices with size (m x n) and (M x N) requires n = M" << endl;
		matrix temp(1, 1);
		return temp;
	}
	matrix temp(rows, mat.column_num());		//implements a simple O(nmp) iterative algorithm from definition of matrix multiplication
	for (int i = 1; i <= rows; i++) {			//source: https://en.wikipedia.org/wiki/Matrix_multiplication_algorithm#Iterative_algorithm
		for (int j = 1; j <= mat.row_num(); j++) {
			double sum = 0;
			for (int k = 1; k <= columns; k++) {
				int index1 = (k - 1) + (i - 1)*columns;
				int index2 = (j - 1) + (k - 1)*mat.column_num();
				sum += marray[index1] * mat[index2];
			}
			temp(i, j) = sum;
		}
	}
	return temp;
}

//output matrix in ostream
ostream &operator <<(ostream &os, matrix &mat) {
	os << endl;
	for (int row = 1; row <= mat.row_num(); row++) {	//iterate over rows and columns
		os << "(";		//add opening bracket on each line
		for (int column = 1; column < mat.column_num(); column++) {
			os << mat(row, column) << ",";
		}
		os <<mat(row,mat.column_num())<< ")" << endl;
	}
	os << endl;
	return os;
}


//function to delete row or column
matrix deleterc(rowcolumn choice,int index, matrix &mat){		
	if (choice == row) {
		matrix temp(mat.rows - 1, mat.columns);
		int k = 0;
		for (int i = 1; i <= mat.rows; i++) {
			for (int j = 1; j <= mat.columns; j++) {
				if (i == index) {}
				else { temp[k] = mat(i, j); k++; }
			}
		}
		return temp;
	}
	else {
		matrix temp(mat.rows, mat.columns-1);
		int k = 0;
		for (int i = 1; i <= mat.rows; i++) {
			for (int j = 1; j <= mat.columns; j++) {
				if (j == index) {}
				else { temp[k] = mat(i, j); k++; }
			}
		}
		return temp;
	}
}

//recursive function to calculate matrix determinant
double determinant(matrix &mat) {
	if (mat.rows != mat.columns) {
		cerr << "Must be square matrix for determinate calculation, returning 0..." << endl;
		return 0;
	}
	else if (mat.size == 4) {
		return mat[0] * mat[3] - mat[1] * mat[2];
	}
	else {
		double det = 0;
		for (int k = 1; k <= mat.columns; k++) {
			matrix temp = deleterc(row, 1, mat);
			temp = deleterc(column, k, temp);
			det += pow(-1, k - 1)*mat(1, k)*determinant(temp);
		}
		return det;
	}
}


//istream  requires conversion of comma delimited string into list of inputs
//this function splits string into vector of strings using chosen delimiter
vector <string> stringsplit(const string &astring, char delim) {
	vector <string> elements;
	stringstream ss(astring);
	string item;
	while (getline(ss, item, delim)) {
		if (item.empty()) {				//any missed values are given a value of 0, so input of 1,2,,3 --> (1,2,0,3) in matrix
			item = "0";
		}
		elements.push_back(item);
	}
	return elements;
}

//input matrix in istream
istream &operator >> (istream &is, matrix &mat) {
	int columnnum, rownum;						//first request number of rows and columns
	cout << "enter number of rows" << endl;
	is >> rownum;
	cout << "enter number of columns" << endl;
	is >> columnnum;
	is.clear();				//need to clear stream before getline
	is.ignore(256,'\n');
	matrix temp(rownum, columnnum);		//create temporary matrix then move data to mat	
	mat = move(temp);

	for (int i = 1; i <= mat.rows; i++) {		//request data row by row, until complete
		cout << "\nEnter comma delimited row of matrix (e.g. 1,2,3,4): ";
		string line;
		getline(is, line);
		vector <string> elements = stringsplit(line, ',');
		int matpos = 1;		//iterator for column position
		for (auto iterator = elements.begin(); iterator != elements.end(); iterator++) {//iterate through elements vector
			double value;
			bool valid = true;
			try {						//stod throws exception if not numerical 
				value = stod(*iterator);
			}
			catch (const invalid_argument& ia) {		//catches stod invalid argument exception and ignores value
				cerr << ia.what()<<" , did you enter a non-numeric value?"<< endl;
				valid = false;
			}
			if (matpos > mat.columns) {		//method asks for whole 
				cerr << "Warning: too many values input, ignoring values at end of row..." << endl;
				valid = false;
			}
			if (valid) {			//adds value to corresponding point in the matrix
				mat(i, matpos) = value;
				matpos++;
			}
		}
	}
	return is;
}

///MAIN PROGRAM STARTS HERE///

int main() {
	string response;
	bool isvalid = false;
	while (!isvalid) {
		cout << "Declare when the constructor, copy, move and destructor functions are called? (y/n)" << endl;
		getline(cin, response);
		if (response == "y") {
			declare = true;
			isvalid = true;
		}
		else if (response == "n") {
			isvalid = true;
			declare = false;
		}
		else cout << "response must be y or n!" << endl;
	}

	cout << "Hello, welcome to the matrix calculator\nEnter matrix A:" << endl;
	matrix mat1;
	cin >> mat1;
	cout << "Enter matrix B:" << endl;
	matrix mat2;
	cin >> mat2;
	cout << endl;
	cout << "Matrix A:" << mat1;
	cout << "Matrix B:" << mat2;
	cout << "A+B:" << endl;
	matrix mat3 = mat1 + mat2;
	cout << mat3;
	cout << "A-B:" << endl;
	mat3 = mat1 - mat2;
	cout << mat3;
	cout << "A*B:" << endl;
	mat3 = mat1 * mat2;
	cout << mat3;
	cout << "determinant of matrix A = " << determinant(mat1) << endl;
	cout << "determinant of matrix B = " << determinant(mat2)<<endl;

	cout << endl;
	cout << "Demonstration of move and copy constructors" << endl;
	cout << "Creating default matrices mat4 and mat5..." << endl;
	matrix mat4;
	matrix mat5;
	cout << "mat4:" << mat4;
	cout << "mat5:" << mat5;
	cout << "mat4 = matrix A"<<endl;
	mat4 = mat1;
	cout << "mat4:" << mat4;
	cout << "mat5 = move(matrix A)"<<endl;
	mat5 = move(mat1);
	cout << "mat5:" << mat5;
	cout << "matrix A:" << mat1;
	cout << "matrix mat6 = matrix B" << endl;
	matrix mat6 = mat2;
	cout << "mat6: " << mat6;
	cout << "matrix mat7 = move(matrix B)" << endl;
	matrix mat7 = move(mat2);
	cout << "mat7: " << mat7;
	return 0;
}