#define Analyze_cxx
#include "Analyze.h"
#include <TH2.h>
#include <TStyle.h>
#include <cmath>
#include <math.h>
#include "TH2F.h"
//******** Definition section *********
//TCanvas *c1 = new TCanvas("c1", "c1",10,244,700,500);
//TCanvas *c2 = new TCanvas("c2", "c2",10,244,700,500);
TCanvas *c1 = new TCanvas("c1","c1",600,400);
TH1* ebeamHist = NULL;
TH1* chi2Hist = NULL;
TH2F* hscat=NULL;
Float_t ebeam,chi2;
void Analyze::Begin(TTree * /*tree*/)
{

  TString option = GetOption();
  //******** Initialization section *********
  chi2Hist = new TH1D("chi2","Histogram of Chi2",100,0,20);
  ebeamHist = new TH1D("ebeam","Histogram of ebeam",100,149,151);
  hscat = new TH2F("hscat","Example of two dimentional histogram (scatter plot)",100,0,20,100,0,20);
  hscat->GetXaxis()->SetTitle("chi2");
  hscat->GetYaxis()->SetTitle("ebeam");
  hscat->GetXaxis()->CenterTitle();
  hscat->GetYaxis()->CenterTitle();
  ebeamHist->FillRandom("gaus",10000);
  TF1 func("user","gaus(0)");
  func.SetParameters(88.,89.,55.);
  gStyle->SetOptFit(1011);
  ebeamHist->Fit("user");
  chi2Hist->GetXaxis()->SetTitle("chi2");
  ebeamHist->GetXaxis()->SetTitle("Theta");
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
  //for (Int_t i = 0; i < 2500; i++) {
  Double_t pt=sqrt((*px)*(*px) + (*py)*(*py));
  Double_t theta=TMath::ATan2(pt,*pz);
  chi2Hist->Fill(*chi2);
  ebeamHist->Fill(theta);
  if ((*chi2 < 1.5)&&(theta < 0.15))
    hscat->Fill(*chi2,theta);
  //}
  return kTRUE;
}
void Analyze::SlaveTerminate() {}
void Analyze::Terminate()
{
  //******** Wrap-up section *********
  hscat->Draw("scat=0.5");
  return c1;
 
}
