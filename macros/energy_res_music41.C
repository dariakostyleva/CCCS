#include <cmath>
#include <iostream>

void energy_res_music41(){
	TFile *file1 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_51_empty_0086_id.root","READ");//15O
	TTree *tree1 = (TTree*)file1->Get("IdTree");

	TH1F *h_id_z1 =  new TH1F("h_id_z1","h_id_z1",500,4,10);
	h_id_z1->GetXaxis()->SetTitle("Z1 MUSIC41");
	TH1F *h_id_z1_ch =  new TH1F("h_id_z1_ch","h_id_z1_ch",500,500,3000);
	h_id_z1_ch->GetXaxis()->SetTitle("dE MUSIC41");

	gStyle->SetTitleSize(0.05, "t");
    gStyle->SetLabelSize(0.05, "XYZ");
    gStyle->SetTitleSize(0.05, "X");  // Set the X-axis title size
    gStyle->SetTitleSize(0.05, "Y");
    gStyle->SetStatFontSize(0.05); 
    gStyle->SetOptStat(0);
    gStyle->SetTitleFillColor(kWhite); 

	TCanvas *c1_1 = new TCanvas("c1_1", "Comparison of Variables", 800, 600);
    c1_1->Divide(1,2);
    c1_1->cd(1);
    gPad->SetLogy();
    tree1->Draw("id_z1_ch >> h_id_z1_ch"); //target
    TF1 *gaus = new TF1("gaus", "gaus", 7.5, 8.5);
	h_id_z1_ch->Fit(gaus,"Q");
	double mean1 = gaus->GetParameter(1);
    double sigma1 = gaus->GetParameter(2);
    double fwhm1 = 2 * sqrt(2 * log(2)) * sigma1;
    double res_ch = fwhm1/mean1*100;
    printf("mean1 %4.2f\n",mean1);
    printf("res_ch %4.2f\n",res_ch);
    TLatex *latex = new TLatex();
    latex->SetNDC();  // Set normalized coordinates (0-1 relative to the canvas)
    latex->SetTextSize(0.07);  // Set the size of the text

    // Write the fit parameters (mean and sigma) at a specific position on the canvas
    latex->DrawLatex(0.15, 0.80, Form("Oxygen peak resolution ~ %.1f %%", res_ch));


    c1_1->cd(2);
    gPad->SetLogy();
    tree1->Draw("id_z1 >> h_id_z1","",""); //target
    h_id_z1->Fit(gaus,"Q");
    double mean2 = gaus->GetParameter(1);
    double sigma2 = gaus->GetParameter(2);
    double fwhm2 = 2 * sqrt(2 * log(2)) * sigma2;
    double res_Z = fwhm2/mean2*100;
    printf("res_Z %4.2f\n",res_Z);
    latex->DrawLatex(0.15, 0.80, Form("Oxygen peak resolution ~ %.1f %%", res_Z));

}