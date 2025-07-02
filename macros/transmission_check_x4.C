#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std;
#include <fstream>
// *** This macro ***
// --- 
// --- 

void transmission_check_x4(){

	TString path("/data.local2/S533_June21_data/s533jun21/roots/");
	//TString name("s533_50_empty_53-54"); 
	TString name("s533_50_gC_12mm_46-47");
	TString fileNameId, fileTransmOut;
	const char * path1 = path.Data();
	const char * name1 = name.Data();
	fileNameId.Form("%s%s_id_m.root", path1,name1);   
	//fileNameHist.Form("%s%s_id_hist.root", path1,name1); 
	TFile *file = new TFile(fileNameId,"READ");
	TTree *tree = (TTree*)file->Get("IdTree");
  	Long64_t nentries = tree->GetEntriesFast();
	tree->SetMakeClass(1);                                             

	//TFile *f_out = new TFile(fileNameHist,"RECREATE");

	cout<< "Processing: " << fileNameId <<endl;

  	Float_t id_AoQ, id_z1, id_z1_ch, id_z2, id_x2, id_y2, tpc_ang_x_s2, tpc_ang_y_s2, tpc_x_41, tpc_y_41;
  	Int_t N0 = 0;
  	Int_t N_sameZ = 0;
  	Float_t ratio;

  	gStyle->SetTitleSize(0.05, "t");
    gStyle->SetLabelSize(0.05, "XYZ");
    gStyle->SetTitleSize(0.05, "X");  // Set the X-axis title size
    gStyle->SetTitleSize(0.05, "Y");
    gStyle->SetStatFontSize(0.05); 
    //gStyle->SetOptStat(0);
    gStyle->SetTitleFillColor(kWhite); 

  	tree->SetBranchAddress("id_AoQ",&id_AoQ);
  	tree->SetBranchAddress("id_z1",&id_z1);
  	tree->SetBranchAddress("id_z1_ch",&id_z1_ch);
  	tree->SetBranchAddress("id_z2",&id_z2);
	tree->SetBranchAddress("id_x2",&id_x2);
	tree->SetBranchAddress("id_y2",&id_y2);
	tree->SetBranchAddress("tpc_ang_x_s2",&tpc_ang_x_s2);
	tree->SetBranchAddress("tpc_ang_y_s2",&tpc_ang_y_s2);
	tree->SetBranchAddress("tpc_x_41",&tpc_x_41);
	tree->SetBranchAddress("tpc_y_41",&tpc_y_41);
	
  	Int_t tpc_cut_c1;
  	Int_t tpc_cut_c2;
  	Float_t id_z1_c1;
  	Float_t id_z1_c2;
  	fileTransmOut.Form("%s_transm_x4.txt",name1);
  	std::ofstream outfile(fileTransmOut);  // Open a file to write
    if (!outfile) {
        std::cerr << "Error opening file!" << std::endl;
    }


    	TH1F *h_z1_ch_cut = new TH1F("h_z1_ch_cut","h_z1_ch_cut",1000,0,4096);
  	h_z1_ch_cut ->SetTitle("Z1 from MUSIC41 in ch, before target, with cut on the main peak in ch and TPC");

	TH2F *h_id_cut_tpc = new TH2F("h_id_cut_tpc","h_id_cut_tpc",500,1.5,2.5,500,4,10);
  	h_id_cut_tpc ->GetXaxis()->SetTitle("AoQ");
  	h_id_cut_tpc ->GetYaxis()->SetTitle("Z music41"); 
  	h_id_cut_tpc ->SetTitle("ID plot with Z from MUSIC41, before target, with condition on TPC");

  	TH1F *h_id_z1_ch_cut_tpc = new TH1F("h_id_z1_ch_cut_tpc","h_id_z1_ch_cut_tpc",1000,0,4096);
  	h_id_z1_ch_cut_tpc ->SetTitle("Z1 from MUSIC41 in ch, before target, with condition on TPC");
  	h_id_z1_ch_cut_tpc ->GetXaxis()->SetTitle("z1 MUSIC41 in ch"); 

  	TH2F *h_id_cut = new TH2F("h_id_cut","h_id_cut",500,1.5,2.5,500,4,10);
  	h_id_cut ->GetXaxis()->SetTitle("AoQ");
  	h_id_cut ->GetYaxis()->SetTitle("Z music41"); 
  	h_id_cut ->SetTitle("ID plot with Z from MUSIC41, before target, with condition on Z1 in ch and TPC");

  	TH1F *h_z2_cut = new TH1F("h_z2_cut","h_z2_cut",500,4,10);
  	h_z2_cut ->SetTitle("Z2 from MUSIC42, after target, with condition on Z1 in ch and TPC");

  	TH1F *h_id_x2 = new TH1F("h_id_x2","h_id_x2",100,-50,50);
  	TH1F *h_id_x2_slice = new TH1F("h_id_x2_slice","h_id_x2_slice",100,-50,50);

  	TH1F *h_id_x4 = new TH1F("h_id_x4","h_id_x4",100,-50,50);
  	TH1F *h_id_x4_slice = new TH1F("h_id_x4_slice","h_id_x4_slice",100,-50,50);


  	printf("Total number of events is %lld \n",nentries);

  	//loop over TPC cut condition
  	for (int k = -50; k <= 50; k+=5) {
  		tpc_cut_c1 = k;
  		tpc_cut_c2 = k+5;
  		printf("TPC cut low %d , TPC cut high %d \n",tpc_cut_c1,tpc_cut_c2);

  		h_z1_ch_cut->Reset();
  		h_id_cut->Reset();
  		h_id_z1_ch_cut_tpc->Reset();
  		h_id_cut_tpc->Reset();
  		h_z2_cut->Reset();

		//loop to fill h_id_z1_ch_cut_tpc and fit it later
		//also to show what is cut on
		for (Int_t i=0;i<nentries;i++) {
			//if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
			tree->GetEntry(i);
			if(//id_x2 > -9 && id_x2 < 9 &&
				//id_x2 > tpc_cut_c1 && id_x2 < tpc_cut_c2){
				tpc_x_41 > tpc_cut_c1 && tpc_x_41 < tpc_cut_c2){
				//tpc_ang_x_s2 > tpc_cut_c1 && tpc_ang_x_s2 < tpc_cut_c2
				h_id_cut_tpc->Fill(id_AoQ,id_z1);
				h_id_z1_ch_cut_tpc->Fill(id_z1_ch);
			}
		}

		TF1 *gaus_Z1 = new TF1("gaus_Z1", "gaus",1700,2500);
		gaus_Z1->SetLineColor(kRed); 
		h_id_z1_ch_cut_tpc->Fit("gaus_Z1","Q NODRAW");
		double mean1 = gaus_Z1->GetParameter(1);
		double sigma1 = gaus_Z1->GetParameter(2);
		id_z1_c1 = mean1 - 3.5 * sigma1;
		id_z1_c2 = mean1 + 3.5 * sigma1;

		for (Int_t i=0;i<nentries;i++) {
			//if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
			tree->GetEntry(i);
			if(id_z1_ch > id_z1_c1 && id_z1_ch < id_z1_c2 &&
			   //id_x2 > -9 && id_x2 < 9 &&
				tpc_x_41 > tpc_cut_c1 && tpc_x_41 < tpc_cut_c2){
			   //id_x2 > tpc_cut_c1 && id_x2 < tpc_cut_c2){
				//tpc_ang_x_s2 > tpc_cut_c1 && tpc_ang_x_s2 < tpc_cut_c2){
					h_id_cut->Fill(id_AoQ,id_z1);
					h_z1_ch_cut->Fill(id_z1_ch);
					h_z2_cut->Fill(id_z2);
			}
		}

		//calculating transmission ratio
		TF1 *gaus_Z2 = new TF1("gaus_Z2", "gaus", 7, 9);
		gaus_Z2->SetLineColor(kBlack); 
		h_z2_cut->Fit("gaus_Z2","Q NODRAW");

		TLegend *l2 = new TLegend(0.3, 0.3, 0.7, 0.7);
		l2->AddEntry(h_z2_cut, "Z2 with condition on incoming beam", "l");
		l2->AddEntry(gaus_Z2, "Gaussian fit", "l");
		//l2->Draw();

		// Get the fit parameters
		double mean2 = gaus_Z2->GetParameter(1);
		double sigma2 = gaus_Z2->GetParameter(2);

		std::cout << "Mean Z2: " << mean2 << std::endl;
		std::cout << "Sigma Z2: " << sigma2 << std::endl;

		// Define the selection range as mean ± 3.5 * sigma
		double lower_bound = mean2 - 3.5 * sigma2;
		//double upper_bound = mean + 10 * sigma;
		double upper_bound = 10;

		std::cout << "Selection range for Z2: [" << lower_bound << ", " << upper_bound << "]" << std::endl;

		// Calculate the number of entries within this range
		int bin_lower = h_z2_cut->FindBin(lower_bound);
		int bin_upper = h_z2_cut->FindBin(upper_bound);

		double int_sameZ = h_z2_cut->Integral(bin_lower, bin_upper);
		double int_N0 = h_id_cut->Integral();

		std::cout << "+++++++++++++++++++" << std::endl;
		std::cout << "N0: " << int_N0 << std::endl;
		std::cout << "NsameZ: " << int_sameZ << std::endl;
		std::cout << "Ratio: " << int_sameZ/int_N0 << std::endl;
		std::cout << "+++++++++++++++++++" << std::endl;

		outfile << tpc_cut_c1 << "\t" <<  tpc_cut_c2  << "\t" <<  int_N0 << "\t" <<  int_sameZ << std::endl;

	}//end of tpc cut loop

	// Close the file
	outfile.close();


	//drawing 
	tpc_cut_c1 = -1;
	tpc_cut_c2 = 0;
	h_z1_ch_cut->Reset();
  	h_id_cut->Reset();
  	h_id_z1_ch_cut_tpc->Reset();
  	h_id_cut_tpc->Reset();
  	h_z2_cut->Reset();
	for (Int_t i=0;i<nentries;i++) {
			if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
			tree->GetEntry(i);
			h_id_x4->Fill(tpc_x_41);
			if(//id_x2 > -9 && id_x2 < 9 &&
				//id_x2 > tpc_cut_c1 && id_x2 < tpc_cut_c2){
				tpc_x_41 > tpc_cut_c1 && tpc_x_41 < tpc_cut_c2){
				//tpc_ang_x_s2 > tpc_cut_c1 && tpc_ang_x_s2 < tpc_cut_c2
				h_id_cut_tpc->Fill(id_AoQ,id_z1);
				h_id_z1_ch_cut_tpc->Fill(id_z1_ch);
			}
		}

		TF1 *gaus_Z1 = new TF1("gaus_Z1", "gaus",1700,2500);
		gaus_Z1->SetLineColor(kRed); 
		h_id_z1_ch_cut_tpc->Fit("gaus_Z1","Q NODRAW");
		double mean1 = gaus_Z1->GetParameter(1);
		double sigma1 = gaus_Z1->GetParameter(2);
		id_z1_c1 = mean1 - 3.5 * sigma1;
		id_z1_c2 = mean1 + 3.5 * sigma1;

		for (Int_t i=0;i<nentries;i++) {
			if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
			tree->GetEntry(i);
			if(id_z1_ch > id_z1_c1 && id_z1_ch < id_z1_c2 &&
			   //id_x2 > -9 && id_x2 < 9 &&
			   //id_x2 > tpc_cut_c1 && id_x2 < tpc_cut_c2){
			   	tpc_x_41 > tpc_cut_c1 && tpc_x_41 < tpc_cut_c2){
				//tpc_ang_x_s2 > tpc_cut_c1 && tpc_ang_x_s2 < tpc_cut_c2){
					h_id_cut->Fill(id_AoQ,id_z1);
					h_z1_ch_cut->Fill(id_z1_ch);
					h_z2_cut->Fill(id_z2);
					h_id_x4_slice->Fill(tpc_x_41);
			}
		}

		//calculating transmission ratio
		TF1 *gaus_Z2 = new TF1("gaus_Z2", "gaus", 7, 9);
		//TF1 *gaus_Z2 = new TF1("gaus_Z2", "TMath::Exp((-[3] + x)/[2]) * TMath::Gaus(x, [0], [1]) * (1 - TMath::Exp((-[3] + x)/[2]))", 7, 9);
		// Set initial parameters: A, mu, sigma, lambda
    	gaus_Z2->SetParameters(8.5, 0, 1, 1);
		gaus_Z2->SetLineColor(kBlack); 
		//h_z2_cut->Fit("gaus_Z2","Q NODRAW");
		h_z2_cut->Fit("gaus_Z2","Q NODRAW");

		TLegend *l2 = new TLegend(0.3, 0.3, 0.7, 0.7);
		l2->AddEntry(h_z2_cut, "Z2 with condition on incoming beam", "l");
		l2->AddEntry(gaus_Z2, "Gaussian fit", "l");
		//l2->Draw();

		// Get the fit parameters
		double mean2 = gaus_Z2->GetParameter(1);
		double sigma2 = gaus_Z2->GetParameter(2);

		std::cout << "Mean Z2: " << mean2 << std::endl;
		std::cout << "Sigma Z2: " << sigma2 << std::endl;

		// Define the selection range as mean ± 3.5 * sigma
		double lower_bound = mean2 - 3.5 * sigma2;
		//double upper_bound = mean + 10 * sigma;
		double upper_bound = 10;


    // *** drawing
	TCanvas *cc = new TCanvas("cc", "cc", 800, 0, 800, 600);
	cc->Divide(2,3);

	cc->cd(1);
	h_id_cut_tpc->Draw("colz");
	TLine *lin1 = new TLine(1.6, id_z1_c1, 2.2, id_z1_c1);
    lin1->SetLineColor(kRed);
    lin1->SetLineWidth(2);
    TLine *lin2 = new TLine(1.6, id_z1_c2, 2.2, id_z1_c2);
    lin2->SetLineColor(kRed);
    lin2->SetLineWidth(2);
	lin1->Draw("same");
	lin2->Draw("same");

	cc->cd(2);
	h_id_z1_ch_cut_tpc->Draw();
	TLine *left1 = new TLine(id_z1_c1, 0, id_z1_c1, 1000);
    left1->SetLineColor(kRed);
    //left1->SetLineStyle(2);
    left1->SetLineWidth(2);
    left1->Draw("same");
    TLine *right1 = new TLine(id_z1_c2, 0, id_z1_c2, 1000);
    right1->SetLineColor(kRed);
    //right1->SetLineStyle(2);
    right1->SetLineWidth(2);
    right1->Draw("same");
    gPad->SetLogy();
    gaus_Z1->Draw("same");

	cc->cd(3);
	h_id_cut->Draw();

	cc->cd(4);
	h_z2_cut->Draw();
	l2->Draw();
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
    gaus_Z2->Draw("same");

    cc->cd(5);
    h_id_x4->Draw();
    h_id_x4_slice->Draw("same");
    gPad->SetLogy();

}
