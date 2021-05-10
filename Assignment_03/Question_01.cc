// Assignment 03

// Name = Mayank Pathania
// Roll. NO = 204103314
// Specialization = Machine Design

// Question No. 01

#include <iostream>
#include <vector>
#include <fstream>

#include "array_io.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

// Evaluates solution by back substitution
vector<double> back_substitution(const vector<vector<double>> &, const vector<double> &, const vector<size_t> &);

// Performs elimination by scaled patial pivoting
vector<double> scaled_partial_pivoting(vector<vector<double>>, vector<double>);

int main(){
    // openining input files
    std::ifstream i_file_lhs{"input_matrix.dat"};
    std::ifstream i_file_rhs{"input_vector.dat"};
    if(i_file_lhs.is_open() && i_file_rhs.is_open()){
        vector<vector<double>> system_matrix{read_matrix(i_file_lhs)};  // reading input matrix
        vector<double> rhs{read_vector(i_file_rhs)};                    // reading input vector

        // printing input data
        cout << "System Matrix ===>" << endl;
        print_matrix(system_matrix);
        cout << "\nRHS Vector ===>" << endl;
        print_vector(rhs);

        if(system_matrix.size() == rhs.size()){
            vector<double> x_values{scaled_partial_pivoting(system_matrix, rhs)}; // solution of the problem

            // printing solution
            cout << "\nSolution ===>" << endl;
            print_vector(x_values);

            // saving solution in file
            std::ofstream o_file{"output_vector.dat"};
            write_vector(x_values, o_file);

            o_file.close(); // closing output file
        }else{ // The input matrix and vector and not compatible for obtaining solution
            cout << "\nLHS and RHS not compatible for solving" << endl;
            cout << "Size of LHS ==> \tRows = " << system_matrix.size()
                 << "; Columns = " << system_matrix.at(0).size() << ";" << endl;
            cout << "Size of RHS ==> \tRows = " << rhs.size()
                 << "; Columns = " << 1 << ";" << endl;
        }

    }else{ // Error : Files cound't be opened
        cout << "Coudn't open input files:\t lhs_matrix.dat and rhs_vector.dat" << endl;
    }

    // closing input files
    i_file_lhs.close();
    i_file_rhs.close();

    return 0;
}

void print(const vector<vector<double>> &A,const vector<double> &B, const vector<size_t> &p){
    for(size_t i{}; i < A.size(); i++){
        for(size_t j{}; j < A.size(); j++){
            cout << A[p[i]][j] << "\t";
        }
        cout << endl;
    }
    for (auto ii: B) cout << ii << endl;
}

// Performs elimination by scaled patial pivoting
vector<double> scaled_partial_pivoting(vector<vector<double>> A, vector<double> B){
    vector<size_t> position(A.size());
    vector<double> S(A.size());
    // Calculating Maximum elements in each row these are stored in vector S
    for(size_t i{}; i < A.size(); ++i){
        double max_element{std::abs(A.at(i).at(0))};
        for(size_t j{1}; j < A.at(0).size(); ++j){
            max_element = std::max(max_element, std::abs(A.at(i).at(j)));
        }
        S.at(i) = max_element;
        position.at(i) = i;
    }

    for(size_t i{}; i < A.size()-1; ++i){
        // Scaled Partial Pivoting
        size_t max_row{i};
        double max_ratio{std::abs(A.at(position.at(i)).at(i)/S.at(i))};
        for(size_t j{i+1}; j < A.size(); ++j){
            double ratio{std::abs(A.at(position.at(j)).at(i)/S.at(j))};
            if(ratio > max_ratio){
                max_ratio = ratio;
                max_row = j;
            }
        }
        // cout <<"\n"<< position.at(i) << "; " << position.at(max_row) << endl;
        std::swap(position.at(i), position.at(max_row));
        
        // cout << position.at(i) << "; " << position.at(max_row) << endl;
    
        // Performing elimination
        for(size_t k{i+1}; k < A.size(); ++k){
            double ratio{A.at(position.at(k)).at(i)/A.at(position.at(i)).at(i)};
            for(size_t j{i+1}; j < A.size(); ++j){
                A.at(position.at(k)).at(j) -= (ratio * A.at(position.at(i)).at(j));
            }
            B.at(position.at(k)) -= (ratio * B.at(position.at(i)));
        }
    }

    return back_substitution(A,B,position);
}

// Evaluated solution by back substitution
vector<double> back_substitution(const vector<vector<double>> &A, const vector<double> &B, const vector<size_t> &position){
    vector<double> x(A.at(0).size(), 0);

    x.at(A.size() - 1) = B.at(position.at(A.size() - 1))/A.at(position.at(A.size() - 1)).at(A.size() - 1);

    for(size_t i{A.size()-2}; i < A.size(); i--){
        double total{};
        for(size_t j{i+1}; j < A.size(); j++){
            total += (A.at(position.at(i)).at(j)*x.at(j));
        }
        x.at(i) = (B.at(position.at(i)) - total)/A.at(position.at(i)).at(i);
    }

    return x;
}
