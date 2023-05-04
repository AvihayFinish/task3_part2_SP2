#pragma once
#include<iostream>

namespace ariel {

    class Fraction { 

    private:

        int num;
        int den;

    public:

        Fraction (int num, int den); // ctor
        Fraction (float num); // ctor
        Fraction (); // ctor

        // append
        Fraction operator+ (const Fraction& app) const;
        Fraction operator+ (float app) const;
        friend Fraction operator+ (float app1, const Fraction& app2);

        // sub
        Fraction operator- (const Fraction& sub) const;
        Fraction operator- (float sub) const;
        friend Fraction operator- (float sub1, const Fraction& sub2);

        // mul
        Fraction operator* (const Fraction& mul) const;
        Fraction operator* (float mul) const;
        friend Fraction operator* (float mul1, const Fraction& mul2);

        // div
        Fraction operator/ (const Fraction& div) const;
        Fraction operator/ (float div) const;
        friend Fraction operator/ (float div1, const Fraction& div2);

        // postfix and prefix
        Fraction& operator++ ();
        Fraction operator++ (int);

        Fraction& operator-- ();
        Fraction operator-- (int);

        // bool operators
        bool operator== (const Fraction& other) const;
        bool operator== (float other) const;
        friend bool operator== (float other1, const Fraction& other2);

        bool operator!= (const Fraction& other) const;
        bool operator!= (float other) const;
        friend bool operator!= (float other1, const Fraction& other2);

        bool operator>= (const Fraction& other) const;
        bool operator>= (float other) const;
        friend bool operator>= (float other1, const Fraction& other2);

        bool operator<= (const Fraction& other) const;
        bool operator<= (float other) const;
        friend bool operator<= (float other1, const Fraction& other2);

        bool operator< (const Fraction& other) const;
        bool operator< (float other) const;
        friend bool operator< (float other1, const Fraction& other2);

        bool operator> (const Fraction& other) const;
        bool operator> (float other) const;
        friend bool operator> (float other1, const Fraction& other2);
        
        friend std::ostream& operator<< (std::ostream& output, const Fraction& frt);
        friend std::istream& operator>> (std::istream& input, Fraction& frt);

        // another functions
        int gcd (int one, int two) const;
        void checkOverFlowApp(int num1, int num2) const;
        void checkOverFlowSub(int num1, int num2) const;
        void checkOverFlowMul(int num1, int num2) const;
        int getNumerator () const {
            return this->num;
        }
        int getDenominator () const {
            return this->den;
        }
        void setNumerator (int num1) {
            this->num = num1;
        }
        void setDenominator (int num1) {
            if (num1 == 0) {
                throw std::invalid_argument("denominator cannot be zero");
            }
            this->den = num1;
        }
    };
}



