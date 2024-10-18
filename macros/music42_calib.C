void music42_calib(){
	gStyle->SetOptFit(1);
	// data is from files 182, 43, 151 and 129 of s533 june 2021 Oxygen run
	const Int_t n_point = 4;
	Double_t dE[n_point] = {2363., 2191., 1607., 1561.};
	Double_t beta[n_point] = {1/pow(0.562356,2), 1/pow(0.585437,2), 1/pow(0.694779,2), 1/pow(0.696314,2)}; // 1/beta2 !!!!

	TGraph graph(n_point,beta,dE);
	graph.GetXaxis()->SetTitle("1/beta2");
  	graph.GetYaxis()->SetTitle("dE of MUSIC 42 (ch)");
  	graph.SetMarkerSize(3);
	graph.SetMarkerStyle(kFullCircle);
	graph.SetMarkerColor(kRed);
	graph.SetLineColor(kBlue);
	graph.Fit("pol1","","");
	graph.DrawClone("AP");
}