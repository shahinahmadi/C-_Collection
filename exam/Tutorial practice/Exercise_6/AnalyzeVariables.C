#define AnalyzeVariables_cxx
#include "AnalyzeVariables.h"
#include <TH2.h>
#include <TStyle.h>
#include <TH1.h>

//**********Definition************
TH1F* h2f=NULL;
void AnalyzeVariables::Begin(TTree * /*tree*/)
{
  //*******Initialization***********
  h2f = new TH1F("h2f","Plotting a derived variable",100,0,10);// Creating the histogram
  TString option = GetOption();
}


void AnalyzeVariables::SlaveBegin(TTree* tree) {}

Bool_t AnalyzeVariables::Process(Long64_t entry)
  
{

  // Don’t delete this line! Without it the program will crash.
  fReader.SetEntry(entry);

 
  //******** Loop section *********
  // You probably want GetEntry(entry) here.
  GetEntry(entry);
  Double_t pt =TMath:: Sqrt((*px)*(*px) + (*py)*(*py));
  h2f->Fill(pt);//Filling the histogram

  return kTRUE;
}

void AnalyzeVariables::SlaveTerminate()
{
 

}

void AnalyzeVariables::Terminate()
{
  //******** Wrap-up section *********
  TFile* file1 = new TFile("analysis.root","UPDATE"); 
  h2f->Write();
  file1->Close();
  
}
