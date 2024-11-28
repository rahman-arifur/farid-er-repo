#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Modified print function for separate matrices
void printSolution(const vector<vector<double>> &A, const vector<double> &B)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        for (double element : A[i])
        {
            cout << element << " ";
        }
        cout << "| " << B[i] << endl;
    }
}

// New function to print a matrix
void printMatrix(const vector<vector<double>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (double element : row)
        {
            cout << element << " ";
        }
        cout << endl;
    }
}

// Modified Gauss-Jordan elimination for separate matrices
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

// New function to calculate inverse matrix
vector<vector<double>> calculateInverse(vector<vector<double>> A)
{
    int n = A.size();
    vector<vector<double>> inverse(n, vector<double>(n, 0));

    // Initialize inverse as identity matrix
    for (int i = 0; i < n; i++)
    {
        inverse[i][i] = 1;
    }

    // Apply Gauss-Jordan elimination
    for (int i = 0; i < n; i++)
    {
        // Find pivot
        int pivotRow = i;
        for (int j = i + 1; j < n; j++)
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
            swap(inverse[i], inverse[pivotRow]);
        }

        // Scale pivot row
        double pivot = A[i][i];
        for (int j = 0; j < n; j++)
        {
            A[i][j] /= pivot;
            inverse[i][j] /= pivot;
        }

        // Eliminate columns
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                double factor = A[j][i];
                for (int k = 0; k < n; k++)
                {
                    A[j][k] -= factor * A[i][k];
                    inverse[j][k] -= factor * inverse[i][k];
                }
            }
        }
    }

    return inverse;
}

// Modified Row Echelon Form for separate matrices
void rowEchelonForm(vector<vector<double>> &A, vector<double> &B)
{
    int n = A.size();
    for (int i = 0; i < n; ++i)
    {
        double lead = A[i][i];
        for (int j = i; j < n; ++j)
        {
            A[i][j] /= lead;
        }
        B[i] /= lead;

        for (int j = i + 1; j < n; ++j)
        {
            double factor = A[j][i];
            for (int k = i; k < n; ++k)
            {
                A[j][k] -= factor * A[i][k];
            }
            B[j] -= factor * B[i];
        }
    }
}

int main()
{
    int n;
    cout << "Enter the number of equations: ";
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> B(n);

    cout << "Enter the coefficients matrix A:\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> A[i][j];
        }
    }

    cout << "Enter the constants vector B:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> B[i];
    }

    cout << "\nThe input system:\n";
    printSolution(A, B);

    // Store copies for different methods
    auto A_gauss = A;
    auto B_gauss = B;
    auto A_echelon = A;
    auto B_echelon = B;

    gaussJordanElimination(A_gauss, B_gauss);
    cout << "\nAfter Gauss-Jordan Elimination:\n";
    printSolution(A_gauss, B_gauss);

    rowEchelonForm(A_echelon, B_echelon);
    cout << "\nIn Row Echelon Form:\n";
    printSolution(A_echelon, B_echelon);

    // Calculate and print inverse matrix
    vector<vector<double>> inverse = calculateInverse(A);
    cout << "\nInverse Matrix:\n";
    printMatrix(inverse);

    return 0;
}
