// This class calculates the gain of 20-in PMT at one point and writes the output to a text file
#include "PTFGainAnalysis.hpp"
#include "ScanPoint.hpp"
#include "WaveformFitResult.hpp"
#include "PTFAnalysis.hpp"
#include <iostream>
#include<fstream>
#include<cmath>
#include<string>
using namespace std;

PTFGainAnalysis::PTFGainAnalysis( TFile *outfile, PTFAnalysis *ptfanalysis, PTF::Wrapper &ptf){
  
  // Putting the scan points into a vector 
  vector<ScanPoint>scanpoints=ptfanalysis->get_scanpoints();
  
  // Looping over scan points
    for(unsigned int iscan=0; iscan<scanpoints.size(); iscan++){
    ScanPoint scanpoint = scanpoints[iscan ];
    long long entry = scanpoint.get_entry();
    double integ_result;
    
    //Looping over waveforms
    if(iscan==16){
      for(unsigned long long iwavfm=0; iwavfm<scanpoint.nentries(); iwavfm++){
	entry += iwavfm;
        const WaveformFitResult fit_result = ptfanalysis->get_fitresult(iscan, iwavfm);
	// Calculation of gain of 20-in PMT
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
	  
	  // Writting the output to a text file
	  cout<<"The result is"<<integ_result<<endl;
	  ofstream myfile;
	  myfile.open ("Gain.txt", ios::app);
	  myfile <<integ_result<<endl;   
	}		       
      }
    }	
  }
}
      

 
     

 

    
   
   
  
