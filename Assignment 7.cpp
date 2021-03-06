/*assignment 7
Joe Longman
program contains:
1. A vector class that implements a cartesian vector of length n, class contains:
	- A default constructor, parameterized constructor and destructor
	- Copy constructor and copy assignment operators
	- Move constructor and move assignment
	- Accessor operators to return components of the vector, check for addressing outside the length of the vector
	- A function to calculate the dot product of two vectors of identical length
	- a friend function for inserting vectors into an ostream
2. A derived class for minkowski 4 vectors 
	- two parameterized constructs, the first takes (ct,x,y,z), the second takes (ct) and the 3-vector (r) as arguments
	- copy constructor and copy assignment operators
	- move assignment and constructor operators
	- accessors returning the 4-vector components
	- an overridden function to return the dot product of 4 vectors
	- a function to return a lorentz boosted 4 vector, taking beta as a parameter
	- a friend function for inserting vectors into cout
3. A class particle which contains a 4 vector for the current position, a double mass and a 3-vector beta as data members
	- parameterised constructor takes 4-vector, double and 3-vector beta
	- a function to calculate gamma
	a function to return the total energy of the particle
	a function to return the momentum of the particle*/
#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

class n_vector {
protected:
	int length;		//integers for the length of array and create memory address for array 
	double *varray;
public:
	//default constructor
	n_vector() { length = 0;  varray = 0; }
	//parameterized constructor
	n_vector(int n) {
		if (n < 1) {
			cerr << "Fatal Error, length cannot be less than 0" << endl;
			exit(1);
		}
		length = n;
		varray = new double[length];
		for (int i = 0; i < length; i++) varray[i] = 0; //initially populate with zeros
	}
	//destructor
	~n_vector() { delete varray; } //varray cleared from memory
	
	//member functions
	n_vector(const n_vector& vec);	//copy constructor
	n_vector& operator =(const n_vector& vec);	//assignment operator
	n_vector(n_vector&& vec);	//move constructor
	n_vector& operator =(n_vector&& vec);	//move assignment	
	double& operator[](const int i)const;	//accessor operators
	double dot(const n_vector& vec)const;	//dot product function
	
	//get function for length
	int get_length() { return length; }

	double magnitude() {
		double output = 0;
		return sqrt(dot(*this));
	}

	friend ostream& operator <<(ostream& os, const n_vector& vec);	//ostream friend

};
//copy constructor
n_vector::n_vector(const n_vector& vec) {
	varray = 0; length = vec.length;	//set length of vector
	if (length > 0) //copy values
	{
		varray = new double[length];
		for (int i = 0; i < length; i++) varray[i] = vec[i];
	}
}

//assignment operator
n_vector& n_vector::operator =(const n_vector& vec) {
	if (&vec == this) return *this;	//check for self assignment
	delete[] varray; length = vec.length;		//delete the old array
	if (length > 0)
	{
		varray = new double[length];
		for (int i = 0; i < length; i++) varray[i] = vec[i];
	}
	return *this;
}

//move constructor
n_vector::n_vector(n_vector&& vec) {
	length = vec.length;
	varray = vec.varray;
	vec.length = 0;
	vec.varray = 0;
}
//move assignment operator
n_vector& n_vector::operator =(n_vector&& vec) {
	swap(length, vec.length);
	swap(varray, vec.varray);
	return *this;
}

//accessor operators
double& n_vector::operator[](const int i)const {
	if (i < 0 || i >= length) {		//check index exists in the vector
		cerr << "Fatal Error: index out of range, closing program..." << endl;
		exit(1);
	}
	return varray[i];
}

//dot product function
double n_vector::dot(const n_vector& vec)const {
	if (length != vec.length) {
		cerr << "Error: length of A must equal length of B for A.dot(B), closing program..." << endl;
		exit(1);
	}
	double output{ 0 };
	for (int i = 0; i < length; i++) {
		output += varray[i] * vec[i];
		return output;
		}
	return NAN;	//needs this for all other return situation
}	

ostream& operator <<(ostream &os,const n_vector& vec) {
	for (int i = 0; i < vec.length; i++) {
		os << "( " << vec[i] << " )" << endl;
	}
	return os;
}


enum elements {ct,x,y,z};
class four_vector: public n_vector {		//public access to n_vector class
public:
	//default constructor
	four_vector() :
		n_vector(4) {}
	//paramaterized constructor 4 vector input
	four_vector(const double ct,const double x,const double y, const double z):
		n_vector(4){	//derived class constructor explicitly uses base class constructor
		varray[0] = ct; varray[1] = x; varray[2] = y; varray[3] = z;
	}
	//paramaterized constructor for ct and vector input
	four_vector(const double ct, const n_vector& vec):
		n_vector(4){varray[0] = ct; varray[1] = vec[0]; varray[2] = vec[1]; varray[3] = vec[2];
	}
	
