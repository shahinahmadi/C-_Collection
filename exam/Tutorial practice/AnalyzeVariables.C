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
  h2f = new TH1F("hf","Test random numbers",100,0,35);
  h2f->GetXaxis()->SetTitle("Sqrt((*px)*(*px) + (*py)*(*py))");
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
  //  Double_t pt =TMath:: Sqrt((*px)*(*px) + (*py)*(*py));
  //auto sroot = new TF2("sroot","pt",0,100,0,100);
 
  // h2f->Fill(pt);
  return kTRUE;
}

void AnalyzeVariables::SlaveTerminate()
{
 

}

void AnalyzeVariables::Terminate()
{
  // h2f->Draw();
  //******** Wrap-up section *********
}
