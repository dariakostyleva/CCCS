#include <TCanvas.h>
#include <TGraphErrors.h>
// *** This macro ***
// --- intermediate stuff
// --- compares ccs calculated from the files with same conditions

void graph_with_error_bars(){
    // Number of data points
    const int n = 7;

    // Define data points (x, y) and their errors (ex, ey)
    double x[n]  = {3,4,5,6,7,8,9};      // x values
    double y[n]  = {736.2400807, 691.4684964, 681.201804, 600.8383098, 689.1893534, 704.8511362, 701.974681};  // y values
    double ex[n] = {0,0,0,0,0,0,0};  // x errors
    double ey[n] = {26.10836702, 26.68922695, 25.191185, 36.58605714, 15.08489025, 12.51058128, 16.01136557};  // y errors

    // Create a TGraphErrors object
    TGraphErrors* gr = new TGraphErrors(n, x, y, ex, ey);

    // Set graph title and axis labels
    gr->SetTitle("Graph with Error Bars;X Axis;Y Axis");

    // Customize the graph appearance
    gr->SetMarkerStyle(21);
    gr->SetMarkerSize(1);
    gr->SetMarkerColor(kBlue);
    gr->SetLineColor(kBlue);

    // Create a canvas to draw the graph
    TCanvas* c1 = new TCanvas("c1", "Graph with Error Bars", 800, 600);
    c1->SetGrid();

    // Draw the graph with error bars
    gr->Draw("AP");

    // Update the canvas to display the graph
    c1->Update();
}
