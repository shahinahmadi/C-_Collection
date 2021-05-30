#ifndef H_PolyPlot
#define H_PolyPlot
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <complex>

//Incude ROOT libraries here
#include<TTree.h>
#include<TH1D.h>
#include<TGraph.h>
//Include Polynomial
#include "Polynomial.h"

using namespace std;
class PolyPlot//This polyPlot class is used to create tree, fill it and putting the data into histogram and graph
{
private:
 TTree* tree;
 TH1D* hist;
 TGraph* graph;
 vector<double> random;

  public:
  
  //Default constructor
  PolyPlot();

  void FillTree(int num_values, double min, double max);
  //Fill tree with num_values of random numbers between min and max

  void PrintTree();
  //Print values in tree

  void WriteRandom(const char* fileName);
  //Save tree to fileName

  void ReadRandom(const char* fileName);
  //Read file with TTree and store values in vector random

  void FillHist(const Polynomial& p);
  //Loop through random to access each random number, rand_i
  //Fill histogram with value rand_i and a weight of p evaluated at rand_i
  //Scale histogram so that the integral is the same as the integral of p

  void PlotHist(const char* fileName);
  //Plot hist and save to fileName

  void MakeGraph(int num_values, double min, double max, const Polynomial& p);
  //Create TGraph where the x values have num_values points between min and max, and the y values are p(x)

  void PlotGraph(const char* fileName);
  //Plot graph and save to fileName

  TH1D* GetHist();
  //Returns hist

  TGraph* GetGraph();
  //Returns graph
};

#endif
