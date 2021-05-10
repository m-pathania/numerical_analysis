#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "array_io.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

double dot_product(const vector<double> &, const vector<double> &);
vector<double> mat_vec(const vector<vector<double>> &, const vector<double> &);
vector<double> conjugate_gradient(const vector<vector<double>> &, const vector<double> &, double = 1e-8, size_t = 1000);

int main(){
    double tolerance{1e-10};
    size_t max_iteration{10};

    std::ifstream ifile_matrix{"input_matrix.dat"};
    std::ifstream ifile_vector{"input_vector.dat"};
    if(ifile_matrix.is_open() && ifile_vector.is_open()){
        vector<vector<double>> system_matrix{read_matrix(ifile_matrix)};
        vector<double> rhs{read_vector(ifile_vector)};

        cout << "System Matrix ===>" << endl;
        print_matrix(system_matrix);
        cout << "\nRHS Vector ===>" << endl;
        print_vector(rhs);
        if(system_matrix.size() == rhs.size()){
            vector<double> solution{conjugate_gradient(system_matrix, rhs, tolerance, max_iteration)};

            cout << "\nSolution ===>" << endl;
            print_vector(solution);

            std::ofstream output_file{"output_solution_conjugate_gradient.dat"};
            if(output_file.is_open())
                write_vector(solution,output_file);
            else
                cout << "\nUnable to write ouput file" << endl;
            output_file.close();
        }else{ // The input matrix and vector and not compatible for obtaining solution
            cout << "\nLHS and RHS not compatible for solving" << endl;
            cout << "Size of LHS ==> \tRows = " << system_matrix.size()
                 << "; Columns = " << system_matrix.at(0).size() << ";" << endl;
            cout << "Size of RHS ==> \tRows = " << rhs.size()
                 << "; Columns = " << 1 << ";" << endl;
        }
    }else{
        cout << "\nUnable to read input files" << endl;
    }

    ifile_matrix.close();
    ifile_vector.close();

    return 0;
}

vector<double> conjugate_gradient(const vector<vector<double>> &A, const vector<double> &B, double tolerance, size_t max_iteration){
    std::srand(std::time(nullptr));

    // range of initial guess
    int minimum{-100};
    int maximum{100};

    double error{1000};
    size_t iteration{0};

    vector<double> x;
    for(size_t i{0}; i < A[0].size(); i++){
        x.push_back(minimum + (std::rand() %(maximum + 1 - minimum)));
    }

    vector<double> d;
    vector<double> *r = new vector<double>;
    {
        vector<double> temp{mat_vec(A, x)};
        for(size_t i{0}; i < A.size(); i++){
            d.push_back(B[i] - temp[i]);
            r->push_back(d.back());
        }
    }

    cout << "\nInitial guess " << endl;
    print_row_vector(x);
    std::ofstream output_file{"ouput_iteration_conjugate_gradient.dat"};

    while(error > tolerance && iteration < max_iteration){
        vector<double> Adi{mat_vec(A, d)};
        double alpha{dot_product(*r, *r)/dot_product(d, Adi)};

        for(size_t i{0}; i < x.size(); i++) x[i] += (alpha*d[i]);

        error = 0;
        vector<double> *r_next = new vector<double>(r->size());
        for(size_t i{0}; i < x.size(); i++){
            r_next->at(i) = r->at(i) - (alpha*Adi[i]);
            error = error + (r_next->at(i))*(r_next->at(i));
        }

        double beta{dot_product(*r_next, *r_next)/dot_product(d, *r)};

        for(size_t i{0}; i < d.size(); i++) d[i] = (r_next->at(i) + beta*d[i]);
        delete r;
        r = r_next;
        r_next = nullptr;

        error = sqrt(error);
        iteration++;
        cout << "iteration = " << iteration << "; error = " << error << "; x = \t";
        print_row_vector(x);
        output_file << iteration << " & " << error << " & ";
        for(auto i: x) output_file << i << " & ";
        output_file << endl;
    }
    output_file.close();
    return x;
}

double dot_product(const vector<double> &a, const vector<double> &b){
    double result{0};
    for(size_t i{0}; i < a.size(); i++)
        result += a[i]*b[i];
    return result;
}

vector<double> mat_vec(const vector<vector<double>> &A, const vector<double> &b){
    vector<double> x(A.size());
    for(size_t i{0}; i < A.size(); i++){
        double temp{0};
        for(size_t j{0}; j < b.size(); j++){
            temp += A[i][j]*b[j];
        }
        x[i] = temp;
    }
    return x;
}