	//member functions
	four_vector(const four_vector& vec);				//copy constructor
	four_vector& operator =(const four_vector& vec);	//copy assignment 
	four_vector(four_vector&& vec);						//move assignment
	four_vector& operator =(four_vector&& vec);			//move constructor

	double& operator [](const elements i)const;			//accessors returning the 4 - vector components
	double& operator [](const int i)const;				//overloaded function allows specification by iteration value and also enum
	double dot(n_vector& vec)const;						//an overridden function to return the dot product of 4 vectors
	four_vector lorentz_boost(n_vector & beta)const;	//a function to return a lorentz boosted 4 vector, taking beta as a parameter

	//a friend function for inserting vectors into cout
	friend ostream& operator <<(ostream& os,four_vector& vec);	//ostream friend

};
//copy constructor
four_vector::four_vector(const four_vector& vec) {
	varray = 0; length = 4;
	varray = new double[4];
	for (int i = 0; i < 4; i++)varray[i] = vec[i];
}
//copy assignment 
four_vector& four_vector::operator =(const four_vector& vec){
	if (&vec == this) return *this;
	delete[] varray;
	length = 4;
	varray = new double[4];
	for (int i = 0; i < 4; i++)varray[i] = vec[i];
	return *this;
}
//move assignment
four_vector& four_vector::operator =(four_vector&& vec){
	swap(varray, vec.varray); 
	return *this;}

//move constructor
four_vector::four_vector(four_vector&& vec) {
	length = 4;
	varray = vec.varray;
	vec.varray = 0;
	vec.length = 0;
	}

//accessor
double& four_vector::operator [](const elements i)const {	//accesses based on enum ct,x,y,z
	if (i == ct)return varray[0];
	else if (i == x)return varray[1];
	else if (i == y) return varray[2];
	else if (i == z) return varray[3];
	else {
		cerr << "Fatal error: invalid reference to four-vector element. Elements must be ct,x,y,z or array index" << endl;
		exit(1);
	}
}
double& four_vector::operator [](const int i)const {			//access based on index
	if (i < 0 || i>3) {
		cerr << "Fatel error : four-vector index out of range" << endl;
		exit(1);
	}
	return varray[i];
}

//overridden dot product function
double four_vector::dot(n_vector& vec)const {
	if (vec.get_length() != 4) {					//check for length
		cout << "Fatal error: a.dot(b) requires a and b to be 4-vectors" << endl;
		exit(1);
	}
	double output = 0;
	output += varray[0] * vec[0];
	for (int i = 1; i < 4; i++) {
		output -= varray[i] * vec[i];	//minus for four_vectors 
	}
	return output;
}

//lorentz boost function
four_vector four_vector::lorentz_boost(n_vector & beta)const {
	//build up components of the equation
	double B = beta.magnitude();		
	double gamma = 1 / sqrt(1 - pow(B, 2));		//gamma = 1/sqrt(1-B^2)
	n_vector x(3);		
	x[0] = varray[1];

	n_vector r(3);		//vector r
	n_vector r_prime(3); //vector r'
	r[0] = varray[1]; r[1] = varray[2]; r[2] = varray[3];

	double constant = (gamma - 1)*(r.dot(beta) / pow(B, 2)) - gamma * varray[0];	//r' = r + constant * beta
	for (int i = 0; i < 3; i++) {
		r_prime[i] = r[i] + constant * beta[i];
	}
	double ct_prime = gamma * (varray[0] - beta.dot(x));
	
	four_vector output(ct_prime, r_prime);
	return output;
}

//friend function for ostream
ostream& operator <<(ostream& os, four_vector& vec) {
	if (vec.get_length() == 4) {
		os << "( ct=" << vec[ct] << " )" << endl;
		os << "( x=" << vec[x] << " )" << endl;
		os << "( y=" << vec[y] << " )" << endl;
		os << "( z=" << vec[z] << " )" << endl;
	}
	return os;
}


class particle {
public:
	four_vector position;
	double mass;
	n_vector beta;

	//default constructor
	particle() {
		n_vector b(3);
		beta = move(b);
		mass = 0;
	}
	//parameterized constructor
	particle(four_vector pos, double m, n_vector B) {
		if (B.get_length() != 3) {
			cerr << "Fatal Error: Beta must be a three vector" << endl;
			exit(1);
		}
		position = pos;
		mass = m;
		beta = B;
	}
	//function to calculate gamma
	double gamma() {
		return  1 / sqrt(1 - pow(beta.magnitude(), 2));
	}

	//function to calculate energy
	double energy() {			//E gamma*mc^2
		return gamma()*mass;
	}

