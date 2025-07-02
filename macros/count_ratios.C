#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std;
// *** This macro ***
// --- calculates N0 and Nsamez in histos from *_id_m_hist.root

void count_ratios(){
	TString path("/data.local2/S533_June21_data/s533jun21/roots/");
	//TString name("s533_50_gC_12mm_46-47"); 
	//TString name("s533_50_empty_0053"); 
	TString name("s533_50_gC_6mm_0045");
	//TString name("s533_50_C_2cm_0048"); 
	//TString name("s533_50_gC_6mm_45_50-52");
	//TString name("s533_50_gC_6mm_0045");
	//s533_50_empty_0076
	//TString name("s533_50_empty_0076");
	//TString name("s533_50_C_2cm_48-49");
	//TString name("s533_50_water_emp_0055");
	TString fileName, fileOut;
	const char * path1 = path.Data();
	const char * name1 = name.Data();
	fileName.Form("%s%s_id.root", path1,name1); 
	TFile *file = new TFile(fileName,"READ");
	TTree *tree = (TTree*)file->Get("IdTree");
  	Long64_t nentries = tree->GetEntriesFast();
	tree->SetMakeClass(1);                                             
	cout<< "Processing: " << fileName <<endl;

	fileOut.Form("%s_ratios.txt",name1);
  	std::ofstream outfile(fileOut);  // Open a file to write
    if (!outfile) {
        std::cerr << "Error opening file!" << std::endl;
    }


	Int_t fixed_cut_x2_c1 = -1000; Int_t fixed_cut_x2_c2 = 1000;
  	Int_t fixed_cut_y2_c1 = -1000; Int_t fixed_cut_y2_c2 = 1000;
  	Int_t fixed_cut_a2_c1 = -1000; Int_t fixed_cut_a2_c2 = 1000;
  	Int_t fixed_cut_b2_c1 = -1000; Int_t fixed_cut_b2_c2 = 1000;
  	Int_t fixed_cut_x4_c1 = -1000; Int_t fixed_cut_x4_c2 = 1000;
  	Int_t fixed_cut_y4_c1 = -1000; Int_t fixed_cut_y4_c2 = 1000;
    
    /*
	Int_t fixed_cut_x2_c1 = -13; Int_t fixed_cut_x2_c2 = 13;
  	Int_t fixed_cut_y2_c1 = -8; Int_t fixed_cut_y2_c2 = 7;
  	Int_t fixed_cut_a2_c1 = -13; Int_t fixed_cut_a2_c2 = 7;
  	Int_t fixed_cut_b2_c1 = -13; Int_t fixed_cut_b2_c2 = 13;
  	Int_t fixed_cut_x4_c1 = -13; Int_t fixed_cut_x4_c2 = 12;
  	Int_t fixed_cut_y4_c1 = -13; Int_t fixed_cut_y4_c2 = 17;
  	*/
  	

	gStyle->SetTitleSize(0.06, "t");
    gStyle->SetLabelSize(0.06, "XYZ");
    gStyle->SetTitleSize(0.06, "X");  // Set the X-axis title size
    gStyle->SetTitleSize(0.06, "Y");
    gStyle->SetStatFontSize(0.06); 
    //gStyle->SetOptStat(0);

	Float_t id_AoQ, id_z1, id_z1_ch, id_z2_ch, id_z2, id_x2, id_y2, tpc_ang_x_s2, tpc_ang_y_s2, tpc_x_41, tpc_y_41;
  	Int_t N0 = 0;
  	Int_t N_sameZ = 0;
  	Float_t ratio;

  	tree->SetBranchAddress("id_AoQ",&id_AoQ);
  	tree->SetBranchAddress("id_z1",&id_z1);
  	tree->SetBranchAddress("id_z1_ch",&id_z1_ch);
  	tree->SetBranchAddress("id_z2_ch",&id_z2_ch);
  	tree->SetBranchAddress("id_z2",&id_z2);
	tree->SetBranchAddress("id_x2",&id_x2);
	tree->SetBranchAddress("id_y2",&id_y2);
	tree->SetBranchAddress("tpc_ang_x_s2",&tpc_ang_x_s2);
	tree->SetBranchAddress("tpc_ang_y_s2",&tpc_ang_y_s2);
	tree->SetBranchAddress("tpc_x_41",&tpc_x_41);
	tree->SetBranchAddress("tpc_y_41",&tpc_y_41);

  	Float_t id_z1_c1;
  	Float_t id_z1_c2;

  	double lower_bound, upper_bound;

    TH1F *h_z1_ch = new TH1F("h_z1_ch","h_z1_ch",4096,0,4096);
  	h_z1_ch ->SetTitle("Z1 from MUSIC41 in ch, no cuts");

  	TH1F *h_z2_ch = new TH1F("h_z2_ch","h_z2_ch",4096,0,4096);
  	h_z2_ch ->SetTitle("Z2 from MUSIC42 in ch, no cuts");

	TH1F *h_z2_ch_cut = new TH1F("h_z2_ch_cut","h_z2_ch_cut",4096,0,4096);
  	h_z2_ch_cut ->GetXaxis()->SetTitle("Z2 from MUSIC42 in ch, with cut on Z1 from MUSIC41 in ch"); 

  	/*
  	TH1F *h_id_z1_ch_cut_tpc = new TH1F("h_id_z1_ch_cut_tpc","h_id_z1_ch_cut_tpc",4096,0,4096);
  	h_id_z1_ch_cut_tpc ->SetTitle("Z1 from MUSIC41 in ch, before target and with stable transmission ranges selected");
  	h_id_z1_ch_cut_tpc ->GetXaxis()->SetTitle("z1 MUSIC41 in ch"); 

  	TH2F *h_id_cut = new TH2F("h_id_cut","h_id_cut",500,1.5,2.5,500,4,12);
  	h_id_cut ->GetXaxis()->SetTitle("AoQ");
  	h_id_cut ->GetYaxis()->SetTitle("Z music41"); 
  	h_id_cut ->SetTitle("ID plot with Z from MUSIC41, before target, with condition on Z1 in ch, all and x2");

  	TH2F *h_id_cut_ch = new TH2F("h_id_cut_ch","h_id_cut_ch",500,1.5,2.5,1000,0,4096);
  	h_id_cut_ch ->GetXaxis()->SetTitle("AoQ");
  	h_id_cut_ch ->GetYaxis()->SetTitle("Z music41 ch"); 
  	h_id_cut_ch ->SetTitle("ID plot with Z from MUSIC41 in ch, before target and stable transmission ranges selected");

  	TH1F *h_z2_cut = new TH1F("h_z2_cut","h_z2_cut",4096,0,4096);
  	h_z2_cut ->SetTitle("Z2 from MUSIC42, after target, with condition on Z1 in ch and stable transmission ranges selected");
  	h_z2_cut ->GetXaxis()->SetTitle("z2 MUSIC42 "); 

  	TH1F *h_id_x2 = new TH1F("h_id_x2","h_id_x2",100,-50,50);
  	TH1F *h_id_x2_slice = new TH1F("h_id_x2_slice","h_id_x2_slice",100,-50,50);
  	TH1F *h_id_y2 = new TH1F("h_id_y2","h_id_y2",100,-50,50);
  	TH1F *h_tpc_ang_x_s2 = new TH1F("h_tpc_ang_x_s2","h_tpc_ang_x_s2",100,-50,50);
  	TH1F *h_tpc_ang_y_s2 = new TH1F("h_tpc_ang_y_s2","h_tpc_ang_y_s2",100,-50,50);
  	TH1F *h_tpc_x_41 = new TH1F("h_tpc_x_41","h_tpc_x_41",100,-50,50);
  	TH1F *h_tpc_y_41 = new TH1F("h_tpc_y_41","h_tpc_y_41",100,-50,50);

  	*/

  	printf("Total number of events is %lld \n",nentries);

		for (Int_t i=0;i<nentries;i++) {
			//if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
			tree->GetEntry(i);
			h_z1_ch->Fill(id_z1_ch);
			h_z2_ch->Fill(id_z2_ch);
			/*
			if( id_x2 > fixed_cut_x2_c1 && id_x2 < fixed_cut_x2_c2 &&
				id_y2 > fixed_cut_y2_c1  && id_y2 < fixed_cut_y2_c2 &&
				tpc_ang_x_s2 > fixed_cut_a2_c1 && tpc_ang_x_s2 < fixed_cut_a2_c2 &&
				tpc_ang_y_s2 > fixed_cut_b2_c1 && tpc_ang_y_s2 < fixed_cut_b2_c2 &&
				tpc_x_41 > fixed_cut_x4_c1 && tpc_x_41 < fixed_cut_x4_c2 &&
				tpc_y_41 > fixed_cut_y4_c1 && tpc_y_41 < fixed_cut_y4_c2){

				
				h_id_z1_ch_cut_tpc->Fill(id_z1_ch);

			}
			*/
		}

		TF1 *gaus_Z1 = new TF1("gaus_Z1", "gaus",0,9999);
		gaus_Z1->SetLineColor(kRed); 
		h_z1_ch->Fit("gaus_Z1","Q NODRAW");
		double mean1 = gaus_Z1->GetParameter(1);
		double sigma1 = gaus_Z1->GetParameter(2);
		id_z1_c1 = mean1 - 3.5 * sigma1;
		id_z1_c2 = mean1 + 3.5 * sigma1;

		std::cout << "id_z1_c1 " << (int)id_z1_c1 << endl;
		std::cout << "id_z1_c2 " << (int)id_z1_c2 << endl;

		for (Int_t i=0;i<nentries;i++) {
			tree->GetEntry(i);
			if(id_z1_ch > id_z1_c1 && id_z1_ch < id_z1_c2){
				h_z2_ch_cut->Fill(id_z2_ch);
			}
				/*if(id_z1_ch > id_z1_c1 && id_z1_ch < id_z1_c2 && 
				id_x2 > fixed_cut_x2_c1 && id_x2 < fixed_cut_x2_c2 &&
				id_y2 > fixed_cut_y2_c1  && id_y2 < fixed_cut_y2_c2 &&
				tpc_ang_x_s2 > fixed_cut_a2_c1 && tpc_ang_x_s2 < fixed_cut_a2_c2 &&
				tpc_ang_y_s2 > fixed_cut_b2_c1 && tpc_ang_y_s2 < fixed_cut_b2_c2 &&
				tpc_x_41 > fixed_cut_x4_c1 && tpc_x_41 < fixed_cut_x4_c2 &&
				tpc_y_41 > fixed_cut_y4_c1 && tpc_y_41 < fixed_cut_y4_c2){
				h_z2_cut->Fill(id_z2_ch);
			}
			h_id_cut->Fill(id_AoQ,id_z1);
			h_id_cut_ch->Fill(id_AoQ,id_z1_ch);*/
		}

		//calculating transmission ratio
		TF1 *gaus_Z2 = new TF1("gaus_Z2", "gaus", 1800,9999);
		gaus_Z2->SetLineColor(kBlack); 
		h_z2_ch_cut->Fit("gaus_Z2","Q NODRAW");

		TLegend *l2 = new TLegend(0.3, 0.3, 0.7, 0.7);
		l2->AddEntry(h_z2_ch_cut, "Z2 with condition on incoming beam", "l");
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
		upper_bound = 10000;

		std::cout << "Selection range for Z2: [" << lower_bound << ", " << upper_bound << "]" << std::endl;

		// Calculate the number of entries within this range
		int z1_bin_lower = h_z1_ch->FindBin(id_z1_c1);
		int z1_bin_upper = h_z1_ch->FindBin(id_z1_c2);
		std::cout << "z1_bin_lower: " << z1_bin_lower << std::endl;
		std::cout << "z1_bin_upper: " << z1_bin_upper << std::endl;

		int z2_bin_lower = h_z2_ch_cut->FindBin(lower_bound);
		int z2_bin_upper = h_z2_ch_cut->FindBin(upper_bound);
		std::cout << "z2_bin_lower: " << z2_bin_lower << std::endl;
		std::cout << "z2_bin_upper: " << z2_bin_upper << std::endl;

		double int_N0 = h_z1_ch->Integral(z1_bin_lower,z1_bin_upper);
		double int_sameZ = h_z2_ch_cut->Integral(z2_bin_lower,z2_bin_upper);
		
		//double int_N0 = h_id_cut_ch->Integral();

		std::cout << "+++++++++++++++++++" << std::endl;
		std::cout << "N0: " << int_N0 << std::endl;
		std::cout << "NsameZ: " << int_sameZ << std::endl;
		std::cout << "Ratio: " << int_sameZ/int_N0 << std::endl;
		std::cout << "+++++++++++++++++++" << std::endl;

		outfile <<  int_N0 << "\t" <<  int_sameZ << std::endl;
		outfile.close();

		TCanvas *c = new TCanvas();
		c->Divide(2,2);
		c->cd(1);
		gPad->SetLogy();
		h_z1_ch->Draw();
		gaus_Z1->Draw("same");
		TLine *line1 = new TLine(id_z1_c1, 0, id_z1_c1, h_z1_ch->GetMaximum());
    	line1->SetLineColor(kBlue);
    	line1->SetLineStyle(2);
    	line1->SetLineWidth(2);
    	line1->Draw();
    	TLine *line2 = new TLine(id_z1_c2, 0, id_z1_c2, h_z1_ch->GetMaximum());
    	line2->SetLineColor(kBlue);
    	line2->SetLineStyle(2);
    	line2->SetLineWidth(2);
    	line2->Draw();

		c->cd(2);
		gPad->SetLogy();
		h_z2_ch_cut->Draw();
		gaus_Z2->Draw("same");
		TLine *line3 = new TLine(lower_bound, 0, lower_bound, h_z2_ch_cut->GetMaximum());
    	line3->SetLineColor(kBlue);
    	line3->SetLineStyle(2);
    	line3->SetLineWidth(2);
    	line3->Draw();

    	c->cd(3);
    	gPad->SetLogy();
    	h_z2_ch->Draw();
    	c->cd(4);
    	//h_id_cut->Draw();
}