#include <TCanvas.h>
#include <TGraphErrors.h>
// *** This macro ***
// --- intermediate stuff
// --- compares ccs calculated for 15,16O ain gC

void draw_CC_new(){
    // Number of data points
    const int n_gC = 2;
    const int n_C = 1;

    // Define data points (x, y) and their errors (ex, ey)
    double x_gC[n_gC]  = {5.89909, 11.801295};      // x values
    double ex_gC[n_gC] = {0.006294,0.007238109145};  // x errors
    double y_16O_gC[n_gC]  = {740.757,714.258};  // y values
    double ey_16O_gC[n_gC] = {8.06902, 6.37335};  // y errors

    double x_C[n_C]  = {13.704};      // x values
    double ex_C[n_C] = {0.014};
    double y_16O_C[n_C]  = {727.916};  // y values
    double ey_16O_C[n_C] = {5.12683};  // y errors
    //double y_15O[n]  = {716.5773158, 704.8511362};  // y values  
    //double ey_15O[n] = {19.31184481, 12.51058128};  // y errors

    // Create a TGraphErrors object
    TGraphErrors* gr_16O_gC = new TGraphErrors(n_gC, x_gC, y_16O_gC, ex_gC, ey_16O_gC);
    TGraphErrors* gr_16O_C = new TGraphErrors(n_C, x_C, y_16O_C, ex_C, ey_16O_C);
    //TGraphErrors* gr_15O = new TGraphErrors(n, x, y_15O, ex, ey_15O);

    // Customize the graph appearance
    gr_16O_gC->SetMarkerStyle(21);
    gr_16O_gC->SetMarkerSize(1);
    gr_16O_gC->SetMarkerColor(kBlue);
    gr_16O_gC->SetLineColor(kBlue);
    gr_16O_gC->SetLineWidth(2);
    gr_16O_gC->GetXaxis()->SetTitle("thickness of target, mm");
    gr_16O_gC->GetYaxis()->SetTitle("sigma_cc, mbarn");

    gr_16O_C->SetMarkerStyle(21);
    gr_16O_C->SetMarkerSize(1);
    gr_16O_C->SetMarkerColor(kRed);
    gr_16O_C->SetLineColor(kRed);
    gr_16O_C->SetLineWidth(2);
    // Customize the graph appearance
    /*
    gr_15O->SetMarkerStyle(21);
    gr_15O->SetMarkerSize(1);
    gr_15O->SetMarkerColor(kRed);
    gr_15O->SetLineColor(kRed);
    gr_15O->SetLineWidth(2);
    */

    // Create a canvas to draw the graph
    TCanvas* c1 = new TCanvas("c1", "Graphs with Error Bars", 800, 600);
    c1->SetGrid();
    gr_16O_gC->SetMinimum(700); // Set the minimum value for the y-axis
    gr_16O_gC->SetMaximum(780);
    gr_16O_gC->GetXaxis()->SetLimits(4, 15);

    // Draw the graph with error bars
    gr_16O_gC->Draw("AP");
    gr_16O_C->Draw("P same");
    //gr_15O->Draw("P same");

    // Create a legend to distinguish the graphs
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(gr_16O_gC, "16O in gC", "p");
    legend->AddEntry(gr_16O_C, "16O in C", "p");
    //legend->AddEntry(gr_15O, "15O", "p");
    legend->Draw();

    // Update the canvas to display the graphs
    c1->Update();

}
