#ifndef PolynomialGPT_H2
#define PolynomialGPT_H2

#include <iostream>
#include <vector>

using namespace std;

class PolynomialGPT {
private:
    vector<double> coeffs; // Store coefficients of the PolynomialGPT

public:
    // Constructors
    PolynomialGPT(); // Default constructor
    PolynomialGPT(const vector<double>& coefficients); // Constructor with coefficients
    PolynomialGPT(const PolynomialGPT& other); // Copy constructor

    // Destructor
    ~PolynomialGPT(); // Destructor

    // Assignment operator
    PolynomialGPT& operator=(const PolynomialGPT& other);

    // Arithmetic operators
    PolynomialGPT operator+(const PolynomialGPT& other) const; // Addition
    PolynomialGPT operator-(const PolynomialGPT& other) const; // Subtraction
    PolynomialGPT operator*(const PolynomialGPT& other) const; // Multiplication

    // Equality operator
    bool operator==(const PolynomialGPT& other) const; // Equality check

    // Output operator
    friend ostream& operator<<(ostream& out, const PolynomialGPT& poly);

    // Utility functions
    int degree() const; // Return the degree of the PolynomialGPT
    double evaluate(double x) const; // Evaluate the PolynomialGPT at x
    PolynomialGPT compose(const PolynomialGPT& q) const; // Composition
    PolynomialGPT derivative() const; // Derivative of the PolynomialGPT
    PolynomialGPT integral() const; // Return a PolynomialGPT of integration
    double integral(double x1, double x2) const; // Integrate from x1 to x2
    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100); // Find root

    // Set coefficients
    void setCoefficients(const vector<double>& coefficients); // Set coefficients
    double getCoefficient(int degree) const; // Get coefficient of a specific degree



    PolynomialGPT rev() const; // Derivative of the PolynomialGPT
};

#endif // PolynomialGPT_H
