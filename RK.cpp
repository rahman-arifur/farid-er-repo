#include <bits/stdc++.h>
using namespace std;

double f(double x, double y)
{
    return sin(x); // dy/dx = sin(x)
}

vector<pair<double, double>> RK4(double x0, double y0, double xEnd, double h)
{
    vector<pair<double, double>> points;
    double x = x0;
    double y = y0;

    while (x <= xEnd + h / 2)
    { // h/2 to handle floating point comparison
        points.push_back({x, y});

        double k1 = f(x, y);
        double k2 = f(x + h / 2, y + h * k1 / 2);
        double k3 = f(x + h / 2, y + h * k2 / 2);
        double k4 = f(x + h, y + h * k3);

        y += (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        x += h;
    }

    return points;
}

int main()
{
    double x0 = 0, y0 = 0;
    double xEnd = 4 * M_PI; // using M_PI for more precise pi value
    double h = 0.1;

    auto result = RK4(x0, y0, xEnd, h);

    cout << "x\t\ty (numerical)\ty (exact)\terror\n";
    cout << fixed << setprecision(6);

    for (auto [x, y] : result)
    {
        double exact = 1 - cos(x); // actual solution: y = -cos(x) + 1
        cout << x << "\t" << y << "\t" << exact << "\t" << abs(y - exact) << endl;
    }

    return 0;
}

/*
#include <bits/stdc++.h>
using namespace std;

double f(double x, double y)
{
    return x * x + y * y; // dy/dx = x^2 + y^2
}

vector<pair<double, double>> RK4(double x0, double y0, double xEnd, double h)
{
    vector<pair<double, double>> points;
    double x = x0;
    double y = y0;

    while (x <= xEnd + h / 2)
    { // h/2 to handle floating point comparison
        points.push_back({x, y});

        double k1 = f(x, y);
        double k2 = f(x + h / 2, y + h * k1 / 2);
        double k3 = f(x + h / 2, y + h * k2 / 2);
        double k4 = f(x + h, y + h * k3);

        y += (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        x += h;
    }

    return points;
}

int main()
{
    double x0 = 0, y0 = 0; // initial conditions
    double xEnd = 2.0;     // reduced end point since solution grows very fast
    double h = 0.1;        // smaller step size for better accuracy

    auto result = RK4(x0, y0, xEnd, h);

    cout << "x\t\ty (numerical)\n";
    cout << fixed << setprecision(6);

    for (auto [x, y] : result)
    {
        cout << x << "\t" << y << endl;
    }

    return 0;
}


*/