#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std;
// *** This macro ***
// --- calculates cross section using N0 and Nsamez from txt files

void calculate_cc(){

    //std::ifstream file_out("s533_50_empty_0076_ratios.txt");
    //std::ifstream file_in("s533_50_PE_37mm_0082_ratios.txt");
	std::ifstream file_out("s533_50_empty_0053_ratios.txt");
    //std::ifstream file_in("s533_50_gC_6mm_0045_ratios.txt");
    std::ifstream file_in("s533_50_C_2cm_0048_ratios.txt");
    //std::ifstream file_out("s533_50_water_emp_0055_ratios.txt");
    //std::ifstream file_in("s533_50_water_4cm_0057_ratios.txt");
    //std::ifstream file_in("s533_50_gC_12mm_46-47_ratios.txt");

    std::vector<double> Y_in, Yerr_in;
    std::vector<double> Y_out, Yerr_out;
    std::vector<double> N0_in_vector, N0_out_vector;
    double num1_in, num2_in, N0_in, Nsamez_in;
    double num1_out, num2_out, N0_out, Nsamez_out;
    //double t = 4.42913E+22; // 6 mm gC taregt property, 1/cm2
    //double t_err = 4.72564E+19; // 6 mm gC taregt property, std of t
    //double t = 1.5E+23; // 37 mm PE taregt property, 1/cm2 from ALEX
    //double t_err =   6.86E+19; // 37 mm PE taregt property, std of t from ALEX
    //double t = 8.87948E+22; // taregt property 12 gC, 1/cm2
    //double t_err = 5.44607E+19;
	double t = 1.26429E+23; // 13.7 mm C RIKEN taregt property, 1/cm2
    double t_err = 1.2916E+20; // 13.7 mm C RIKEN taregt property, std of t
    //double t = 1.07177E+23; 	// big water property, 1/cm2
    //double t_err = 3.33678E+20; // big water property, std of t
    double cons = 1e27; //cm2 to mbarn

    // Read TARGET file
    while (file_in >> N0_in >> Nsamez_in) {
        double y_in = Nsamez_in / N0_in;
        double y_err_in = Nsamez_in/N0_in * sqrt((1-Nsamez_in/N0_in)/(N0_in*Nsamez_in/N0_in));
        Y_in.push_back(y_in);
        Yerr_in.push_back(y_err_in);
        N0_in_vector.push_back(N0_in);
    }
    file_in.close();
    int n_in = Y_in.size();

    // Read NO TARGET file
    while (file_out >> N0_out >> Nsamez_out) {
        double y_out = Nsamez_out / N0_out;
        double y_err_out = Nsamez_out/N0_out * sqrt((1-Nsamez_out/N0_out)/(N0_out*Nsamez_out/N0_out));
        Y_out.push_back(y_out);
        Yerr_out.push_back(y_err_out);
        N0_out_vector.push_back(N0_out);
    }
    file_out.close();
    int n_out = Y_out.size();
    std::vector<double> CC(n_out);
    std::vector<double> CC_err(n_out);

    // Calculate cross section by dividing vetors
    for (size_t i = 0; i < n_out; ++i) {
        //std::cout << "I am here: at " << i << " "<< std::endl;
        CC[i] = (1/t)*std::log(Y_out[i]/Y_in[i])*cons;
        double term1 = (1 - Y_in[i]) / (N0_in_vector[i] * Y_in[i]) + (1 - Y_out[i]) / (N0_out_vector[i] * Y_out[i]);
        double term2 = 1 / (CC[i] * t * (1 / cons));
        double error_term1 = term1 * std::pow(term2, 2);
        double error_term2 = std::pow(t_err / t, 2);
        CC_err[i] = std::sqrt(error_term1 + error_term2) * CC[i];
    }

    // Print CC
    for (double val3 : CC) {
        std::cout << "CC: " << val3 << " "<< std::endl;
    }

    for (double val4 : CC_err) {
        std::cout << "CC_err: " << val4 << " "<< std::endl;
    }

	
}