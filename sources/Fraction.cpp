#include "Fraction.hpp"
#include <cstdlib>
#include <limits.h>
using namespace ariel;
using namespace std;

// constructors
Fraction::Fraction (int num, int den) {
    if (den == 0) {
        throw invalid_argument("denominator cannot be zero");
    }
    if (num < 0 && den < 0) {
        num = abs(num);
        den = abs(den);
    }
    else if (den < 0 && num > 0) {
        den = abs(den);
        num = -num;
    }
    if (num == 0) {
        den = 1;
    }
    int gcd1 = gcd(num, den);
    this->num = num / gcd1;
    this->den = den / gcd1;
}

Fraction::Fraction (float num) {
    int numFl = 1000 * num; // for acurrate of 3 numbers after the point
    int denFl = 1000;
    int gcdFl = gcd(numFl, denFl);
    Fraction frt((numFl / gcdFl), (denFl / gcdFl));
    this->num = frt.getNumerator();
    this->den = frt.getDenominator();
}

Fraction::Fraction () : num(0), den(1) {
    
}

// append operators
Fraction Fraction::operator+ (const Fraction& app) const {
    checkOverFlowMul(this->getNumerator(), app.getDenominator());
    checkOverFlowMul(app.getNumerator(), this->getDenominator());
    checkOverFlowMul(this->getDenominator(), app.getDenominator());
    checkOverFlowApp(this->getNumerator() * app.getDenominator(), app.getNumerator() * this->getDenominator());
    int num1 = (this->getNumerator() * app.getDenominator()) + (app.getNumerator() * this->getDenominator());
    int den1 = this->getDenominator() * app.getDenominator();
    return Fraction(num1, den1);
}

Fraction Fraction::operator+ (const float app) const {
    Fraction floatFra(app);
    return *this + floatFra;
}

Fraction ariel::operator+ (const float app1, const Fraction& app2) {
    Fraction floatFra(app1);
    return floatFra + app2;
} 

// sub operators
Fraction Fraction::operator- (const Fraction& sub) const {
    checkOverFlowMul(this->getNumerator(), sub.getDenominator());
    checkOverFlowMul(sub.getNumerator(), this->getDenominator());
    checkOverFlowMul(this->getDenominator(), this->getDenominator());
    checkOverFlowSub(this->getNumerator() * sub.getDenominator(), this->getDenominator() * sub.getNumerator());
    int num1 = (this->getNumerator() * sub.getDenominator()) - (this->getDenominator() * sub.getNumerator());
    int den1 = this->getDenominator() * sub.getDenominator();
    return Fraction(num1, den1);
}

Fraction Fraction::operator- (const float sub) const {
    Fraction floatFra(sub);
    return *this - floatFra;
}

Fraction ariel::operator- (const float sub1, const Fraction& sub2) {
    Fraction floatFra(sub1);
    return floatFra - sub2;
}

// multiply operators
Fraction Fraction::operator* (const Fraction& mul) const {
    checkOverFlowMul(this->getNumerator(), mul.getNumerator());
    checkOverFlowMul(this->getDenominator(), mul.getDenominator());
    int num1 = this->getNumerator() * mul.getNumerator();
    int den1 = this->getDenominator() * mul.getDenominator();
    return Fraction(num1, den1);
}

Fraction Fraction::operator* (const float mul) const {
    Fraction floatFra(mul);
    return *this * floatFra;
}

Fraction ariel::operator* (const float mul1, const Fraction& mul2) {
    Fraction floatFra(mul1);
    return floatFra * mul2;
}   

// divide operators
Fraction Fraction::operator/ (const Fraction& div) const {
    if (div.getNumerator() == 0) {
        throw runtime_error("cannot divide by zero");
    }
    checkOverFlowMul(this->getNumerator(), div.getDenominator());
    checkOverFlowMul(this->getDenominator(), div.getNumerator());
    int num1 = this->getNumerator() * div.getDenominator();
    int den1 = this->getDenominator() * div.getNumerator();
    return Fraction(num1, den1);
}

Fraction Fraction::operator/ (const float div) const {
    if (div == 0) {
        throw runtime_error("cannot divide by zero");
    }
    Fraction floatFra(div);
    return *this / floatFra;
}

Fraction ariel::operator/ (const float div1, const Fraction& div2) {
    if (div2.getNumerator() == 0) {
        throw runtime_error("cannot divide by zero");
    }
    Fraction floatFra(div1);
    return floatFra / div2;
}

// postfix and prefix
Fraction& Fraction::operator++ () {
    int toSet = this->getNumerator() + this->getDenominator();
    this->setNumerator(toSet);
    return *this;
}
Fraction Fraction::operator++ (int) {
    Fraction copy(this->getNumerator(), this->getDenominator());
    int toSet = this->getNumerator() + this->getDenominator();
    this->setNumerator(toSet);
    return copy; 
}

Fraction& Fraction::operator-- (){
    int toSet = this->getNumerator() - this->getDenominator();
    this->setNumerator(toSet);
    return *this;
}
Fraction Fraction::operator-- (int) {
    Fraction copy(this->getNumerator(), this->getDenominator());
    int toSet = this->getNumerator() - this->getDenominator();
    this->setNumerator(toSet);
    return copy;
}

