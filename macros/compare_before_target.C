#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std; 
// *** This macro ***
// --- 

void compare_before_target(){
    // Open the first file and retrieve the tree
    TFile *file1 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_PE_37mm_0074_id.root","READ");//16O
    //TFile *file1 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_51_PE_37mm_0114_id.root","READ");//15O
    if (!file1 || file1->IsZombie()) {
        std::cerr << "Error opening file1.root" << std::endl;
        return;
    }
    TTree *tree1 = (TTree*)file1->Get("IdTree");
    if (!tree1) {
        std::cerr << "Error: tree1 not found in file1.root" << std::endl;
        return;
    }

    // Open the second file and retrieve the tree
    TFile *file2 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_empty_0053_id.root","READ"); //16O
    //TFile *file2 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_51_empty_0086_id.root","READ"); //15O
    if (!file2 || file2->IsZombie()) {
        std::cerr << "Error opening file2.root" << std::endl;
        return;
    }
    TTree *tree2 = (TTree*)file2->Get("IdTree");
    if (!tree2) {
        std::cerr << "Error: tree2 not found in file2.root" << std::endl;
        return;
    }
    gStyle->SetTitleSize(0.08, "t");
    gStyle->SetLabelSize(0.08, "XYZ");
    gStyle->SetStatFontSize(0.08); 

    // Create histograms for the variables you want to plot
    TH2F *h_id_t = new TH2F("h_id_t", "id with target",250,1.8,2.2,250,4,10);
    TH2F *h_id_nt = new TH2F("h_id_nt", "id no target",250,1.8,2.2,250,4,10);
    TH1F *h_beta_t =  new TH1F("h_beta_t","beta with target",5000,0.4,0.7);
    TH1F *h_beta_nt =  new TH1F("h_beta_nt","beta no target",5000,0.4,0.7);
    TH1F *h_mhtdc_tof4121_t =  new TH1F("h_mhtdc_tof4121_t","mhtdc tof4121 with target",1000,180,290);
    TH1F *h_mhtdc_tof4121_nt =  new TH1F("h_mhtdc_tof4121_nt","mhtdc tof4121 no target",1000,180,290);
	TH1F *h_id_AoQ_t =  new TH1F("h_id_AoQ_t","AoQ with target",500,1.8,2.2);
	TH1F *h_id_AoQ_nt =  new TH1F("h_id_AoQ_nt","AoQ no target",500,1.8,2.2);
	TH1F *h_z1_t =  new TH1F("h_z1_t","Z1 with target",500,4,10);
	TH1F *h_z1_nt =  new TH1F("h_z1_nt","Z1 no target",500,4,10);
	TH1F *h_id_x2_t =  new TH1F("h_id_x2_t","x2 with target",500,-50,50);
	TH1F *h_id_x2_nt =  new TH1F("h_id_x2_nt","x2 no target",500,-50,50);
	TH1F *h_id_y2_t =  new TH1F("h_id_y2_t","y2 with target",500,-50,50);
	TH1F *h_id_y2_nt =  new TH1F("h_id_y2_nt","y2 no target",500,-50,50);
	TH1F *h_tpc_x_41_t =  new TH1F("h_tpc_x_41_t","tpc41 x with target",500,-50,50);
	TH1F *h_tpc_x_41_nt =  new TH1F("h_tpc_x_41_nt","tpc41 x no target",500,-50,50);
	TH1F *h_tpc_y_41_t =  new TH1F("h_tpc_y_41_t","tpc41 x with target",500,-50,50);
	TH1F *h_tpc_y_41_nt =  new TH1F("h_tpc_y_41_nt","tpc41 x no target",500,-50,50);
	TH1F *h_a_s2_t =  new TH1F("h_a_s2_t","a s2 with target",500,-50,50);
	TH1F *h_a_s2_nt =  new TH1F("h_a_s2_nt","a s2 no target",500,-50,50);
	TH1F *h_b_s2_t =  new TH1F("h_b_s2_t","y s2 with target",500,-50,50);
	TH1F *h_b_s2_nt =  new TH1F("h_b_s2_nt","y s2 no target",500,-50,50);

    // Create a canvas to plot histograms
    TCanvas *c1 = new TCanvas("c1", "Comparison of Variables", 800, 600);
    c1->Divide(2,3);
    c1->cd(1);
    tree1->Draw("id_z1:id_AoQ >> h_id_t"); //target
    c1->cd(2);
    tree2->Draw("id_z1:id_AoQ >> h_id_nt"); //no target
    c1->cd(3);
    gPad->SetLogy();
    tree1->Draw("id_beta >> h_beta_t"); //target
    c1->cd(4);
    gPad->SetLogy();
    tree2->Draw("id_beta >> h_beta_nt"); //no target
    c1->cd(5);
    tree1->Draw("id_AoQ >> h_id_AoQ_t"); //target
    c1->cd(6);
    tree2->Draw("id_AoQ >> h_id_AoQ_nt"); //no target
    c1->Update();
    c1->SaveAs("c1_16O.pdf");

    TCanvas *c1_1 = new TCanvas("c1_1", "Comparison of Variables", 800, 600);
    c1_1->Divide(1,2);
    c1_1->cd(1);
    gPad->SetLogy();
    tree1->Draw("id_z1 >> h_z1_t"); //target
    c1_1->cd(2);
    gPad->SetLogy();
    tree2->Draw("id_z1 >> h_z1_nt"); //no target
    c1_1->Update();
    c1_1->SaveAs("c1_1_16O.pdf");

    TCanvas *c2 = new TCanvas("c2", "Comparison of Variables", 1800, 600);
    c2->Divide(2,2);
    c2->cd(1);
    tree1->Draw("id_x2 >> h_id_x2_t"); //target
    c2->cd(2);
    tree2->Draw("id_x2 >> h_id_x2_nt"); //no target
    c2->cd(3);
    tree1->Draw("id_y2 >> h_id_y2_t"); //target
    c2->cd(4);
    tree2->Draw("id_y2 >> h_id_y2_nt"); //no target
    c2->SaveAs("c2_16O.pdf");

	TCanvas *c2_2 = new TCanvas("c2_2", "Comparison of Variables", 1800, 600);
    c2_2->Divide(2,2);
    c2_2->cd(1);
    tree1->Draw("tpc_ang_x_s2 >> h_a_s2_t"); //target
    c2_2->cd(2);
    tree2->Draw("tpc_ang_x_s2 >> h_a_s2_nt"); //no target
    c2_2->cd(3);
    tree1->Draw("tpc_ang_y_s2 >> h_b_s2_t"); //target
    c2_2->cd(4);
    tree2->Draw("tpc_ang_y_s2 >> h_b_s2_nt"); //no target
    c2_2->SaveAs("c2_2_16O.pdf");

    TCanvas *c3 = new TCanvas("c3", "Comparison of Variables", 1800, 600);
    c3->Divide(2,2);
    c3->cd(1);
    tree1->Draw("tpc_x_41 >> h_tpc_x_41_t"); //target
    c3->cd(2);
    tree2->Draw("tpc_x_41 >> h_tpc_x_41_nt"); //no target
    c3->cd(3);
    tree1->Draw("tpc_y_41 >> h_tpc_y_41_t"); //target
    c3->cd(4);
    tree2->Draw("tpc_y_41 >> h_tpc_y_41_nt"); //no target
    c3->SaveAs("c3_16O.pdf");

    
    




}