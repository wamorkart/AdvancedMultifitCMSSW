
void FilterTreeZee(std::string nameInputFile = "output.root", std::string nameOutputFile = "outputFilter.root"){
  
  //Get old file, old tree and set top branch address
  TFile *oldfile = new TFile(nameInputFile.c_str());
  TTree *oldtree = (TTree*) oldfile->Get("ZeeTreeProducer/electrons");
  
  float mll;
  oldtree->SetBranchAddress("mee_advanced_multifit",&mll);
  
  int ntot = oldtree->GetEntries();
  
  
  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile(nameOutputFile.c_str(),"recreate");
  newfile->mkdir("ZeeTreeProducer");
  newfile->cd("ZeeTreeProducer");
  TTree *newtree = oldtree->CloneTree(0);
  
  std::cout << " ntot = " << ntot << std::endl;
  for (int i=0; i<ntot; i++) {
    oldtree->GetEntry(i);
//     std::cout << " i::tot = " << i << " :: " << ntot << std::endl;
    
    //     std::cout << " ampl_multifit[5] = " << ampl_multifit[5] << std::endl;
    if (mll > 0) {
      newtree->Fill();
    }
  }
  
  std::cout << " end " << std::endl;
  
  newtree->AutoSave();
  
}

