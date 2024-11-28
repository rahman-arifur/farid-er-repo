#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Function to calculate the product term in the interpolation
double ds(double x, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        double mul = 1;
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                mul *= (x - j);
            }
        }
        sum += mul;
    }
    return sum;
}

// Backward interpolation function
void backward()
{
    int n;
    cout << "Enter the number of points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter the x values: ";
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    cout << "Enter the y values: ";
    for (int i = 0; i < n; i++)
    {
        cin >> y[i];
    }

    double x_val;
    cout << "Enter the value of x for interpolation: ";
    cin >> x_val;

    // Calculate step size (h) and s
    double h = x[1] - x[0];
    double s = (x_val - x[n - 1]) / h; // Adjust s for backward interpolation

    // Initialize a matrix to store the backward differences
    vector<vector<double>> mat(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
    {
        mat[i][0] = y[i];
    }

    // Fill in the backward difference table
    for (int j = 1; j < n; j++)
    {
        for (int i = n - 1; i >= j; i--)
        {
            mat[i][j] = mat[i][j - 1] - mat[i - 1][j - 1];
        }
    }

    // Calculate the result using backward interpolation
    vector<double> delta(n);
    for (int i = 0; i < n; i++)
    {
        delta[i] = mat[n - 1][i];
    }

    double res = delta[0];
    for (int i = 1; i < n; i++)
    {
        res += (delta[i] * ds(s, i)) / tgamma(i + 1); // tgamma(i+1) gives i! in C++
    }

    res /= h;

    cout << "Interpolated result (Backward): " << res << endl;
}

// Forward interpolation function (same as before)
void forward()
{
    int n;
    cout << "Enter the number of points: ";
    cin >> n;

    vector<double> x(n), y(n);
    cout << "Enter the x values: ";
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    cout << "Enter the y values: ";
    for (int i = 0; i < n; i++)
    {
        cin >> y[i];
    }

    double x_val;
    cout << "Enter the value of x for interpolation: ";
    cin >> x_val;

    // Calculate step size (h) and s
    double h = x[1] - x[0];
    double s = (x_val - x[0]) / h;

    // Initialize a matrix to store the forward differences
    vector<vector<double>> mat(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
    {
        mat[i][0] = y[i];
    }

    // Fill in the forward difference table
    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < n - j; i++)
        {
            mat[i][j] = mat[i + 1][j - 1] - mat[i][j - 1];
        }
    }

    // Calculate the result using forward interpolation
    vector<double> delta(n);
    for (int i = 0; i < n; i++)
    {
        delta[i] = mat[0][i];
    }

    double res = delta[0];
    for (int i = 1; i < n; i++)
    {
        res += (delta[i] * ds(s, i)) / tgamma(i + 1); // tgamma(i+1) gives i! in C++
    }

    res /= h;

    cout << "Interpolated result (Forward): " << res << endl;
}

int main()
{
    int choice;
    cout << "Enter 1 for Forward Interpolation, 2 for Backward Interpolation: ";
    cin >> choice;

    if (choice == 1)
    {
        forward();
    }
    else if (choice == 2)
    {
        backward();
    }
    else
    {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
