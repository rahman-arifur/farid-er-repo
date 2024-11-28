#include <bits/stdc++.h>
using namespace std;

double func(double x)
{
    return 1 / (1 + pow(x, 2)); // Example function
}

double trapezoidalRule(double a, double b, int n, double h)
{
    double result = func(a) + func(b); // Start with the first and last terms
    for (int i = 1; i < n; i++)
    { // Intermediate points
        result += 2 * func(a + i * h);
    }
    result *= (h / 2.0);
    return result;
}

double simpsonOneThirdRule(double a, double b, int n, double h)
{
    if (n % 2 != 0)
    {
        cout << "Error: n must be even for Simpson's 1/3 Rule." << endl;
        return -1;
    }

    double result = func(a) + func(b);
    for (int i = 1; i < n; i++)
    {
        if (i % 2 == 0)
        {
            result += 2 * func(a + i * h); // Even index
        }
        else
        {
            result += 4 * func(a + i * h); // Odd index
        }
    }
    result *= (h / 3.0);
    return result;
}

double simpsonThreeEighthRule(double a, double b, int n, double h)
{
    if (n % 3 != 0)
    {
        cout << "Error: n must be a multiple of 3 for Simpson's 3/8 Rule." << endl;
        return -1;
    }

    double result = func(a) + func(b);
    for (int i = 1; i < n; i++)
    {
        if (i % 3 == 0)
        {
            result += 2 * func(a + i * h); // Multiple of 3
        }
        else
        {
            result += 3 * func(a + i * h); // Not a multiple of 3
        }
    }
    result *= (3 * h / 8.0);
    return result;
}

int main()
{
    double a, b, h;
    int n;

    cout << "Enter the lower limit a: ";
    cin >> a;
    cout << "Enter the upper limit b: ";
    cin >> b;
    cout << "Enter the number of divisions n: ";
    cin >> n;

    h = (b - a) / n;
    cout << "Step size h: " << h << endl;

    // Trapezoidal Rule
    double result1 = trapezoidalRule(a, b, n, h);
    cout << "Result of Trapezoidal Rule: " << result1 << endl;

    // Simpson's 1/3 Rule
    double result2 = simpsonOneThirdRule(a, b, n, h);
    if (result2 != -1)
    {
        cout << "Result of Simpson's 1/3 Rule: " << result2 << endl;
    }

    // Simpson's 3/8 Rule
    double result3 = simpsonThreeEighthRule(a, b, n, h);
    if (result3 != -1)
    {
        cout << "Result of Simpson's 3/8 Rule: " << result3 << endl;
    }

    return 0;
}
