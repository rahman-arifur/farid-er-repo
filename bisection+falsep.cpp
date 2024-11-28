
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
double sq(double x)
{
    double ans = a[0] * x * x + a[1] * x + a[2];
    return ans;
}
double cube(double x)
{
    double ans = a[0] * x * x * x + a[1] * x * x + a[2] * x + a[3];
    return ans;
}
double quadratic(double x)
{
    double ans = a[0] * x * x * x * x + a[1] * x * x * x + a[2] * x * x + a[3] * x + a[4];
    return ans;
}
void bisection(double mini, double maxa, ll n)
{
    double a, b, i;
    double aa, bb, mid, mm;
    set<double> ans;
    for (i = mini - 1; i <= maxa + 1; i++)
    {
        a = i, b = i + 1;
        if (n == 3)
        {
            aa = sq(a);
            bb = sq(b);
        }
        else if (n == 4)
        {
            aa = cube(a);
            bb = cube(b);
        }
        else
        {
            aa = quadratic(a);
            bb = quadratic(b);
        }
        if (aa == 0)
        {
            ans.insert(a);
            if (bb == 0)
            {
                ans.insert(b);
            }
            continue;
        }
        if (bb == 0)
        {
            ans.insert(b);
            if (aa == 0)
            {
                ans.insert(a);
            }
            continue;
        }
        if (aa * bb < 0)
        {
            //
            mid = (a + b) / 2;
            cout << mid << endl;
            double prev = mid;
            if (n == 3)
                mm = sq(mid);
            else if (n == 4)
                mm = cube(mid);
            else
                mm = quadratic(mid);

            while (fabs(mm) > 1e-6)
            {
                mid = (a + b) / 2;
                if (n == 3)
                    mm = sq(mid);
                else if (n == 4)
                    mm = cube(mid);
                else
                    mm = quadratic(mid);
                if ((mm < 0 && aa < 0) || (mm > 0 && aa > 0))
                {
                    a = mid;
                    aa = mm;
                }
                else
                {
                    b = mid;
                    bb = mm;
                }
                // cout << mid << endl;
                // cout << fabs(prev - mid) << endl;
                prev = mid;
            }
            ans.insert(mid);
        }
    }
    cout << "Root : ";
    for (auto it : ans)
    {
        cout << it << " ";
    }
    cout << endl;
}

