#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"

void tree2(){
  //Creating root file and tree
  TFile f("AFile.root", "RECREATE");
  TTree t("myTree","A Tree");
  Float_t myEvent;
  Float_t yourEvent;
  Float_t ourEvent;
  Double_t random;
  TRandom *r1 = new TRandom1();
  //Creating branches for tree
  t.Branch("EventBranch1", &myEvent,"myEvent/F");
  t.Branch("EventBranch2", &yourEvent, "yourEvent/F");
  t.Branch("EventBranch3", &ourEvent, "ourEvent/F");
  //Filling the branches by data
  for (Int_t e=0;e<1000;++e) {
    myEvent=r1->Rndm(e);  
    yourEvent=r1->Rndm(e);
    ourEvent=myEvent+yourEvent;
    t.Fill();
  }
  //Writing the tree to the file
  t.Write();
  
}
