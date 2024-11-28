#include "bits/stdc++.h"
using namespace std;
const int MOD = 1e9 + 7;
const double PI = acos(-1);
typedef long long ll;
typedef unsigned long long ull;
#define FAST                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0)

vector<double> a;

double fxx(double x)
{
    double ans = 0;
    ll n = a.size();
    for (int i = 0; i < n; ++i)
    {
        ans += pow(x, i) * a[i];
    }
    return ans;
}

double ddx(double x)
{
    ll n = a.size();
    double ans = 0;
    for (ll i = 1; i < n; i++)
    {
        ans += pow(x, i - 1) * a[i] * i;
    }
    return ans;
}

double secantMethod(double x1, double x2, double tolerance = 1e-6, int maxIterations = 1000)
{
    double fx1, fx2, x3, fx3;

    for (int iter = 0; iter < maxIterations; iter++)
    {
        fx1 = fxx(x1);
        fx2 = fxx(x2);

        x3 = x2 - (fx2 * (x2 - x1) / (fx2 - fx1));
        fx3 = fxx(x3);

        if (fabs(fx3) < tolerance || fabs(x3 - x2) < tolerance)
        {
            return x3;
        }

        x1 = x2;
        x2 = x3;
    }
    return x2;
}

double newtonRaphson(double x, double tolerance = 1e-6, int maxIterations = 1000)
{
    double fx, dx;
    for (int iter = 0; iter < maxIterations; ++iter)
    {
        fx = fxx(x);
        dx = ddx(x);
        if (fabs(dx) < tolerance)
            break;
        double x1 = x - (fx / dx);
        if (fabs(x1 - x) < tolerance)
            return x1;
        x = x1;
    }
    return x;
}

int main()
{
    FAST;
    ll degree;
    cout << "Enter the degree of the polynomial: " << endl;
    cin >> degree;
    cout << "Enter the coefficients (highest to lowest degree): " << endl;
    for (ll i = 0; i <= degree; i++)
    {
        double coefficient;
        cin >> coefficient;
        a.push_back(coefficient);
    }

    reverse(a.begin(), a.end());

    set<double> uniqueRoots;
    double intervalStart = -100, intervalEnd = 100;
    double step = 1;

    cout << "Choose Method (1: Newton-Raphson, 2: Secant): " << endl;
    int choice;
    cin >> choice;

    for (double initialGuess = intervalStart; initialGuess <= intervalEnd; initialGuess += step)
    {
        double root;
        if (choice == 1)
        {
            root = newtonRaphson(initialGuess);
        }
        else if (choice == 2)
        {
            root = secantMethod(initialGuess, initialGuess + step);
        }
        else
        {
            cout << "Invalid choice!" << endl;
            return 1;
        }

        bool isUnique = true;
        for (double foundRoot : uniqueRoots)
        {
            if (fabs(foundRoot - root) < 1e-3)
            {
                isUnique = false;
                break;
            }
        }

        if (isUnique && fabs(fxx(root)) < 1e-3)
        {
            uniqueRoots.insert(root);
            cout << "Root found: " << root << endl;
        }
    }

    if (uniqueRoots.empty())
    {
        cout << "No real roots found." << endl;
    }

    return 0;
}
