#ifndef POLYNOMIAL_H1
#define POLYNOMIAL_H1

#include <iostream>
#include <vector>

using namespace std;


class Polynomial {
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    Polynomial(); // Default constructor
    Polynomial(const vector<double> &coefficients); // Constructor with coefficients
    Polynomial(const Polynomial &other); // Copy constructor

    // Destructor
    ~Polynomial(); // Destructor

    // Assignment operator
    Polynomial &operator=(const Polynomial &other);

    // Arithmetic operators
    Polynomial operator+(const Polynomial &other) const; // Addition
    Polynomial operator-(const Polynomial &other) const; // Subtraction
    Polynomial operator*(const Polynomial &other) const; // Multiplication

    // Equality operator
    bool operator==(const Polynomial &other) const; // Equality check

    // Output operator
    friend ostream &operator<<(ostream &out, const Polynomial &poly);

    // Utility functions
    int degree() const; // Return the degree of the polynomial
    double evaluate(double x) const; // Evaluate the polynomial at x
    Polynomial compose(const Polynomial &q) const; // Composition
    Polynomial derivative() const; // Derivative of the polynomial
    Polynomial integral() const; // Return a polynomial of integration
    double integral(double x1, double x2) const; // Integrate from x1 to x2
    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100) const; // Find root

    // Set coefficients
    void setCoefficients(const vector<double> &coefficients); // Set coefficients
    double getCoefficient(int degree) const; // Get coefficient of a specific degree
};

#endif // POLYNOMIAL_H
