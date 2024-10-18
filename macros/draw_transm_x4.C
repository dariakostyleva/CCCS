#include <TGraphErrors.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <cmath> 

void draw_transm_x4(){

    std::ifstream file_in("s533_51_gC_12mm_0090_transm_x4.txt");
    std::ifstream file_out("s533_51_empty_0086_transm_x4.txt");
    Int_t fitlim1 = -12;
    Int_t fitlim2 = 25;
    
    if (!file_in.is_open() && !file_out.is_open()) {
        std::cerr << "Error: Could not open txt files" << std::endl;
        return;
    }

    std::vector<double> X_in, Xerr_in, Y_in, Yerr_in;
    std::vector<double> X_out, Xerr_out, Y_out, Yerr_out;
    std::vector<double> N0_in_vector, N0_out_vector;
    double num1_in, num2_in, N0_in, Nsamez_in;
    double num1_out, num2_out, N0_out, Nsamez_out;
    double t_12mm_gC = 8.87948E+22; // 1/cm2
    double t_12mm_gC_err = 5.44607E+19; // std of t_12mm_gC
    double cons = 1e27; //cm2 to mbarn

    // Read TARGET file
    while (file_in >> num1_in >> num2_in >> N0_in >> Nsamez_in) {
        double x_in = (num1_in + num2_in) / 2.0;
        double x_err_in = std::abs(num1_in - x_in);
        double y_in = Nsamez_in / N0_in;
        double y_err_in = Nsamez_in/N0_in * sqrt((1-Nsamez_in/N0_in)/(N0_in*Nsamez_in/N0_in));
        X_in.push_back(x_in);
        Y_in.push_back(y_in);
        Xerr_in.push_back(x_err_in);
        Yerr_in.push_back(y_err_in);
        N0_in_vector.push_back(N0_in);
    }
    file_in.close();
    int n_in = Y_in.size();

    // Read NO TARGET file
    while (file_out >> num1_out >> num2_out >> N0_out >> Nsamez_out) {
        double x_out = (num1_out + num2_out) / 2.0;
        double x_err_out = std::abs(num1_out - x_out);
        double y_out = Nsamez_out / N0_out;
        double y_err_out = Nsamez_out/N0_out * sqrt((1-Nsamez_out/N0_out)/(N0_out*Nsamez_out/N0_out));
        X_out.push_back(x_out);
        Y_out.push_back(y_out);
        Xerr_out.push_back(x_err_out);
        Yerr_out.push_back(y_err_out);
        N0_out_vector.push_back(N0_out);
    }
    file_out.close();
    int n_out = Y_out.size();
    std::vector<double> CC(n_out);
    std::vector<double> CC_err(n_out);

    // Print Y_out
    for (double val1 : Y_out) {
        std::cout << "Y_out: " << val1 << " "<< std::endl;
    }

    // Print Y_in
    for (double val2 : Y_in) {
        std::cout << "Y_in: " << val2 << " "<< std::endl;
    }

    // Calculate cross section by dividing vetors
    for (size_t i = 0; i < n_out; ++i) {
        //std::cout << "I am here: at " << i << " "<< std::endl;
        CC[i] = (1/t_12mm_gC)*std::log(Y_out[i]/Y_in[i])*cons;
        //CC[i] = Y_in[i]/Y_out[i];
        //CC_err[i] = std::sqrt(((1-Y_in[i])/(N0_in_vector[i]*Y_in[i])+(1-Y_out[i])/(N0_out_vector[i]*Y_out[i]))*(1/(CC[i]*t_12mm_gC*1/cons))^2 + (t_12mm_gC_err/t_12mm_gC)^2)*CC[i];
        double term1 = (1 - Y_in[i]) / (N0_in_vector[i] * Y_in[i]) + (1 - Y_out[i]) / (N0_out_vector[i] * Y_out[i]);
        double term2 = 1 / (CC[i] * t_12mm_gC * (1 / cons));
        double error_term1 = term1 * std::pow(term2, 2);
        double error_term2 = std::pow(t_12mm_gC_err / t_12mm_gC, 2);
        CC_err[i] = std::sqrt(error_term1 + error_term2) * CC[i];
    }

    // Print CC
    for (double val3 : CC) {
        std::cout << "CC: " << val3 << " "<< std::endl;
    }

    for (double val4 : CC_err) {
        std::cout << "CC_err: " << val4 << " "<< std::endl;
    }


    // Create a TGraphErrors object
    //int n = X_in.size();  // Number of points
    TGraphErrors* graph_in = new TGraphErrors(n_in, &X_in[0], &Y_in[0], &Xerr_in[0], &Yerr_in[0]);
    TGraphErrors* graph_out = new TGraphErrors(n_out, &X_out[0], &Y_out[0], &Xerr_out[0], &Yerr_out[0]);

    TGraphErrors* graph_cccs = new TGraphErrors(n_out, &X_out[0], &CC[0], &Xerr_out[0], &CC_err[0]);

    // Set graph_in style
    //graph_in->SetTitle("Transmisstion ratio");
    graph_in->SetMarkerStyle(21);
    graph_in->SetMarkerColor(kRed);
    graph_in->SetMarkerSize(1);
    graph_in->SetLineWidth(2);
    graph_in->GetXaxis()->SetTitle("X at S4");
    graph_in->GetYaxis()->SetTitle("Transmission");

    graph_out->SetMarkerStyle(21);
    graph_out->SetMarkerColor(kBlue);
    graph_out->SetMarkerSize(1);
    graph_out->SetLineWidth(2);
    graph_out->GetXaxis()->SetTitle("X at S4");
    graph_out->GetYaxis()->SetTitle("Transmission");

    graph_cccs->SetMarkerStyle(21);
    graph_cccs->SetMarkerColor(kGreen);
    graph_cccs->SetMarkerSize(1);
    graph_cccs->SetLineWidth(2);
    graph_cccs->GetXaxis()->SetTitle("X at S4");
    graph_cccs->GetYaxis()->SetTitle("CCCS, mbarn");

    //TF1 *linfit = new TF1("linfit", "[0] + [1]*x", -9, 9);
    TF1 *linfit = new TF1("linfit", "pol0", fitlim1, fitlim2);
    graph_cccs->Fit(linfit, "R");
    double a = linfit->GetParameter(0);
    //double b = linfit->GetParameter(1);
    double aErr = linfit->GetParError(0);
    //double bErr = linfit->GetParError(1);


    // Draw the graph_in
    TCanvas* c = new TCanvas("c", "graph_in with Errors", 800, 800);
    c->Divide(2,2);
    c->cd(1);
    graph_out->Draw("AP");  
    TLine *line1 = new TLine(fitlim1, 0, fitlim1, 1);
    line1->SetLineColor(kBlue);
    line1->SetLineStyle(2);
    line1->SetLineWidth(2);
    line1->Draw("same");
    TLine *line2 = new TLine(fitlim2, 0, fitlim2, 1);
    line2->SetLineColor(kBlue);
    line2->SetLineStyle(2);
    line2->SetLineWidth(2);
    line2->Draw("same");
    TLegend *l = new TLegend(0.3, 0.3, 0.4, 0.4);
    l->AddEntry(graph_in, "R_in", "lp");
    l->AddEntry(graph_out, "R_out", "lp"); 
    l->Draw("same");  
    c->cd(3);
    graph_in->Draw("AP"); 
    line1->Draw("same");
    line2->Draw("same");
    l->Draw("same");
    
    c->cd(2);
    graph_cccs->Draw("AP");
    TLegend *lc = new TLegend(0.1, 0.1, 0.6, 0.6);
    lc->AddEntry(graph_cccs, "CCCS of 15O in 12 mm gC", "lp");
    lc->AddEntry(linfit, Form("Fit: %.3f * x ", a), "l");
    lc->Draw("same");

    //TCanvas* cc = new TCanvas("cc", "graph_in with Errors", 800, 600);
    //graph_out->Draw("");


    
    //l2->AddEntry(gaus_Z2, "Gaussian fit", "l");

    //c->SaveAs("graph_with_errors.png");  // Save the graph_in as an image (optional)
}
