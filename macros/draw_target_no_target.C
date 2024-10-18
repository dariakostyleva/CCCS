void draw_target_no_target() {
    // Open the ROOT file
    TFile *f_empt = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_empty_0053_id_hist.root", "READ");
    TH1F *h_empt = (TH1F*)f_empt->Get("h_z2_cut");

    TFile *f_targ1 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_gC_6mm_0045_id_hist.root", "READ");
    TH1F *h_targ1 = (TH1F*)f_targ1->Get("h_z2_cut");

    TFile *f_targ2 = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_gC_12mm_0046_id_hist.root", "READ");
    TH1F *h_targ2 = (TH1F*)f_targ2->Get("h_z2_cut");

    TFile *f_empt_nc = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_empty_0053_id_hist_nocuts.root", "READ");
    TH1F *h_empt_nc = (TH1F*)f_empt_nc->Get("h_z2_cut");

    TFile *f_targ1_nc = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_gC_6mm_0045_id_hist_nocuts.root", "READ");
    TH1F *h_targ1_nc = (TH1F*)f_targ1_nc->Get("h_z2_cut");

    TFile *f_targ2_nc = new TFile("/data.local2/S533_June21_data/s533jun21/roots/s533_50_gC_12mm_0046_id_hist_nocuts.root", "READ");
    TH1F *h_targ2_nc = (TH1F*)f_targ2_nc->Get("h_z2_cut");

    // Normalize the histograms
    h_empt->Scale(1.0 / h_empt->Integral());
    h_targ1->Scale(1.0 / h_targ1->Integral());
    h_targ2->Scale(1.0 / h_targ2->Integral());

    h_empt_nc->Scale(1.0 / h_empt_nc->Integral());
    h_targ1_nc->Scale(1.0 / h_targ1_nc->Integral());
    h_targ2_nc->Scale(1.0 / h_targ2_nc->Integral());

    gStyle->SetTitleSize(0.08, "t");
    gStyle->SetLabelSize(0.08, "XYZ");
    gStyle->SetTitleSize(0.08, "X");  // Set the X-axis title size
    gStyle->SetTitleSize(0.08, "Y");
    gStyle->SetStatFontSize(0.08); 
    gStyle->SetOptStat(0);

    TCanvas *c = new TCanvas();
    c->Divide(1,2);
    c->cd(1);
    h_empt->SetLineColor(kRed); // Set line color for histo1
    h_empt->SetLineWidth(2); // Set line width for histo1
    h_empt->Draw("HIST");
    h_empt->GetXaxis()->SetTitle("Z2 from MUSIC42");  // Set title for the X-axis
    h_empt->GetYaxis()->SetTitle("Counts normalized a.u.");  // Set title for the Y-axis

    // Draw the second histogram on the same canvas
    h_targ1->SetLineColor(kBlue); // Set line color for histo2
    h_targ1->SetLineWidth(2); // Set line width for histo2
    h_targ1->Draw("HIST SAME");

    h_targ2->SetLineColor(kGreen); // Set line color for histo2
    h_targ2->SetLineWidth(2); // Set line width for histo2
    h_targ2->Draw("HIST SAME");

    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_empt, "empty target", "l");
    legend->AddEntry(h_targ1, "6 mm gC", "l");
    legend->AddEntry(h_targ2, "12 mm gC", "l");
    legend->Draw();
    gPad->SetLogy();

    c->cd(2);
    gPad->SetLogy();
    h_targ2_nc->SetLineColor(kBlack);
    h_targ2_nc->SetLineWidth(2);
    h_targ2_nc->GetXaxis()->SetTitle("Z2 from MUSIC42");  // Set title for the X-axis
    h_targ2_nc->GetYaxis()->SetTitle("Counts normalized a.u.");  // Set title for the Y-axis
    h_targ2_nc->Draw("HIST ");
    h_targ2->Draw("HIST SAME");

    TLegend *legend2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend2->AddEntry(h_targ2, "12 mm gC", "l");
    legend2->AddEntry(h_targ2_nc, "12 mm gC, no conditions on incoming beam", "l");
    legend2->Draw();

    //c->SaveAs("target_no_target_16O.pdf");



    // Clean up
    //f_empt->Close();
}
