#include <TGraphErrors.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
#include <cmath> 

void draw_transm_y4(){

    std::ifstream file_out("s533_50_empty_53-54_transm_y4.txt");
    std::ifstream file_in("s533_50_gC_12mm_46-47_transm_y4.txt");

    //double t = 4.42913E+22; // taregt property 6 gC, 1/cm2
    //double t_err = 4.72564E+19; // taregt property, std of t

    double t = 8.87948E+22; // taregt property 12 gC, 1/cm2
    double t_err = 5.44607E+19;

    double cons = 1e27; //cm2 to mbarn

    double percentageDifference_limit = 0.2;
    
    if (!file_in.is_open() && !file_out.is_open()) {
        std::cerr << "Error: Could not open txt files" << std::endl;
        return;
    }

    std::vector<double> X_in, Xerr_in, Y_in, Yerr_in;
    std::vector<double> X_out, Xerr_out, Y_out, Yerr_out;
    std::vector<double> N0_in_vector, N0_out_vector;
    double num1_in, num2_in, N0_in, Nsamez_in;
    double num1_out, num2_out, N0_out, Nsamez_out;

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
        //std::cout << "Y_out: " << val1 << " "<< std::endl;
    }

    // Print Y_in
    for (double val2 : Y_in) {
        //std::cout << "Y_in: " << val2 << " "<< std::endl;
    }

    // Calculate cross section by dividing vetors
    for (size_t i = 0; i < n_out; ++i) {
        //std::cout << "I am here: at " << i << " "<< std::endl;
        CC[i] = (1/t)*std::log(Y_out[i]/Y_in[i])*cons;
        //CC[i] = Y_in[i]/Y_out[i];
        //CC_err[i] = std::sqrt(((1-Y_in[i])/(N0_in_vector[i]*Y_in[i])+(1-Y_out[i])/(N0_out_vector[i]*Y_out[i]))*(1/(CC[i]*t*1/cons))^2 + (t_err/t)^2)*CC[i];
        double term1 = (1 - Y_in[i]) / (N0_in_vector[i] * Y_in[i]) + (1 - Y_out[i]) / (N0_out_vector[i] * Y_out[i]);
        double term2 = 1 / (CC[i] * t * (1 / cons));
        double error_term1 = term1 * std::pow(term2, 2);
        double error_term2 = std::pow(t_err / t, 2);
        CC_err[i] = std::sqrt(error_term1 + error_term2) * CC[i];
    }

    // Print CC
    for (double val3 : CC) {
        //std::cout << "CC: " << val3 << " "<< std::endl;
    }

    for (double val4 : CC_err) {
        //std::cout << "CC_err: " << val4 << " "<< std::endl;
    }

    TGraphErrors* graph_in = new TGraphErrors(n_in, &X_in[0], &Y_in[0], &Xerr_in[0], &Yerr_in[0]);
    TGraphErrors* graph_out = new TGraphErrors(n_out, &X_out[0], &Y_out[0], &Xerr_out[0], &Yerr_out[0]);
    TGraphErrors* graph_cccs = new TGraphErrors(n_out, &X_out[0], &CC[0], &Xerr_out[0], &CC_err[0]);

    //*****************************
    //COMPARISON TO CENTRAL REGION !!!!    
    //*****************************

    double sumY = 0;
    int count = 0;
    double averageY = 0; 
    TLine* lineFirst = new TLine();
    TLine* lineLast = new TLine();

    for (int i = 0; i < graph_in->GetN(); ++i) {
        double x, y;
        graph_in->GetPoint(i, x, y);
	//std::cout << "x: " << x << " y "<<y<< std::endl;
        if (x >= -5 && x <= 5) {
            sumY += y;
            ++count;
        }
    }

    if (count > 0) {
        averageY = sumY / count;
        std::cout << "Average of Y values in the range -5 <= X <= 5: " << averageY << std::endl;
    } else {
        std::cout << "No points found in the specified range." << std::endl;
    }
    // Vector to store indices of consecutive close points
    std::vector<int> closePoints;

    // Flag to check if we have found a valid sequence of points
    bool foundSequence = false;
    double x_first, x_last;

    for (int i = 0; i < graph_in->GetN(); ++i) {
        double x, y;
        graph_in->GetPoint(i, x, y);

        // Check if the Y value is within 1% of the average
        double percentageDifference = std::abs(y - averageY) / averageY * 100;

        if (percentageDifference < percentageDifference_limit) {
            std::cout << "percentageDifference = " << percentageDifference  << std::endl;
            std::cout << "X = " << x << ", Y = " << y << std::endl;
            closePoints.push_back(i);

            // Record the first and last X values within the first valid range
            if (!foundSequence && closePoints.size() == 1) {
                x_first = x;  // Set the first X in the range
            }
            x_last = x; // Continuously update to the last X within the sequence
        } else {
            // If a sequence of 5 or more consecutive points was found, stop searching
            if (closePoints.size() >= 5) {
                foundSequence = true;
                std::cout << "Found a range with " << closePoints.size() 
                          << " consecutive points where Y is within "<< percentageDifference_limit 
                          << "% of the average:" << std::endl;
                for (int j : closePoints) {
                    graph_in->GetPoint(j, x, y);
                    std::cout << "X = " << x << ", Y = " << y << std::endl;
                }
                break; // Stop after finding the first valid range
            }
            closePoints.clear();  // Reset for a new sequence
        }
    }

    // Print any remaining sequence if it ends with the last points in the graph
    if (closePoints.size() >= 5) {
        foundSequence = true;
        std::cout << "Found a range with " << closePoints.size() 
                  << " consecutive points where Y is within 1% of the average:" << std::endl;
        for (int j : closePoints) {
            double x, y;
            graph_in->GetPoint(j, x, y);
            std::cout << "X = " << x << ", Y = " << y << std::endl;
        }
    }

    // Draw vertical lines at the first and last X values in the first valid range
    if (foundSequence) {
        lineFirst->SetX1(x_first);
        lineFirst->SetX2(x_first);
        lineFirst->SetY1(graph_in->GetYaxis()->GetXmin());
        lineFirst->SetY2(graph_in->GetYaxis()->GetXmax());
        lineFirst->SetLineColor(kRed);
        lineFirst->SetLineStyle(2);

        lineLast->SetX1(x_last);
        lineLast->SetX2(x_last);
        lineLast->SetY1(graph_in->GetYaxis()->GetXmin());
        lineLast->SetY2(graph_in->GetYaxis()->GetXmax());
        lineLast->SetLineColor(kRed);
        lineLast->SetLineStyle(2);
        lineFirst->SetLineColor(kRed);
        lineFirst->SetLineStyle(2);
        lineLast->SetLineColor(kRed);
        lineLast->SetLineStyle(2);
    } else {
        std::cout << "No range of 5 or more consecutive points found where Y is within 1% of the average." << std::endl;
    }

  
    //*****************************
    //DERIVATIVES !!!!    
    //*****************************
    std::vector<double> Derivative;
    std::vector<int> flat_indices;
    double thresh_deriv = 0.004;  // Derivative threshold for "flatness"
    // Calculate the derivative (finite difference method)
    for (int i = 1; i < n_in - 1; i++) {
        double derivative = (Y_in[i+2] - Y_in[i-2]) / (X_in[i+2] - X_in[i-2]);
        Derivative.push_back(derivative);
        //std::cout << derivative << " derivative \n";
    }
    for (int i = 1; i < Derivative.size() - 1; i++) {
        if (std::abs(Derivative[i]) < thresh_deriv) {
            flat_indices.push_back(i);
        }
    }

    // Optionally, print the flat region indices
    std::cout << "Flat regions found at indices: ";
    for (size_t i = 0; i < flat_indices.size(); i++) {
        std::cout << X_in[flat_indices[i]] << " ";
    }
    std::cout << std::endl;
    
    //*****************************
    //MOVING AVERAGE !!!!    
    //*****************************
    int window = 3;  // Moving average window
    double threshold = 0.004; // Threshold to select "stable" region of transmission
    int consec_num = 5;  // Minimal number of points where transmission should be "stable"
    std::vector<double> Y_in_avr(n_in); // Vector to store the moving average y-values
    // Loop to compute the moving average
    for (int i = 0; i < n_in; ++i) {
        double sum = 0;
        int count = 0;
        // Moving average for the current point (centered)
        for (int j = -window / 2; j <= window / 2; ++j) {
            if ((i + j) >= 0 && (i + j) < n_in) {
                sum += Y_in[i + j];
                count++;
            }
        }
        Y_in_avr[i] = sum / count;  // Store the moving average
    }
    TGraph *graph_in_avg = new TGraph(n_in, &X_in[0], &Y_in_avr[0]);

    std::vector<double> Y_in_avr_diff(n_in); // the modulo of the differences  
    std::vector<double> Y_threshold(n_in); // Vector for threshold comparison result
    // Calculate the modulo of the differences between Y_in and Y_in_avr
    for (int i = 0; i < n_in; ++i) {
        Y_in_avr_diff[i] = fabs(Y_in[i] - Y_in_avr[i]);  // Absolute difference
        // Apply threshold condition
        if (Y_in_avr_diff[i] < threshold) {
            Y_threshold[i] = 1;  // Set to 1 if below threshold
        } else {
            Y_threshold[i] = 0;  // Set to 0 if above threshold
        }
    }
    TGraph* graph_in_diff = new TGraph(n_in, &X_in[0], &Y_in_avr_diff[0]);
    TGraph* graph_threshold = new TGraph(n_in, &X_in[0], &Y_threshold[0]);
    // Finding x of stable y
    int consecutive_count = 0;
    int start_index = -1;           // To store the starting index of the range
    int end_index = -1;             // To store the ending index of the range

     // Loop through Y_threshold to find consecutive 1s
    for (int i = 0; i < n_in; ++i) {
        if (Y_threshold[i] == 1) {
            if (consecutive_count == 0) {
                start_index = i;  // Start a new sequence
            }
            consecutive_count++;
        } else if (Y_threshold[i] == 0) {
            // Check if we found a valid sequence of at least consec_num consecutive 1s
            if (consecutive_count >= consec_num) {
                end_index = i - 1;  // The last index where we had a 1 in the first sequence
            
                // Check that there's exactly one 0, followed by at least 3 consecutive 1s
                if (i + 1 < n_in && Y_threshold[i + 1] == 1) {
                    int secondary_count = 0;
                    int j = i + 1;  // Start checking from the element after the 0
                
                    // Count the second sequence of consecutive 1s
                    while (j < n_in && Y_threshold[j] == 1) {
                        secondary_count++;
                        end_index = j;  // Extend the end_index to each new 1 in this second sequence
                        j++;
                    }

                    // Only keep this extended range if there were at least 3 consecutive 1s after the 0
                    if (secondary_count < 3) {
                        end_index = i - 1;  // Reset to the end of the first sequence if condition isn't met
                    }
                }
                break;  // Stop the loop after finding a valid range
            }
            // Reset if a 0 is found and no valid range has been detected
            consecutive_count = 0;
            start_index = -1;
        }
    }

    // Check again after loop ends (in case last element is part of a valid sequence)
    if (consecutive_count >= consec_num && end_index == -1) {
        end_index = n_in - 1;  // Set the end index to the last element if it wasn't set
    }

    // If we found a valid range, print the corresponding X range
    if (start_index != -1 && end_index != -1) {
        std::cout << "Range where transmission is stable: " << X_in[start_index] << " to " << X_in[end_index] << " mm\n";
    } else {
        std::cout << "No range found with " << consec_num << " consecutive 1s.\n";
    }

    double fitlim1 = X_in[start_index];
    double fitlim2 = X_in[end_index];
    // fitting cccs in the range
    TF1 *fitpol0 = new TF1("fitpol0", "pol0", fitlim1, fitlim2);
    graph_cccs->Fit(fitpol0, "RQ");
    double a = fitpol0->GetParameter(0);
    double aErr = fitpol0->GetParError(0);
    //return;

    //**************************************
    // Plotting
    TCanvas *cc1 = new TCanvas("cc1","COMPARISON TO CENTRAL REGION");
    cc1->Divide(1,2);
    cc1->cd(1);
    graph_in->Draw("AP");
    lineFirst->Draw("same");
    lineLast->Draw("same");
    cc1->cd(2);
    graph_cccs->SetMarkerStyle(21);
    graph_cccs->SetMarkerColor(kGreen);
    graph_cccs->SetMarkerSize(1);
    graph_cccs->SetLineWidth(2);
    graph_cccs->GetXaxis()->SetTitle("X position at S2");
    graph_cccs->GetYaxis()->SetTitle("CCCS, mbarn");
    graph_cccs->Draw("AP");
    TF1 *fitpol0cc = new TF1("fitpol0cc", "pol0", x_first, x_last);
    graph_cccs->Fit(fitpol0cc, "RQ");
    double acc = fitpol0cc->GetParameter(0);
    double aErrcc = fitpol0cc->GetParError(0);
    TLegend *lcc = new TLegend(0.3, 0.3, 0.4, 0.4);
    lcc->AddEntry(graph_cccs, "CCCS of 15O in 12 mm gC", "lp");
    lcc->AddEntry(fitpol0cc, Form("Fit: %.3f * x ", acc), "l");
    lcc->Draw("same");
    lineFirst->Draw("same");
    lineLast->Draw("same");


    TCanvas *c1 = new TCanvas("c1", "DERIVATIVES");
    c1->Divide(2,2);
    c1->cd(1);
    graph_in->SetMarkerStyle(20);
    graph_in->Draw("AP");
    graph_in_avg->SetMarkerStyle(21);
    graph_in_avg->SetMarkerColor(kGreen+3);
    graph_in_avg->Draw("P SAME");
    // Adding a legend to differentiate original graph and moving average
    auto legend = new TLegend(0.1, 0.7, 0.3, 0.9);
    legend->AddEntry(graph_in, "R_in original", "p");
    legend->AddEntry(graph_in_avg, Form("R_in moving average on %d points", window), "p");
    legend->Draw();
    c1->cd(2);
    graph_in_diff->SetMarkerStyle(20);
    graph_in_diff->SetMarkerColor(kBlack);
    graph_in_diff->GetXaxis()->SetTitle("Y position at S4");
    graph_in_diff->GetYaxis()->SetTitle("Absolute difference");
    graph_in_diff->Draw("AP");  
    // Add a horizontal line at the threshold value
    TLine* threshold_line = new TLine(X_in[0], threshold, X_in[n_in-1], threshold);
    threshold_line->SetLineColor(kBlack);  // Set the color of the line
    threshold_line->SetLineStyle(2);       // Set dashed line
    threshold_line->SetLineWidth(2);       // Set line width
    threshold_line->Draw("SAME"); 
    c1->cd(3);
    graph_threshold->SetMarkerStyle(20);
    graph_threshold->SetMarkerColor(kBlack);
    graph_threshold->GetXaxis()->SetTitle("Y position at S4");
    graph_threshold->GetYaxis()->SetTitle("Threshold crossing");
    graph_threshold->Draw("AP");  
    c1->cd(4);
    graph_in->Draw("AP");
    for (size_t i = 0; i < flat_indices.size(); i++) {
        // Mark flat regions with vertical lines
        TLine* line = new TLine(X_in[flat_indices[i]], Y_in[flat_indices[i]] - 1, X_in[flat_indices[i]], Y_in[flat_indices[i]] + 1);
        line->SetLineColor(kRed);
        line->SetLineStyle(2);  // Dashed lines for flat regions
        line->Draw();
    }

    TCanvas* c = new TCanvas("c", "MOVING AVERAGE");
    c->Divide(2,2);
    c->cd(1);
    graph_out->SetMarkerStyle(21);
    graph_out->SetMarkerColor(kBlue);
    graph_out->SetMarkerSize(1);
    graph_out->SetLineWidth(2);
    graph_out->GetXaxis()->SetTitle("Y position at S4");
    graph_out->GetYaxis()->SetTitle("Transmission");
    graph_out->GetYaxis()->SetRangeUser(0.9, 1.01);
    graph_out->Draw("AP");// "B" for axis, "P" for points with errors
    TLine *line1 = new TLine(fitlim1, 0.9, fitlim1, 1);
    line1->SetLineColor(kBlue);
    line1->SetLineStyle(2);
    line1->SetLineWidth(2);
    line1->Draw();
    TLine *line2 = new TLine(fitlim2, 0.9, fitlim2, 1);
    line2->SetLineColor(kBlue);
    line2->SetLineStyle(2);
    line2->SetLineWidth(2);
    line2->Draw();
    TLegend *lo = new TLegend(0.3, 0.3, 0.4, 0.4);
    lo->AddEntry(graph_out, "R_out", "lp"); 
    lo->AddEntry(line1, "Limits for stable transission", "l");  
    lo->Draw("same");
    c->cd(3);
    graph_in->SetMarkerStyle(21);
    graph_in->SetMarkerColor(kRed);
    graph_in->SetMarkerSize(1);
    graph_in->SetLineWidth(2);
    graph_in->GetXaxis()->SetTitle("Y position at S4");
    graph_in->GetYaxis()->SetTitle("Transmission");
    graph_in->GetYaxis()->SetRangeUser(0.9, 1.01);
    graph_in->Draw("AP"); 
    line1->Draw();
    line2->Draw(); 
    TLegend *li = new TLegend(0.3, 0.3, 0.4, 0.4);
    li->AddEntry(graph_in, "R_in", "lp");
    li->AddEntry(line1, "Limits for stable transission", "l"); 
    li->Draw("same");
    c->cd(2);
    graph_cccs->SetMarkerStyle(21);
    graph_cccs->SetMarkerColor(kGreen);
    graph_cccs->SetMarkerSize(1);
    graph_cccs->SetLineWidth(2);
    graph_cccs->GetXaxis()->SetTitle("Y position at S4");
    graph_cccs->GetYaxis()->SetTitle("CCCS, mbarn");
    graph_cccs->Draw("AP");
    TLegend *lc = new TLegend(0.3, 0.3, 0.4, 0.4);
    lc->AddEntry(graph_cccs, "CCCS of 15O in 12 mm gC", "lp");
    lc->AddEntry(fitpol0, Form("Fit: %.3f * x ", a), "l");
    lc->Draw("same");
}

 //SLICES !!!!
    /*
    int sliceWidth = 3; double chiSqThreshold = 1.0;
    int nPoints = graph_in->GetN();
    TCanvas *c1 = new TCanvas("c1", "Fit slices", 800, 600);
    graph_in->Draw("AP"); // Draw the graph with error bars
    int firstX = graph_in->GetX()[0];
    double lastX = graph_in->GetX()[graph_in->GetN() - 1];
    int nSlices = nPoints / sliceWidth;
    std::cout << "firstX  " << firstX <<endl;
    std::cout << "lastX  " << lastX <<endl;
    std::cout << "nPoints  " << nPoints <<endl;
    std::cout << "nSlices  " << nSlices <<endl;
    TCanvas *sliceCanvas = new TCanvas("sliceCanvas", "Slice Graphs", 1200, 800);
    int nCols = TMath::CeilNint(sqrt(nSlices)); // Number of columns
    int nRows = TMath::CeilNint((double)nSlices / nCols); // Number of rows
    sliceCanvas->Divide(nCols, nRows); // Divide canvas into subplots
    std::cout << "nCols  " << nCols <<endl;
    std::cout << "nRows  " << nRows <<endl;
    int sliceIndex = 1; // Initialize slice index to 1
    std::vector<double> fitValues;
    std::vector<double> fitErrors;

    // Loop through slices of the graph
    for (int i = firstX; i <= lastX; i += sliceWidth) {
        sliceCanvas->cd(sliceIndex); // Switch to the current subplot
        std::cout << "sliceIndex  " << sliceIndex <<endl;
        // Create arrays for the slice data
        double *xSlice = new double[sliceWidth];
        double *ySlice = new double[sliceWidth];
        double *exSlice = new double[sliceWidth];
        double *eySlice = new double[sliceWidth];
        
        
        // Find the starting index in the graph for the current x value i
        int startIdx = -1;
        for (int k = 0; k < nPoints; ++k) {
            double xVal;
            graph_in->GetPoint(k, xVal, ySlice[0]); // Get x value from the graph
            if (xVal >= i) {
                startIdx = k;
                break; // Found the first index with x >= i
            }
        }

        // Collect points within the slice range
        int count = 0;
        for (int j = startIdx; j < nPoints && count < sliceWidth; ++j) {
            double xVal;
            graph_in->GetPoint(j, xVal, ySlice[count]);
            if (xVal >= i && xVal < i + sliceWidth) {
                xSlice[count] = xVal;
                exSlice[count] = graph_in->GetEX()[j];
                eySlice[count] = graph_in->GetEY()[j];
                count++;
            }
        }
        
        // Create a new TGraphErrors for the slice
        TGraphErrors *sliceGraph = new TGraphErrors(sliceWidth, xSlice, ySlice, exSlice, eySlice);
        sliceGraph->SetMinimum(0.9); // Set the minimum y value
        sliceGraph->SetMaximum(1.0); // Set the maximum y value
        sliceGraph->SetMarkerColor(kBlue);
        sliceGraph->SetMarkerStyle(20);
        sliceGraph->Draw("");

        
        // Fit a constant (flat) line to the current slice
        TF1 *fitFunc = new TF1("fitFunc", "pol0", sliceGraph->GetX()[0], sliceGraph->GetX()[sliceWidth - 1]);
        sliceGraph->Fit(fitFunc, "R");
        double fitValue = fitFunc->GetParameter(0);
        double fitError = fitFunc->GetParError(0);

        fitValues.push_back(fitValue);
        fitErrors.push_back(fitError);
        
        // Get the chi-square of the fit
        double chiSq = fitFunc->GetChisquare();
        int ndf = fitFunc->GetNDF();
        double chiSqNDF = (ndf > 0) ? chiSq / ndf : 0;

        // Create a TPaveText to display fit parameters
        TPaveText *paveText = new TPaveText(0.2, 0.5, 0.8, 1.0, "NDC");
        paveText->SetFillColor(0); // No fill
        paveText->SetBorderSize(0); // No border
        paveText->AddText(Form("Fit Value: %.3f #pm %.3f\n chi^2/ndf = %.3f", fitValue, fitError,chiSqNDF));

        // Draw the TPaveText on the canvas
        paveText->Draw();

        //std::cout << "Slice from point " << i << " to " << i + sliceWidth - 1 
                 // << ": chi^2/ndf = " << chiSqNDF << std::endl;
        
        // Highlight flat regions (based on chi-square threshold)
        if (chiSqNDF < chiSqThreshold) {
            std::cout << "Flat region found in slice: " << i << " to " << i + sliceWidth - 1 << std::endl;
            TLine *line = new TLine(sliceGraph->GetX()[0], fitFunc->GetParameter(0), 
                                     sliceGraph->GetX()[sliceWidth - 1], fitFunc->GetParameter(0));
            line->SetLineColor(kRed);
            line->Draw("same");
        }

        // Move to the next slice index
        sliceIndex++;

        // Clean up
        delete[] xSlice;
        delete[] ySlice;
        delete[] exSlice;
        delete[] eySlice;
        delete sliceGraph;
    }
    std::cout << "sliceIndex  " << sliceIndex <<endl;

    TH1F *fitValueHist = new TH1F("fitValueHist", "Fit Values", 1000, 0.9, 1.0); // Adjust range as needed
    for (size_t k = 0; k < fitValues.size(); ++k) {
        fitValueHist->Fill(fitValues[k]);
    }
    sliceCanvas->cd(sliceIndex);
    fitValueHist->Draw();
    */
