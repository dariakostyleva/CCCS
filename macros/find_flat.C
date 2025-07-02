#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TH1F.h>
#include <iostream>
#include <vector>
#include <cmath>

void findFlatRegion(TGraphErrors* graph_in) {
    // Number of points in the graph
    int n_points = graph_in->GetN();
    
    // Vectors to store the x, y values and the derivative
    std::vector<double> X, Y, Derivative;
    
    // Get the X and Y values from the graph
    for (int i = 0; i < n_points; i++) {
        double x, y;
        graph_in->GetPoint(i, x, y);
        X.push_back(x);
        Y.push_back(y);
    }

    // Calculate the derivative (finite difference method)
    for (int i = 1; i < n_points - 1; i++) {
        double derivative = (Y[i+1] - Y[i-1]) / (X[i+1] - X[i-1]);
        Derivative.push_back(derivative);
        std::cout << derivative << " derivative \n";
    }

    // Find the flat regions (where the derivative is close to zero)
    double threshold = 2;  // Derivative threshold for "flatness"
    std::vector<int> flat_indices;

    for (int i = 1; i < Derivative.size() - 1; i++) {
        if (std::abs(Derivative[i]) <= threshold) {
            flat_indices.push_back(i);
        }
    }

    // Visualize the graph with lines marking the flat regions
    TCanvas* c1 = new TCanvas("c1", "Derivative Flat Region", 800, 600);
    graph_in->Draw("AP");

    for (size_t i = 0; i < flat_indices.size(); i++) {
        // Mark flat regions with vertical lines
        TLine* line = new TLine(X[flat_indices[i]], Y[flat_indices[i]] - 1, X[flat_indices[i]], Y[flat_indices[i]] + 1);
        line->SetLineColor(kRed);
        line->SetLineStyle(2);  // Dashed lines for flat regions
        line->Draw();
    }

    // Optionally, print the flat region indices
    std::cout << "Flat regions found at indices: ";
    for (size_t i = 0; i < flat_indices.size(); i++) {
        std::cout << flat_indices[i] << " ";
    }
    std::cout << std::endl;
}

void exampleFlatRegion() {
    // Example data: X, Y, Xerror, Yerror
    const int n_in = 10;
    double X_in[n_in] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    double Y_in[n_in] = {10, 12, 15, 18, 20, 20, 19, 18, 15, 10};
    double Xerr_in[n_in] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    double Yerr_in[n_in] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

    // Create a TGraphErrors object
    TGraphErrors* graph_in = new TGraphErrors(n_in, X_in, Y_in, Xerr_in, Yerr_in);

    // Call the function to find flat regions
    findFlatRegion(graph_in);
}

