/*
Name = Mayank Pathania
Roll No. = 204103314
Specialization = Machine Design
*/

/*
Input is read from the file "input_data.dat"
Format of the file is as follow:
_________________________________________
number of intervals

start
end
x(start)
x(end)
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "array_io.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

// These functions are from the formulation 
// and can be changed according to problem
inline double a(double h, double t){
    return 1 + h*std::cos(t)/2;
}

inline double b(double h, double t){
    return -h*h*std::exp(t);
}

inline double c(double h, double t){
    return (1 - h*std::cos(t)/2);
}

inline double d(double h, double t){
    return -(2 + h*h*std::sin(t));
}

// Fills the A matrix and B vector of equation Ax = B
void fill_AB(vector<vector<double>>&, vector<double>&, double, double, double, double, int);

// solves Ax = B using gauss elimination method modified for tridiagonal matrix
vector<double> solve(vector<vector<double>>&, vector<double>&);

int main(){
    double start, end, x0, xn;
    int n;

    std::ifstream i_file("input_data.dat");
    if(!i_file.is_open()){
        cout << "Unable to read input_data.dat file" << endl;
        exit(-1);
    }
    i_file >> n >> start >> end >> x0 >> xn;
    i_file.close();

    n = std::max(2, n); // ensuring minimum 2 intervals are there

    vector<vector<double>> A(n - 1, vector<double>(3));
    vector<double> B(n - 1);
    fill_AB(A, B, start, end, x0, xn, n);

    cout << "Only the tridiagonal elements of the matrix are stored" << endl;
    cout << "Matrix, A ===>\n";
    print_matrix(A);
    cout << "\nVector, B ===>\n";
    print_vector(B);

    vector<double> x{solve(A, B)};

    // Printing solution
    cout << "\nNumber of intervals = " << n << endl;
    cout << "\nSolution ===>" << endl;
    cout << "t\t\t\t" << "x(t)" << endl;
    cout << start << "\t\t\t" << x0 << endl;
    for(size_t i{}; i < x.size(); i++)
        cout << (start + (i + 1)*((end - start)/n)) << "\t\t\t" << x[i] << endl;
    cout << end << "\t\t\t" << xn << endl;

    // Saving solution to file
    std::string filename{"output_n_" + std::to_string(n) + ".dat"};
    std::ofstream o_file{filename};
    o_file << "t," << "x(t)" << endl;
    o_file << start << "," << x0 << endl;
    for(size_t i{}; i < x.size(); i++)
        o_file << (start + (i + 1)*((end - start)/n)) << "," << x[i] << endl;
    o_file << end << "," << xn << endl;

    o_file.close();

    return 0;
}

void fill_AB(vector<vector<double>>& A, vector<double>& B, double start, double end, double x0, double xn, int n){
    double h{(end - start)/n};              // Step size
    for(size_t i{}; i < A.size(); i++){
        double t{start + (i + 1)*h};        // value of t; 
        if(i > 0)
            A[i][0] = a(h, t);

        A[i][1] = d(h, t);

        if(i < A.size() - 1)
            A[i][2] = c(h, t);
        B[i] = b(h, t);
    }
    B[0] -= (a(h, start + h)*x0);
    B.back() -= (c(h, start + B.size()*h)*xn);
}

// Solves using gauss elimination method modified for tridiagonal matrix
vector<double> solve(vector<vector<double>> &A, vector<double> &B){
    // Elimination Step
    for(size_t i{}; i < A.size()-1; ++i){
        // Performing elimination
        double ratio{A.at(i + 1).at(0)/A.at(i).at(1)};
        A.at(i + 1).at(1) -= (ratio * A.at(i).at(2));
        B.at(i + 1) -= (ratio * B.at(i));
    }

    // Back Substitution 
    vector<double> x(B.size(), 0);
    x.back() = B.back()/A.back()[1];
    for(size_t i{A.size() - 1}; i > 0; i--){
        x[i - 1] = (B[i - 1] - (A[i - 1][2]*x[i]))/A[i - 1][1];
    }

    return x;
}