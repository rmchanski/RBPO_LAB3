
#include <math.h>
#include <iostream>
export module Math;
export class Complex
{
	double m_re;
	double m_im;
public:
	Complex() { //конструктор по умолчанию
		m_re = m_im = 0.0;
	}
	Complex(double re) {//конструктор преобразования
		m_re = re; m_im = 0.0;
	}
	Complex(double re, double im) {//конструктор инициализации
		m_re = re; m_im = im;
	}
	static Complex FromExponentialForm(double module, double arg) {
		Complex a;
		a.m_re = module * cos(arg);
		a.m_im = module * sin(arg);
		return a;
	}
	static Complex FromAlgebraicForm(double real, double imag) {
		Complex a{ real, imag };
		return a;
	}
	double Re() const {
		return m_re;
	}
	double Im() const {
		return m_im;
	}
	double Mod() const {
		return sqrt(m_re * m_re + m_im * m_im);
	}
	double Arg() const {
		return atan2(m_im, m_re);
	}

	explicit operator double() const {
		return m_re;
	}
	Complex operator- () {
		Complex num{ *this };
		num.m_im *= -1;
		num.m_re *= -1;
		return num;
	}
	Complex& operator++ () {
		m_re++;
		return *this;
	}
	Complex operator++ (int) {
		Complex temp(*this);
		++(*this);
		return temp;
	}
	Complex& operator-- () {
		m_re--;
		return *this;
	}
	Complex operator-- (int) {
		Complex temp(*this);
		--(*this);
		return temp;
	}
	Complex& operator+=(Complex num) {
		m_re += num.m_re;
		m_im += num.m_im;
		return *this;
	}
	Complex& operator-=(Complex num) {
		m_re -= num.m_re;
		m_im -= num.m_im;
		return *this;
	}
	Complex& operator*=(Complex num) {
		double real = m_re;
		double im = m_im;
		m_re = real * num.m_re - im * num.m_im;
		m_im = real * num.m_im + im * num.m_re;
		return *this;
	}
	Complex& operator/=(Complex num) {
		double divider = num.m_re * num.m_re + num.m_im * num.m_im;
		double re = (m_re * num.m_re + m_im * num.m_im) / divider;
		double im = (num.m_re * m_im - m_re * num.m_im) / divider;
		m_re = re;
		m_im = im;

		return *this;
	}

	friend Complex operator+ (const Complex& lhs, const Complex& rhs);
	friend Complex operator- (const Complex& lhs, const Complex& rhs);
	friend Complex operator* (const Complex& lhs, const Complex& rhs);
	friend Complex operator/ (const Complex& lhs, const Complex& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const Complex& instance);
	friend Complex operator ""i(long double im);
	friend Complex operator ""i(unsigned long long im);
};
export Complex operator+(const Complex& lhs, const Complex& rhs)
{
	return Complex(lhs.m_re + rhs.m_re, lhs.m_im + rhs.m_im);
}

export Complex operator-(const Complex& lhs, const Complex& rhs)
{
	return Complex(lhs.m_re - rhs.m_re, lhs.m_im - rhs.m_im);
}

export Complex operator*(const Complex& lhs, const Complex& rhs)
{
	double real = lhs.m_re * rhs.m_re - lhs.m_im * rhs.m_im;
	double im = lhs.m_re * rhs.m_im + lhs.m_im * rhs.m_re;
	return Complex(real, im);
}

export Complex operator/(const Complex& lhs, const Complex& rhs)
{

	double divider = rhs.m_re * rhs.m_re + rhs.m_im * rhs.m_im;
	double real = (lhs.m_re * rhs.m_re + lhs.m_im * rhs.m_im) / divider;
	double imag = (rhs.m_re * lhs.m_im - lhs.m_re * rhs.m_im) / divider;
	return Complex(real, imag);
}

export Complex operator ""i(unsigned long long im) {
	return Complex(0.0, static_cast<double>(im));
}
export Complex operator ""i(long double im) {
	return Complex(0.0, static_cast<double>(im));
}
export std::ostream& operator<<(std::ostream& stream, const Complex& instance) {
	if (instance.m_im < 0) {
		stream << instance.m_re << " " << instance.m_im << "i";
	}
	else {
		stream << instance.m_re << " +" << instance.m_im << "i";
	}
	return stream;
}

