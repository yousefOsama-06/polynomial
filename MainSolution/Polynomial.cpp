#include "Polynomial.h"
#include "bits/stdc++.h"


Polynomial::Polynomial() {
    coeffs = {0};
}

Polynomial::Polynomial(const vector<double> &coefficients) {
    coeffs = coefficients;
}

Polynomial::Polynomial(const Polynomial &other) {
    coeffs = other.coeffs;
}

// Destructor
Polynomial::~Polynomial() = default;

// Assignment operator
Polynomial &Polynomial::operator=(const Polynomial &other) {
    coeffs = other.coeffs;
    return *this;
}

// Arithmetic operators
Polynomial Polynomial::operator+(const Polynomial &other) const {
    Polynomial ans = *this;
    while (ans.coeffs.size() < other.coeffs.size())
        ans.coeffs.push_back(0);
    for (int i = 0; i < other.coeffs.size(); i++)
        ans.coeffs[i] += other.coeffs[i];
    return ans;
}

Polynomial Polynomial::operator-(const Polynomial &other) const {
    Polynomial ans = *this;
    while (ans.coeffs.size() < other.coeffs.size())
        ans.coeffs.push_back(0);
    for (int i = 0; i < other.coeffs.size(); i++)
        ans.coeffs[i] -= other.coeffs[i];
    return ans;
}

Polynomial Polynomial::operator*(const Polynomial &other) const {
    Polynomial ans(vector<double>(coeffs.size() + other.coeffs.size() - 1, 0));
    for (int i = 0; i < coeffs.size(); i++)
        for (int j = 0; j < other.coeffs.size(); j++)
            ans.coeffs[i + j] += coeffs[i] * other.coeffs[j];
    return ans;
}

// Equality operator
bool Polynomial::operator==(const Polynomial &other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream &operator<<(ostream &out, const Polynomial &poly) {
    for (double i: poly.coeffs)
        out << i << ' ';
    return out;
}

// Utility functions
int Polynomial::degree() const {
    return int(coeffs.size()) - 1;
} // Return the degree of the polynomial
double Polynomial::evaluate(double x) const {
    double ans = 0;
    for (int i = 0; i < coeffs.size(); i++)
        ans += coeffs[i] * pow(x, i);
    return ans;
}; // Evaluate the polynomial at x
Polynomial Polynomial::compose(const Polynomial &q) const {
    Polynomial ans, powerOfQ({1.0});
    for (double coeff: coeffs) {
        ans = ans + powerOfQ * Polynomial({coeff});
        powerOfQ = powerOfQ * q;
    }
    return ans;
}; // Composition
Polynomial Polynomial::derivative() const {
    if (degree() == 0)
        return Polynomial();
    Polynomial ans(vector<double>(max(1, int(coeffs.size()) - 1), 0));
    for (int i = 0; i < ans.coeffs.size(); i++)
        ans.coeffs[i] = coeffs[i + 1] * (i + 1);
    return ans;
} // Derivative of the polynomial
Polynomial Polynomial::integral() const {
    Polynomial ans(vector<double>(coeffs.size() + 1, 0));
    for (int i = 1; i < ans.coeffs.size(); i++)
        ans.coeffs[i] = coeffs[i - 1] / i;
    return ans;
} // Return a polynomial of integration
double Polynomial::integral(double x1, double x2) const {
    return integral().evaluate(x2) - integral().evaluate(x1);
} // Integrate from x1 to x2
double Polynomial::getRoot(double guess, double tolerance, int maxIter) const {
    double x = guess;
    Polynomial deriv = derivative();
    for (int i = 0; i < maxIter; ++i) {
        double fx = evaluate(x);
        double fpx = deriv.evaluate(x);
        if (fabs(fx) < tolerance) {
            return x;
        }
        x = x - fx / fpx;
    }
    return x;
}

// Set coefficients
void Polynomial::setCoefficients(const vector<double> &coefficients) {
    coeffs = coefficients;
}

// Get coefficient of a specific degree
double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size())
        return 0;
    return coeffs[degree];
}
