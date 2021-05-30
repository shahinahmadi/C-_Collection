// This class calculates the gain of 20-in PMT
#include "PTFGainAnalysis.hpp"
#include "ScanPoint.hpp"
#include "WaveformFitResult.hpp"
#include "PTFAnalysis.hpp"
#include <iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
using namespace std;

PTFGainAnalysis::PTFGainAnalysis( TFile *outfile, PTFAnalysis *ptfanalysis, PTF::Wrapper &wrapper){
  
  // Decleration of histograms 
  Sum = new TH1D("Summation","Sum over all points",40,0,6000);
  vector<ScanPoint>scanpoints=ptfanalysis->get_scanpoints();
  //Looping over scan points
  for(unsigned int iscan=0; iscan<scanpoints.size(); iscan++){
    string name = "Gain_hist" + std::to_string(iscan);
    Gain_hist = new TH1D(name.c_str(),"Charge_distribution of some pulses on the PMT",40,0,6000);
    Gain_hist->GetXaxis()->SetTitle("Charge distribution(ADC unit)");
    Gain_hist->GetYaxis()->SetTitle("The number of events");
    Gain_hist->GetXaxis()->CenterTitle();
    Gain_hist->GetYaxis()->CenterTitle();
    
      
    ScanPoint scanpoint = scanpoints[iscan ];
    long long entry = scanpoint.get_entry();
    double integ_result;
    //  if(iscan==16){
    //Looping over waveforms
    for(unsigned long long iwavfm=0; iwavfm<scanpoint.nentries(); iwavfm++){
      entry += iwavfm;
      const WaveformFitResult fit_result = ptfanalysis->get_fitresult(iscan, iwavfm);
      // Calculation of Gain
      if (fit_result.haswf){
	integ_result=0;
	int n=100000;
	double dx;
	double xmax=wrapper.getSampleLength();
	double xmin=0;
	dx=(xmax-xmin)/n;
    
	for (int i=0; i<n;i++){
	  double xi=xmin+i*dx;
	  double functionValue=(fit_result.amp * exp( -0.5 * pow( (xi-fit_result.mean)/(fit_result.sigma* fit_result.sigma), 2.0 )));
	  double integral=functionValue*dx;
	  integ_result+=integral;
	}
	cout<<"This is integ_results"<<integ_result<<endl;
        Gain_hist->Fill(integ_result);
    	//}
      }
    }
    // Summation of histograms of different scan points
    Sum->Add(Gain_hist);
    Sum->Draw();	
  }
}

  
      

 
     

 

    
   
   
  
