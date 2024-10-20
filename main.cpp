#include "bits/stdc++.h"
#include "MainSolution/Polynomial.h"
#include "ChatGPT/Polynomial.h"
#include "Gemini/Polynomial.h"

const double eps = 1e-6;
int totalCnt, gptCnt, gemCnt;

bool near(double x, double y) {
    x = fabs(x), y = fabs(y);
    return fabs(x - y) <= max(x, y) * eps;
}

#define check(expected, AI, valid)\
        for (int i = 0; i <= AI.degree(); i++)\
            if (!near(expected.getCoefficient(i), AI.getCoefficient(i)))\
                gptValid = false;

using namespace std;

mt19937 _rnd(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
    return uniform_int_distribution<int>(l, r)(_rnd);
}

void testCase() {

    /*
     * Choices
     * 1. Add 2 polynomials
     * 2. Subtract 2 polynomials
     * 3. Multiply 2 polynomials
     * 4. Compose 2 polynomials
     * 5. Evaluate the polynomial at x
     * 6. Get the derivative
     * 7. Get the integral
     * 8. Get the definite integral
     * 9. Get the root
     */
    int q = random(1, 9);
    int n = random(1, 10);
    vector<double> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = random(1, 1000) / 100.0;
    }
    int m = random(1, 10);
    vector<double> b(m);
    for (int i = 0; i < m; i++) {
        b[i] = random(1, 1000) / 100.0;
    }
    double x = random(1, 1000) / 100.0, y = random(1, 10000) / 100.0;


    cout << n << '\n';
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';

    cout << '\n' << m << '\n';
    for (int i = 0; i < m; i++)
        cout << b[i] << ' ';

    cout << '\n' << q << '\n' << x << ' ' << y << "\n\n";

    bool gptValid = true, gemValid = true;
    if (q == 1) {
        auto expected = Polynomial(a) + Polynomial(b);
        auto gpt = PolynomialGPT(a) + PolynomialGPT(b);
        auto gem = PolynomialGemini(a) + PolynomialGemini(b);
        cout << "Expected: " << expected << '\n'
             << "Chat GPT: " << gpt << '\n'
             << "Gemini: " << gem << '\n';
        check(expected, gpt, gptValid);
        check(expected, gem, gemValid);

    } else if (q == 2) {
        auto expected = Polynomial(a) - Polynomial(b);
        auto gpt = PolynomialGPT(a) - PolynomialGPT(b);
        auto gem = PolynomialGemini(a) - PolynomialGemini(b);
        cout << "Expected: " << expected << '\n'
             << "Chat GPT: " << gpt << '\n'
             << "Gemini: " << gem << '\n';
        check(expected, gpt, gptValid);
        check(expected, gem, gemValid);
    } else if (q == 3) {
        auto expected = Polynomial(a) * Polynomial(b);
        auto gpt = PolynomialGPT(a) * PolynomialGPT(b);
        auto gem = PolynomialGemini(a) * PolynomialGemini(b);
        cout << "Expected: " << expected << '\n'
             << "Chat GPT: " << gpt << '\n'
             << "Gemini: " << gem << '\n';
        check(expected, gpt, gptValid);
        check(expected, gem, gemValid);
    } else if (q == 4) {
        auto expected = Polynomial(a).compose(Polynomial(b));
        auto gpt = PolynomialGPT(a).compose(PolynomialGPT(b));
        auto gem = PolynomialGemini(a).compose(PolynomialGemini(b));
        cout << "Expected: " << expected << '\n'
             << "Chat GPT: " << gpt << '\n'
             << "Gemini: " << gem << '\n';
        check(expected, gpt, gptValid);
        check(expected, gem, gemValid);
    } else if (q == 5) {
        auto expected = Polynomial(a).evaluate(x);
        auto gpt = PolynomialGPT(a).evaluate(x);
        auto gem = PolynomialGemini(a).evaluate(x);
        cout << "Expected: " << expected << '\n'
             << "Chat GPT: " << gpt << '\n'
             << "Gemini: " << gem << '\n';
        gptValid = near(expected, gpt);
        gemValid = near(expected, gem);
    } else if (q == 6) {
        auto expected = Polynomial(a).derivative();
        auto gpt = PolynomialGPT(a).derivative();
        auto gem = PolynomialGemini(a).derivative();
        cout << "Expected: " << expected << '\n'
             << "Chat GPT: " << gpt << '\n'
             << "Gemini: " << gem << '\n';
        check(expected, gpt, gptValid);
        check(expected, gem, gemValid);
    } else if (q == 7) {
        auto expected = Polynomial(a).integral();
        auto gpt = PolynomialGPT(a).integral();
        auto gem = PolynomialGemini(a).integral();
        cout << "Expected: " << expected << '\n'
             << "Chat GPT: " << gpt << '\n'
             << "Gemini: " << gem << '\n';
        check(expected, gpt, gptValid);
        check(expected, gem, gemValid);
    } else if (q == 8) {
        auto expected = Polynomial(a).integral(x, y);
        auto gpt = PolynomialGPT(a).integral(x, y);
        auto gem = PolynomialGemini(a).integral(x, y);
        cout << "Expected: " << expected << '\n'
             << "Chat GPT: " << gpt << '\n'
             << "Gemini: " << gem << '\n';
        gptValid = near(expected, gpt);
        gemValid = near(expected, gem);
    } else if (q == 9) {
        auto expected = Polynomial(a).getRoot();
        auto gpt = PolynomialGPT(a).getRoot();
        auto gem = PolynomialGemini(a).getRoot();
        cout << "Expected: " << expected << '\n'
             << "Chat GPT: " << gpt << '\n'
             << "Gemini: " << gem << '\n';
        gptValid = near(expected, gpt);
        gemValid = near(expected, gem);
    }

    cout << boolalpha;
    cout << "\nChat GPT: " << gptValid << '\n' << "Gemini: " << gemValid << '\n';
    totalCnt++;
    gptCnt += gptValid;
    gemCnt += gemValid;

}

int main() {
    int no_tc = 100;
    while (no_tc--)
        testCase();
    cout << "Chat GPT Accuracy: " << (double) gptCnt / totalCnt * 100 << "%\n";
    cout << "Chat Gemini Accuracy: " << (double) gemCnt / totalCnt * 100 << "%\n";
}
