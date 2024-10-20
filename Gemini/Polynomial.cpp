#include "Polynomial.h"

// Default constructor
PolynomialGemini::PolynomialGemini() {
    coeffs = {0};
}

// Constructor with coefficients
PolynomialGemini::PolynomialGemini(const vector<double> &coefficients) {
    coeffs = coefficients;
}

// Copy constructor
PolynomialGemini::PolynomialGemini(const PolynomialGemini &other) {
    coeffs = other.coeffs;
}

// Destructor
PolynomialGemini::~PolynomialGemini() {
}

// Assignment operator
PolynomialGemini &PolynomialGemini::operator=(const PolynomialGemini &other) {
    coeffs = other.coeffs;
    return *this;
}

// Addition
PolynomialGemini PolynomialGemini::operator+(const PolynomialGemini &other) const {
    int maxDegree = max(degree(), other.degree());
    vector<double> result(maxDegree + 1, 0);

    for (int i = 0; i <= degree(); ++i) {
        result[i] += coeffs[i];
    }

    for (int i = 0; i <= other.degree(); ++i) {
        result[i] += other.coeffs[i];
    }

    return PolynomialGemini(result);
}

// Subtraction
PolynomialGemini PolynomialGemini::operator-(const PolynomialGemini &other) const {
    int maxDegree = max(degree(), other.degree());
    vector<double> result(maxDegree + 1, 0);

    for (int i = 0; i <= degree(); ++i) {
        result[i] += coeffs[i];
    }

    for (int i = 0; i <= other.degree(); ++i) {
        result[i] -= other.coeffs[i];
    }

    return PolynomialGemini(result);
}

// Multiplication
PolynomialGemini PolynomialGemini::operator*(const PolynomialGemini &other) const {
    int maxDegree = degree() + other.degree();
    vector<double> result(maxDegree + 1, 0);

    for (int i = 0; i <= degree(); ++i) {
        for (int j = 0; j <= other.degree(); ++j) {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }

    return PolynomialGemini(result);
}

// Equality operator
bool PolynomialGemini::operator==(const PolynomialGemini &other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream &operator<<(ostream &out, const PolynomialGemini &poly) {
    bool firstTerm = true;
    for (int i = poly.degree(); i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (!firstTerm) {
                if (poly.coeffs[i] > 0) {
                    out << " + ";
                } else {
                    out << " - ";
                }
            }
            firstTerm = false;

            if (i == 0) {
                out << abs(poly.coeffs[i]);
            } else if (i == 1) {
                out << abs(poly.coeffs[i]) << "x";
            } else {
                out << abs(poly.coeffs[i]) << "x^" << i;
            }
        }
    }

    if (firstTerm) {
        out << 0;
    }

    return out;
}

// Utility functions

// Return the degree of the PolynomialGemini
int PolynomialGemini::degree() const {
    int deg = coeffs.size() - 1;
    while (deg >= 0 && coeffs[deg] == 0) {
        --deg;
    }
    return deg;
}

// Evaluate the PolynomialGemini at x
double PolynomialGemini::evaluate(double x) const {
    double result = 0;
    for (int i = degree(); i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

// Composition
PolynomialGemini PolynomialGemini::compose(const PolynomialGemini &q) const {
    PolynomialGemini result;
    for (int i = degree(); i >= 0; --i) {
        PolynomialGemini term = PolynomialGemini({coeffs[i]});
        for (int j = 0; j < i; ++j) {
            term = term * q;
        }
        result = result + term;
    }
    return result;
}

// Derivative of the PolynomialGemini
PolynomialGemini PolynomialGemini::derivative() const {
    if (degree() == 0) {
        return PolynomialGemini();
    }

    vector<double> derivativeCoeffs(degree());
    for (int i = 1; i <= degree(); ++i) {
        derivativeCoeffs[i - 1] = coeffs[i] * i;
    }
    return PolynomialGemini(derivativeCoeffs);
}

// Return a PolynomialGemini of integration
PolynomialGemini PolynomialGemini::integral() const {
    vector<double> integralCoeffs(degree() + 2);
    integralCoeffs[0] = 0; // Constant term of integration
    for (int i = 0; i <= degree(); ++i) {
        integralCoeffs[i + 1] = coeffs[i] / (i + 1);
    }
    return PolynomialGemini(integralCoeffs);
}

// Integrate from x1 to x2
double PolynomialGemini::integral(double x1, double x2) const {
    PolynomialGemini integralPoly = integral();
    return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
}

// Find root using Newton-Raphson method
double PolynomialGemini::getRoot(double guess, double tolerance, int maxIter) {
    // Determine a good initial guess based on the PolynomialGemini's coefficients
    guess = 0.0;
    if (coeffs[degree()] > 0) {
        // If the leading coefficient is positive, try a negative guess
        guess = -1.0;
    } else {
        // If the leading coefficient is negative, try a positive guess
        guess = 1.0;
    }

    // Adjust the guess based on the signs of the coefficients
    for (int i = degree() - 1; i >= 0; --i) {
        if (coeffs[i] > 0) {
            guess = max(guess, -coeffs[i] / coeffs[degree()]);
        } else {
            guess = min(guess, -coeffs[i] / coeffs[degree()]);
        }
    }

    // Apply Newton-Raphson method for root-finding
    for (int i = 0; i < maxIter; ++i) {
        double f = evaluate(guess);
        double df = derivative().evaluate(guess);
        if (abs(df) < tolerance) {
            return guess;
        }
        guess -= f / df;
    }
    return guess; // If not converged, return the last guess
}

// Set coefficients
void PolynomialGemini::setCoefficients(const vector<double> &coefficients) {
    coeffs = coefficients;
}

// Get coefficient of a specific degree
double PolynomialGemini::getCoefficient(int degree) const {
    if (degree >= coeffs.size()) {
        return 0;
    }
    return coeffs[degree];
}