void falsep(double mini, double maxa, ll n)
{
    double a, b, i;
    double aa, bb, mid, mm;
    set<double> ans;
    for (i = mini - 1; i <= maxa + 1; i++)
    {
        a = i, b = i + 1;
        if (n == 3)
        {
            aa = sq(a);
            bb = sq(b);
        }
        else if (n == 4)
        {
            aa = cube(a);
            bb = cube(b);
        }
        else
        {
            aa = quadratic(a);
            bb = quadratic(b);
        }
        if (aa == 0)
        {
            ans.insert(a);
            if (bb == 0)
            {
                ans.insert(b);
            }
            continue;
        }
        if (bb == 0)
        {
            ans.insert(b);
            if (aa == 0)
            {
                ans.insert(a);
            }
            continue;
        }
        if (aa * bb < 0)
        {
            // mid = (a + b) / 2;
            mid = (a * (bb)-b * aa) / (bb - aa);
            double prev = mid;
            if (n == 3)
                mm = sq(mid);
            else if (n == 4)
                mm = cube(mid);
            else
                mm = quadratic(mid);

            while (fabs(mm) > 1e-6)
            {
                mid = (a * (bb)-b * aa) / (bb - aa);
                // cout << b << endl;
                if (n == 3)
                    mm = sq(mid);
                else if (n == 4)
                    mm = cube(mid);
                else
                    mm = quadratic(mid);
                if ((mm < 0 && aa < 0) || (mm > 0 && aa > 0))
                {
                    a = mid;
                    aa = mm;
                }
                else
                {
                    b = mid;
                    bb = mm;
                }
                // cout << mid << endl;
                //  cout << fabs(prev - mid) << endl;
                prev = mid;
            }
            ans.insert(mid);
        }
    }
    cout << "Root : ";
    for (auto it : ans)
    {
        cout << it << " ";
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
    double m, x;
    x = (a[1] / a[0]);
    x *= x;
    double y = 2 * (a[2] / a[0]);
    double maxa = abs(x - y);
    double mini = -maxa;
    // cout << maxa << mini;

    bisection(mini, maxa, degree + 1);
    cout << endl;
    falsep(mini, maxa, degree + 1);
    return 0;
}

// #include "bits/stdc++.h"
// using namespace std;
// const int MOD = 1e9 + 7;
// const double PI = acos(-1);
// typedef long long ll;
// typedef unsigned long long ull;
// #define FAST                      \
//     ios_base::sync_with_stdio(0); \
//     cin.tie(0)

// vector<double> a;

// double fxx(double x)
// {
//     double ans = 0;
//     ll n = a.size();
//     for (int i = 0; i < n; ++i)
//     {
//         ans += pow(x, i) * a[i];
//     }
//     return ans;
// }

// void bisection(double minRange, double maxRange, double tolerance = 1e-6, double step = 1.0)
// {
//     set<double> roots;
//     for (double i = minRange; i <= maxRange; i += step)
//     {
//         double a = i, b = i + step;
//         double fa = fxx(a), fb = fxx(b);

//         if (fa == 0)
//             roots.insert(a);
//         if (fb == 0)
//             roots.insert(b);

//         if (fa * fb < 0)
//         {
//             double mid, fm;
//             while (fabs(b - a) > tolerance)
//             {
//                 mid = (a + b) / 2.0;
//                 fm = fxx(mid);
//                 if (fabs(fm) < tolerance)
//                     break;

//                 if (fm * fa < 0)
//                 {
//                     b = mid;
//                     fb = fm;
//                 }
//                 else
//                 {
//                     a = mid;
//                     fa = fm;
//                 }
//             }
//             roots.insert(mid);
//         }
//     }
//     cout << "Bisection Roots: ";
//     for (auto root : roots)
//         cout << root << " ";
//     cout << endl;
// }

// void falsePosition(double minRange, double maxRange, double tolerance = 1e-6, double step = 1.0)
// {
//     set<double> roots;
//     for (double i = minRange; i <= maxRange; i += step)
//     {
//         double a = i, b = i + step;
//         double fa = fxx(a), fb = fxx(b);

//         if (fa == 0)
//             roots.insert(a);
//         if (fb == 0)
//             roots.insert(b);

//         if (fa * fb < 0)
//         {
//             double root, fm;
//             while (fabs(b - a) > tolerance)
//             {
//                 root = (a * fb - b * fa) / (fb - fa);
//                 fm = fxx(root);
//                 if (fabs(fm) < tolerance)
//                     break;

//                 if (fm * fa < 0)
//                 {
//                     b = root;
//                     fb = fm;
//                 }
//                 else
//                 {
//                     a = root;
//                     fa = fm;
//                 }
//             }
//             roots.insert(root);
//         }
//     }
//     cout << "False Position Roots: ";
//     for (auto root : roots)
//         cout << root << " ";
//     cout << endl;
// }
// int main()
// {
//     FAST;
//     ll degree;
//     cout << "Enter the degree of the polynomial: " << endl;
//     cin >> degree;
//     cout << "Enter the coefficients (highest to lowest degree): " << endl;
//     for (ll i = 0; i <= degree; i++)
//     {
//         double coefficient;
//         cin >> coefficient;
//         a.push_back(coefficient);
//     }
//     reverse(a.begin(), a.end());

//     double x = (a[1] / a[0]);
//     double maxa = fabs(x * x - 2 * (a[2] / a[0]));
//     double minRange = -maxa, maxRange = maxa;

//     cout << endl;
//     bisection(minRange, maxRange);
//     falsePosition(minRange, maxRange);

//     return 0;
// }
