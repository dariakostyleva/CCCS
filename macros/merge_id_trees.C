#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TSystem.h>  // For gSystem->Exit()
// *** This macro ***
// --- merges trees IdTree with id data from several files *_id.root taken under same conditons
// --- writes one large file *_id_m.root

void merge_id_trees() {
    TString path("/data.local2/S533_June21_data/s533jun21/roots/");
    TString file_in_1("s533_50_gC_12mm_0046"); 
    TString file_in_2("s533_50_gC_12mm_0047");
    //TString file_in_3("s533_50_gC_6mm_0052");
    //TString file_in_4("s533_50_gC_6mm_0052");
    TString file_out("s533_50_gC_12mm_46-47");

    TString fileName1, fileName2;
    TString fileName3, fileName4;
    TString fileOut;
    const char * p = path.Data();
    const char * n1 = file_in_1.Data();
    const char * n2 = file_in_2.Data();
    //const char * n3 = file_in_3.Data();
    //const char * n4 = file_in_4.Data();
    const char * o = file_out.Data();
    fileName1.Form("%s%s_id.root",p,n1); 
    fileName2.Form("%s%s_id.root",p,n2);
    //fileName3.Form("%s%s_id.root",p,n3);
    //fileName4.Form("%s%s_id.root",p,n4);
    fileOut.Form("%s%s_id_m.root",p,o);
    const char* treeName = "IdTree";
    
    TChain chain(treeName);
    chain.Add(fileName1);
    chain.Add(fileName2);
    //chain.Add(fileName3);
    //chain.Add(fileName4);
    
    TFile *outFile = new TFile(fileOut, "RECREATE");
     if (!outFile || outFile->IsZombie()) {
        std::cerr << "Warning: Failed to create the merged file !" << std::endl;
        gSystem->Exit(1); 
    }
    TTree* mergedTree = chain.CloneTree(0);
    Long64_t nEntries = chain.GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        chain.GetEntry(i);
        mergedTree->Fill();
    }
    mergedTree->Write();
    std::cout << "File with merged tree has been written sucessfully: " << fileOut << "" << std::endl;
    outFile->Close();
}


