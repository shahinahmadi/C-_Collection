#include "wrapper.hpp"
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>
#include <unordered_set>
#include "TH1D.h"
#include "TFile.h"

using namespace std;
int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Enter the run number.";
  }
  // Open  a root file
  TFile outFile("histograms_average_waveform.root", "recreate");//Naming and recreating the file, We can also use Update
  const string run_no = argv[1];
  string root_f = "/home/shahin/ptf-analysis-2/data/out_run0" + run_no + ".root";
  string csv_f  = "/home/shahin/ptf-analysis-2/data/out_run0" + run_no + ".csv";
  
  vector<int> phidgets = {0, 1, 3};
  vector<PTF::PMTChannel> activeChannels = {
    {0, 0}
    //   {1, 4},
    //   {2, 5},
    //   {3, 6},
    //   {4, 7}, 
    //   {5, 8},
    //   {6, 9},
    //   {7, 10}
  };
  PTF::Wrapper wrapper = PTF::Wrapper(16384, 70, activeChannels, phidgets);
  
  unordered_set<int> skipLines = {};// {962,1923,2884,5240,6201,9611,10572,11533,12494,13455,15811,16771};
  
  wrapper.openFile(root_f, "scan_tree");
  //ofstream csv(csv_f);
  
  cerr << "Num entries: " << wrapper.getNumEntries() << endl << endl;
  
  //csv << "X0,Y0,Z0, Bx0,By0,Bz0, Bx1,By1,Bz1, Bx3,By3,Bz3" << endl;
  
  uint32_t lines = 0;
  const uint32_t freq = 100;
  
  for (int i = 0; i < wrapper.getNumEntries(); i++) {
    if (i % freq == 0 || i == wrapper.getNumEntries() - 1) {
      cerr << "Entry " << i << "/" << wrapper.getNumEntries() << "\u001b[34;1m (" << (((double)i)/wrapper.getNumEntries()*100) << "%)\u001b[0m\033[K";
      if (skipLines.find(i) != skipLines.end()) {
        cerr << "\u001b[31;1m Skipping...\u001b[0m\r";
        continue;
      } else {
        cerr << "\r";
      }
    }
    
    if (skipLines.find(i) != skipLines.end()) continue;
    
    lines++;
    wrapper.setCurrentEntry(i);
    
    auto location = wrapper.getDataForCurrentEntry(PTF::Gantry1);
    
    cerr << location.x << "," << location.y << "," << location.z << endl;
    
    //string name = "h1_" + std::to_string(i); // change so you have unique file name
 
    //cout << activeChannels.size() << endl;
    for (auto  Channel : activeChannels)
      // for (int phidget : phidgets)
      {
	
	
	//get number of samples
	size_t  numSamples= wrapper.getNumSamples();
	cout<<numSamples<<endl;
	// 1. create new histogram for sum
	
	string name_sum = "h1_sum_"+ std::to_string(i); // change so you have unique file name
	auto  h1_sum=new TH1D(name_sum.c_str(), "Pulse waveform; Sample length;Collected charges",70,0,70);
	h1_sum->GetXaxis()->CenterTitle();
	h1_sum->GetYaxis()->CenterTitle();
	for ( int j=0; j<numSamples; j++){
	//  get pmt sample
	  
	  double* pmtsample=wrapper.getPmtSample( Channel.pmt, j);
	  for(int k=0; k<wrapper.getSampleLength(); k++){
	    
	    	//2. Get bin content for sum
	    	double bin_value = h1_sum->GetBinContent(k+1);
	    	//3. Calculate new bin content
	    	bin_value = bin_value + pmtsample[k]-8135.4;
	    	  //h1_sum->Fill(k, pmtsample[k]);
	    	//4. Set new bin content
	    	h1_sum->SetBinContent(k+1,bin_value);
	   
	   } 
	  }
	  
		h1_sum->Scale(1./numSamples);
	        h1_sum->Write();
	
	 
	}
	
	
    
    outFile.cd();//saying to  root we want to save hist to outfile
  			
    
    
   
  }
  outFile.Close();

  
  
  
}



