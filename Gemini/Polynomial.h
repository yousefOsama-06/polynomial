#ifndef PolynomialGemini_H3
#define PolynomialGemini_H3

#include <iostream>
#include <vector>

using namespace std;


class PolynomialGemini {
private:
    vector<double> coeffs; // Store coefficients of the PolynomialGemini

public:
    // Constructors
    PolynomialGemini(); // Default constructor
    PolynomialGemini(const vector<double>& coefficients); // Constructor with coefficients
    PolynomialGemini(const PolynomialGemini& other); // Copy constructor

    // Destructor
    ~PolynomialGemini(); // Destructor

    // Assignment operator
    PolynomialGemini& operator=(const PolynomialGemini& other);

    // Arithmetic operators
    PolynomialGemini operator+(const PolynomialGemini& other) const; // Addition
    PolynomialGemini operator-(const PolynomialGemini& other) const; // Subtraction
    PolynomialGemini operator*(const PolynomialGemini& other) const; // Multiplication

    // Equality operator
    bool operator==(const PolynomialGemini& other) const; // Equality check

    // Output operator
    friend ostream& operator<<(ostream& out, const PolynomialGemini& poly);

    // Utility functions
    int degree() const; // Return the degree of the PolynomialGemini
    double evaluate(double x) const; // Evaluate the PolynomialGemini at x
    PolynomialGemini compose(const PolynomialGemini& q) const; // Composition
    PolynomialGemini derivative() const; // Derivative of the PolynomialGemini
    PolynomialGemini integral() const; // Return a PolynomialGemini of integration
    double integral(double x1, double x2) const; // Integrate from x1 to x2
    double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100); // Find root

    // Set coefficients
    void setCoefficients(const vector<double>& coefficients); // Set coefficients
    double getCoefficient(int degree) const; // Get coefficient of a specific degree
};

#endif // PolynomialGemini_H
