#include <cmath>
#include <iostream>
#include <fstream>

size_t function_evaluations{};
double error{0.000000001};

double function(double);
double bisection_method(double, double, bool &, double = 1);

int main() {
    double start_point{-2};
    double end_point{2};
    bool check{false};
    double increment{end_point - start_point};

    std::ofstream output_file{"output_a.dat"};
    output_file << "Parameters\n";
    output_file << "start_point = \t" << start_point << std::endl;
    output_file << "end_point = \t" << end_point << std::endl;
    output_file << "increment = \t" << increment << std::endl;
    output_file << "error = \t" << error << std::endl;

    double zero{bisection_method(start_point, end_point, check, increment)};

    if (check) {
        std::cout << "The solution of problem:\t" << zero << "\n"
                  << "Total Number of Function evaluations:\t" << function_evaluations << std::endl;
        output_file << "\nThe solution of problem:\t" << zero << "\n"
                  << "Total Number of Function evaluations:\t" << function_evaluations << std::endl;

    } else {
        std::cout << "Could not find solution in region ( " << start_point << " , " << end_point << " )" << std::endl;
        std::cout << "\nTotal Number of Function evaluations:\t" << function_evaluations << std::endl;

        output_file << "Could not find solution in region ( " << start_point << " , " << end_point << " )" << std::endl;
        output_file << "\nTotal Number of Function evaluations:\t" << function_evaluations << std::endl;
    }

    return 0;
}

double function(double x) {
    function_evaluations++;
    return x * exp(x);
    // return pow(x, 3) - (2 * x) + 1;
    // return sin(x) - (1.0 / x);
}

double bisection_method(double start, double last, bool &check, double increment) {
    double a{start};
    double b{a + increment};
    double f_a{function(a)};
    double f_b{function(b)};
    while (b <= last) {
        if (std::abs(f_a) < error) {
            check = true;
            return a;
        } else if (std::abs(f_b) < error) {
            check = true;
            return b;
        }

        if (f_a * f_b < 0) {
            double mid{(a + b) / 2};
            double f_mid{function(mid)};
            if (std::abs(f_mid) < error) {
                check = true;
                return mid;
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

    return 0;
}