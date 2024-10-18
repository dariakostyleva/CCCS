#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std;
// *** This macro ***
// --- calculates N0 and Nsamez in histos from *_id_m_hist.root

void calculate_cc(){
	TString path("/data.local2/S533_June21_data/s533jun21/roots/");
	TString name("s533_51_empty_0086"); 
	TString fileNameHist;
	const char * path1 = path.Data();
	const char * name1 = name.Data();
	fileNameHist.Form("%s%s_id_hist.root", path1,name1); 

	gStyle->SetTitleSize(0.06, "t");
    gStyle->SetLabelSize(0.06, "XYZ");
    gStyle->SetTitleSize(0.06, "X");  // Set the X-axis title size
    gStyle->SetTitleSize(0.06, "Y");
    gStyle->SetStatFontSize(0.06); 
    gStyle->SetOptStat(0);

	TFile *file = new TFile(fileNameHist,"READ");
	cout<< "Processing: " << fileNameHist <<endl;
	TH1F *h_z2_cut = (TH1F*)file->Get("h_z2_cut");
	TH2F *h_id_cut = (TH2F*)file->Get("h_id_cut");

	TCanvas *c = new TCanvas("c", "ID canvas", 0, 0, 800, 600);
	c->Divide(1,2);
	c->cd(1);
	h_id_cut->Draw("COLZ");
	c->cd(2);
	gPad->SetLogy();
	h_z2_cut->SetLineColor(kRed);
	h_z2_cut->GetXaxis()->SetTitle("Z2 MUSIC42");
	h_z2_cut->Draw();


	TF1 *gaus = new TF1("gaus", "gaus", 7.5, 8.5);
	gaus->SetLineColor(kBlack); 
	h_z2_cut->Fit(gaus,"Q");

	TLegend *l2 = new TLegend(0.3, 0.3, 0.7, 0.7);
    l2->AddEntry(h_z2_cut, "Z2 with condition on incoming beam", "l");
    l2->AddEntry(gaus, "Gaussian fit", "l");
    l2->Draw();

    // Get the fit parameters
    double mean = gaus->GetParameter(1);
    double sigma = gaus->GetParameter(2);

    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Sigma: " << sigma << std::endl;

    // Define the selection range as mean ± 3.5 * sigma
    double lower_bound = mean - 3.5 * sigma;
    //double upper_bound = mean + 10 * sigma;
    double upper_bound = 10;

    std::cout << "Selection range: [" << lower_bound << ", " << upper_bound << "]" << std::endl;

    // Calculate the number of entries within this range
    int bin_lower = h_z2_cut->FindBin(lower_bound);
    int bin_upper = h_z2_cut->FindBin(upper_bound);

    double int_sel = h_z2_cut->Integral(bin_lower, bin_upper);
    double int_tot = h_z2_cut->Integral();
    double int_N0 = h_id_cut->Integral();

    std::cout << "Number of entries total: " << int_tot << std::endl;
    std::cout << "Number of entries within selection: " << int_sel << std::endl;

	std::cout << "+++++++++++++++++++" << std::endl;
    std::cout << "N0: " << int_N0 << std::endl;
    std::cout << "NsameZ: " << int_sel << std::endl;
    std::cout << "Ratio: " << int_sel/int_N0 << std::endl;
    std::cout << "+++++++++++++++++++" << std::endl;

    // Draw vertical line at the lower bound with a very large upper limit
    double y_max = h_z2_cut->GetMaximum();

    TLine *line1 = new TLine(lower_bound, 0, lower_bound, h_z2_cut->GetMaximum());
    line1->SetLineColor(kBlue);
    line1->SetLineStyle(2);
    line1->SetLineWidth(2);
    line1->Draw();

    // Draw vertical line at the upper bound
    TLine *line2 = new TLine(upper_bound, 0, upper_bound, h_z2_cut->GetMaximum());
    line2->SetLineColor(kBlue);
    line2->SetLineStyle(2);
    line2->SetLineWidth(2);
    line2->Draw();

    TBox *b2 = new TBox(lower_bound, 0, upper_bound, h_z2_cut->GetMaximum());
    b2->SetFillColorAlpha(kRed, 0.9);  // Semi-transparent red
    b2->SetFillStyle(3003);
    b2->Draw();


}