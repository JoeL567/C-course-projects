//Assingment 8
//Joe Longman

/*Program contains a class heirachy to describe the properties of 2D and 3D shapes
Class Requirements:
	- Abstract base class used as an interfrace for all shapes with pure virtual functions and virtual destructor			line 28
	- Abstract derived class for 2D and 3D shapes																			line 38 (2D) and line 89(3D)
	- Further derived classes for 4 2D shapes: rectangle, square, ellipse, circle
	- Further derived classes for 4 3D shapes: cuboid, cube, ellipsoid, sphere
	- Constructors and virtual destructors
	- Pure virtual functions to return area and volume (can be zero for 2D shapes)
	- Write an extra derived prism class which takes a double (depth) and a base class pointer to any of the 2D shapes

Main program requirements:
	- Implement vector of 8 base class pointers, each pointing to a different shape
	- Output the area and volume of each shape
	- Clean up by deleting objects and array when finished
*/
#include "stdafx.h"
#include <iostream>		
#include <cmath>		//to calculate area and volume
#include <vector>
#include <string>

const double pi = 3.14159265358979323846;
using namespace std;

//base class for a shape
class shape {
public:
	virtual ~shape() {}	//destructor
	virtual double area() = 0;	//pure virtual functions return the area and volume
	virtual double volume() = 0;
	virtual string info() = 0;

};

//derived class for a 2D shape
class twoD_shape : public shape {
public:
	virtual ~twoD_shape() {}//destructor
	virtual double area() = 0;
	virtual string info() = 0;
	double volume() { cerr << "Error: A 2D shape has no volume"<<endl; return 0; }
};
	
class rectangle: public twoD_shape{	//rectangle class
protected:
	double length, width;
public:
	rectangle() : length{ 0 }, width{ 0 } {}		//default constructor
	rectangle(double l, double w) : length{ l }, width{ w } {}	//parametrized constructor
	~rectangle() {}	//destructor

	string info() { return "rectangle"; }
	double area() { return length * width; }
};

class square : public rectangle {//square class (derived from rectangle) 
public:
	square() : rectangle() {}
	square(double size) : rectangle(size, size) {}
	~square() {}

	string info() { return "square"; }
};

class ellipse : public twoD_shape {			//ellipse class
protected:
	double major, minor;
public:
	ellipse() : major{ 0 }, minor{ 0 } {}	//constructors
	ellipse(double a, double b) : major{ a }, minor{ b } {}
	~ellipse() {}

	double area() { return pi*major * minor; }
	string info() { return "ellipse"; }
};

class circle : public ellipse {//circle class	(derived from ellipse)
public:
	circle() : ellipse() {}
	circle(double radius) : ellipse(radius, radius) {}
	~circle() {}
	string info() { return "circle"; }
};


//derived class for a 3D shape
class threeD_shape : public shape {
public:
	virtual string info() = 0;
	virtual double area() = 0;
	virtual double volume() = 0;
	virtual ~threeD_shape() {}//destructor
};

class cuboid : public threeD_shape {	//cuboid class
protected:
	double length, width, depth;	//declare attributes
public:
	cuboid() : length{ 0 }, width{ 0 }, depth{ 0 } {}
	cuboid(double l, double w, double d) : length{ l }, width{ w }, depth{ d } {}
	~cuboid() {}

	double volume() { return length * width * depth; }
	double area() { return 2 * ((length * width) + (length * depth) + (width * depth)); }
	string info() { return "cuboid"; }
};
	
class cube : public cuboid {			//cube class	(derived from cuboid)
public:
	cube() : cuboid() {}
	cube(double size) : cuboid(size, size, size) {}
	~cube() {}
	string info() { return "cube"; }
};
	
class ellipsoid : public threeD_shape {//ellipsoid class
protected:
	double a, b, c;
public:
	ellipsoid() :a{ 0 }, b{ 0 }, c{ 0 } {}
	ellipsoid(double d1, double d2, double d3) : a{ d1 }, b{ d2 }, c{ d3 } {}
	~ellipsoid() {}

	double volume() { return (4 / 3)*pi*a*b*c; }
	double area() { return 4 * pi*pow((pow(a*b, 1.6) + pow(a*c, 1.6) + pow(b*c, 1.6)) / 3, 1 / 1.6); }
	string info() { return "ellipsoid"; }
};

class sphere : public ellipsoid {//sphere class	(derived from ellipsoid)
public:
	sphere() : ellipsoid() {}
	sphere(double radius) : ellipsoid(radius, radius, radius) {}
	~sphere() {}
	string info() { return "sphere"; }
};

class prism : public threeD_shape {		//class for prism
private:
	double base_area, depth;	
	string base_type;

public:
	prism() : base_area{ 0 }, depth{ 0 } {}		//constructor takes a twoD shape base pointer as a parameter
	prism(twoD_shape *base, double d) : base_area{ base->area() }, depth{ d } { base_type = base->info(); delete base; }// MUST BE VERY CAREFUL HERE, THE 2D SHAPE IS DELETED AFTER PRISM CONSTRUCTION!!!
	~prism() {}

	double volume() { return base_area * depth; }		
	double area() {cerr << "Error: cannot calculate surface area for 3D shape of class prism" << endl; return 0; }
	string info() { return "prism (" + base_type + " base)"; }		//provides info on this class and the base class
};


int main()
{
	//create a vector of base class pointers
	vector <shape*>	shape_vector;
	//add rectangle, square, ellipse, circle, cuboid, cube, ellipsoid, sphere, prism
	shape_vector.push_back(new rectangle(2, 3));
	shape_vector.push_back(new square(3));
	shape_vector.push_back(new ellipse(2, 3));
	shape_vector.push_back(new circle(3));
	shape_vector.push_back(new cuboid(2, 3, 4));
	shape_vector.push_back(new cube(3));
	shape_vector.push_back(new ellipsoid(2, 3, 4));
	shape_vector.push_back(new sphere(3));
	shape_vector.push_back(new prism(new circle(4), 3));

	cout << "vector size: " << shape_vector.size() << endl;								//display information about each shape (type, area, volume)
	for (auto iterator = shape_vector.begin(); iterator != shape_vector.end(); ++iterator) {
		cout << "shape information:" << endl;
		cout << "type: " << (*iterator)->info() << endl;
		cout << "area: " << (*iterator) -> area() << endl;
		cout << "volume: " << (*iterator) -> volume() << endl;
		cout << endl;
		delete *iterator;		//clean up the memory
	}
	shape_vector.clear();

    return 0;
}

