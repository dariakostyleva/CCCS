#include "Riostream.h"
#include <bits/stdc++.h> 
using namespace std; 
// *** This macro ***
// --- considers only 0th and 1st hits based on selection TPC21 dt, lt and rt
// --- calibrates std FRS detectors
// --- id_x4,y4 are from TPC41 only!
// --- no cuts are applied
// --- output is *_id.root
// --- output is slightly changed. see below.
// --- further adaptations done by A. Vitantzakis
// --- original is available as calibrate_and_id.C provided by D. Kostyleva
// --- use specifically for oxygen 16 runs
// --- PART I out of II (25/02/21)

void O16PID_I_AV(){
	//change path, file name and corresponding bfield below
	TString path("/data.local2/S533_June21_data/s533jun21/roots/");
    TString path_out("/u/avitantz/Analysis01/");
	TString name("s533_50_gC_12mm_0047");
	Float_t bfield = 4.4848; 	//S2-S4 16O
	//Float_t bfield = 4.2094; 	//S2-S4 15O
	TString fileNameSort, fileNameCalib, fileNameOut;
	const char * path1 = path.Data();
    const char * path2 = path_out.Data();
	const char * name1 = name.Data();
	fileNameSort.Form("%s%s_sort.root", path1,name1);
	fileNameCalib.Form("%s%s_calib.root", path1,name1);
	fileNameOut.Form("%s%s_id_O16_AV.root", path2,name1);

	// *** input files and tree
	TFile *f_in_sort = new TFile(fileNameSort,"READ");
	TTree *t_sort = (TTree*)f_in_sort->Get("SortxTree");
	Long64_t nentries = t_sort->GetEntriesFast();
	t_sort->SetMakeClass(1);

	TFile *f_in_calib = new TFile(fileNameCalib,"READ");	
	TTree *t_calib = (TTree*)f_in_calib->Get("CalibrxTree");
	Long64_t nentries_calib = t_calib->GetEntriesFast();
	t_calib->SetMakeClass(1);
    
    printf("\033[1;32mThis is only part I of analysis. Be sure to also run subsequent parts of analysis afterwards.\033[0m\n");

	cout<< "Processing: "<< endl << fileNameSort << endl << fileNameCalib <<endl;

	if(nentries!=nentries_calib) {
		cerr << "Sort and calib trees have different number of entries!" << endl;
    	return;
    }	
    cout << "Current bfield value is "<<bfield<<". Is this correct? (y/n):";
	char response;
	cin >> response;
	if(response != 'y' && response !='Y'){
		cerr<< "Terminating due to incorrect bfield value." << endl;
		return;
	}
	
	gStyle->SetOptStat("n");
	gStyle->SetTitleXSize(0.05);
    gStyle->SetTitleYSize(0.05);
    gStyle->SetLabelSize(0.05,"xyz");
    gStyle->SetTitleOffset(1.3,"x");
    gStyle->SetTitleOffset(1.3,"y");
    gStyle->SetPadTopMargin(0.2);
    gStyle->SetPadBottomMargin(0.2);
    gStyle->SetPadLeftMargin(0.2);
    gStyle->SetPadRightMargin(0.2);
	
	gBenchmark->Start("Time");

	// *** output file and tree
	TFile *f_out = new TFile(fileNameOut.Data(),"RECREATE");
    TTree *t_id = new TTree("IdTree","Particle identification data");
    Float_t id_z1 ,  id_z2, id_AoQ, tpc_x_21, tpc_x_22, tpc_x_41, tpc_x_42, tpc_y_21, tpc_y_22, tpc_y_41, tpc_y_42, tpc_ang_x_s2, tpc_ang_y_s2, tpc_ang_x_s4, tpc_ang_y_s4;
    Float_t id_x2, id_y2, id_x4, id_y4, s4target_x, s4target_y;
    Float_t mhtdc_tof4121;
    Float_t id_beta;
    Float_t id_z1_ch, id_z2_ch; // uncalibrated music de in channels
    id_z1 = 0.0; id_z2= 0.0; id_AoQ= 0.0; id_z1_ch = 0.0;
    tpc_x_21= 0.0; tpc_x_22= 0.0; tpc_x_41= 0.0; 
    tpc_x_42= 0.0; tpc_y_21= 0.0; tpc_y_22= 0.0; 
    tpc_y_41= 0.0; tpc_y_42= 0.0; tpc_ang_x_s2= 0.0; 
    tpc_ang_y_s2= 0.0; tpc_ang_x_s4= 0.0; tpc_ang_y_s4= 0.0;
    id_x2 = 0.0; id_y2 = 0.0; id_x4 = 0.0; id_y4 = 0.0;
    s4target_x = 0.0; s4target_y = 0.0;
    t_id->Branch("id_z1",&id_z1,"id_z1/F");
    t_id->Branch("id_z1_ch",&id_z1_ch,"id_z1_ch/F");
    t_id->Branch("id_z2_ch",&id_z2_ch,"id_z2_ch/F");
    t_id->Branch("id_z2",&id_z2,"id_z2/F");
    t_id->Branch("id_AoQ",&id_AoQ,"id_AoQ/F");
    t_id->Branch("id_x2",&id_x2,"id_x2/F");
    t_id->Branch("id_y2",&id_y2,"id_y2/F");
    t_id->Branch("id_x4",&id_x4,"id_x4/F");
    t_id->Branch("id_y4",&id_y4,"id_y4/F");
    t_id->Branch("tpc_x_21",&tpc_x_21,"tpc_x_21/F");
    t_id->Branch("tpc_x_22",&tpc_x_22,"tpc_x_22/F");
    t_id->Branch("tpc_x_41",&tpc_x_41,"tpc_x_41/F");
    t_id->Branch("tpc_x_42",&tpc_x_42,"tpc_x_42/F");
    t_id->Branch("tpc_y_21",&tpc_y_21,"tpc_y_21/F");
    t_id->Branch("tpc_y_22",&tpc_y_22,"tpc_y_22/F");
    t_id->Branch("tpc_y_41",&tpc_y_41,"tpc_y_41/F");
    t_id->Branch("tpc_y_42",&tpc_y_42,"tpc_y_42/F");
    t_id->Branch("tpc_ang_x_s2",&tpc_ang_x_s2,"tpc_ang_x_s2/F");
    t_id->Branch("tpc_ang_y_s2",&tpc_ang_y_s2,"tpc_ang_y_s2/F");
    t_id->Branch("tpc_ang_x_s4",&tpc_ang_x_s4,"tpc_ang_x_s4/F");
    t_id->Branch("tpc_ang_y_s4",&tpc_ang_y_s4,"tpc_ang_y_s4/F");
    //what doeas x/F mean? what use does it have? --> it means that variable x is saved as float!

    t_id->Branch("s4target_x",&s4target_x,"s4target_x/F");
    t_id->Branch("s4target_y",&s4target_y,"s4target_y/F");
    t_id->Branch("mhtdc_tof4121",&mhtdc_tof4121,"mhtdc_tof4121/F");
    t_id->Branch("id_beta",&id_beta,"id_beta/F");
    
    //***MUSICs
    Int_t music_e1[8], music_e2[8];
    Float_t de[2], de2[2]; //energy loss in musics at s4
    t_id->Branch("de[2]",&de,"de[2]/F");
    t_id->Branch("de2[2]",&de2,"de2[2]/F");
    const int primary_z = 8;
    Float_t r1 = 0., r2 = 0., r3 = 0., r4 = 0.; 
    Float_t power = 0., sum = 0.;
    Float_t id_v_cor = 0., mhtdc_offset_z_music41 = 0., mhtdc_offset_z_music42 = 0.; 
    Int_t music1_anodes_cnt, music2_anodes_cnt;  
    Int_t music_cond1 = 10, music_cond2 = 4096-10;
    //calibration coefficients
    Float_t mhtdc_vel_a_music41[4], mhtdc_vel_a_music42[4]; // MUSICs correction for velocity MHTDC
	mhtdc_vel_a_music41[0]=12.2831; 
	mhtdc_vel_a_music41[1]=718.616;
	mhtdc_vel_a_music41[2]=0.0;
	mhtdc_vel_a_music41[3]=0.0;
	mhtdc_vel_a_music42[0]=111.783; 
	mhtdc_vel_a_music42[1]=712.253;
	mhtdc_vel_a_music42[2]=0.0;
	mhtdc_vel_a_music42[3]=0.0;

	//***Scintillators, only SCI21 at S2
	Int_t tof_select=1;
	if(tof_select==1) printf("Beta is calculated using MHTDC\n");
	else if(tof_select==2) printf("Beta is calculated using TAC\n");
	else printf("tof_select is set to %d\n",tof_select);	

	Int_t dt_21l_41l, dt_21r_41r; //tac
	Int_t tdc_sc41l[10], tdc_sc41r[10], tdc_sc21l[10], tdc_sc21r[10]; //mhtdc
	//how can these be stored as integers? I'd expect these to be decimals.
	Float_t id_tofoff2, id_path2, sci_tof2, sci_tof2_calib;
	Float_t sci_tofll2 = 0., sci_tofrr2 = 0.;
	//calibration coefficients
	//TAC
	Float_t tac_factor22_41ll, tac_factor22_41rr;
	Int_t tac_cond1, tac_cond2;
	bool sci_b_tofll2, sci_b_tofrr2;
	tac_factor22_41ll = 18.7611; //SC41L-SC22L [ps/ch] 
	tac_factor22_41rr = 18.5460; //SC41R-SC22R [ps/ch] 
	id_tofoff2 =  223722; // offset (ps) 
	id_path2   =  123454; // path/c (ps)
	tac_cond1 = 2500; tac_cond2 = 200000;
	//MultihitTDC
	Float_t speed_light= 0.299792458; //m per ns 
	Float_t mhtdc_factor_ch_to_ns = 0.025; //ns per channel
	Float_t mhtdc_offset_41_21  =  182.38 + 4.8641; //ns //s533 16^O
	Float_t mhtdc_length_sc2141 = 38.11561336; // SCI 21-41 s533 meter!!!!

	//TPCs, only TPC21 and TPC22 at S2
	//HERE: add my own calibration data aka adjust data taken for identification -> change arrays! -> done!
	//might need SOLUTION because not all TPCs were recalibrated by me! Solution successfully applied!
	Float_t tpc_xraw[7][2], tpc_yraw[7][4]; // 21 - 0, 22 - 1, 41 -4, 42 - 5 first index;  number of cathode(x) or anode(y) second index
	Float_t tpc_x[7], tpc_y[7]; // 21 - 0, 22 - 1, 41 -4, 42 - 5
	Bool_t b_tpc_xy[7];			// 21 - 0, 22 - 1, 41 -4, 42 - 5
	Float_t	tpc_angle_x_s2_foc_21_22, tpc_angle_y_s2_foc_21_22,	tpc_x_s2_foc_21_22,	tpc_y_s2_foc_21_22;
	Float_t tpc_angle_x_s4, tpc_angle_y_s4, tpc_x_s4, tpc_y_s4;
	Int_t tpc_nhit_dt[7][4];	// 1st index 21 - 0, 22 - 1, 41 -4, 42 - 5, 2nd index 4 anodes 
	Int_t tpc_nhit_rt[7][2];
	Int_t tpc_nhit_lt[7][2];
	bool id_b_x2, id_b_x4;
	Float_t dist_focS2 = 2012.5; // degrader disk position standard
	Float_t dist_TPC21 =  604.0;
	Float_t dist_TPC22 = 1782.5;
	Float_t dist_TPC21_TPC22, dist_TPC21_focS2;
	dist_TPC21_TPC22 = dist_TPC22 - dist_TPC21;
	dist_TPC21_focS2 = dist_TPC21 - dist_focS2;
	Float_t dist_focS4   = 1500.0; // standard
	Float_t dist_S4target= 1020.0; // check!!!, was 1212.5
	Float_t dist_S4target_focS4 = dist_S4target - dist_focS4;
	//Float_t dist_TPC41 =  370.0; //S533 2021/June/19
	//Float_t dist_TPC42 = 1730.0; //S533 2021/June/19 approximate
	Float_t dist_TPC41 =  250.0; //S533 my photos
	Float_t dist_TPC42 = 1690.0; //S533 my photos
	Float_t dist_TPC41_TPC42, dist_TPC42_focS4, dist_TPC41_S4target;
	dist_TPC41_TPC42 = dist_TPC42 - dist_TPC41;
	dist_TPC42_focS4 = dist_focS4 - dist_TPC42; 
	dist_TPC41_S4target = dist_S4target - dist_TPC41;
	Float_t dispersion[2]; // BARB 2021-June S2-S4, 1.5m version
	dispersion[0] = -6.287;
	dispersion[1] =  7.981;
	Float_t magnification =  1.268; // BARB 2021-June S2-S4, 1.5m version
	Float_t id_rho, id_brho, id_gamma;

	const double f = 931.4940/299.792458; /* factor needed for aoq calculation.. the u/(c*10^-6) factor  */

	//***reading out sort branches
	t_sort->SetBranchAddress("FRSSortEvent.music_e1[8]",&music_e1);
	t_sort->SetBranchAddress("FRSSortEvent.music_e2[8]",&music_e2);
	t_sort->SetBranchAddress("FRSSortEvent.dt_21l_41l",&dt_21l_41l);
	t_sort->SetBranchAddress("FRSSortEvent.dt_21r_41r",&dt_21r_41r);
	t_sort->SetBranchAddress("FRSSortEvent.tdc_sc41l[10]",&tdc_sc41l);
	t_sort->SetBranchAddress("FRSSortEvent.tdc_sc41r[10]",&tdc_sc41r);
	t_sort->SetBranchAddress("FRSSortEvent.tdc_sc21l[10]",&tdc_sc21l);
	t_sort->SetBranchAddress("FRSSortEvent.tdc_sc21r[10]",&tdc_sc21r);
	t_sort->SetBranchAddress("FRSSortEvent.tpc_nhit_dt[7][4]",&tpc_nhit_dt);
	t_sort->SetBranchAddress("FRSSortEvent.tpc_nhit_rt[7][2]",&tpc_nhit_rt);
	t_sort->SetBranchAddress("FRSSortEvent.tpc_nhit_lt[7][2]",&tpc_nhit_lt);
	
	
	//***reading out calib branches
    //adjust read-out -> change arrays! -> done!
	t_calib->SetBranchAddress("FRSCalibrEvent.tpc_x[7]",&tpc_x);
    t_calib->SetBranchAddress("FRSCalibrEvent.tpc_xraw[7][2]",&tpc_xraw);
	t_calib->SetBranchAddress("FRSCalibrEvent.tpc_y[7]",&tpc_y);
    t_calib->SetBranchAddress("FRSCalibrEvent.tpc_yraw[7][4]",&tpc_yraw);
	t_calib->SetBranchAddress("FRSCalibrEvent.b_tpc_xy[7]",&b_tpc_xy);
     
	TH1F *h_id_z1 =  new TH1F("h_id_z1","h_id_z1",500,0,10);
	TH1F *h_id_z1_ch =  new TH1F("h_id_z1_ch","h_id_z1_ch",1000,0,4096);
	TH1F *h_id_z2 =  new TH1F("h_id_z2","h_id_z2",500,0,12);
	TH1F *h_id_AoQ =  new TH1F("h_id_AoQ","h_id_AoQ",5000,0,10);
	TH1F *h_id_beta =  new TH1F("h_id_beta","h_id_beta",5000,0,1);
	TH1F *h_mhtdc_tof4121 =  new TH1F("h_mhtdc_tof4121","h_mhtdc_tof4121",500,0,500);
	TH2F *h_id =  new TH2F("h_id","h_id",1000,1.5,2.5,1000,3,10);
    TH2F *h_idC = new TH2F("PID","copy",1000,1.5,2.5,1000,3,10);
	TH2F *h_id_cut =  new TH2F("h_id_cut","h_id_cut",1000,1.5,2.5,1000,3,10);
	TH2F *h_target = new TH2F("h_target","h_target",100,-100,100,100,-100,100);
    TH2F *h_XY_S2 = new TH2F("Beam position tracking at S2","h_XY_S2",100,-100,100,100,-100,100);
    TH2F *h_XY_S4 = new TH2F("Beam position tracking at S4","h_XY_S4",100,-100,100,100,-100,100);
	TH1F *h_id_x4 =  new TH1F("h_id_x4","h_id_x4",500,-50,50);
	TH1F *h_id_y4 =  new TH1F("h_id_y4","h_id_y4",500,-50,50);
    TH1F *h_de1 = new TH1F("dE MUSIC41","h_de1",640,0,4000);
    TH1F *h_de2 = new TH1F("dE MUSIC42 No Cut","h_de2",640,0,4000);
    TH1F *h_de2_CutO16 = new TH1F("dE MUSIC42","h_de2_CutO16",640,0,4000);
	TH1I *h_tpc_nhit_dt[7][4];
	TH1I *h_tpc_nhit_rt[7][2];
	TH1I *h_tpc_nhit_lt[7][2];
    for (int i = 0; i < 7; ++i){
        for (int j = 0; j < 4; ++j){
            // Generate a unique name for each histogram
            TString histName = Form("h_tpc_nhit_dt[%d][%d]", i, j);
            TString histTitle = Form("h_tpc_nhit_dt %d %d", i, j);
            h_tpc_nhit_dt[i][j] = new TH1I(histName, histTitle, 10, 0, 10);
            h_tpc_nhit_dt[i][j]->GetXaxis()->SetTitle("number of hits");
        }
    }
    for (int i = 0; i < 7; ++i){
        for (int j = 0; j < 2; ++j){
            // Generate a unique name for each histogram
            TString histName_rt = Form("h_tpc_nhit_rt[%d][%d]", i, j);
            TString histTitle_rt = Form("h_tpc_nhit_rt %d %d", i, j);
            h_tpc_nhit_rt[i][j] = new TH1I(histName_rt, histTitle_rt, 10, 0, 10);
            h_tpc_nhit_rt[i][j]->GetXaxis()->SetTitle("number of hits");
            TString histName_lt = Form("h_tpc_nhit_lt[%d][%d]", i, j);
            TString histTitle_lt = Form("h_tpc_nhit_lt %d %d", i, j);
            h_tpc_nhit_lt[i][j] = new TH1I(histName_lt, histTitle_lt, 10, 0, 10);
            h_tpc_nhit_lt[i][j]->GetXaxis()->SetTitle("number of hits");
        }
    }
    TH1I *h_tdc_sc21l[10]; TH1I *h_tdc_sc21r[10];
    for (int i = 0; i < 10; ++i){
    	TString histNameL = Form("h_tdc_sc21l[%d]", i);
        TString histTitleL = Form("h_tdc_sc21l %d", i);
        h_tdc_sc21l[i] = new TH1I(histNameL, histTitleL, 1000, 0, 140000);
        TString histNameR = Form("h_tdc_sc21r[%d]", i);
        TString histTitleR = Form("h_tdc_sc21r %d", i);
        h_tdc_sc21r[i] = new TH1I(histNameR, histTitleR, 1000, 0, 140000);
    }
	
	//***main loop over events
	//nentries = 10000;
	printf("Total number of events is %lld \n",nentries);
	
	//return;
	for (Int_t i=0;i<nentries;i++) { //*** start of events loop
		if(i % 100000 == 0 && i!=0) printf("Events processed %d \n",i);
		t_sort->GetEntry(i);
		t_calib->GetEntry(i);

		//condition to take only 0th and 1st hit in TPC41 dt, lt and rt and SCI21 L and R
		if (/*tpc_nhit_dt[0][0] < 2 && tpc_nhit_dt[0][1] < 2 && tpc_nhit_dt[0][2] < 2 && tpc_nhit_dt[0][3] < 2 &&
			tpc_nhit_rt[0][0] < 2 && tpc_nhit_rt[0][1] < 2 &&
			tpc_nhit_lt[0][0] < 2 && tpc_nhit_lt[0][1] < 2 &&
			tpc_nhit_dt[1][0] < 2 && tpc_nhit_dt[1][1] < 2 && tpc_nhit_dt[1][2] < 2 && tpc_nhit_dt[1][3] < 2 &&
			tpc_nhit_rt[1][0] < 2 && tpc_nhit_rt[1][1] < 2 &&
			tpc_nhit_lt[1][0] < 2 && tpc_nhit_lt[1][1] < 2 &&*/
			tpc_nhit_dt[4][0] < 2 && tpc_nhit_dt[4][1] < 2 && tpc_nhit_dt[4][2] < 2 && tpc_nhit_dt[4][3] < 2 &&
			tpc_nhit_rt[4][0] < 2 && tpc_nhit_rt[4][1] < 2 &&
			tpc_nhit_lt[4][0] < 2 && tpc_nhit_lt[4][1] < 2 &&
			tdc_sc21l[1]==0 && tdc_sc21l[2]==0 &&  tdc_sc21l[3]==0 &&
			tdc_sc21r[1]==0 && tdc_sc21r[2]==0 &&  tdc_sc21r[3]==0){
		/*if ((tpc_nhit_dt[0][0] >= 2 || tpc_nhit_dt[0][1] >= 2 || tpc_nhit_dt[0][2] >= 2 || tpc_nhit_dt[0][3] >= 2) &&
			(tpc_nhit_rt[0][0] >= 2 || tpc_nhit_lt[0][0] >= 2) &&
			(tpc_nhit_rt[0][1] >= 2 || tpc_nhit_lt[0][1] >= 2) &&
			(tpc_nhit_dt[1][0] >= 2 || tpc_nhit_dt[1][1] >= 2 || tpc_nhit_dt[1][2] >= 2 || tpc_nhit_dt[1][3] >= 2) &&
			(tpc_nhit_rt[1][0] >= 2 || tpc_nhit_lt[1][0] >= 2) &&
			(tpc_nhit_rt[1][1] >= 2 || tpc_nhit_lt[1][1] >= 2) &&
			(tpc_nhit_dt[4][0] >= 2 || tpc_nhit_dt[4][1] >= 2 || tpc_nhit_dt[4][2] >= 2|| tpc_nhit_dt[4][3] >= 2) &&
			(tpc_nhit_rt[4][0] >= 2 || tpc_nhit_lt[4][0] >= 2) &&
			(tpc_nhit_rt[4][1] >= 2 || tpc_nhit_lt[4][1] >= 2) &&
			(tdc_sc21l[1]!=0 && tdc_sc21l[2]!=0 &&  tdc_sc21l[3]!=0) &&
			(tdc_sc21r[1]!=0 && tdc_sc21r[2]!=0 &&  tdc_sc21r[3]!=0)){ continue;}*/
			//if (tpc_nhit_dt[0][0] >= 2) { continue;}

			// BETA calculation
			if(1 == tof_select){ //MultihitTDC
				if(0!=tdc_sc21l[0] && 0!=tdc_sc41r[0] && 0!=tdc_sc41l[0] && 0!=tdc_sc41r[0]){
	    			mhtdc_tof4121 = mhtdc_factor_ch_to_ns*( 0.5*(tdc_sc41l[0]+tdc_sc41r[0])  - 0.5*(tdc_sc21l[0]+tdc_sc21r[0]) ) + mhtdc_offset_41_21;
	    		}
				id_beta = (mhtdc_length_sc2141/mhtdc_tof4121) / speed_light;
                //printf("beta = %f\n", id_beta);
			}
			else if(2 == tof_select) { //TAC
				sci_b_tofll2 = false; sci_b_tofrr2 = false;
				sci_tofll2 = dt_21l_41l*tac_factor22_41ll; 
				sci_tofrr2 = dt_21r_41r*tac_factor22_41rr;
				if(sci_tofll2 > tac_cond1 && sci_tofll2 < tac_cond2) sci_b_tofll2 = true; 
				if(sci_tofrr2 > tac_cond1 && sci_tofrr2 < tac_cond2) sci_b_tofrr2 = true;
				if(true==sci_b_tofll2 && true==sci_b_tofrr2){
					sci_tof2 = (sci_tofll2 + sci_tofrr2)/2.0 ;
					sci_tof2_calib   =  -1.0*sci_tof2 + id_tofoff2;
				}
				id_beta = id_path2/sci_tof2_calib ;
                //printf("beta = %f\n", id_beta);
			}
			else {
				printf("Beta is not calculated!\n"); return;
			}

			music1_anodes_cnt = 0;
			music2_anodes_cnt = 0;

			for (int i=0;i<8;i++){
				//printf("music_e2[%d] = %d\n",i,music_e2[i]);
				if(music_e1[i]>music_cond1 && music_e1[i]<music_cond2) music1_anodes_cnt++;
				if(music_e2[i]>music_cond1 && music_e1[i]<music_cond2) music2_anodes_cnt++;
			} //why music_e1 instead of music_e2 in the last line? Is this correct?

			// Z calculation MUSIC41
			if (8 == music1_anodes_cnt) {
	    		r1 = music_e1[0]*music_e1[1];
	    		r2 = music_e1[2]*music_e1[3];
	    		r3 = music_e1[4]*music_e1[5];
	    		r4 = music_e1[6]*music_e1[7];
				if ( (r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0) ) {
					de[0] = sqrt( sqrt( sqrt(r1) * sqrt(r2) ) * sqrt( sqrt(r3) * sqrt(r4) ) );
				}
			}
	   		if (5 <= music1_anodes_cnt){
	     		Float_t temp_de1 = 1.0;
	     		Int_t temp_count1 = 0;
	     		for(int ii=0; ii<8; ii++){
		 			temp_de1 *= music_e1[ii];
		 			temp_count1 ++;
	     		}
	     		de[0] = TMath::Power(temp_de1, 1./((float)(temp_count1)));
	     	}
			if((de[0]>0.0) && (id_beta>0.0) && (id_beta<1.0)){
	      		power = 1., sum = 0.;
	      		for (int i=0;i<4;i++){
	  	  			sum += power * mhtdc_vel_a_music41[i];
	  	  			power *= (1.0/id_beta)*(1.0/id_beta);
	      		}
	      		id_v_cor = sum;
	      		if (id_v_cor > 0.0){
	      			id_z1 = primary_z * sqrt(de[0]/id_v_cor) + mhtdc_offset_z_music41;
	      			id_z1_ch = de[0];
	      		}
			}
			//printf("id_z1 %4.2f ",id_z1);
			//printf("id_z1_ch %4.2f\n",id_z1_ch);

			// Z calculation MUSIC42
			r1 = 0.; r2 = 0.; r3 = 0.; r4 = 0.; id_v_cor = 0; //reset
			if (8 == music2_anodes_cnt) {
	    		r1 = music_e2[0]*music_e2[1];
	    		r2 = music_e2[2]*music_e2[3];
	    		r3 = music_e2[4]*music_e2[5];
	    		r4 = music_e2[6]*music_e2[7];
				if ( (r1 > 0) && (r2 > 0) && (r3 > 0) && (r4 > 0) ) {
					de2[0] = sqrt( sqrt( sqrt(r1) * sqrt(r2) ) * sqrt( sqrt(r3) * sqrt(r4) ) );
					//printf("de2[0] %4.2f\n",de2[0]);
				}
			}
			if (5 <= music2_anodes_cnt){
	     		Float_t temp_de2 = 1.0;
	     		Int_t temp_count2 = 0;
	     		for(int ii=0; ii<8; ii++){
		 			temp_de2 *= music_e2[ii];
		 			temp_count2 ++;
	     		}
	     		de2[0] = TMath::Power(temp_de2, 1./((float)(temp_count2)));
	     	}
			if((de2[0]>0.0) && (id_beta>0.0) && (id_beta<1.0)){
	      		power = 1., sum = 0.;
	      		for (int i=0;i<4;i++){
	  	  			sum += power * mhtdc_vel_a_music42[i];
	  	  			power *= (1.0/id_beta)*(1.0/id_beta);
	      		}
	      		id_v_cor = sum;
	      		if (id_v_cor > 0.0){
	      			id_z2 = primary_z * sqrt(de2[0]/id_v_cor) + mhtdc_offset_z_music42;
                    id_z2_ch = de2[0];
	      			//printf("id_z2 %4.2f\n",id_z2);
	      		}
			}
			//printf("id_z2 %4.2f\n",id_z2);
			//ADJUST THE ARRAYS ACCORDING TO MY CALIBRATION!! -> should do it...? works!
			if(b_tpc_xy[0]) {tpc_x_21 = ((0.00777597*tpc_xraw[0][0]-0.380766)+(0.00778137*tpc_xraw[0][0]-0.3648)+(0.00778531*tpc_xraw[0][1]+0.566669)+(0.00794302*tpc_xraw[0][1]+0.593338))*0.25; tpc_y_21 = ((0.00387158*tpc_yraw[0][0]-55.6943)+(0.00386024*tpc_yraw[0][1]-55.743)+(0.00385325*tpc_yraw[0][2]-55.6308)+(0.00385332*tpc_yraw[0][3]-55.762))*0.25;}
			if(b_tpc_xy[1]) {tpc_x_22 = ((0.00948*tpc_xraw[1][1]+5.282)+(0.009481*tpc_xraw[1][1]+5.283))*0.5; tpc_y_22 = ((0.00392*tpc_yraw[1][2]-57.46)+(0.003882*tpc_yraw[1][3]-56.11))*0.5;}
			//if(b_tpc_xy[0]) {tpc_x_21 = tpc_x[0]; tpc_y_21 = tpc_y[0];}
			//if(b_tpc_xy[1]) {tpc_x_22 = tpc_x[1]; tpc_y_22 = tpc_y[1];}
			if(b_tpc_xy[4]) {tpc_x_41 = tpc_x[4]; tpc_y_41 = tpc_y[4];}
			if(b_tpc_xy[5]) {tpc_x_42 = tpc_x[5]; tpc_y_42 = tpc_y[5];}

			//AoQ calculation
			//ADJUST THE ARRAYS ACCORDING TO MY CALIBRATION!! -> should do it...? works!
			if(b_tpc_xy[0] && b_tpc_xy[1]){
                tpc_angle_x_s2_foc_21_22 = (tpc_x_22 - tpc_x_21)/dist_TPC21_TPC22*1000.;
                tpc_angle_y_s2_foc_21_22 = (tpc_y_22 - tpc_y_21)/dist_TPC21_TPC22*1000.;
				//tpc_angle_x_s2_foc_21_22 = (tpc_x[1] - tpc_x[0])/dist_TPC21_TPC22*1000.;
	    		//tpc_angle_y_s2_foc_21_22 = (tpc_y[1] - tpc_y[0])/dist_TPC21_TPC22*1000.;
	    		tpc_ang_x_s2 = tpc_angle_x_s2_foc_21_22; tpc_ang_y_s2 = tpc_angle_y_s2_foc_21_22;
                tpc_x_s2_foc_21_22 = -tpc_angle_x_s2_foc_21_22 * dist_TPC21_focS2/1000. + tpc_x_21;
                tpc_y_s2_foc_21_22 = -tpc_angle_y_s2_foc_21_22 * dist_TPC21_focS2/1000. + tpc_y_21;
	    		//tpc_x_s2_foc_21_22 = -tpc_angle_x_s2_foc_21_22 * dist_TPC21_focS2/1000. + tpc_x[0];
	    		//tpc_y_s2_foc_21_22 = -tpc_angle_y_s2_foc_21_22 * dist_TPC21_focS2/1000. + tpc_y[0];
	    		id_x2 = tpc_x_s2_foc_21_22; id_y2 = tpc_y_s2_foc_21_22;
	    	}
	    	/* old piece of code with position calculated at x4 focus from both TPC41 and 42
	    	if(b_tpc_xy[4] && b_tpc_xy[5]){
	    		tpc_angle_x_s4 = (tpc_x[5] - tpc_x[4])/dist_TPC41_TPC42*1000.;
	    		tpc_angle_y_s4 = (tpc_y[5] - tpc_y[4])/dist_TPC41_TPC42*1000.;
	    		tpc_ang_x_s4 = tpc_angle_x_s4; tpc_ang_y_s4 = tpc_angle_y_s4;
	    		tpc_x_s4 = tpc_angle_x_s4 * dist_TPC42_focS4/1000. + tpc_x[5];
	    		tpc_y_s4 = tpc_angle_y_s4 * dist_TPC42_focS4/1000. + tpc_y[5];
	    		s4target_x = (tpc_angle_x_s4/1000.* dist_S4target_focS4)+tpc_x_s4;
				s4target_y = (tpc_angle_y_s4/1000.* dist_S4target_focS4)+tpc_y_s4;
	    		id_x4 = tpc_x_s4; id_y4 = tpc_y_s4;
	    	}*/
            
	    	if(b_tpc_xy[4] && b_tpc_xy[5]){
	    		tpc_angle_x_s4 = (tpc_x[5] - tpc_x[4])/dist_TPC41_TPC42*1000.;
	    		tpc_angle_y_s4 = (tpc_y[5] - tpc_y[4])/dist_TPC41_TPC42*1000.;
	    		tpc_ang_x_s4 = tpc_angle_x_s4; tpc_ang_y_s4 = tpc_angle_y_s4;
	    	}

	    	if(b_tpc_xy[4]){
	    		tpc_x_s4 = tpc_x[4]; tpc_y_s4 = tpc_y[4];
	    		id_x4 = tpc_x_s4; id_y4 = tpc_y_s4;
	    		s4target_x = (tpc_angle_x_s4/1000.* dist_TPC41_S4target)+tpc_x_s4;
				s4target_y = (tpc_angle_y_s4/1000.* dist_TPC41_S4target)+tpc_y_s4;
	    	}
	    	
	    	id_b_x2 = false; id_b_x4 = false;
	    	if(id_x2 > -100.0 && id_x2 < 100.0) id_b_x2 = true;
	    	if(id_x4 > -100.0 && id_x4 < 100.0) id_b_x4 = true;

	    	if (id_b_x2 && id_b_x4 /*do we miss the argument id_b_xX = true here?*/ ){
				id_rho = (1. - (id_x4 - magnification * id_x2) / 1000. / dispersion[1]);
	    		id_brho = (fabs(bfield) + fabs(bfield))/ 2. * id_rho;
				id_gamma = 1./sqrt(1. - id_beta*id_beta);
				id_AoQ = id_brho/id_beta/id_gamma/f;
				//printf("id_AoQ %4.2f\n",id_AoQ);
			}

			h_id_z1->Fill(id_z1);
			h_id_z1_ch->Fill(id_z1_ch);
			h_id_z2->Fill(id_z2);
			h_id_AoQ->Fill(id_AoQ);
			h_id_beta->Fill(id_beta);
			h_mhtdc_tof4121->Fill(mhtdc_tof4121);
			h_id->Fill(id_AoQ,id_z1);
            h_idC->Fill(id_AoQ,id_z1);
            h_de1->Fill(de[0]);
            h_de2->Fill(de2[0]);
            h_de2_CutO16->Fill(de2[0]);
            /* failed try on cut
            TF1 *f1=new TF1("f1","gaus",1,1);
            h_de1->Fit("f1","Q","",0,9999);
            double Mean1, Sig1, LoBo1, HiBo1;
            Mean1 = f1->GetParameter(1);
            Sig1 = f1->GetParameter(2);
            LoBo1 = Mean1-3.5*Sig1;
            HiBo1 = Mean1+3.5*Sig1;
            if(de[0] > LoBo1 && de[0] < HiBo1){
            h_de2_CutO16->Fill(de2[0]);
            }
            */
            if(id_beta > 0.604 ) h_id_cut->Fill(id_AoQ,id_z1);
			h_target->Fill(s4target_x,s4target_y);
            h_XY_S2->Fill(id_x2,id_y2);
            h_XY_S4->Fill(id_x4,id_y4);
			h_id_x4->Fill(id_x4);
			h_id_y4->Fill(id_y4);
			for (int i = 0; i < 7; ++i){
	        	for (int j = 0; j < 4; ++j){	
	            	h_tpc_nhit_dt[i][j]->Fill(tpc_nhit_dt[i][j]);
	        	}
	        	for (int j = 0; j < 2; ++j){	
	            	h_tpc_nhit_rt[i][j]->Fill(tpc_nhit_rt[i][j]);
	            	h_tpc_nhit_lt[i][j]->Fill(tpc_nhit_lt[i][j]);
	        	}
	    	}
	    	for (int i = 0; i < 10; ++i){
	    		h_tdc_sc21l[i]->Fill(tdc_sc21l[i]);
	    		h_tdc_sc21r[i]->Fill(tdc_sc21r[i]);
	    	}

			t_id->Fill();
		} // end of condition on hits
    }//*** end of events loop
	
	TCanvas *cc = new TCanvas("cc", "ID canvas AV", 0, 0, 800, 600);
	cc->Divide(3,3);
	cc->cd(1);
	gPad->SetLogy();
	h_id_z1->Draw();
	cc->cd(2);
	gPad->SetLogy();
	h_id_z2->Draw();
	cc->cd(3);
	gPad->SetLogy();
	h_id_AoQ->Draw();
	cc->cd(4);
	h_id_z1_ch->Draw();
	//h_id_beta->Draw();
	cc->cd(5);
	h_mhtdc_tof4121->Draw();
	cc->cd(6);
	h_id->Draw();
	cc->cd(7);
	h_target->Draw();
	cc->cd(8);
	h_id_x4->Draw();
	cc->cd(9);
	h_id_y4->Draw();
    
    TCanvas *BeamCanvas = new TCanvas("BeamCanvas","Positon plot",0,0,1440,1080);
    BeamCanvas->UseCurrentStyle();
    /* Beam at S2 "not working"
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
    */
    h_XY_S4->Draw("COLZ");
    h_XY_S4->GetXaxis()->SetRangeUser(-100, 100);
    h_XY_S4->GetYaxis()->SetRangeUser(-50, 50);
    h_XY_S4->SetTitle(";Beam position X [mm];Beam position Y [mm]");
    h_XY_S4->GetXaxis()->CenterTitle();
    h_XY_S4->GetYaxis()->CenterTitle();
    h_XY_S4->SetStats(0);
    
    TCanvas *AutoPIDCanvas2 = new TCanvas("AutoPIDCanvas2","ID plot",0,0,1440,1080);
    AutoPIDCanvas2->UseCurrentStyle();
    h_idC->Draw("COLZ");
    h_idC->GetXaxis()->SetRangeUser(1.85, 2.15);
    h_idC->GetYaxis()->SetRangeUser(4.4, 10.0);
    h_idC->SetTitle(";Mass over charge ratio A/Q;Atomic number Z");
    h_idC->GetXaxis()->CenterTitle();
    h_idC->GetYaxis()->CenterTitle();
    h_idC->SetStats(0);
    
    TCanvas *AutoPIDCanvas = new TCanvas("AutoPIDCanvas","MUSIC charge measurement",0,0,1440,1080);
    AutoPIDCanvas->UseCurrentStyle();
    TF1 *f1=new TF1("f1","gaus",1,1);
    AutoPIDCanvas->Divide(1,2);
    AutoPIDCanvas->cd(1);
    gPad->SetLogy();
    h_de1->Draw();
    h_de1->SetTitle(";Channels;Entries");
    h_de1->GetXaxis()->CenterTitle();
    h_de1->GetYaxis()->CenterTitle();
    h_de1->Fit("f1","Q+","",0,9999);
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
    double LoBoBi1, HiBoBi1, INT1;
    LoBoBi1 = h_de1->FindBin(LoBo1);
    HiBoBi1 = h_de1->FindBin(HiBo1);
    INT1 = h_de1->Integral(LoBoBi1,HiBoBi1,"");
    printf("\033[1;31mOUTDATED: \033[0mNumber of entries within borders of 3-sigma before target is %f\n",INT1);
    AutoPIDCanvas->cd(2);
    gPad->SetLogy();
    h_de2_CutO16->Draw();
    h_de2_CutO16->SetTitle(";Channels;Entries");
    h_de2_CutO16->GetXaxis()->CenterTitle();
    h_de2_CutO16->GetYaxis()->CenterTitle();
    h_de2_CutO16->Fit("f1","Q+","",2000,9999);
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
    double LoBoBi2, HiBoBi2, INT2;
    LoBoBi2 = h_de2_CutO16->FindBin(LoBo2);
    HiBoBi2 = h_de2_CutO16->FindBin(HiBo2);
    INT2 = h_de2_CutO16->Integral(LoBoBi2,641,"");
    printf("\033[1;31mOUTDATED: \033[0mNumber of entries within lower border of 3-sigma after target is %f\n",INT2);
    
    double ratio, DeltaR;
    ratio = INT2/INT1;
    DeltaR = ratio*sqrt((1-ratio)/(INT1*ratio));
    printf("\033[1;31mOUTDATED: \033[0mTransmission-ratio of this run is %f\n\033[1;31mOUTDATED: \033[0mDelta of this ratio is %f\n",ratio,DeltaR);
    
	/* series of canvasses and plots follow which are of no further use for as is now
    TCanvas *c_nhit_tpc = new TCanvas("c_nhit_tpc", "TPC dt nhit histos", 1200, 800);
	c_nhit_tpc->Divide(4,7); // Divide the canvas into a grid
	for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 4; ++j) {
        	if(i==2 || i==3 || i==6) continue;
            int padNumber = i * 4 + j + 1; // Calculate pad number
            c_nhit_tpc->cd(padNumber);             // Move to the correct pad
            h_tpc_nhit_dt[i][j]->Draw();          // Draw the histogram
        }
    }

    TCanvas *c_nhit_tpc_21 = new TCanvas("c_nhit_tpc_21", "TPC21 nhit histos", 1200, 800);
    c_nhit_tpc_21->Divide(4,2);
    c_nhit_tpc_21->cd(1);
    h_tpc_nhit_dt[0][0]->Draw();
    c_nhit_tpc_21->cd(2);
    h_tpc_nhit_dt[0][1]->Draw();
    c_nhit_tpc_21->cd(3);
    h_tpc_nhit_dt[0][2]->Draw();
    c_nhit_tpc_21->cd(4);
    h_tpc_nhit_dt[0][3]->Draw();
    c_nhit_tpc_21->cd(5);
    h_tpc_nhit_rt[0][0]->Draw();
    c_nhit_tpc_21->cd(6);
    h_tpc_nhit_rt[0][1]->Draw(); 
    c_nhit_tpc_21->cd(7);
    h_tpc_nhit_lt[0][0]->Draw();
    c_nhit_tpc_21->cd(8);
    h_tpc_nhit_lt[0][1]->Draw();

    TCanvas *c_nhit_tpc_41 = new TCanvas("c_nhit_tpc_41", "TPC41 nhit histos", 1200, 800);
    c_nhit_tpc_41->Divide(4,2);
    c_nhit_tpc_41->cd(1);
    h_tpc_nhit_dt[4][0]->Draw();
    c_nhit_tpc_41->cd(2);
    h_tpc_nhit_dt[4][1]->Draw();
    c_nhit_tpc_41->cd(3);
    h_tpc_nhit_dt[4][2]->Draw();
    c_nhit_tpc_41->cd(4);
    h_tpc_nhit_dt[4][3]->Draw();
    c_nhit_tpc_41->cd(5);
    h_tpc_nhit_rt[4][0]->Draw();
    c_nhit_tpc_41->cd(6);
    h_tpc_nhit_rt[4][1]->Draw(); 
    c_nhit_tpc_41->cd(7);
    h_tpc_nhit_lt[4][0]->Draw();
    c_nhit_tpc_41->cd(8);
    h_tpc_nhit_lt[4][1]->Draw();



    TCanvas *c_nhit_sci21l = new TCanvas("c_nhit_sci21l", "SCI 21 L nhit histos", 1200, 800);
	c_nhit_sci21l->Divide(2,5); // Divide the canvas into a grid
	TCanvas *c_nhit_sci21r = new TCanvas("c_nhit_sci21r", "SCI 21 R nhit histos", 1200, 800);
	c_nhit_sci21r->Divide(2,5); // Divide the canvas into a grid
	for (int i = 0; i < 10; ++i) {
            c_nhit_sci21l->cd(i+1); 
            h_tdc_sc21l[i]->Draw(); 
            c_nhit_sci21r->cd(i+1); 
            h_tdc_sc21r[i]->Draw(); //bisher auch nur 1 aus 10 histos mit sinnvollen entries
    }

    TCanvas *ccc = new TCanvas("ccc", "ccc", 1200, 800);
    h_id_cut->Draw(); //produziert bisher nur leeres histo
    */
    
	f_out->cd();
    t_id->Write();
	if(f_out->IsZombie()){
		cerr << "Error: file "<< fileNameOut <<"was not written!"<<endl;
	}
	else {
		cout<< "File "<< fileNameOut <<" was written successfully!"<<endl;
	}
	printf("\033[1;35mContinue work with IdTree *t_id containing Particle identification data stored in file %s_id_O16_AV.root processed by O16PID_II_AV.C\033[0m\n",name1);
	gBenchmark->Show("Time");
    gBenchmark->Reset();
	//f_out->Close();
}
