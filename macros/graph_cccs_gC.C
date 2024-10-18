#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TAxis.h>
// *** This macro ***
// --- intermediate stuff
// --- compares ccs calculated from the files with same conditions

void graph_cccs_gC(){
    // Number of data points
    const int n1 = 2;
    const int n2 = 2;

    // Define data points (x, y) and their errors (ex, ey)
    double tt1[n1]  = {5.89909, 11.801295};      // target thickness
    double ett1[n1] = {0.006294, 0.007238109145};  // error on target thickness
    double tt2[n1]  = {5.89909, 11.801295};      // target thickness
    double ett2[n1] = {0.006294, 0.007238109145};  // error on target thickness

    double cccs_16O[n1]  = {666.1536062, 682.3309948};  // charge changing cross section
    double ecccs_16O[n1] = {23.32089078, 13.87533335};  // error on cccs

    double cccs_15O[n2]  = {719.1746524, 718.7425425};  // charge changing cross section
    double ecccs_15O[n2] = {30.1471803, 19.92461423};  // error on cccs
    // Create a TGraphErrors object
    TGraphErrors* gr_16O = new TGraphErrors(n1, tt1, cccs_16O, ett1, ecccs_16O);
    gr_16O->SetLineColor(kBlue);
    gr_16O->SetLineWidth(2);
    gr_16O->SetMarkerStyle(21);
    gr_16O->SetMarkerSize(2);
    gr_16O->SetMarkerColor(kBlue);

    TGraphErrors* gr_15O = new TGraphErrors(n2, tt2, cccs_15O, ett2, ecccs_15O);
    gr_15O->SetLineColor(kRed);
    gr_15O->SetLineWidth(2);
    gr_15O->SetMarkerStyle(22);
    gr_15O->SetMarkerSize(2);
    gr_15O->SetMarkerColor(kRed);


    // Create a canvas to draw the graph
    TCanvas* c1 = new TCanvas("c1", "Graph with Error Bars", 800, 600);
    c1->SetGrid();

    // Draw the graph with error bar
    gr_15O->Draw("AP");
    gr_16O->Draw("P same");

    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9); // Position (x1, y1, x2, y2)
    legend->AddEntry(gr_15O, "^{15}O in gC target, 370 MeV/u", "lep"); // "lep" means line, error bars, and points
    legend->AddEntry(gr_16O, "^{16}O in gC target, 370 MeV/u", "lep"); // "lep" means line, error bars, and points
    legend->SetFillColor(0); // Set legend background to transparent
    legend->Draw(); // Draw the legend on the canvas

    gr_15O->GetXaxis()->SetLimits(4, 14);
    gr_16O->GetYaxis()->SetRangeUser(600, 800);
    gr_15O->GetYaxis()->SetRangeUser(600, 800);
    gr_15O->GetXaxis()->SetTitle("Target thickness, mm");
    gr_15O->GetYaxis()->SetTitle("CCCS, mbarn");

    // Update the canvas to display the graph
    c1->Update();
}
