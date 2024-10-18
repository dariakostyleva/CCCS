#include <TCanvas.h>
#include <TGraphErrors.h>
// *** This macro ***
// --- intermediate stuff
// --- compares ccs calculated for 15,16O ain gC

void draw_CC_gC(){
    // Number of data points
    const int n = 2;

    // Define data points (x, y) and their errors (ex, ey)
    double x[n]  = {5.89909, 11.801295};      // x values
    double ex[n] = {0,0};  // x errors
    double y_16O[n]  = {689.2302473, 676.0817587};  // y values
    double ey_16O[n] = {10.65448958, 9.336238912};  // y errors
    double y_15O[n]  = {716.5773158, 704.8511362};  // y values  
    double ey_15O[n] = {19.31184481, 12.51058128};  // y errors

    // Create a TGraphErrors object
    TGraphErrors* gr_16O = new TGraphErrors(n, x, y_16O, ex, ey_16O);
    TGraphErrors* gr_15O = new TGraphErrors(n, x, y_15O, ex, ey_15O);

    // Customize the graph appearance
    gr_16O->SetMarkerStyle(21);
    gr_16O->SetMarkerSize(1);
    gr_16O->SetMarkerColor(kBlue);
    gr_16O->SetLineColor(kBlue);
    gr_16O->SetLineWidth(2);
    gr_16O->GetXaxis()->SetTitle("thickness of gC, mm");
    gr_16O->GetYaxis()->SetTitle("sigma_cc, mbarn");
    // Customize the graph appearance
    gr_15O->SetMarkerStyle(21);
    gr_15O->SetMarkerSize(1);
    gr_15O->SetMarkerColor(kRed);
    gr_15O->SetLineColor(kRed);
    gr_15O->SetLineWidth(2);

    // Create a canvas to draw the graph
    TCanvas* c1 = new TCanvas("c1", "Graphs with Error Bars", 800, 600);
    c1->SetGrid();
    gr_16O->SetMinimum(650); // Set the minimum value for the y-axis
    gr_16O->SetMaximum(750);

    // Draw the graph with error bars
    gr_16O->Draw("AP");
    gr_15O->Draw("P same");

    // Create a legend to distinguish the graphs
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(gr_16O, "16O", "p");
    legend->AddEntry(gr_15O, "15O", "p");
    legend->Draw();

    // Update the canvas to display the graphs
    c1->Update();

}
