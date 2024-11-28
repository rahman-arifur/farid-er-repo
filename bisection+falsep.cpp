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

// Replace multiple polynomial functions with a single one
double evaluate(double x)
{
    double result = 0;
    for (int i = 0; i < a.size(); i++)
    {
        result = result * x + a[i];
    }
    return result;
}

// Helper function to find initial intervals containing roots
vector<pair<double, double>> findInitialIntervals(double mini, double maxa, double step = 0.1)
{
    vector<pair<double, double>> intervals;
    for (double x = mini; x <= maxa; x += step)
    {
        double fa = evaluate(x);
        double fb = evaluate(x + step);
        if (fa * fb <= 0)
        {
            intervals.push_back({x, x + step});
        }
    }
    return intervals;
}

// Helper function to check if a root already exists
bool rootExists(const set<double> &roots, double newRoot, double tolerance = 1e-6)
{
    for (double root : roots)
    {
        if (fabs(root - newRoot) < tolerance)
        {
            return true;
        }
    }
    return false;
}

void findRoots(double mini, double maxa, bool useFalsePosition)
{
    set<double> roots;
    auto intervals = findInitialIntervals(mini, maxa);
    const double tolerance = 1e-6;

    for (auto [a, b] : intervals)
    {
        double fa = evaluate(a);
        double fb = evaluate(b);

        // Handle exact roots
        if (fabs(fa) < tolerance && !rootExists(roots, a))
        {
            roots.insert(a);
            continue;
        }
        if (fabs(fb) < tolerance && !rootExists(roots, b))
        {
            roots.insert(b);
            continue;
        }

        // Iterative root finding
        int maxIter = 100;
        while (maxIter-- && fabs(b - a) > tolerance)
        {
            double c;
            if (useFalsePosition)
            {
                c = (a * fb - b * fa) / (fb - fa);
            }
            else
            {
                c = (a + b) / 2;
            }

            double fc = evaluate(c);
            if (fabs(fc) < tolerance)
            {
                if (!rootExists(roots, c))
                {
                    roots.insert(c);
                }
                break;
            }

            if (fc * fa < 0)
            {
                b = c;
                fb = fc;
            }
            else
            {
                a = c;
                fa = fc;
            }
        }
        if (maxIter >= 0 && fabs(b - a) < tolerance)
        {
            double finalRoot = (a + b) / 2;
            if (!rootExists(roots, finalRoot))
            {
                roots.insert(finalRoot);
            }
        }
    }

    cout << "Roots using " << (useFalsePosition ? "False Position" : "Bisection") << ": ";
    for (double root : roots)
    {
        cout << fixed << setprecision(6) << root << " ";
    }
    cout << endl;
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

    // Calculate bounds using a more reliable method
    double bound = 1.0;
    for (int i = 1; i < a.size(); i++)
    {
        bound = max(bound, pow(2.0 * fabs(a[i] / a[0]), 1.0 / i));
    }

    double mini = -bound, maxa = bound;

    findRoots(mini, maxa, false); // Bisection
    findRoots(mini, maxa, true);  // False Position

    return 0;
}