export int FindGreatestCommonDivisor(int a, int b) {
	a = abs(a);
	b = abs(b);
	if (b > a) {
		int temp = b;
		b = a;
		a = temp;
	}
	if (b == 0) { return a; }

	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

export int FindLeastCommonMultiple(int a, int b) {
	return abs(a * b) / FindGreatestCommonDivisor(a, b);
}

export class Rational {
	int m_nominator;
	int m_denominator;
	void reduction() {//функция для сокращения дробей

		if (m_denominator < 0) {
			m_denominator *= -1;
			m_nominator *= -1;
		}

		int nod = FindGreatestCommonDivisor(m_nominator, m_denominator);
		m_nominator /= nod;
		m_denominator /= nod;
	}
public:
	Rational() {
		m_nominator = 0;
		m_denominator = 1;
	}
	Rational(int nominator, int denominator) {
		m_denominator = denominator;
		m_nominator = nominator;
		reduction();
	}
	Rational(int nominator) {
		m_nominator = nominator;
		m_denominator = 1;
	}
	int Nominator() const {
		return m_nominator;
	}
	int Denominator() const {
		return m_denominator;
	}
	explicit operator double() const {
		return double(m_nominator) / m_denominator;
	}
	Rational operator-() {
		Rational temp(*this);
		temp.m_nominator *= -1;
		return temp;
	}
	Rational& operator++ () {
		m_nominator += m_denominator;
		return *this;
	}
	Rational operator++ (int) {
		Rational temp(*this);
		(*this).m_nominator += m_denominator;
		temp.reduction();
		return temp;
	}
	Rational& operator-- () {
		m_nominator -= m_denominator;
		reduction();
		return *this;
	}
	Rational operator-- (int) {
		Rational temp(*this);
		(*this).m_nominator -= m_denominator;
		return temp;
	}
	Rational& operator+=(Rational num) {
		int a = FindLeastCommonMultiple(m_denominator, num.m_denominator);
		m_nominator = a * m_nominator / m_denominator;
		m_nominator += a * num.m_nominator / num.m_denominator;
		m_denominator = a;
		reduction();
		return *this;
	}
	Rational& operator-=(Rational num) {
		int a = FindGreatestCommonDivisor(m_denominator, num.m_denominator);
		m_nominator = a / m_denominator * m_nominator;
		m_nominator -= a / num.m_denominator * num.m_nominator;
		m_denominator = a;
		reduction();
		return *this;
	}
	Rational& operator*=(Rational num) {
		m_denominator *= num.m_denominator;
		m_nominator *= num.m_nominator;
		reduction();
		return *this;
	}
	Rational& operator/=(Rational num) {
		m_denominator *= num.m_nominator;
		m_nominator *= num.m_denominator;
		reduction();
		return *this;
	}
	friend Rational operator+ (const Rational& lhs, const Rational& rhs);
	friend Rational operator- (const Rational& lhs, const Rational& rhs);
	friend Rational operator* (const Rational& lhs, const Rational& rhs);
	friend Rational operator/(const Rational& lhs, const Rational& rhs);
	friend bool operator==(const Rational& lhs, const Rational& rhs);
	friend bool operator>(const Rational& lhs, const Rational& rhs);
	friend bool operator<(const Rational& lhs, const Rational& rhs);
	friend bool operator>=(const Rational& lhs, const Rational& rhs);
	friend bool operator<=(const Rational& lhs, const Rational& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const Rational& instance);
};

export Rational operator+ (const Rational& lhs, const Rational& rhs) {
	int denominator = lhs.m_denominator * rhs.m_denominator;
	int nominator = lhs.m_nominator * rhs.m_denominator + rhs.m_nominator * lhs.m_denominator;
	return Rational(nominator, denominator);
}

export Rational operator-(const Rational& lhs, const Rational& rhs)
{
	int denominator = lhs.m_denominator * rhs.m_denominator;
	int nominator = lhs.m_nominator * rhs.m_denominator - rhs.m_nominator * lhs.m_denominator;
	return Rational(nominator, denominator);
}

export Rational operator*(const Rational& lhs, const Rational& rhs)
{
	int nominator = lhs.m_nominator * rhs.m_nominator;
	int denominator = rhs.m_denominator * lhs.m_denominator;
	return Rational(nominator, denominator);
}

export Rational operator/(const Rational& lhs, const Rational& rhs)
{
	int nominator = lhs.m_nominator * rhs.m_denominator;
	int denominator = lhs.m_denominator * rhs.m_nominator;
	return Rational(nominator, denominator);
}

export bool operator==(const Rational& lhs, const Rational& rhs)
{
	return lhs.m_nominator == rhs.m_nominator && lhs.m_denominator == rhs.m_denominator;
}

export bool operator>(const Rational& lhs, const Rational& rhs)
{
	int nominator_1 = lhs.m_nominator * rhs.m_denominator;
	int nominator_2 = rhs.m_nominator * lhs.m_denominator;
	return nominator_1 > nominator_2;
}

export bool operator<(const Rational& lhs, const Rational& rhs)
{
	int nominator_1 = lhs.m_nominator * rhs.m_denominator;
	int nominator_2 = rhs.m_nominator * lhs.m_denominator;
	return nominator_1 < nominator_2;
}

export bool operator>=(const Rational& lhs, const Rational& rhs)
{
	int nominator_1 = lhs.m_nominator * rhs.m_denominator;
	int nominator_2 = rhs.m_nominator * lhs.m_denominator;
	return nominator_1 >= nominator_2;
}

export bool operator<=(const Rational& lhs, const Rational& rhs)
{
	int nominator_1 = lhs.m_nominator * rhs.m_denominator;
	int nominator_2 = rhs.m_nominator * lhs.m_denominator;
	return nominator_1 <= nominator_2;
}

export std::ostream& operator<<(std::ostream& stream, const Rational& instance) {
	stream << instance.m_nominator << "/" << instance.m_denominator;
	return stream;
}

export Complex f(const Complex& z) {
	Complex a = 5i; 
	return (z / 3) - 1 / (a + z);
}

export Rational f(const Rational& r) {
	Rational a = 1 / 5;
	return (r / 3) - 1 / (a + r);
}

export double f(double x) {
	int a = 0.2;
	double result = (x / 3) - 1 / (a + x);
	return result;
}


