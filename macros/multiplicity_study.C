#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std; 

void multiplicity_study(){
	TFile *file1 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_0041_id_all.root","READ");//16O
	TTree *tree1 = (TTree*)file1->Get("IdTree");

	//TFile *file2 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_0041_id_gt2_2.root","READ"); //16O
	TFile *file2 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_0041_id_1det.root","READ"); //16O
	TTree *tree2 = (TTree*)file2->Get("IdTree");

	TFile *file3 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_0041_id_hits.root","READ"); //16O
	TTree *tree3 = (TTree*)file3->Get("IdTree");

	gStyle->SetTitleSize(0.06, "t");
    gStyle->SetLabelSize(0.06, "XYZ");
    gStyle->SetTitleSize(0.06, "X");  // Set the X-axis title size
    gStyle->SetTitleSize(0.06, "Y");
    gStyle->SetStatFontSize(0.06); 
    gStyle->SetOptStat(0);

	TH1F *h_z1_1 =  new TH1F("h_z1_1","h_z1_1",125,4,10);
	h_z1_1->GetXaxis()->SetTitle("Z1 MUSIC41");
	TH1F *h_z2_1 =  new TH1F("h_z2_1","h_z2_1",125,4,10);
	h_z2_1->GetXaxis()->SetTitle("Z2 MUSIC42");
	TH1F *h_AoQ_1 =  new TH1F("h_AoQ_1","h_AoQ_1",125,1.8,4.2);
	h_AoQ_1->GetXaxis()->SetTitle("AoQ of incoming");
	
	//tree1->SetLineColor(kRed);
	tree2->SetLineColor(kRed);
	tree3->SetLineColor(kBlack);

	TCanvas *c1_1 = new TCanvas("c1_1", "Comparison of Variables", 800, 600);
    c1_1->Divide(1,3);
    c1_1->cd(1);
    gPad->SetLogy();
    tree1->Draw("id_z1 >> h_z1_1"); //target
    tree2->Draw("id_z1 ","","same"); //target
    tree3->Draw("id_z1 ","","same"); //target
    TLegend *l2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    l2->AddEntry(tree1, "no condition on mult, all events", "l");
    l2->AddEntry(tree2, "event excluded if 1det >= 2 hits", "l");
    l2->AddEntry(tree3, "only no hit or 1st hit", "l");
    l2->Draw();
    
    c1_1->cd(2);
    gPad->SetLogy();
    tree1->Draw("id_z2 >> h_z2_1"); //target
    tree2->Draw("id_z2","","same"); //target
    tree3->Draw("id_z2","","same"); //target
    c1_1->cd(3);
    gPad->SetLogy();
    tree1->Draw("id_AoQ >> h_AoQ_1"); //target
    tree2->Draw("id_AoQ","","same"); //target
    tree3->Draw("id_AoQ","","same"); //target




}