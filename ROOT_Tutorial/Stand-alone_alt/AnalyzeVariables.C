#define AnalyzeVariables_cxx
#include "AnalyzeVariables.h"
#include <TH2.h>
#include <TStyle.h>
#include <TH1.h>
#include <TMath.h>
//**********Definition************
TH1F* h2f=NULL;
TH1F* h1f=NULL;
void AnalyzeVariables::Begin(TTree * /*tree*/)
{
  //*******Initialization***********
  h2f = new TH1F("h2f","Stand-alone program1",100,0,10);// Creating the histogram
  h2f->GetXaxis()->SetTitle("pt(GeV)");
  h2f->GetYaxis()->SetTitle("Events");
  h2f->GetXaxis()->CenterTitle();
  h2f->GetYaxis()->CenterTitle();
  TString option = GetOption();



   h1f = new TH1F("h1f","Stand-alone program2",100,0,10);// Creating the histogram
  h1f->GetXaxis()->SetTitle("pt(GeV)");
  h1f->GetYaxis()->SetTitle("Events");
  h1f->GetXaxis()->CenterTitle();
  h1f->GetYaxis()->CenterTitle();

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
  h1f->Fill(2*pt);

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
