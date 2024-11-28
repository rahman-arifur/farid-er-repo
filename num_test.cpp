/*#include "bits/stdc++.h"
using namespace std;
const int MOD = 1e9 + 7;
const double PI = acos(-1);
typedef long long ll;
typedef unsigned long long ull;
#define SetBit(x, k) (x |= (1ll << k))
#define ClearBit(x, k) (x &= ~(1ll << k))
#define CheckBit(x, k) ((x >> k) & 1)
#define toggleBit(x, k) (x ^ (1ll << k))
#define FAST                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0)

const int maxIterations = 10000;

void makeDiagonallyDominant(vector<vector<double>> &A, vector<double> &b)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                sum += fabs(A[i][j]);
            }
        }

        if (fabs(A[i][i]) < sum)
        {
            for (int k = i + 1; k < n; k++)
            {
                double newSum = 0.0;
                for (int j = 0; j < n; j++)
                {
                    if (k != j)
                    {
                        newSum += fabs(A[k][j]);
                    }
                }
                if (fabs(A[k][k]) >= newSum)
                {
                    swap(A[i], A[k]);
                    swap(b[i], b[k]);
                    break;
                }
            }
        }
    }
}

vector<double> gaussSeidelMethod(vector<vector<double>> &A, vector<double> &b, double tol = 1e-10)
{
    int n = A.size();
    makeDiagonallyDominant(A, b);

    vector<double> x(n, 0.0);
    vector<double> x_new(n);

    for (int iteration = 0; iteration < maxIterations; iteration++)
    {
        for (int i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
            {
                sum += A[i][j] * x_new[j];
            }
            for (int j = i + 1; j < n; j++)
            {
                sum += A[i][j] * x[j];
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        double error = 0.0;
        double norm = 0.0;
        for (int i = 0; i < n; i++)
        {
            error = max(error, abs(x_new[i] - x[i]));
            norm = max(norm, abs(x_new[i]));
        }

        if (error / norm < tol)
        {
            return x_new;
        }

        x = x_new;
    }
    return x_new;
}

double chk(double a, double b, double c, double x)
{
    return a + b * x + c * x * x;
}
void two(vector<double> &x, vector<double> &y)
{
    int n = x.size();

    // Normalize x values for better numerical stability
    double x_mean = 0;
    for (double val : x)
        x_mean += val;
    x_mean /= n;

    vector<double> x_normalized(n);
    for (int i = 0; i < n; i++)
    {
        x_normalized[i] = (x[i] - x_mean) / 6.0;
    }

    double sumX = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0, sumY = 0, sumXY = 0, sumX2Y = 0;
    for (int i = 0; i < n; i++)
    {
        double x2 = x_normalized[i] * x_normalized[i];
        sumX += x_normalized[i];
        sumX2 += x2;
        sumX3 += x2 * x_normalized[i];
        sumX4 += x2 * x2;
        sumY += y[i];
        sumXY += x_normalized[i] * y[i];
        sumX2Y += x2 * y[i];
    }

    vector<vector<double>> A = {
        {n, sumX, sumX2},
        {sumX, sumX2, sumX3},
        {sumX2, sumX3, sumX4}};
    vector<double> b = {sumY, sumXY, sumX2Y};

    vector<double> slv = gaussSeidelMethod(A, b);

    // Denormalize coefficients
    double t = 6.0;
    double aa = slv[0] - slv[1] * x_mean / t + slv[2] * x_mean * x_mean / (t * t);
    double bb = slv[1] / t - 2 * slv[2] * x_mean / (t * t);
    double cc = slv[2] / (t * t);

    cout << endl
         << " y = " << aa << " + " << bb << " * x + " << cc << " * x^2" << endl;

    // Calculate predictions and errors
    double sum_error = 0.0;
    double sum_squared_error = 0.0;
    double ans = 0;
    vector<string> mon = {"January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};
    cout << "Month\tActual\tPredicted\tError" << endl;
    for (int i = 0; i < n; i++)
    {
        double predicted = chk(aa, bb, cc, x[i]);
        double error = y[i] - predicted;
        sum_error += fabs(error);
        sum_squared_error += error * error;
        ans += predicted;
        cout << mon[i] << "\t" << y[i] << "\t" << predicted << "\t" << error << endl;
    }
    ans /= n;
    cout << "\nAverage predicted value: " << ans << endl;
    cout << "Mean Absolute Error: " << sum_error / n << endl;
    cout << "Root Mean Square Error: " << sqrt(sum_squared_error / n) << endl;
}
double chk2(double a, double b, double c, double d, double x)
{
    return a + b * x + c * x * x + d * x * x * x;
}
void three(vector<double> &x, vector<double> &y)
{
    int n = x.size();

    double x_mean = 0;
    for (double val : x)
        x_mean += val;
    x_mean /= n;

    vector<double> x_normalized(n);
    for (int i = 0; i < n; i++)
    {
        x_normalized[i] = (x[i] - x_mean) / 6.0;
    }

    double sumX = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0, sumY = 0;
    double sumXY = 0, sumX2Y = 0, sumX5 = 0, sumX6 = 0, sumX3Y = 0;

    for (int i = 0; i < n; i++)
    {
        double x2 = x_normalized[i] * x_normalized[i];
        double x3 = x2 * x_normalized[i];
        sumX += x_normalized[i];
        sumX2 += x2;
        sumX3 += x3;
        sumX4 += x2 * x2;
        sumX5 += x2 * x3;
        sumX6 += x3 * x3;
        sumY += y[i];
        sumXY += x_normalized[i] * y[i];
        sumX2Y += x2 * y[i];
        sumX3Y += x3 * y[i];
    }

    vector<vector<double>> A = {
        {n, sumX, sumX2, sumX3},
        {sumX, sumX2, sumX3, sumX4},
        {sumX2, sumX3, sumX4, sumX5},
        {sumX3, sumX4, sumX5, sumX6}};
    vector<double> b = {sumY, sumXY, sumX2Y, sumX3Y};

    vector<double> slv = gaussSeidelMethod(A, b);

    double t = 6.0;
    double aa = slv[0] - slv[1] * x_mean / t + slv[2] * x_mean * x_mean / (t * t) - slv[3] * x_mean * x_mean * x_mean / (t * t * t);
    double bb = slv[1] / t - 2 * slv[2] * x_mean / (t * t) + 3 * slv[3] * x_mean * x_mean / (t * t * t);
    double cc = slv[2] / (t * t) - 3 * slv[3] * x_mean / (t * t * t);
    double dd = slv[3] / (t * t * t);

    cout << endl;
    cout << " y = " << aa << " + " << bb << " * x + " << cc << " * x^2 + " << dd << " * x^3" << endl;

    // Calculate predictions and errors
    double sum_error = 0.0;
    double sum_squared_error = 0.0;
    double ans = 0;
    vector<string> mon = {"January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};
    cout << "Month\tActual\tPredicted\tError" << endl;
    for (int i = 0; i < n; i++)
    {
        double predicted = chk2(aa, bb, cc, dd, x[i]);
        double error = y[i] - predicted;
        sum_error += fabs(error);
        sum_squared_error += error * error;
        ans += predicted;
        cout << mon[i] << "\t" << y[i] << "\t" << predicted << "\t" << error << endl;
    }
    ans /= n;
    cout << "\nAverage predicted value: " << ans << endl;
    cout << "Mean Absolute Error: " << sum_error / n << endl;
    cout << "Root Mean Square Error: " << sqrt(sum_squared_error / n) << endl;
}

int main()
{
    FAST;
    int i, j, k;

    vector<double> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    vector<double> y = {23.8, 26.6, 33.1, 35.3, 34.5, 34.1, 32.5, 32.2, 32.2, 31.3, 29.3, 27.1};

    vector<double> p = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    vector<double> q = {27.1, 31.3, 33.0, 36.7, 35.7, 35.0, 33.1, 32.5, 32.1, 32.1, 30.0, 25.3};
    three(p, q);
    cout << endl;
    cout << endl;
    two(x, y);
    cout << endl;

    return 0;
}*/