	//function to caluclate momentum
	four_vector momentum() {		//4-momentum (E/c,px,py,pz) = (E/c,gamma*mv)
		four_vector output;
		output[ct] = energy();
		output[x] = gamma()*mass*beta[0];
		output[y] = gamma()*mass*beta[1];
		output[z] = gamma()*mass*beta[2];
		return output;
	}
};



int main()
{
	//main function aims to demonstrate the use of these three classes and their functions 
	//start with the n_vector class
	//define a 3-vector v1 (1,2,1)
	cout << "Demonstration of vector class:" << endl;
	n_vector v1(3);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 1;
	cout << "v1:\n" << v1<<endl;		//output v1

	//demonstrate copy constructors
	cout << "Demonstration of copy constructors:" << endl;
	//v2 = v1
	n_vector v2 = v1;
	n_vector v3;
	v3 = v1;
	v1[1] = 3;
	cout << "v1:\n" << v1 << endl;		//here it is shown that the copy is a deep copy
	cout << "v2:\n" << v2 << endl;
	cout << "v3:\n" << v3 << endl;

	//demonstration of move constructors
	cout << "Demonstration of move constructors" << endl;
	n_vector v4;
	v4 =  move(v2);
	n_vector v5 = move(v3);
	cout << "v4:\n" << v4 << endl;
	cout << "v5:\n" << v5 << endl;
	cout << "v2:\n" << v2 << endl;
	cout << "v3:\n" << v3 << endl;

	//demonstration of accessor
	cout << "\nDemonstration of accessor:" << endl;
	cout << "v4[1] = " << v4[1]<<endl;					///FOR TESTING TRY CHANGING THIS VALUE TO OUT OF RANGE

	//demonstration of dot product;
	cout << "\nDemonstration of the dot product:" << endl;
	cout << "v4.v5 = " << v4.dot(v5) << endl;

	//demonstration of 4-vector class
	cout << "\nDemonstration of four-vectors class:" << endl;
	four_vector f1(2, 1, 1, 1);
	four_vector f2(6, v4);

	cout << "f1:\n" << f1 << endl;
	cout << "f2:\n" << f2 << endl;

	//demonstrate copy constructors
	cout << "Demonstration of copy constructors:" << endl;
	four_vector f3 = f1;
	four_vector f4;
	f4 = f1;
	f1[1] = 3;
	cout << "f1:\n" << f1 << endl;		//here it is shown that the copy is a deep copy
	cout << "f3:\n" << f3 << endl;
	cout << "f4:\n" << f4 << endl;

	//demonstration of move constructors
	cout << "Demonstration of move constructors" << endl;
	four_vector f5;
	f5 = move(f1);
	four_vector f6 = move(f2);
	cout << "f5:\n" << f5 << endl;
	cout << "f6:\n" << f6 << endl;
	cout << "f1:\n" << f1 << endl;
	cout << "f2:\n" << f2<<endl;

	//demonstration of accessor
	cout << "\nDemonstration of accessor:" << endl;
	cout << "f5[x] = " << f5[x] << endl;					///FOR TESTING TRY CHANGING THIS VALUE TO OUT OF RANGE

	//demonstration of dot product;
	cout << "\nDemonstration of the dot product:" << endl;	///FOR TESTING TRY DOT PRODUCT WITH 3 VECTOR
	cout << "f5.f6 = " << f5.dot(f6) << endl;

	//demonstration of lorentz boost function
	n_vector beta(3);
	beta[0] = 0.1;
	cout << "\nDemonstration of lorentz boost function" << endl;
	cout << "B = 0.1x" << endl;
	cout << "lorentz boost(f5):" << endl;
	cout << f5.lorentz_boost(beta);

	//demonstration of particle class
	particle p1(f5, 2.6, beta);
	cout << "\nparticle p1(f5, 2.6, beta):" << endl;
	cout << "\ngamma" << endl;
	cout << p1.gamma() << endl;
	cout << "\nenergy" << endl;
	cout << p1.energy() << endl;
	cout << "\nmomentum" << endl;
	cout << p1.momentum() << endl;
	/*
	n_vector a;
	cout << a;
	n_vector b(3);
	b[0] = 3;
	b[1] = 4;
	b[2] = 5;
	n_vector c(3);
	c[0] = 1;
	c[1] = 2;
	c[2] = 1;
	cout << b << endl;
	cout << c << endl;
	cout << b.dot(c) << endl;

	four_vector d(25,b);
	four_vector e(1, 2, 3, 4);
	cout << e << endl;
	cout << d[ct] << endl;
	cout << d << endl;
	cout << d.dot(e)<<endl;
	n_vector beta(3);
	beta[0] = 0.1;
	cout << d.lorentz_boost(beta);
	*/
    return 0;
}

