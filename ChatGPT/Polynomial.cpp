#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <limits>

// Default constructor
PolynomialGPT::PolynomialGPT() : coeffs(1, 0.0) {}

// Constructor with coefficients
PolynomialGPT::PolynomialGPT(const vector<double> &coefficients) : coeffs(coefficients) {
    // Remove trailing zeros
    while (coeffs.size() > 1 && coeffs.back() == 0.0) {
        coeffs.pop_back();
    }
}

// Copy constructor
PolynomialGPT::PolynomialGPT(const PolynomialGPT &other) : coeffs(other.coeffs) {}

// Destructor
PolynomialGPT::~PolynomialGPT() {}

// Assignment operator
PolynomialGPT &PolynomialGPT::operator=(const PolynomialGPT &other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

// Arithmetic operators
PolynomialGPT PolynomialGPT::operator+(const PolynomialGPT &other) const {
    vector<double> resultCoeffs(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        resultCoeffs[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); ++i) {
        resultCoeffs[i] += other.coeffs[i];
    }
    return PolynomialGPT(resultCoeffs);
}

PolynomialGPT PolynomialGPT::operator-(const PolynomialGPT &other) const {
    vector<double> resultCoeffs(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        resultCoeffs[i] += coeffs[i];
    }
    for (size_t i = 0; i < other.coeffs.size(); ++i) {
        resultCoeffs[i] -= other.coeffs[i];
    }
    return PolynomialGPT(resultCoeffs);
}

PolynomialGPT PolynomialGPT::operator*(const PolynomialGPT &other) const {
    vector<double> resultCoeffs(coeffs.size() + other.coeffs.size() - 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            resultCoeffs[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return PolynomialGPT(resultCoeffs);
}

// Equality operator
bool PolynomialGPT::operator==(const PolynomialGPT &other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream &operator<<(ostream &out, const PolynomialGPT &poly) {
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0.0) {
            if (i < poly.coeffs.size() - 1) {
                out << (poly.coeffs[i] > 0 ? " + " : " - ");
            }
            out << abs(poly.coeffs[i]);
            if (i > 0) {
                out << "x";
                if (i > 1) {
                    out << "^" << i;
                }
            }
        }
    }
    return out;
}

// Utility functions
int PolynomialGPT::degree() const {
    return coeffs.size() - 1; // Return the degree of the PolynomialGPT
}

double PolynomialGPT::evaluate(double x) const {
    double result = 0.0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

PolynomialGPT PolynomialGPT::compose(const PolynomialGPT &q) const {
    PolynomialGPT result;
    for (int i = degree(); i >= 0; --i) {
        result = result * q + PolynomialGPT(vector<double>{coeffs[i]});
    }
    return result;
}

PolynomialGPT PolynomialGPT::derivative() const {
    if (degree() < 1) return PolynomialGPT(); // Return zero PolynomialGPT for constants
    vector<double> derivCoeffs(degree());
    for (int i = 1; i < coeffs.size(); ++i) {
        derivCoeffs[i - 1] = coeffs[i] * i;
    }
    return PolynomialGPT(derivCoeffs);
}

PolynomialGPT PolynomialGPT::integral() const {
    vector<double> intCoeffs(degree() + 2); // Degree increases by 1
    intCoeffs[0] = 0.0; // Constant of integration
    for (int i = 0; i < coeffs.size(); ++i) {
        intCoeffs[i + 1] = coeffs[i] / (i + 1);
    }
    return PolynomialGPT(intCoeffs);
}

double PolynomialGPT::integral(double x1, double x2) const {
    PolynomialGPT integralPoly = integral();
    return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
}

double PolynomialGPT::getRoot(double guess, double tolerance, int maxIter) {
    // Calculate an initial guess as the average of the coefficients
    double sum = 0.0;
    for (double coeff: coeffs) {
        sum += coeff;
    }
    guess = sum / coeffs.size(); // Simple average of coefficients

    for (int i = 0; i < maxIter; ++i) {
        double fValue = evaluate(guess);
        double fPrimeValue = derivative().evaluate(guess);

        if (fabs(fPrimeValue) < tolerance) {
            return guess;
            throw std::runtime_error("Derivative is too close to zero. No solution found.");
        }

        double nextGuess = guess - fValue / fPrimeValue;

        if (fabs(nextGuess - guess) < tolerance) {
            return nextGuess; // Converged
        }

        guess = nextGuess; // Update guess for next iteration
    }

    return guess;
    throw std::runtime_error("Max iterations reached. No solution found.");
}

// Set coefficients
void PolynomialGPT::setCoefficients(const vector<double> &coefficients) {
    coeffs = coefficients;
    // Remove trailing zeros
    while (coeffs.size() > 1 && coeffs.back() == 0.0) {
        coeffs.pop_back();
    }
}

// Get coefficient of a specific degree
double PolynomialGPT::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) return 0.0;
    return coeffs[degree];
}
