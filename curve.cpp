#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

void gaussJordanElimination(vector<vector<double>> &A, vector<double> &B)
{
    int n = A.size();
    for (int i = 0; i < n; ++i)
    {
        // Find pivot row
        int pivotRow = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (abs(A[j][i]) > abs(A[pivotRow][i]))
            {
                pivotRow = j;
            }
        }

        // Swap rows if necessary
        if (i != pivotRow)
        {
            swap(A[i], A[pivotRow]);
            swap(B[i], B[pivotRow]);
        }

        // Normalize the pivot row
        double pivot = A[i][i];
        for (int j = 0; j < n; ++j)
        {
            A[i][j] /= pivot;
        }
        B[i] /= pivot;

        // Eliminate elements above and below pivot
        for (int j = 0; j < n; ++j)
        {
            if (j != i)
            {
                double factor = A[j][i];
                for (int k = 0; k < n; ++k)
                {
                    A[j][k] -= factor * A[i][k];
                }
                B[j] -= factor * B[i];
            }
        }
    }
}

// Straight line y = a + b * x
void straightLineFit(const vector<double> &x, const vector<double> &y)
{
    int n = x.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    // Keep existing sum calculations
    for (int i = 0; i < n; i++)
    {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    // Set up matrix equation
    vector<vector<double>> A = {
        {(double)n, sumX},
        {sumX, sumX2}};
    vector<double> B = {sumY, sumXY};

    // Solve using Gauss-Jordan elimination
    gaussJordanElimination(A, B);
    double a = B[0]; // intercept
    double b = B[1]; // slope

    cout << "Straight Line Fit: y = " << a << " + " << b << " * x" << endl;

    // Predict for 2001
    double pred_x = 2001;
    double pred_y = a + b * pred_x;
    cout << "Prediction for x = 2001: " << pred_y << endl;
}

// Parabola y = a + b * x + c * x^2
void parabolaFit(const vector<double> &x, const vector<double> &y)
{
    int n = x.size();
    double sumX = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0;
    double sumY = 0, sumXY = 0, sumX2Y = 0;

    // Keep existing sum calculations
    for (int i = 0; i < n; i++)
    {
        double x2 = x[i] * x[i];
        sumX += x[i];
        sumX2 += x2;
        sumX3 += x2 * x[i];
        sumX4 += x2 * x2;
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2Y += x2 * y[i];
    }

    // Set up matrix equation
    vector<vector<double>> A = {
        {(double)n, sumX, sumX2},
        {sumX, sumX2, sumX3},
        {sumX2, sumX3, sumX4}};
    vector<double> B = {sumY, sumXY, sumX2Y};

    // Solve using Gauss-Jordan elimination
    gaussJordanElimination(A, B);
    double a = B[0]; // constant term
    double b = B[1]; // coefficient of x
    double c = B[2]; // coefficient of x^2

    cout << "Parabola Fit: y = " << a << " + " << b << " * x + " << c << " * x^2" << endl;

    // Predict for 2001
    double pred_x = 2001;
    double pred_y = a + b * pred_x + c * pred_x * pred_x;
    cout << "Prediction for x = 2001: " << pred_y << endl;
}

// Exponential curve y = a * b^x
void exponentialFit(const vector<double> &x, const vector<double> &y)
{
    int n = x.size();
    double sumX = 0, sumLogY = 0, sumXLogY = 0, sumX2 = 0;

    // Keep existing sum and error check
    for (int i = 0; i < n; i++)
    {
        if (y[i] <= 0)
        {
            cout << "Error: y values must be positive for exponential fit." << endl;
            return;
        }
        double logY = log(y[i]);
        sumX += x[i];
        sumLogY += logY;
        sumXLogY += x[i] * logY;
        sumX2 += x[i] * x[i];
    }

    // Set up matrix equation
    vector<vector<double>> A = {
        {(double)n, sumX},
        {sumX, sumX2}};
    vector<double> B = {sumLogY, sumXLogY};

    // Solve using Gauss-Jordan elimination
    gaussJordanElimination(A, B);
    double a = exp(B[0]);
    double b = exp(B[1]);

    cout << "Exponential Fit: y = " << a << " * " << b << "^x" << endl;

    // Predict for 2001
    double pred_x = 2001;
    double pred_y = a * pow(b, pred_x);
    cout << "Prediction for x = 2001: " << pred_y << endl;
}

// Power curve y = a * x^b
void powerFit(const vector<double> &x, const vector<double> &y)
{
    int n = x.size();
    double sumLogX = 0, sumLogY = 0, sumLogXLogY = 0, sumLogX2 = 0;

    // Keep existing sum and error check
    for (int i = 0; i < n; i++)
    {
        if (x[i] <= 0 || y[i] <= 0)
        {
            cout << "Error: x and y values must be positive for power fit." << endl;
            return;
        }
        double logX = log(x[i]);
        double logY = log(y[i]);
        sumLogX += logX;
        sumLogY += logY;
        sumLogXLogY += logX * logY;
        sumLogX2 += logX * logX;
    }

    // Set up matrix equation
    vector<vector<double>> A = {
        {(double)n, sumLogX},
        {sumLogX, sumLogX2}};
    vector<double> B = {sumLogY, sumLogXLogY};

    // Solve using Gauss-Jordan elimination
    gaussJordanElimination(A, B);
    double a = exp(B[0]);
    double b = B[1];

    cout << "Power Fit: y = " << a << " * x^" << b << endl;

    // Predict for 2001
    double pred_x = 2001;
    double pred_y = a * pow(pred_x, b);
    cout << "Prediction for x = 2001: " << pred_y << endl;
}

int main()
{
    int n;
    cout << "Enter the number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter x values: ";
    for (int i = 0; i < n; i++)
        cin >> x[i];
    cout << "Enter y values: ";
    for (int i = 0; i < n; i++)
        cin >> y[i];

    cout << fixed << setprecision(6);

    // Perform curve fitting
    straightLineFit(x, y);
    parabolaFit(x, y);
    exponentialFit(x, y);
    powerFit(x, y);

    return 0;
}
