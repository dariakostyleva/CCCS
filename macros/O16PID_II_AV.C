#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std; 
// *** This macro ***
// --- shall give correct transmission ratios
// --- use specifically for oxygen 16 runs
// --- PART II out of II (25/02/21)

void O16PID_II_AV(){
	gBenchmark->Start("Time");
	TString path("/u/avitantz/Analysis01/");
    TString path_out("/u/avitantz/Analysis01/");
	//TString name("s533_50_empty_0085_id_O16_AV");         //ADJUST NUMBER empty
	//TString name("s533_50_gC_6mm_0052_id_O16_AV");        //ADJUST NUMBER gC     6mm
    //TString name("s533_50_gC_12mm_0047_id_O16_AV");       //ADJUST NUMBER gC     12mm
    //TString name("s533_50_C_2cm_0049_id_O16_AV");         //ADJUST NUMBER C      2cm
    //TString name("s533_50_water_emp_0066_id_O16_AV");     //ADJUST NUMBER water  empty
    //TString name("s533_50_water_4cm_0064_id_O16_AV");     //ADJUST NUMBER water  4cm
    //TString name("s533_50_PE_5mm_0080_id_O16_AV");        //ADJUST NUMBER PE     5mm
    TString name("s533_50_PE_37mm_0082_id_O16_AV");       //ADJUST NUMBER PE     37mm
	//Float_t bfield = 4.4848; 	//S2-S4 16O
	//Float_t bfield = 4.2094; 	//S2-S4 15O
	TString fileNameIn, fileNameOut;
	const char * path1 = path.Data();
    const char * path2 = path_out.Data();
	const char * name1 = name.Data();
    fileNameIn.Form("%s%s.root",path1,name1);
	fileNameOut.Form("%s%s_II.root",path2,name1);

	// *** input files and tree
	TFile *f_In = new TFile(fileNameIn,"READ");
	TTree *t_id = (TTree*)f_In->Get("IdTree");
	Long64_t nentries = t_id->GetEntriesFast();
	t_id->SetMakeClass(1);
    
    printf("\033[1;32mThis is part II of analysis. Be sure to also run subsequent parts of analysis afterwards if available. (note: currently not the case 25/02/21)\033[0m\n");

	cout<< "Processing: "<< endl << fileNameIn << endl;

	gStyle->SetOptStat("n");
	gStyle->SetTitleXSize(0.06);
    gStyle->SetTitleYSize(0.06);
    gStyle->SetLabelSize(0.06,"xyz");
    gStyle->SetTitleOffset(1.3,"x");
    gStyle->SetTitleOffset(0.75,"y");
    gStyle->SetPadTopMargin(0.2);
    gStyle->SetPadBottomMargin(0.2);
    gStyle->SetPadLeftMargin(0.2);
    gStyle->SetPadRightMargin(0.2);
    gStyle->SetLegendTextSize(0.06);
    
	// *** output file and tree
	TFile *f_out = new TFile(fileNameOut.Data(),"RECREATE");
    TTree *t_out = new TTree("TreeOut","ID data II");
    double X;
    t_out->Branch("X",&X,"X/D");
    
	//***reading out id branches
    float id_z1_ch, id_z2_ch, de[2], de2[2];
	t_id->SetBranchAddress("id_z1_ch",&id_z1_ch);
    t_id->SetBranchAddress("id_z2_ch",&id_z2_ch);
	t_id->SetBranchAddress("de[2]",&de);
	t_id->SetBranchAddress("de2[2]",&de2);
    
    TH1F *h_de1 = new TH1F("dE MUSIC41","h_de1",640,0,4000);
    TH1F *h_de2_CutO16 = new TH1F("dE MUSIC42","h_de2_CutO16",640,0,4000);
    
    for(int i=0; i<nentries; i++){
        t_id->GetEntry(i);
        h_de1->Fill(id_z1_ch);
    }
    
    TCanvas *PIDCanvas_II = new TCanvas("PIDCanvas_II","MUSIC charge ID",0,0,1440,1080);
    PIDCanvas_II->UseCurrentStyle();
    TF1 *f1 = new TF1("f1","gaus",1,1);
    PIDCanvas_II->Divide(1,2);
    PIDCanvas_II->cd(1);
    gPad->SetLogy();
    h_de1->Draw();
    h_de1->SetTitle(";Energy deposit [channels];Entries");
    h_de1->GetXaxis()->CenterTitle();
    h_de1->GetYaxis()->CenterTitle();
    h_de1->Fit("f1","+","",0,9999);
    h_de1->SetStats(0);
    double Mean1, Sig1, LoBo1, HiBo1;
    Mean1 = f1->GetParameter(1);
    Sig1 = f1->GetParameter(2);
    LoBo1 = Mean1-3*Sig1;
    HiBo1 = Mean1+3*Sig1;
    TLine *t01 = new TLine(LoBo1,h_de1->GetYaxis()->GetXmin(),LoBo1,11000);
    t01->IsVertical();
    t01->SetLineColor(4);
    t01->SetLineWidth(3);
    t01->Draw();
    TLine *t02 = new TLine(HiBo1,h_de1->GetYaxis()->GetXmin(),HiBo1,11000);
    t02->IsVertical();
    t02->SetLineColor(4);
    t02->SetLineWidth(3);
    t02->Draw();
    auto *MUSIC41 = new TLegend(0.6625,0.65,0.8,0.8);
    MUSIC41->SetHeader("MUSIC 41","c");
    MUSIC41->AddEntry(f1,"gaussian fit","l");
    MUSIC41->Draw();
    double LoBoBi1, HiBoBi1, INT1;
    LoBoBi1 = h_de1->FindBin(LoBo1);
    HiBoBi1 = h_de1->FindBin(HiBo1);
    INT1 = h_de1->Integral(LoBoBi1,HiBoBi1,"");
    printf("\033[1;33mNumber of entries within borders of 3-sigma before target is %f\033[0m\n",INT1);
    
    for(int i=0; i<nentries; i++){
        t_id->GetEntry(i);
        if(id_z1_ch > LoBo1 && id_z1_ch < HiBo1){
            h_de2_CutO16->Fill(id_z2_ch);
        }
    }
    
    PIDCanvas_II->cd(2);
    gPad->SetLogy();
    h_de2_CutO16->Draw();
    h_de2_CutO16->SetTitle(";Energy deposit [channels];Entries");
    h_de2_CutO16->GetXaxis()->CenterTitle();
    h_de2_CutO16->GetYaxis()->CenterTitle();
    h_de2_CutO16->Fit("f1","+","",1800,9999);
    h_de2_CutO16->SetStats(0);
    double Mean2, Sig2, LoBo2, HiBo2;
    Mean2 = f1->GetParameter(1);
    Sig2 = f1->GetParameter(2);
    LoBo2 = Mean2-3*Sig2;
    HiBo2 = Mean2+3*Sig2;
    TLine *t03 = new TLine(LoBo2,h_de2_CutO16->GetYaxis()->GetXmin(),LoBo2,11000);
    t03->IsVertical();
    t03->SetLineColor(4);
    t03->SetLineWidth(3);
    t03->Draw();
    auto *MUSIC42 = new TLegend(0.6625,0.65,0.8,0.8);
    MUSIC42->SetHeader("MUSIC 42","c");
    MUSIC42->AddEntry(f1,"gaussian fit","l");
    MUSIC42->Draw();
    double LoBoBi2, HiBoBi2, INT2;
    LoBoBi2 = h_de2_CutO16->FindBin(LoBo2);
    HiBoBi2 = h_de2_CutO16->FindBin(HiBo2);
    INT2 = h_de2_CutO16->Integral(LoBoBi2,641,"");
    printf("\033[1;33mNumber of entries within lower border of 3-sigma after target is %f\033[0m\n",INT2);
    
    double ratio, DeltaR;
    ratio = INT2/INT1;
    DeltaR = ratio*sqrt((1-ratio)/(INT1*ratio));
    printf("\033[1;36mTransmission-ratio of this run is %f\nDelta of this ratio is %f\033[0m\n",ratio,DeltaR);
    
    /* Beam Canvas
    TCanvas *BeamCanvas = new TCanvas("BeamCanvas","Positon plot",0,0,1440,1080);
    BeamCanvas->UseCurrentStyle();
    BeamCanvas->Divide(1,2);
    BeamCanvas->cd(1);
    h_XY_S2->Draw("COLZ");
    h_XY_S2->GetXaxis()->SetRangeUser(-100, 100);
    h_XY_S2->GetYaxis()->SetRangeUser(-66, 66);
    h_XY_S2->SetTitle(";Beam position X;Beam position Y");
    h_XY_S2->GetXaxis()->CenterTitle();
    h_XY_S2->GetYaxis()->CenterTitle();
    //h_XY_S2->SetStats(0);
    BeamCanvas->cd(2);
    h_XY_S4->Draw("COLZ");
    h_XY_S4->GetXaxis()->SetRangeUser(-100, 100);
    h_XY_S4->GetYaxis()->SetRangeUser(-50, 50);
    h_XY_S4->SetTitle(";Beam position X;Beam position Y");
    h_XY_S4->GetXaxis()->CenterTitle();
    h_XY_S4->GetYaxis()->CenterTitle();
    //h_XY_S4->SetStats(0);
    */
    
    /* ID Z versus A/Q
    TCanvas *PIDCanvas_II2 = new TCanvas("PIDCanvas_II2","ID plot",0,0,1440,1080);
    PIDCanvas_II2->UseCurrentStyle();
    h_idC->Draw("COLZ");
    h_idC->GetXaxis()->SetRangeUser(1.85, 2.15);
    h_idC->GetYaxis()->SetRangeUser(4.4, 10.0);
    h_idC->SetTitle(";Mass over charge ratio A/Q;Atomic number Z");
    h_idC->GetXaxis()->CenterTitle();
    h_idC->GetYaxis()->CenterTitle();
    h_idC->SetStats(0);
    */
    
	f_out->cd();
    t_out->Write();
	if(f_out->IsZombie()){
		cerr << "Error: file "<< fileNameOut <<"was not written!"<<endl;
	}
	else {
		cout<< "File "<< fileNameOut <<" was written successfully!"<<endl;
	}
	printf("\033[1;35mContinue work with TreeOut *t_out containing ID data II stored in file %s_II.root processed by O16PID_III_AV.C (note: O16PID_III_AV.C does not exist yet 25/02/21)\033[0m\n",name1);
	gBenchmark->Show("Time");
    gBenchmark->Reset();
	//f_out->Close();
}
