#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std;
#include <fstream>
// *** This macro ***
// --- 2nd round of iterations looking for stable cross section
// --- all 6 variables are fixed to a range selected within 1st iteration
// --- the x2 is varied again

void transmission_check_all_b2(){

	TString path("/data.local2/S533_June21_data/s533jun21/roots/");
	TString name("s533_50_empty_53-54"); 
	//TString name("s533_50_gC_6mm_45_50-52");
	//TString name("s533_50_gC_12mm_46-47");

	Int_t fixed_cut_x2_c1 = -13; Int_t fixed_cut_x2_c2 = 23;
  	Int_t fixed_cut_y2_c1 = -13; Int_t fixed_cut_y2_c2 = 8;
  	Int_t fixed_cut_a2_c1 = -23; Int_t fixed_cut_a2_c2 = 8;
  	Int_t fixed_cut_b2_c1 = -13; Int_t fixed_cut_b2_c2 = 8;
  	Int_t fixed_cut_x4_c1 = -13; Int_t fixed_cut_x4_c2 = 23;
  	Int_t fixed_cut_y4_c1 = -15; Int_t fixed_cut_y4_c2 = 10;

	TString fileNameId;
	const char * path1 = path.Data();
	const char * name1 = name.Data();
	fileNameId.Form("%s%s_id_m.root", path1,name1);   
	TFile *file = new TFile(fileNameId,"READ");
	TTree *tree = (TTree*)file->Get("IdTree");
  	Long64_t nentries = tree->GetEntriesFast();
	tree->SetMakeClass(1);                                             
	cout<< "Processing: " << fileNameId <<endl;
	TString fileTransmOut;
	fileTransmOut.Form("%s_transm_all_b2.txt",name1);
  	std::ofstream outfile(fileTransmOut);  // Open a file to write
    if (!outfile) {
        std::cerr << "Error opening file!" << std::endl;
    }

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

  	double lower_bound, upper_bound;

    TH1F *h_z1_ch = new TH1F("h_z1_ch","h_z1_ch",1000,0,4096);
  	h_z1_ch ->SetTitle("Z1 from MUSIC41 in ch, before target, no cuts");

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
  	h_id_cut ->SetTitle("ID plot with Z from MUSIC41, before target, with condition on Z1 in ch, all and x2");

  	TH2F *h_id_cut_ch = new TH2F("h_id_cut_ch","h_id_cut_ch",500,1.5,2.5,1000,0,4096);
  	h_id_cut_ch ->GetXaxis()->SetTitle("AoQ");
  	h_id_cut_ch ->GetYaxis()->SetTitle("Z music41 ch"); 
  	h_id_cut_ch ->SetTitle("ID plot with Z from MUSIC41 in ch, before target, with condition on Z1 in ch, all and x2");

  	TH1F *h_z2_cut = new TH1F("h_z2_cut","h_z2_cut",500,4,10);
  	h_z2_cut ->SetTitle("Z2 from MUSIC42, after target, with condition on Z1 in ch, all and x2");

  	TH1F *h_id_x2 = new TH1F("h_id_x2","h_id_x2",100,-50,50);
  	TH1F *h_id_b2_slice = new TH1F("h_id_b2_slice","h_id_b2_slice",100,-50,50);
  	TH1F *h_id_y2 = new TH1F("h_id_y2","h_id_y2",100,-50,50);
  	TH1F *h_tpc_ang_x_s2 = new TH1F("h_tpc_ang_x_s2","h_tpc_ang_x_s2",100,-50,50);
  	TH1F *h_tpc_ang_y_s2 = new TH1F("h_tpc_ang_y_s2","h_tpc_ang_y_s2",100,-50,50);
  	TH1F *h_tpc_x_41 = new TH1F("h_tpc_x_41","h_tpc_x_41",100,-50,50);
  	TH1F *h_tpc_y_41 = new TH1F("h_tpc_y_41","h_tpc_y_41",100,-50,50);

  	printf("Total number of events is %lld \n",nentries);

  	//loop over TPC cut condition
  	for (int k = fixed_cut_b2_c1; k <= fixed_cut_b2_c2; k+=5) {
  		tpc_cut_c1 = k;
  		tpc_cut_c2 = k+5;
  		printf("TPC cut low %d , TPC cut high %d \n",tpc_cut_c1,tpc_cut_c2);

  		//h_z1_ch_cut->Reset();
  		h_id_cut->Reset();
  		h_id_z1_ch_cut_tpc->Reset();
  		h_id_cut_tpc->Reset();
  		h_z2_cut->Reset();
  		h_id_cut_ch->Reset();

		//loop to fill h_id_z1_ch_cut_tpc and fit it later
		//also to show what is cut on
		for (Int_t i=0;i<nentries;i++) {
			//if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
			tree->GetEntry(i);
			if(id_x2 > fixed_cut_x2_c1  && id_x2 < fixed_cut_x2_c2 &&
				id_y2 > fixed_cut_y2_c1 && id_y2 < fixed_cut_y2_c2 &&
				tpc_ang_x_s2 > fixed_cut_a2_c1 && tpc_ang_x_s2 < fixed_cut_a2_c2 &&
				tpc_x_41 > fixed_cut_x4_c1 && tpc_x_41 < fixed_cut_x4_c2 &&
				tpc_y_41 > fixed_cut_y4_c1 && tpc_y_41 < fixed_cut_y4_c2 &&
				tpc_ang_y_s2 > tpc_cut_c1 && tpc_ang_y_s2 < tpc_cut_c2){

				h_id_z1_ch_cut_tpc->Fill(id_z1_ch);

			}
		}

		TF1 *gaus_Z1 = new TF1("gaus_Z1", "gaus",1700,2500);
		gaus_Z1->SetLineColor(kRed); 
		h_id_z1_ch_cut_tpc->Fit("gaus_Z1","Q NODRAW");
		double mean1 = gaus_Z1->GetParameter(1);
		double sigma1 = gaus_Z1->GetParameter(2);
		printf("sigma1 %f \n",sigma1);
		id_z1_c1 = mean1 - 3.5 * sigma1;
		id_z1_c2 = mean1 + 3.5 * sigma1;
		printf("id_z1_c1 %f \n",id_z1_c1);

		for (Int_t i=0;i<nentries;i++) {
			tree->GetEntry(i);
			if(id_z1_ch > id_z1_c1 && id_z1_ch < id_z1_c2 && 
				id_x2 > fixed_cut_x2_c1  && id_x2 < fixed_cut_x2_c2 &&
				id_y2 > fixed_cut_y2_c1 && id_y2 < fixed_cut_y2_c2 &&
				tpc_ang_x_s2 > fixed_cut_a2_c1 && tpc_ang_x_s2 < fixed_cut_a2_c2 &&
				tpc_x_41 > fixed_cut_x4_c1 && tpc_x_41 < fixed_cut_x4_c2 &&
				tpc_y_41 > fixed_cut_y4_c1 && tpc_y_41 < fixed_cut_y4_c2 &&
				tpc_ang_y_s2 > tpc_cut_c1 && tpc_ang_y_s2 < tpc_cut_c2){

				h_id_cut_ch->Fill(id_AoQ,id_z1_ch);
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
		lower_bound = mean2 - 3.5 * sigma2;
		//double upper_bound = mean + 10 * sigma;
		upper_bound = 10;

		std::cout << "Selection range for Z2: [" << lower_bound << ", " << upper_bound << "]" << std::endl;

		// Calculate the number of entries within this range
		int bin_lower = h_z2_cut->FindBin(lower_bound);
		int bin_upper = h_z2_cut->FindBin(upper_bound);

		double int_sameZ = h_z2_cut->Integral(bin_lower, bin_upper);
		double int_N0 = h_id_cut_ch->Integral();

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
	//h_z1_ch_cut->Reset();
  	h_id_cut->Reset();
  	h_id_z1_ch_cut_tpc->Reset();
  	h_id_cut_tpc->Reset();
  	h_z2_cut->Reset();
  	h_id_cut_ch->Reset();

	for (Int_t i=0;i<nentries;i++) {
		if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
		tree->GetEntry(i);
		h_z1_ch->Fill(id_z1_ch);

		if(	id_y2 > fixed_cut_y2_c1  && id_y2 < fixed_cut_y2_c2 &&
			tpc_ang_x_s2 > fixed_cut_a2_c1 && tpc_ang_x_s2 < fixed_cut_a2_c2 &&
			tpc_ang_y_s2 > fixed_cut_b2_c1 && tpc_ang_y_s2 < fixed_cut_b2_c2 &&
			tpc_x_41 > fixed_cut_x4_c1 && tpc_x_41 < fixed_cut_x4_c2 &&
			tpc_y_41 > fixed_cut_y4_c1 && tpc_y_41 < fixed_cut_y4_c2 &&
			id_x2 > fixed_cut_x2_c1 && id_x2 < fixed_cut_x2_c2){
			
			h_id_x2->Fill(id_x2);
			h_id_y2->Fill(id_y2);
			h_tpc_ang_x_s2->Fill(tpc_ang_x_s2);
			h_tpc_ang_y_s2->Fill(tpc_ang_y_s2);
			h_tpc_x_41->Fill(tpc_x_41);
			h_tpc_y_41->Fill(tpc_y_41);
		}
		
		if(id_z1_ch > id_z1_c1 && id_z1_ch < id_z1_c2 && 
				id_x2 > fixed_cut_x2_c1  && id_x2 < fixed_cut_x2_c2 &&
				id_y2 > fixed_cut_y2_c1 && id_y2 < fixed_cut_y2_c2 &&
				tpc_ang_x_s2 > fixed_cut_a2_c1 && tpc_ang_x_s2 < fixed_cut_a2_c2 &&
				tpc_x_41 > fixed_cut_x4_c1 && tpc_x_41 < fixed_cut_x4_c2 &&
				tpc_y_41 > fixed_cut_y4_c1 && tpc_y_41 < fixed_cut_y4_c2 &&
				tpc_ang_y_s2 > tpc_cut_c1 && tpc_ang_y_s2 < tpc_cut_c2){

				h_id_cut->Fill(id_AoQ,id_z1);
				h_z2_cut->Fill(id_z2);
				h_id_b2_slice->Fill(tpc_ang_y_s2);
				h_id_cut_ch->Fill(id_AoQ,id_z1_ch);
				h_id_cut_tpc->Fill(id_AoQ,id_z1);
				h_id_z1_ch_cut_tpc->Fill(id_z1_ch);
		}
	}

    // *** drawing
	TCanvas *cc = new TCanvas("cc", "cc", 800, 0, 800, 600);
	cc->Divide(2,2);

	cc->cd(1);
	h_id_cut_ch->Draw("colz");
	TLine *lin1 = new TLine(1.6, id_z1_c1, 2.2, id_z1_c1);
    lin1->SetLineColor(kRed);
    lin1->SetLineWidth(2);
    TLine *lin2 = new TLine(1.6, id_z1_c2, 2.2, id_z1_c2);
    lin2->SetLineColor(kRed);
    lin2->SetLineWidth(2);
	lin1->Draw("same");
	lin2->Draw("same");

	cc->cd(2);
	h_z1_ch->Draw();
	h_id_z1_ch_cut_tpc->Draw("same");
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
    //gaus_Z1->Draw("same");

	cc->cd(3);
	h_id_cut->Draw();

	cc->cd(4);
	h_z2_cut->Draw();
	gPad->SetLogy();
	//l2->Draw();
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

    /*TBox *b2 = new TBox(lower_bound, 0, upper_bound, h_z2_cut->GetMaximum());
    b2->SetFillColorAlpha(kRed, 0.9);  // Semi-transparent red
    b2->SetFillStyle(3003);
    b2->Draw();*/
    //gaus_Z2->Draw("same");

    TCanvas *cc1 = new TCanvas("cc1", "cc1", 800, 0, 800, 600);
	cc1->Divide(2,3);
	cc1->cd(1);
    h_id_x2->Draw();
    cc1->cd(2);
    h_id_y2->Draw();
    cc1->cd(3);
    h_tpc_ang_x_s2->Draw();
    cc1->cd(4);
    h_tpc_ang_y_s2->Draw();
    h_id_b2_slice->Draw("same");
    cc1->cd(5);
    h_tpc_x_41->Draw();
    cc1->cd(6);
    h_tpc_y_41->Draw();
    


}
