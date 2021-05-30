#include "PolyPlot.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include <cmath>
using namespace std;
PolyPlot:: PolyPlot(){
hist = new TH1D("h","Histogram of polynomial values in terms of random number",10,0,1);
} //default constructor
void PolyPlot:: FillTree(int  num_values, double min, double max)
//Fill tree with num_values of random numbers between min and max
{ 
  tree = new TTree("tree","Example of tree filled by random number");
  Double_t  x; 
  tree->Branch("x",&x,"x/d");
  for (Int_t i=0;i<num_values;i++) {
    x=gRandom->Uniform(min,max);
    tree->Fill();
  }
}
void  PolyPlot:: PrintTree(){
  //Print values in tree
  tree->Print();
}
void PolyPlot:: WriteRandom(const char* fileName){
  TFile* outputfile = new TFile(fileName,"UPDATE");
  outputfile->cd();
  tree->Write();
  outputfile->Close();
  //Save tree to fileName
}
void PolyPlot:: ReadRandom(const char* fileName){
  TFile* inputfile = new TFile(fileName,"READ");
  //Read file with TTree and store values in vector random
  tree = (TTree*) inputfile->Get("tree");
  Double_t x;
  tree->SetBranchAddress("x",&x);
  for(int entry=0; entry<tree->GetEntries(); entry++){
    tree->GetEntry(entry);
    random.push_back(x);
  }
}
void  PolyPlot:: FillHist(const Polynomial& p){
  //Loop through random to access each random number, rand_i
  cout << random.size()<< endl;
  for (int rand_i=0; rand_i<random.size();rand_i++){
    //Fill histogram with value rand_i and a weight of p evaluated at rand_i
    hist->Fill(random.at(rand_i), p.operator()(random.at(rand_i)));
    cout<<random.at(rand_i)<<" "<< p.operator()(random.at(rand_i))<<endl;
    hist->GetXaxis()->SetTitle("Random numbers");
    hist->GetYaxis()->SetTitle("Polynomial values");
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
    hist->SetTitle("Histogram of random numbers and polynomial values");
    
  }
  //Scale histogram so that the integral is the same as the integral of p
  Double_t normal = p.analytical_integrate(0.0,1);
  Double_t scale = normal/(hist->Integral());
  cout<<normal<<" "<<scale<<endl;
  hist->Scale(scale);   
}

void  PolyPlot::  PlotHist(const char* fileName){
  
  //Plot hist and save to fileName
  TFile* outputfile = new TFile(fileName,"UPDATE");
  outputfile->cd();
  hist->Draw();
  hist->Write();
  outputfile->Close();
}
void  PolyPlot:: MakeGraph(int num_values, double min, double max, const Polynomial& p){
  //Create TGraph where the x values have num_values points between min and max, and the y values are p(x)
  Double_t x[num_values], y[num_values];
  for (Int_t i=0;i<num_values;i++) {
    x[i] = i;
    y[i] = p.operator()(i);
  }
 
  graph = new TGraph(num_values,x,y);
  graph->GetXaxis()->SetRangeUser(min,max);
  graph->SetTitle("TGraph example of polynomial(100 points between 0 and 50)");
  graph->GetXaxis()->SetTitle("Random numbers");
  graph->GetYaxis()->SetTitle("Polynomial values");
  graph->GetXaxis()->CenterTitle();
  graph->GetYaxis()->CenterTitle();
}
void PolyPlot:: PlotGraph(const char* fileName){
  //Plot graph and save to fileName
  TFile* outputfile = new TFile(fileName,"UPDATE");
  outputfile->cd();
  graph->Draw();
  graph->Write();
  outputfile->Close();
}
TH1D* PolyPlot::  GetHist(){
  //Returns hist
  return hist;
}
TGraph* PolyPlot:: GetGraph(){
  //Returns graph
  return graph;
}
