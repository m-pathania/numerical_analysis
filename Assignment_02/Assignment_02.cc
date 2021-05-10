#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;

class NewtonForm{
    private:
     vector<double> coefficients;
     vector<double> x_values;

    public:
     NewtonForm(const vector<vector<double>> &);
     double evaluate(double, size_t);
     void add_point(double, double);
     void write_data(std::ofstream &);
};

vector<vector<double>> arctan_data(double, double, size_t);

int main(){
    // Newton form polynomial
    vector<vector<double>> initial_data{arctan_data(1, 6, 11)};
    NewtonForm polynomial(initial_data);
    // data where polynomial is to be evaluated
    vector<vector<double>> data{arctan_data(0, 8, 33)};

    // evaluating polynomial
    vector<double> results_2_degree(data.at(0).size(), 0);
    vector<double> results_4_degree{results_2_degree};
    vector<double> results_10_degree{results_2_degree};
    for(size_t ii{}; ii < data.at(0).size(); ++ii){
        results_2_degree.at(ii) = polynomial.evaluate(data.at(0).at(ii),2);
        results_4_degree.at(ii) = polynomial.evaluate(data.at(0).at(ii),4);
        results_10_degree.at(ii) = polynomial.evaluate(data.at(0).at(ii),10);
    }

    std::ofstream file;

    file.open("coefficients.dat");
    polynomial.write_data(file);
    file.close();

    file.open("data_points.csv");
    file << "x values,Function values" << endl;
    for(size_t ii{}; ii < initial_data.at(0).size(); ii++){
        file << initial_data.at(0).at(ii) << "," << initial_data.at(1).at(ii) << endl;
    }
    file.close();

    file.open("differences_2.csv");
    file << "For 2nd degree Polynomial\n";
    file << "x,arctan(x),obtained_value,(arctan(x) - obtained_value)" << endl;
    cout << "\nFor 2nd degree Polynomial\n";
    cout << "x\t\tarctan(x)\t\tObtained_value\t\tDifference\n";
    for(size_t ii{}; ii < results_2_degree.size(); ii++){
        file << data.at(0).at(ii) <<  "," << data.at(1).at(ii) << "," << results_2_degree.at(ii) << "," << (data.at(1).at(ii) - results_2_degree.at(ii)) << endl;
        cout << data.at(0).at(ii) <<  "\t\t" << data.at(1).at(ii) << "\t\t" << results_2_degree.at(ii) << "\t\t" << (data.at(1).at(ii) - results_2_degree.at(ii)) << endl;
    }
    file.close();

    file.open("differences_4.csv");
    file << "For 4th degree Polynomial\n";
    file << "x,arctan(x),obtained_value,(arctan(x) - obtained_value)" << endl;
    cout << "\nFor 4th degree Polynomial\n";
    cout << "x\t\tarctan(x)\t\tObtained_value\t\tDifference\n";
    for(size_t ii{}; ii < results_4_degree.size(); ii++){
        file << data.at(0).at(ii) <<  "," << data.at(1).at(ii) << "," << results_4_degree.at(ii) << "," << (data.at(1).at(ii) - results_4_degree.at(ii)) << endl;
        cout << data.at(0).at(ii) <<  "\t\t" << data.at(1).at(ii) << "\t\t" << results_4_degree.at(ii) << "\t\t" << (data.at(1).at(ii) - results_4_degree.at(ii)) << endl;
    }
    file.close();

    file.open("differences_10.csv");
    file << "For 10th degree Polynomial\n";
    file << "x,arctan(x),obtained_value,(arctan(x) - obtained_value)" << endl;
    cout << "\nFor 10th degree Polynomial\n";
    cout << "x\t\tarctan(x)\t\tObtained_value\t\tDifference\n";
    for(size_t ii{}; ii < results_10_degree.size(); ii++){
        file << data.at(0).at(ii) <<  "," << data.at(1).at(ii) << "," << results_10_degree.at(ii) << "," << (data.at(1).at(ii) - results_10_degree.at(ii)) << endl;
        cout << data.at(0).at(ii) <<  "\t\t" << data.at(1).at(ii) << "\t\t" << results_10_degree.at(ii) << "\t\t" << (data.at(1).at(ii) - results_10_degree.at(ii)) << endl;
    }
    file.close();

    return 0;
}

vector<vector<double>> arctan_data(double start_point, double end_point,size_t points){
    vector<vector<double>> data(2, vector<double>(points,0));
    double increment{(end_point - start_point)/((double)points - 1)};
    for(size_t ii{}; ii < points; ii++){
        data.at(0).at(ii) = start_point + double(ii)*increment;
        data.at(1).at(ii) = std::atan(data.at(0).at(ii));
    }
    return data;
}

NewtonForm::NewtonForm(const vector<vector<double>> &data): x_values{data.at(0)}, coefficients{data.at(1)}{
    for(size_t ii{1}; ii < coefficients.size(); ii++){
        double denominator{1};
        double numenator{0};
        for(size_t jj{}; jj < ii; jj++){
            double product{1};
            for(size_t kk{}; kk < jj; kk++){
                product *= (data.at(0).at(ii) - data.at(0).at(kk));
            }
            numenator += coefficients.at(jj)*product;
            denominator *= (data.at(0).at(ii) - data.at(0).at(jj));
        }
        coefficients.at(ii) = (data.at(1).at(ii) - numenator)/denominator;
    }
}

double NewtonForm::evaluate(double point, size_t degree){
    if(degree < coefficients.size()){
        double value{coefficients.at(degree)};
        while(degree--){
            value *= (point - x_values.at(degree));
            value += coefficients.at(degree);
        }
        return value;
    }else{
        cout << "Degree to large for the polynomial\n returning -1" << endl;
        return -1;
    }
}

void NewtonForm::add_point(double x, double y){
    x_values.push_back(x);
    size_t ii{coefficients.size()};
    double denominator{1};
    double numenator{0};
    for(size_t jj{}; jj < ii; jj++){
        double product{1};
        for(size_t kk{}; kk < jj; kk++){
            product *= (x - x_values.at(kk));
        }
        numenator += coefficients.at(jj)*product;
        denominator *= (x - x_values.at(jj));
    }
    coefficients.push_back((y - numenator)/denominator);
}

void NewtonForm::write_data(std::ofstream &file){
    cout << "coefficients for 2nd degree polynomial:" << endl;
    file << "coefficients for 2nd degree polynomial:" << endl;
    for(size_t ii{}; ii <= 2; ii++){
        file << "a( " << ii << " ) = " << " " << coefficients.at(ii) << endl;
        cout << "a( " << ii << " ) = " << " " << coefficients.at(ii) << endl;
    }

    cout << "\n\ncoefficients for 4th degree polynomial:" << endl;
    file << "\n\ncoefficients for 4th degree polynomial:" << endl;
    for(size_t ii{}; ii <= 4; ii++){
        file << "a( " << ii << " ) = " << " " << coefficients.at(ii) << endl;
        cout << "a( " << ii << " ) = " << " " << coefficients.at(ii) << endl;
    }

    cout << "\n\ncoefficients for 10th degree polynomial:" << endl;
    file << "\n\ncoefficients for 10th degree polynomial:" << endl;
    for(size_t ii{}; ii <= 10; ii++){
        file << "a( " << ii << " ) = " << " " << coefficients.at(ii) << endl;
        cout << "a( " << ii << " ) = " << " " << coefficients.at(ii) << endl;
    }
}