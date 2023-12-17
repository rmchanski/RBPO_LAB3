#include <iostream>

import Math;
using namespace std;
int main()
{
	int u = 4;
	Complex num1 = f((Complex)u);
	Rational num2 = f((Rational)u);
	double num3 = f(u);
	cout << "Complex = " <<  num1 << endl;
	cout << "Rational = " << num2 << endl;
	cout << "Double = " << num3 << endl;
	return 0;
}