/*	C++ class to store complex numbers, z = x=iy
	Data for each object contains two doubles to represent x and y
	member functions:
		-return real part - done
		-return imaginary part - done
		-return modulus - done
		-return argument - done
		-return complex conjugate - done
		-overloaded + and - operators for complex addition and subtraction - done
		-overloaded * and / operators perform multiplication and division - done

	non-member friend functions:
		-allow insertion of complex objects into an ostream - done
		-allow extraction of complex objects from an istream - done
*/

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;
//complex number class
class complex_num {
private:
	double Re, Im;		//data to store real and imaginary parts

public:

	//constructor and destructor member functions
	complex_num() { Re = Im = 0; }
	complex_num(double Rein, double Imin) { Re = Rein; Im = Imin; }
	~complex_num() { cout << "Called destructor" << endl; }

	//get function
	double getRe()const { return Re; }
	double getIm()const { return Im; }

	//set functions
	void setRe(double Rein) { Re = Rein; }
	void setIm(double Imin) { Im = Imin; }

	//modulus function
	double mod()const { return sqrt(pow(Re, 2) + pow(Im, 2)); }

	//argument function
	double arg()const { return atan2(Im, Re); }

	//complex conjugate function
	complex_num complex_conjugate()const {complex_num temp(Re, Im*-1);return temp;}

	//overloaded + operator
	complex_num operator+(const complex_num &num)const {
		complex_num temp(Re + num.Re, Im + num.Im);
		return temp;
	}
	//overloaded - operator
	complex_num operator-(const complex_num &num)const {
		complex_num temp(Re - num.Re, Im - num.Im);
		return temp;
	}
	//overloaded * operator
	complex_num operator *(const complex_num &num)const{
		complex_num temp(Re*num.Re - Im * num.Im, Im*num.Re + Re * num.Im);
		return temp;
	}
	//overloaded / operator
	complex_num operator/(const complex_num &num)const {
		double real{ (Re*num.Re + Im * num.Im) / (pow(num.Re, 2) + pow(num.Im, 2)) };
		double imaginary{ (Im*num.Re - Re * num.Im) / (pow(num.Re, 2) + pow(num.Im, 2)) };
		complex_num temp(real, imaginary);
		return temp;
	}

	friend ostream &operator <<(ostream &os, const complex_num &num);		//draft friend functions for iostream
	friend istream &operator >>(istream &is, complex_num &num);
};

ostream &operator <<(ostream &os, const complex_num &num)
 {
	
	if (num.Im >= 0) {
		os << num.Re<<"+"<<num.Im<<"i";
	}
	else {
		os << num.Re << num.Im << "i";
	}
	return os;
}

istream &operator >>(istream &is, complex_num &num) {
	is >> num.Re >> num.Im;
	return is;
}


int main()	//main program gets two user input complex numbers and then demonstrates all methods of the complex number class
{
	bool done{ false };

	while (!done) {
		complex_num a;		//two complex numbers
		complex_num b;
		cout << "Welcome to the complex number calculator" << endl;
		cout << "enter first complex number:" << endl;
		cin >> a;
		cin.clear();
		cin.ignore(INT_MAX,'\n');
		cout << "a = " << a<<endl;
		cout << "|a| = " << a.mod() << endl;
		cout << "arg(a) " << a.arg() << endl;
		cout << "a* = " << a.complex_conjugate() << endl;
		cout << endl;
		cout << "enter second complex number:" << endl;
		cin >> b;
		cin.clear();
		cin.ignore(256, '\n');
		cout << "b = " << b << endl;
		cout << "|b| = " << b.mod() << endl;
		cout << "arg(b) " << b.arg() << endl;
		cout << "b* = " << b.complex_conjugate() << endl;
		cout << endl;
		cout << "a + b = " << a + b << endl;
		cout << "a - b = " << a - b << endl;
		cout << "a * b = " << a * b << endl;
		cout << "a / b = " << a / b << endl;

		string response;
		cout << "Again? (y/n)" << endl;
		getline(cin,response);
		cout << response << endl;
		if (response == "n") { done = true; }
	}
    return 0;
}

