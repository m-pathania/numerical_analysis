// Name = Mayank Pathania
// Roll. No = 204103314
// Specialization = Machine Design
// Email = mayank_pathania@iitg.ac.in

// array_io.h header contain functions to perform following operations:
// read matrix and vectors form a std::ifstream obj
// write matrix and vectors to a std::ofstream obj
// print matrix and vectors using std::cout

#ifndef _ARRAY_IO_H_
#define _ARRAY_IO_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// functions to read matrix or vector from file
std::vector<std::vector<double>> read_matrix(std::ifstream &i_file) {
    if (i_file.is_open()) {
        std::string Line;
        std::vector<std::vector<double>> matrix;
        while (std::getline(i_file, Line)) {
            std::vector<double> temp;
            std::istringstream i_string{Line};
            double elem{};
            while (i_string >> elem) temp.push_back(elem);
            if (temp.size()) matrix.push_back(temp);
        }
        return matrix;
    } else {
        std::cerr << "Error reading file" << std::endl;
        exit(1);
    }
}

std::vector<double> read_vector(std::ifstream &i_file) {
    if (i_file.is_open()) {
        std::vector<double> vec;
        double elem;
        while (i_file >> elem) vec.push_back(elem);
        return vec;
    } else {
        std::cerr << "Error reading file" << std::endl;
        exit(1);
    }
}

// functions to print matrices or vectors to consol
void print_matrix(const std::vector<std::vector<double>> &mat, int prec = 6) {
    std::cout << std::setprecision(prec);
    for (const auto &ii : mat) {
        for (const auto &jj : ii) {
            std::cout << jj << '\t';
        }
        std::cout << std::endl;
    }
}

void print_vector(const std::vector<double> &vec, int prec = 6) {
    std::cout << std::setprecision(prec);
    for (const auto &ii : vec) {
        std::cout << ii << std::endl;
    }
}

void print_row_vector(const std::vector<double> &vec, int prec = 6) {
    std::cout << std::setprecision(prec);
    for (const auto &ii : vec)
        std::cout << ii << "\t";
    std::cout << std::endl;
}

// functions to write matrix or vector to file
void write_matrix(const std::vector<std::vector<double>> &mat, std::ofstream &o_file, int prec = 6) {
    if (o_file) {
        o_file << std::setprecision(prec);
        for (const auto &ii : mat) {
            for (const auto &jj : ii) {
                o_file << jj << '\t';
            }
            o_file << std::endl;
        }
    } else {
        std::cerr << "Error writing file" << std::endl;
        exit(1);
    }
}

void write_vector(const std::vector<double> &vec, std::ofstream &o_file, int prec = 6) {
    if (o_file) {
        o_file << std::setprecision(prec);
        for (const auto &ii : vec) o_file << ii << '\n';
    } else {
        std::cerr << "Error writing file" << std::endl;
        exit(1);
    }
}

void write_row_vector(const std::vector<double> &vec, std::ofstream &o_file, int prec = 6) {
    if (o_file) {
        o_file << std::setprecision(prec);
        for (const auto &ii : vec) o_file << ii << '\t';
        o_file << std::endl;
    } else {
        std::cerr << "Error writing file" << std::endl;
        exit(1);
    }
}

#endif
