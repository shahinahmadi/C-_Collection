#include "wrapper.hpp"
#include "Signal.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Enter the run number.";
  }
  // Open  a root file
  // TFile outFile("histograms_average_waveform.root", "RECREATE");//Naming and recreating the file, We can also use Update
  
  const string run_no = argv[1];
  string root_f = "/home/shahin/Desktop/Signal/Signal/out_run0" + run_no + ".root";
  
  vector<int> phidgets = {0, 1, 3};
  vector<PTF::PMTChannel> activeChannels = {
    {0, 0}
  };
  cerr << "Works1" << endl;
 PTF::Wrapper wrapper = PTF::Wrapper(16384, 70, activeChannels, phidgets); 
  unordered_set<int> skipLines = {};// {962,1923,2884,5240,6201,9611,10572,11533,12494,13455,15811,16771};
    cerr << "Works2" << endl;
    cerr << root_f << endl;
  wrapper.openFile(root_f, "scan_tree");
   cerr << "Num entries: " << wrapper.getNumEntries() << endl << endl;
  
  //csv << "X0,Y0,Z0, Bx0,By0,Bz0, Bx1,By1,Bz1, Bx3,By3,Bz3" << endl;
  
  uint32_t lines = 0;
  const uint32_t freq = 100;
    cerr << "Works3" << endl;

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
    //cout << "There are " << wrapper.getNumEntries() << " entries." << endl;
    Signal S(&wrapper); 
    S.FillHist();
    S.PlotHist("histogram.root");
    return 0;  
  }
    cerr << "Works4" << endl;

}
