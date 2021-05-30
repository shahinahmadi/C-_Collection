#define Analyze_cxx
#include "Analyze.h"
#include <TH2.h>
#include <TStyle.h>
#include <cmath>
#include <math.h>
#include "TH2F.h"
//******** Definition section *********
TH1* chi2Hist=NULL;
TH1* ebeamHist=NULL;
Float_t ebeam,chi2;
void Analyze::Begin(TTree * /*tree*/)
{

  TString option = GetOption();
  //******** Initialization section *********
  chi2Hist = new TH1D("chi2","Histogram of variable  Chi2",100,0,2);
  ebeamHist = new TH1D("ebeam","Histogram of variable  ebeam",100,149,151);
  chi2Hist->GetXaxis()->SetTitle("chi2");
  ebeamHist->GetXaxis()->SetTitle("ebeam");
  chi2Hist->GetYaxis()->SetTitle("number of events");
  ebeamHist->GetYaxis()->SetTitle("number of events");
}
void Analyze::SlaveBegin(TTree* tree) {}
Bool_t Analyze::Process(Long64_t entry)
{
  // Don’t delete this line! Without it the program will crash.
  fReader.SetEntry(entry);
  //******** Loop section *********
  // You probably want GetEntry(entry) here.
  GetEntry(entry);
  ebeamHist->Fill(*ebeam);
   
  return kTRUE;
}
void Analyze::SlaveTerminate() {}
void Analyze::Terminate()
{
  //******** Wrap-up section *********
  ebeamHist->Fit("gaus");
  gStyle->SetOptFit(1011);
  ebeamHist->Draw("e");
}
