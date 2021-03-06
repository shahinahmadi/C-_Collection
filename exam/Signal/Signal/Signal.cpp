#include "Signal.h"
#include <TStyle.h>
#include <cmath>
#include "TMath.h"
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include <unordered_set>
#include "TH1D.h"
#include "TFile.h"
#include "TF1.h"
#include <TVirtualFitter.h>
#include<TFitter.h>
#include "wrapper.hpp"

using namespace std;


Signal::Signal(PTF::Wrapper *wrp)// Default constructor for histogram
{
  wrapper = wrp;
  numSamples= wrapper->getNumSamples();
  for (unsigned i = 0; i < wrapper->getNumEntries(); i++)
    {
      string name_sum = "h1_sum_" + std::to_string(i);
      TH1D*  h1_sum=new TH1D(name_sum.c_str(), "Pulse waveform; Sample length;Collected charges",70,0, 70);
    }
}

Double_t Signal:: Fitfunc(Double_t *x, Double_t *par)//Fitting functionFitting function
{
  Double_t arg=0;
  if(par[2]!=0) arg=(x[0]-par[1])/par[2];
  Double_t gfunc=-par[0]*TMath::Exp(-0.5*arg*arg)+par[3];
  return gfunc;
}

void Signal:: FillHist()//Filling the histogram
{
  for (auto  Channel : activeChannels)
    // for (int phidget : phidgets)
    {
      //get number of samples
      //int  numSamples= wrapper->getNumSamples();
      for ( int j=0; j<10; j++){
	double* pmtsample=wrapper->getPmtSample( Channel.pmt, j);
	for(int k=0; k<wrapper->getSampleLength(); k++){
	  //Get bin content for sum
	  double bin_value = h1_sum->GetBinContent(k+1);
	  // Calculate new bin content
	  bin_value = bin_value + pmtsample[k];
	  //Set new bin content
	  // h1_sum->SetBinContent(k+1,bin_value);
	  h1_sum->Fill(k,pmtsample[k]);
	  // hist.push_back(h1_sum);
    
	}
      }
    }
}
  void Signal::PlotHist(const char* filename)//Plotting the histogram
  {
    TFile* outputfile = new TFile(filename,"recreate");
    h1_sum->Scale(1/numSamples);
    //TF1 *f1=new TF1("m1","gaus");
    // TF1 *f1=new TF1("m1",Fitfunc,20,50,4);
    //f1->SetParameters(-.025,35.01,5.0);
    //f1->SetParameters(0.015,35.5,200.219);
    // f1->SetParameters(0.06,37.0,10.0,-2.95);
    h1_sum->Fit("m1","","",20,50);
    gStyle->SetOptFit(1011);
    //save histogram to root file
    h1_sum->Write();

  }
  
