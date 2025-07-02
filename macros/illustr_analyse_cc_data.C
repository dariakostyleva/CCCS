#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std;
// *** This macro ***
// --- performs cuts on id data from *_id.root
// --- writes two histograms with counts N0 and Nsamez into *_id_m_hist.root

void illustr_analyse_cc_data(){
	TString path("/data.local2/S533_June21_data/s533jun21/roots/");
	TString name("s533_51_empty_0086"); 
	TString fileNameId, fileNameHist;
	const char * path1 = path.Data();
	const char * name1 = name.Data();
	fileNameId.Form("%s%s_id.root", path1,name1);   
	fileNameHist.Form("%s%s_id_hist.root", path1,name1); 
	TFile *file = new TFile(fileNameId,"READ");
	TTree *tree = (TTree*)file->Get("IdTree");
  	Long64_t nentries = tree->GetEntriesFast();
	tree->SetMakeClass(1);                                             

	TFile *f_out = new TFile(fileNameHist,"RECREATE");

	cout<< "Processing: " << fileNameId <<endl;

  	Float_t id_AoQ, id_z1, id_z2, tpc_x_21, tpc_x_22, tpc_x_41, tpc_y_21, tpc_y_22, tpc_y_41, tpc_ang_x_s2, tpc_ang_y_s2, tpc_ang_x_s4, tpc_ang_y_s4, s4target_x, s4target_y, id_x2, id_y2;
  	Int_t N0 = 0;
  	Int_t N_sameZ = 0;
  	Float_t ratio;

  	gStyle->SetTitleSize(0.05, "t");
    gStyle->SetLabelSize(0.05, "XYZ");
    gStyle->SetTitleSize(0.05, "X");  // Set the X-axis title size
    gStyle->SetTitleSize(0.05, "Y");
    gStyle->SetStatFontSize(0.05); 
    gStyle->SetOptStat(0);
    gStyle->SetTitleFillColor(kWhite); 

  	tree->SetBranchAddress("id_AoQ",&id_AoQ);
  	tree->SetBranchAddress("id_z1",&id_z1);
  	tree->SetBranchAddress("id_z2",&id_z2);
	tree->SetBranchAddress("tpc_x_21",&tpc_x_21);
	tree->SetBranchAddress("tpc_x_22",&tpc_x_22);
  	tree->SetBranchAddress("tpc_x_41",&tpc_x_41);
	tree->SetBranchAddress("tpc_y_21",&tpc_y_21);
	tree->SetBranchAddress("tpc_y_22",&tpc_y_22);
	tree->SetBranchAddress("tpc_y_41",&tpc_y_41);
	tree->SetBranchAddress("tpc_ang_x_s2",&tpc_ang_x_s2);
	tree->SetBranchAddress("tpc_ang_y_s2",&tpc_ang_y_s2);
	tree->SetBranchAddress("tpc_ang_x_s4",&tpc_ang_x_s4);
	tree->SetBranchAddress("tpc_ang_y_s4",&tpc_ang_y_s4);
	tree->SetBranchAddress("s4target_x",&s4target_x);
    tree->SetBranchAddress("s4target_y",&s4target_y);
    tree->SetBranchAddress("id_x2",&id_x2);
    tree->SetBranchAddress("id_y2",&id_y2);

  	TH2F *h_id = new TH2F("h_id","h_id",500,1.5,2.5,500,4,10);
  	h_id ->GetXaxis()->SetTitle("AoQ");
  	h_id ->GetYaxis()->SetTitle("Z music41");
  	h_id ->SetTitle("ID plot with Z from MUSIC41, before target");

  	 TH2F *h_id2 = new TH2F("h_id2","h_id2",500,1.5,2.5,500,4,10);
  	h_id2 ->GetXaxis()->SetTitle("AoQ");
  	h_id2 ->GetYaxis()->SetTitle("Z music42");
  	h_id2 ->SetTitle("ID plot with Z from MUSIC42, after target");

  	TH2F *h_id_cut = new TH2F("h_id_cut","h_id_cut",500,1.5,2.5,500,4,10);
  	h_id_cut ->GetXaxis()->SetTitle("AoQ");
  	h_id_cut ->GetYaxis()->SetTitle("Z music41"); 
  	h_id_cut ->SetTitle("ID plot with Z from MUSIC41, before target, with condition on Z1 and TPC21,22,41");

  	TH2F *h_id_cut_tpc = new TH2F("h_id_cut_tpc","h_id_cut_tpc",500,1.5,2.5,500,4,10);
  	h_id_cut_tpc ->GetXaxis()->SetTitle("AoQ");
  	h_id_cut_tpc ->GetYaxis()->SetTitle("Z music41"); 
  	h_id_cut_tpc ->SetTitle("ID plot with Z from MUSIC41, before target, with condition on TPC21,22,41");

  	TH1F *h_z1 = new TH1F("h_z1","h_z1",500,4,10);
  	h_z1 ->GetXaxis()->SetTitle("z1 MUSIC41");
  	h_z1 ->SetTitle("Z1 from MUSIC41, before target");
  
  	TH1F *h_z2 = new TH1F("h_z2","h_z2",500,4,10);
  	h_z2 ->GetXaxis()->SetTitle("z2 MUSIC42");
  	h_z2 ->SetTitle("Z2 from MUSIC42, after target");

  	TH1F *h_z1_cut = new TH1F("h_z1_cut","h_z1_cut",500,4,10);
  	h_z1_cut ->SetTitle("Z1 from MUSIC41, before target, with condition on Z1 and TPC21,22,41");

  	TH1F *h_id_z1_cut_tpc = new TH1F("h_id_z1_cut_tpc","h_id_z1_cut_tpc",500,4,10);
  	h_id_z1_cut_tpc ->SetTitle("Z1 from MUSIC41, before target, with condition on TPC21,22,41");
  	h_id_z1_cut_tpc ->GetXaxis()->SetTitle("z1 MUSIC41"); 

  	TH1F *h_z2_cut = new TH1F("h_z2_cut","h_z2_cut",500,4,10);
  	h_z2_cut ->SetTitle("Z2 from MUSIC42, after target, with condition on Z1 and TPC21,22,41");

  	TH2F *h_z1z2 = new TH2F("h_z1z2","h_z1z2",500,4,10,500,4,10);
  	h_z1z2 ->SetTitle("Z1 vs Z2");

  	TH2F *h_target = new TH2F("h_target","h_target",100,-50,50,100,-50,50);
  	h_target ->GetXaxis()->SetTitle("X");
  	h_target ->GetYaxis()->SetTitle("Y"); 
  	h_target ->SetTitle("Beam spot on target");

  	TH2F *h_target_cut = new TH2F("h_target_cut","h_target_cut",100,-50,50,100,-50,50);
  	h_target_cut ->GetXaxis()->SetTitle("X");
  	h_target_cut ->GetYaxis()->SetTitle("Y"); 
  	h_target_cut ->SetTitle("Beam spot on target, with condition on Z1 and TPC21,22,41");

  	TH1F *h_tpc_x_21 = new TH1F("h_tpc_x_21","h_tpc_x_21",100,-50,50);
  	TH1F *h_tpc_x_22 = new TH1F("h_tpc_x_22","h_tpc_x_22",100,-50,50);
  	TH1F *h_id_x2 = new TH1F("h_id_x2","h_id_x2",100,-50,50);
  	TH1F *h_id_y2 = new TH1F("h_id_y2","h_id_y2",100,-50,50);
  	TH1F *h_tpc_x_41 = new TH1F("h_tpc_x_41","h_tpc_x_41",100,-50,50);
  	TH1F *h_tpc_y_21 = new TH1F("h_tpc_y_21","h_tpc_y_21",100,-50,50);
  	TH1F *h_tpc_y_22 = new TH1F("h_tpc_y_22","h_tpc_y_22",100,-50,50);
  	TH1F *h_tpc_y_41 = new TH1F("h_tpc_y_41","h_tpc_y_41",100,-50,50);
  	TH1F *h_tpc_ang_x_s2 = new TH1F("h_tpc_ang_x_s2","h_tpc_ang_x_s2",100,-50,50);
  	TH1F *h_tpc_ang_y_s2 = new TH1F("h_tpc_ang_y_s2","h_tpc_ang_y_s2",100,-50,50);
  	TH1F *h_tpc_ang_x_s4 = new TH1F("h_tpc_ang_x_s4","h_tpc_ang_x_s4",100,-50,50);
  	TH1F *h_tpc_ang_y_s4 = new TH1F("h_tpc_ang_y_s4","h_tpc_ang_y_s4",100,-50,50);
  	h_tpc_x_21->GetXaxis()->SetTitle("mm");
  	h_tpc_x_22->GetXaxis()->SetTitle("mm");
  	h_tpc_x_41->GetXaxis()->SetTitle("mm");
  	h_tpc_y_21->GetXaxis()->SetTitle("mm");
  	h_tpc_y_22->GetXaxis()->SetTitle("mm");
  	h_tpc_y_41->GetXaxis()->SetTitle("mm");
  	h_tpc_ang_x_s2->GetXaxis()->SetTitle("mrad");
  	h_tpc_ang_y_s2->GetXaxis()->SetTitle("mrad");
  	h_tpc_ang_x_s4->GetXaxis()->SetTitle("mrad");
  	h_tpc_ang_y_s4->GetXaxis()->SetTitle("mrad");

  	//defining cut conditions 
  	//Float_t id_AoQ_c1 = 1.98; //16O
  	//Float_t id_AoQ_c2 = 2.02; //16O
  	//Float_t id_AoQ_c1 = 1.84; //15O
  	//Float_t id_AoQ_c2 = 1.91; //15O

  	//Float_t id_z1_c1 = 7.6;	//16O
  	//Float_t id_z1_c2 = 8.4;	//16O
  	Float_t id_z1_c1;    // in channels
  	Float_t id_z1_c2;	// in channels

  	Float_t tpc_pos_c1 = -10;
  	Float_t tpc_pos_c2 = 10;
  	Float_t tpc_ang_c1 = -10;
  	Float_t tpc_ang_c2 = 10;


  	printf("Total number of events is %lld \n",nentries);
	for (Int_t i=0;i<nentries;i++) {

		if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
		tree->GetEntry(i);
		//printf("id_z1 %4.2f\n",id_z1)

		//for illustrational purposes only
		if(tpc_x_21 > tpc_pos_c1 && tpc_x_21 < tpc_pos_c2 &&
			tpc_y_21 > tpc_pos_c1 && tpc_y_21 < tpc_pos_c2 &&
			tpc_x_22 > tpc_pos_c1 && tpc_x_22 < tpc_pos_c2 &&
			tpc_y_22 > tpc_pos_c1 && tpc_y_22 < tpc_pos_c2 &&
			tpc_x_41 > tpc_pos_c1 && tpc_x_41 < tpc_pos_c2 &&
			tpc_y_41 > tpc_pos_c1 && tpc_y_41 < tpc_pos_c2 &&
			tpc_ang_x_s2 > tpc_ang_c1 && tpc_ang_x_s2 < tpc_ang_c2 &&
			tpc_ang_y_s2 > tpc_ang_c1 && tpc_ang_y_s2 < tpc_ang_c2){
			h_id_cut_tpc->Fill(id_AoQ,id_z1);
			h_id_z1_cut_tpc->Fill(id_z1);
		}

		h_id->Fill(id_AoQ,id_z1);
		h_id2->Fill(id_AoQ,id_z2);
		//h_id2->Fill(id_AoQ,id_z2);
		h_z1->Fill(id_z1);
		h_z2->Fill(id_z2);		
		h_z1z2->Fill(id_z1,id_z2);
		h_tpc_x_21->Fill(tpc_x_21);
		h_tpc_x_22->Fill(tpc_x_22);
		h_tpc_x_41->Fill(tpc_x_41);
		h_tpc_y_21->Fill(tpc_y_21);
		h_tpc_y_21->Fill(tpc_y_21);
		h_tpc_y_41->Fill(tpc_y_41);
		h_tpc_ang_x_s2->Fill(tpc_ang_x_s2);
		h_tpc_ang_y_s2->Fill(tpc_ang_y_s2);
		h_tpc_ang_x_s4->Fill(tpc_ang_x_s4);
		h_tpc_ang_y_s4->Fill(tpc_ang_y_s4);
		h_target->Fill(s4target_x,s4target_y);
		h_id_x2->Fill(id_x2);
		h_id_y2->Fill(id_y2);
	}

	TF1 *gaus = new TF1("gaus", "gaus", 7.5, 8.5);
	gaus->SetLineColor(kBlack); 
	h_id_z1_cut_tpc->Fit(gaus,"Q");
	double mean = gaus->GetParameter(1);
    double sigma = gaus->GetParameter(2);
    id_z1_c1 = mean - 3.5 * sigma;
    id_z1_c2 = mean + 3.5 * sigma;

	for (Int_t i=0;i<nentries;i++) {

		if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
		tree->GetEntry(i);
		if(//id_AoQ > id_AoQ_c1 && id_AoQ < id_AoQ_c2 && 
			id_z1 > id_z1_c1 && id_z1 < id_z1_c2 &&
			id_x2 > tpc_pos_c1 && id_x2 < tpc_pos_c2 &&
			id_y2 > tpc_pos_c1 && id_y2 < tpc_pos_c2 &&
			tpc_ang_x_s2 > tpc_ang_c1 && tpc_ang_x_s2 < tpc_ang_c2 &&
			tpc_ang_y_s2 > tpc_ang_c1 && tpc_ang_y_s2 < tpc_ang_c2 &&
			tpc_x_41 > tpc_pos_c1 && tpc_x_41 < tpc_pos_c2 &&
			tpc_y_41 > tpc_pos_c1 && tpc_y_41 < tpc_pos_c2){

				h_id_cut->Fill(id_AoQ,id_z1);
				h_z2_cut->Fill(id_z2);
				h_z1_cut->Fill(id_z1);
				h_target_cut->Fill(s4target_x,s4target_y);
		}
	}


	//ratio = (float)(N_sameZ/N0);
	//printf("Number of incident particle with Z=8 is N0 = %d\n",N0);
	//("Number of emerged particles with Z=8 is N_sameZ = %d\n",N_sameZ);
	//printf("N_sameZ/N0 = %4.2f\n",ratio);

	//****drawing id
	TCanvas *c = new TCanvas("c", "ID canvas", 0, 0, 800, 600);
	c->Divide(2,3);
	c->cd(1);
	h_id->Draw("COLZ");
	/*TBox *b1 = new TBox(id_AoQ_c1, id_z1_c1, id_AoQ_c2, id_z1_c2);
   	b1->SetFillStyle(0);
    b1->SetLineColor(kRed);       // Box border color
    b1->SetLineWidth(2);          // Box border width
    b1->Draw("same");*/
    c->Update();

	c->cd(2);
	h_id_cut->Draw();

	c->cd(3);
	gPad->SetLogy();
	h_z1->Draw("");
	h_z1_cut->SetLineColor(kRed);
	h_z1_cut->Draw("same");
	TLegend *l2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    l2->AddEntry(h_z1, "Z1", "l");
    l2->AddEntry(h_z1_cut, "Z1 with condition", "l");
    l2->Draw();

	c->cd(4);
	gPad->SetLogy();
	h_z2->Draw("");
	h_z2_cut->SetLineColor(kRed);
	h_z2_cut->Draw("same");
	TLegend *l1 = new TLegend(0.7, 0.7, 0.9, 0.9);
    l1->AddEntry(h_z2, "Z2", "l");
    l1->AddEntry(h_z2_cut, "Z2 with condition", "l");
    l1->Draw();

	c->cd(5);
	h_id2->Draw();

	//****drawing tpcs
	TLine *line1 = new TLine(tpc_pos_c1, 0, tpc_pos_c1, 1e5);
    line1->SetLineColor(kBlue);
    line1->SetLineStyle(2);
    line1->SetLineWidth(2);

    TLine *line2 = new TLine(tpc_pos_c2, 0, tpc_pos_c2, 1e5);
    line2->SetLineColor(kBlue);
    line2->SetLineStyle(2);
    line2->SetLineWidth(2);

    TBox *b2 = new TBox(tpc_pos_c1, 0, tpc_pos_c2, 10000);
    b2->SetFillColorAlpha(kRed, 0.7);  // Semi-transparent red
    b2->SetFillStyle(3003);

    TCanvas *ct = new TCanvas("ct", "Target position canvas", 0, 700, 800, 600);
	ct->Divide(2,1);
	ct->cd(1); 
	h_target->Draw();
	ct->cd(2);
	h_target_cut->Draw();

	TCanvas *ctpc = new TCanvas("ctpc", "TPCs", 800, 0, 800, 600);
	ctpc->Divide(3,2);
	ctpc->cd(1); 
	h_tpc_x_21->Draw();
	line1->Draw("same");
	line2->Draw("same");
	//b2->Draw("same");
	ctpc->cd(2);
	h_tpc_x_22->Draw();
	line1->Draw("same");
	line2->Draw("same");
	//b2->Draw("same");
	ctpc->cd(3);
	h_tpc_x_41->Draw();
	line1->Draw("same");
	line2->Draw("same");
	//b2->Draw("same");
	ctpc->cd(4);
	h_tpc_y_21->Draw();
	line1->Draw("same");
	line2->Draw("same");
	//b2->Draw("same");
	ctpc->cd(5);
	h_tpc_y_21->Draw();
	line1->Draw("same");
	line2->Draw("same");
	//b2->Draw("same");
	ctpc->cd(6);
	h_tpc_y_41->Draw();
	line1->Draw("same");
	line2->Draw("same");
	//b2->Draw("same");

	TCanvas *ctpc2 = new TCanvas("ctpc2", "Cuts on incoming", 800, 0, 800, 600);
	ctpc2->Divide(4,2);
	ctpc2->cd(1);
	h_id_x2->Draw();
	line1->Draw("same");
	line2->Draw("same");
	ctpc2->cd(2);
	h_id_y2->Draw();
	line1->Draw("same");
	line2->Draw("same");
	ctpc2->cd(3); 
	h_tpc_ang_x_s2->Draw();
	line1->Draw("same");
	line2->Draw("same");
	//b2->Draw("same");
	ctpc2->cd(4);
	h_tpc_ang_y_s2->Draw();
	line1->Draw("same");
	line2->Draw("same");
	//b2->Draw("same");
	ctpc2->cd(5);
	h_tpc_x_41->Draw();
	line1->Draw("same");
	line2->Draw("same");
	ctpc2->cd(6);
	h_tpc_y_41->Draw();
	line1->Draw("same");
	line2->Draw("same");
	ctpc2->cd(7);
	h_id_z1_cut_tpc->Draw();
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
	ctpc2->cd(8);
	h_id_cut_tpc->Draw("colz");
	TLine *lin1 = new TLine(1.6, id_z1_c1, 2.2, id_z1_c1);
    lin1->SetLineColor(kRed);
    lin1->SetLineWidth(2);
    TLine *lin2 = new TLine(1.6, id_z1_c2, 2.2, id_z1_c2);
    lin2->SetLineColor(kRed);
    lin2->SetLineWidth(2);
	lin1->Draw("same");
	lin2->Draw("same");
	//b1->Draw("same");

	



	
	/*h_tpc_ang_x_s4->Draw();
	line1->Draw("same");
	line2->Draw("same");
	b2->Draw("same");
	ctpc->cd(10);
	h_tpc_ang_y_s4->Draw();
	line1->Draw("same");
	line2->Draw("same");
	b2->Draw("same");*/

	h_id_cut->Write();
	h_z2_cut->Write();
}