// muin
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
int const N = 15;

vector<ld> gaussSeidelMethod(const vector<vector<ld>> &A, const vector<ld> &b)
{
    int maxIteration = 1000;
    int n = b.size();
    vector<ld> x(n, 0.0);
    vector<ld> xOld(n, 0.0);

    for (int iter = 0; iter < maxIteration; ++iter)
    {
        xOld = x;
        for (int i = 0; i < n; ++i)
        {
            ld sum = 0.0;
            for (int j = 0; j < n; ++j)
            {
                if (j != i)
                {
                    sum += A[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
    }

    return x;
}

int main()
{
    int n = 12;
    vector<ld> xx = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    vector<ld> yy = {23.8, 26.6, 33.1, 35.3, 34.5, 34.1, 32.5, 32.2, 32.2, 31.3, 29.3, 27.1};
    vector<ld> v = {27.1, 31.3, 33.0, 36.7, 35.7, 35.0, 33.1, 32.5, 32.1, 32.1, 30.0, 25.3};

    ld x = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0, x6 = 0, y = 0, yx = 0, yx2 = 0, yx3 = 0;

    for (int i = 0; i < n; i++)
    {
        x += xx[i];
        y += yy[i];
        x2 += pow(xx[i], 2);
        x3 += pow(xx[i], 3);
        x4 += pow(xx[i], 4);
        x5 += pow(xx[i], 5);
        x6 += pow(xx[i], 6);
        yx += yy[i] * xx[i];
        yx2 += yy[i] * pow(xx[i], 2);
        yx3 += yy[i] * pow(xx[i], 3);
    }

    ld nn = n;

    vector<vector<ld>> m1 = {
        {nn, x, x2},
        {x, x2, x3},
        {x2, x3, x4}};
    vector<ld> b1 = {y, yx, yx2};

    vector<vector<ld>> m2 = {
        {nn, x, x2, x3},
        {x, x2, x3, x4},
        {x2, x3, x4, x5},
        {x3, x4, x5, x6}};

    vector<ld> b2 = {y, yx, yx2, yx3};

    vector<ld> s1 = gaussSeidelMethod(m1, b1);
    vector<ld> s2 = gaussSeidelMethod(m2, b2);

    ld avg1 = 0, avg2 = 0, t1 = 0, t2 = 0;

    cout << "Prediction 1 : \n";
    for (int i = 0; i < n; i++)
    {
        ld it = xx[i];
        ld y = s1[0] + s1[1] * it + s1[2] * it * it;
        // cout << i + 1 << " : " << y << "\n";
        t1 += y;
        avg1 += abs(y - v[i]);
    }
    cout << "\nAverage Temperature: " << t1 / 12 << "\n";
    cout << "Mean Absolute Error: " << avg1 / 12 << "\n\n";

    cout << "\nPrediction 2 : \n";
    for (int i = 0; i < n; i++)
    {
        ld it = xx[i];
        ld y = s2[0] + s2[1] * it + s2[2] * it * it + s2[3] * it * it * it;
        // cout << i + 1 << " : " << y << "\n";
        t2 += y;
        avg2 += abs(y - v[i]);
    }
    cout << "\nAverage Temperature: " << t2 / 12 << "\n";
    cout << "Mean Absolute Error: " << avg2 / 12 << "\n\n";

    return 0;
}