// boolian operators
bool Fraction::operator== (const Fraction& other) const {
    Fraction temp1(this->getNumerator(), this->getDenominator());
    Fraction temp2(other.getNumerator(), other.getDenominator());
    if (temp1.getNumerator() == temp2.getNumerator() && temp1.getDenominator() == temp2.getDenominator()) {
        return true;
    }
    return false;
}

bool Fraction::operator== (const float other) const {
    Fraction temp1(this->getNumerator(), this->getDenominator());
    Fraction floatFra(other);
    return temp1 == floatFra;
}

bool ariel::operator== (const float other, const Fraction& fra) {
    Fraction floatFra(other);
    Fraction temp1(fra.getNumerator(), fra.getDenominator());
    return temp1 == floatFra;
}

bool Fraction::operator!= (const Fraction& other) const {
    Fraction temp1(this->getNumerator(), this->getDenominator());
    Fraction temp2(other.getNumerator(), other.getDenominator());
    if (temp1.getNumerator() != temp2.getNumerator() || temp1.getDenominator() != temp2.getDenominator()) {
        return true;
    }
    return false;
}

bool Fraction::operator!= (const float other) const {
    Fraction temp1(this->getNumerator(), this->getDenominator());
    Fraction floatFra(other);
    return temp1 != floatFra;
}

bool ariel::operator!= (const float other, const Fraction& fra) {
    Fraction temp1(fra.getNumerator(), fra.getDenominator());
    Fraction floatFra(other);
    return temp1 != floatFra;
}

bool Fraction::operator>= (const Fraction& other) const {
    int temp1 = this->getNumerator() * other.getDenominator();
    int temp2 = other.getNumerator() * this->getDenominator();
    return temp1 >= temp2;  
}

bool Fraction::operator>= (const float other) const {
    Fraction temp1(other);
    Fraction temp2(this->getNumerator(), this->getDenominator());
    return temp2 >= temp1; 
}

bool ariel::operator>= (const float other, const Fraction& fra) {
    Fraction floatFra(other);
    return floatFra >= fra;
}

bool Fraction::operator<= (const Fraction& other) const {
    int fraThis = this->getNumerator() * other.getDenominator();
    int fraOther = other.getNumerator() * this->getDenominator();
    return fraThis <= fraOther;
}

bool Fraction::operator<= (const float other) const {
    Fraction temp1(other);
    Fraction temp2(this->getNumerator(), this->getDenominator());
    return temp2 <= temp1;
}

bool ariel::operator<= (const float other, const Fraction& fra) {
    Fraction floatFra(other);
    return floatFra <= fra;
}

bool Fraction::operator< (const Fraction& other) const {
    int fraThis = this->getNumerator() * other.getDenominator();
    int fraOther = other.getNumerator() * this->getDenominator();
    return fraThis < fraOther;
}

bool Fraction::operator< (const float other) const {
    Fraction temp1(other);
    Fraction temp2(this->getNumerator(), this->getDenominator());
    return temp2 < temp1;
}

bool ariel::operator< (const float other, const Fraction& fra) {
    Fraction temp(other);
    return temp < fra;
}

bool Fraction::operator> (const Fraction& other) const {
    int fraThis = this->getNumerator() * other.getDenominator();
    int fraOther = other.getNumerator() * this->getDenominator();
    return fraThis > fraOther;
}

bool Fraction::operator> (const float other) const {
    Fraction temp1(other);
    Fraction temp2(this->getNumerator(), this->getDenominator());
    return temp2 > temp1;
}

bool ariel::operator> (const float other, const Fraction& fra) {
    Fraction temp(other);
    return temp > fra;
}

// stout and stdin operators
std::istream& ariel::operator>> (std::istream& input, Fraction& frac) { 
    int num, den;
    input >> num >> den;
    
    if (input.fail()) {
        throw runtime_error("illegle format, the format is integer whitespace integer");
    }
    if (den == 0) {
        throw runtime_error("denominator cannot be zero");
    }
    frac = Fraction(num, den);
    return input;
}


std::ostream& ariel::operator<< (std::ostream& output, const Fraction& frt) {
return (output << frt.getNumerator() << "/" << frt.getDenominator());
}

// gcd function by euclidean algorithm
int Fraction::gcd (int one, int two) const {
    one = abs(one);
    two = abs(two);
    if (two == 0) {
        return one;
    }
    else {
        return gcd(two, one % two);
    }
}

void Fraction::checkOverFlowApp(int num1, int num2) const {
    if (((num1 > 0) && num2 > INT_MAX - num1) || ((num1 < 0) && (num2 < INT_MIN - num1))) {
        throw overflow_error("the append of that two fraction leading to overflow");
    }
}

void Fraction::checkOverFlowSub(int num1, int num2) const {
    if (((num2 < 0) && (num1 > INT_MAX + num2)) || ((num2 > 0) && (num1 < INT_MIN + num2))) {
        throw overflow_error("the sub of that two fraction leading to overflow");
    }
}

void Fraction::checkOverFlowMul(int num1, int num2) const {
    if ((num1 > 0 && num2 > INT_MAX / num1) || (num1 < 0 && num2 < INT_MAX / num1)) {
        throw overflow_error("the multiply of that two fraction leading to overflow");
    }
}