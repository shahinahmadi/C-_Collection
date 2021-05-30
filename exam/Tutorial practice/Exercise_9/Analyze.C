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
TH1* ElossHist = NULL;
TH1* zvHist = NULL;
TH2F* hscat=NULL;
Float_t Eloss,zv;
void Analyze::Begin(TTree * /*tree*/)
{

  TString option = GetOption();
  //******** Initialization section *********
  zvHist = new TH1D("zv","Histogram of Chi2",100,0,20);
  ElossHist = new TH1D("Eloss","Histogram of Chi2",100,0,20);
  hscat = new TH2F("hscat","Example of two dimentional histogram (scatter plot)",100,0,20,100,0,20);
  hscat->GetXaxis()->SetTitle("zv");
  hscat->GetYaxis()->SetTitle("Eloss");
  hscat->GetXaxis()->CenterTitle();
  hscat->GetYaxis()->CenterTitle();
}
void Analyze::SlaveBegin(TTree* tree) {}
Bool_t Analyze::Process(Long64_t entry)
{
  // Don’t delete this line! Without it the program will crash.
  fReader.SetEntry(entry);
  //******** Loop section *********
  // You probably want GetEntry(entry) here.
  GetEntry(entry);
  
  Double_t Emeas=sqrt((*px)*(*px) + (*py)*(*py)+(*pz)*(*pz));
  Double_t Eloss=*ebeam-Emeas;
  zvHist->Fill(*zv);
  ElossHist->Fill(Eloss);
  hscat->Fill(*zv,Eloss);
  
  return kTRUE;
}
void Analyze::SlaveTerminate() {}
void Analyze::Terminate()
{
  //******** Wrap-up section *********
  hscat->Draw("scat=0.5");
  return c1;
 
}
