#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>

void drawTwoGraphs() {
    // Define data for the first graph with errors
    const int nPoints1 = 5;
    double x1[nPoints1] = {1, 2, 3, 4, 5};
    double y1[nPoints1] = {1, 4, 9, 16, 25};
    double ex1[nPoints1] = {0.1, 0.2, 0.1, 0.2, 0.1}; // x errors
    double ey1[nPoints1] = {0.2, 0.4, 0.3, 0.6, 0.5}; // y errors

    // Define data for the second graph with errors
    const int nPoints2 = 5;
    double x2[nPoints2] = {1, 2, 3, 4, 5};
    double y2[nPoints2] = {2, 3, 6, 12, 20};
    double ex2[nPoints2] = {0.1, 0.2, 0.1, 0.2, 0.1}; // x errors
    double ey2[nPoints2] = {0.2, 0.3, 0.2, 0.5, 0.4}; // y errors

    // Create the first graph with errors
    TGraphErrors *graph1 = new TGraphErrors(nPoints1, x1, y1, ex1, ey1);
    graph1->SetLineColor(kBlue);
    graph1->SetLineWidth(2);
    graph1->SetMarkerStyle(21);
    graph1->SetMarkerColor(kBlue);

    // Create the second graph with errors
    TGraphErrors *graph2 = new TGraphErrors(nPoints2, x2, y2, ex2, ey2);
    graph2->SetLineColor(kRed);
    graph2->SetLineWidth(2);
    graph2->SetMarkerStyle(22);
    graph2->SetMarkerColor(kRed);

    // Create a canvas to draw the graphs
    TCanvas *c = new TCanvas("c", "Two Graphs with Errors", 800, 600);

    // Set axis limits before drawing
    c->SetGrid();
    c->DrawFrame(0, 0, 6, 30);  // Set x-axis from 0 to 6 and y-axis from 0 to 30

    // Draw the first graph
    graph1->Draw("AP");  // A = Axis, P = Points (errors will be included automatically)

    // Draw the second graph on the same canvas
    graph2->Draw("P SAME");  // SAME means it will draw on the same canvas

    // Set axis labels
    graph1->GetXaxis()->SetTitle("X Axis");
    graph1->GetYaxis()->SetTitle("Y Axis");

    // Update the canvas
    c->Update();
}
