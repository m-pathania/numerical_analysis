#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

struct solution {
    double zero;
    size_t feval;
    solution(double a, size_t b) : zero{a}, feval{b} {}
};

size_t function_evaluations{};
double error{0.000000001};

double function(double);

std::vector<solution> false_position(double, double, double = 1);

int main() {
    double start_point{-2};
    double end_point{2};
    double increment{0.5};

    std::ofstream output_file{"output_b.dat"};
    output_file << "Parameters\n";
    output_file << "start_point = \t" << start_point << std::endl;
    output_file << "end_point = \t" << end_point << std::endl;
    output_file << "increment = \t" << increment << std::endl;
    output_file << "error = \t" << error << std::endl;

    std::vector<solution> zeros{false_position(start_point, end_point, increment)};

    if (zeros.size()) {
        std::cout << "root\t\t"
                  << "Function Evaluations" << std::endl;
        for (auto ii : zeros)
            std::cout << ii.zero << "\t\t" << ii.feval << std::endl;
        std::cout << "\nTotal Number of Function evaluations:\t" << function_evaluations << std::endl;

        output_file << "\nroot\t\t"
                    << "Function Evaluations" << std::endl;
        for (auto ii : zeros)
            output_file << ii.zero << "\t\t" << ii.feval << std::endl;
        output_file << "\nTotal Number of Function evaluations:\t" << function_evaluations << std::endl;
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
    // return x * exp(x);
    return (pow(x, 3) - (2 * x) + 1);
    // return sin(x) - (1.0 / x);
}

std::vector<solution> false_position(double start, double last, double increment) {
    double a{start};
    double b{a + increment};
    double f_a{function(a)};
    double f_b{function(b)};

    std::vector<solution> output;

    while (b <= last) {
        if (f_a * f_b < 0) {
            double mid{(a * f_b - b * f_a) / (f_b - f_a)};
            double f_mid{function(mid)};
            // std::cout << ">> " << a << "; " << f_a << "; " << b << "; " << f_b << std::endl;
            // std::cout << mid << "; " << f_mid << std::endl;
            if (std::abs(b - a) < error) {
                output.push_back(solution(mid, function_evaluations));
                a = b;
                f_a = f_b / 2;
                b = a + increment;
                f_b = function(b);
            } else if (f_a * f_mid < 0) {
                b = mid;
                f_b = f_mid;
                f_a /= 2;
            } else {
                a = mid;
                f_a = f_mid;
                f_b /= 2;
            }
        } else {
            a = b;
            f_a = f_b / 2;
            b = a + increment;
            f_b = function(b);
        }
    }

    return output;
}