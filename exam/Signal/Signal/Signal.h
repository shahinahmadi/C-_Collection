#ifndef H_Signal
#define H_Signal
#include "TH1D.h"
#include "TF1.h"
#include <TVirtualFitter.h>
#include<TFitter.h>
#include "wrapper.hpp"
using namespace std;
class Signal//This class is taking the input data and analyzing the related histogram of that
{
 private:
TH1D* h1_sum; // Declaration to be used in cpp file
vector<int> phidgets;
vector<PTF::PMTChannel> activeChannels;
// Declaring vector of histograms here
//vector<TH1D*>hist;
PTF::Wrapper *wrapper;
int numSamples;

public:
Signal(PTF::Wrapper *wrp);// Default constructor for histogram
static Double_t Fitfunc(Double_t *x, Double_t *par);//Fitting functionFitting function
void FillHist();//Filling the histogram
void PlotHist(const char* filename);//Plotting the histogram
};
#endif  
