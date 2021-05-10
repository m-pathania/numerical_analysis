#include<iostream>
#include<vector>
#include<fstream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

double analytical(double t){
    return t + 1;
}

double slope(double t, double y){
    return -100*y + 100*t + 101;
}

int main(){
    double t0{0};            // inital point
    double tn{1};            // point upto which we want to calculate
    double h{0.1};           // step size

    // Analytical Solution
    vector<double> analytical_solution;
    for(double i{t0}; i <= tn; i += h){
        analytical_solution.push_back(analytical(i));
    }

    // First case y(0) = 1
    double y_at_t0{1};      // value of y at t0
    vector<double> first_case{y_at_t0};
    for(double i{t0}; i < tn; i += h){
        double y_at_i{first_case.back() + h*slope(i, first_case.back())};
        first_case.push_back(y_at_i);
    }

    // Second case y(0) = 0.99
    y_at_t0 = 0.99;      // value of y at t0
    vector<double> second_case{y_at_t0};
    for(double i{t0}; i < tn; i += h){
        double y_at_i{second_case.back() + h*slope(i, second_case.back())};
        second_case.push_back(y_at_i);
    }

    // Third Case y(0) = 1.01
    y_at_t0 = 1.01;      // value of y at t0
    vector<double> third_case{y_at_t0};
    for(double i{t0 }; i < tn; i += h){
        double y_at_i{third_case.back() + h*slope(i, third_case.back())};
        third_case.push_back(y_at_i);
    }

    // Printing Obtained Solutions
    cout << "t\t\tAnalytical\ty(0) = 1\ty(0) = 0.99\t\ty(0) = 1.01" << endl; 
    for(size_t i{0}; i < analytical_solution.size(); i++){
        cout << (t0 + h*i) << "\t\t" << analytical_solution[i] << "\t\t" << first_case[i]
             << "\t\t" << second_case[i] << "\t\t\t" << third_case[i] << endl;
    }

    std::ofstream outputfile("output_data.dat");
    if(outputfile.is_open()){
        outputfile << "t\tAnalytical\ty(0) = 1\ty(0) = 0.99\ty(0) = 1.01" << endl; 
        for(size_t i{0}; i < analytical_solution.size(); i++){
            outputfile << (t0 + h*i) << "\t" << analytical_solution[i] << "\t" << first_case[i]
                << "\t" << second_case[i] << "\t" << third_case[i] << endl;
        }
    }else{
        cout << "Unable to write ouput_data.dat" << endl;
    }

    outputfile.close();

    return 0;
}