#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

double error{0.000000001};

// function declarations
double function(double);
std::vector<double> bisection_method(double, double, double = 1);

int main() {
    double start_point{-2};
    double end_point{2};
    double increment{0.5};

    std::ofstream output_file{"output_c.dat"};
    std::vector<double> zeros{bisection_method(start_point, end_point, increment)};

    if (zeros.size()) {
        output_file << "\n# root\t\t"
                    << "Function value" << std::endl;
        for (auto ii : zeros)
            output_file << ii << "\t\t" << function(ii) << std::endl;
    }
    output_file.close();

    return 0;
}

double function(double x) {
    // return x * exp(x);
    // return (pow(x, 3) - (2 * x) + 1);
    return sin(x) - (1.0 / x);
}

std::vector<double> bisection_method(double start, double last, double increment) {
    double a{start};
    double b{a + increment};
    double f_a{function(a)};
    double f_b{function(b)};
    std::ofstream data_points{"points_c.dat"};
    data_points << "# a\t\t"
                << "b\t\t"
                << "mid\t\t"
                << "f(mid)" << std::endl;

    std::vector<double> output;

    while (b <= last) {
        if (f_a * f_b < 0) {
            double mid{(a + b) / 2};
            double f_mid{function(mid)};
            data_points << a << " " << b << " " << mid << " " << f_mid << std::endl;
            if (std::abs(f_mid) < error) {
                output.push_back(mid);
                a = b;
                f_a = f_b;
                b = a + increment;
                f_b = function(b);
            } else if (std::abs(b - a) < error) {
                a = b;
                f_a = f_b;
                b = a + increment;
                f_b = function(b);
            } else if (f_a * f_mid < 0) {
                b = mid;
                f_b = f_mid;
            } else {
                a = mid;
                f_a = f_mid;
            }
        } else {
            a = b;
            f_a = f_b;
            b = a + increment;
            f_b = function(b);
        }
    }
    data_points.close();
    return output;
}