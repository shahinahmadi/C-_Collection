// test.cpp
// Code to test Polynomial and PolyPlot classes
#include "PolyPlot.h"
#include "Polynomial.h"
#include <iostream>
#include <complex>
#include <vector>
#include<cmath>

using namespace std;

int main(){

  //Declare a Polynomial
  Polynomial p1;
  //Give it some parameters
  vector<double> a1{ 12.0, 05.0, 2.0, 10.0, 1.0 };
  p1.set_parameters( a1 );

  //vector<double> a1{ -6.0, -5.0, 2.0, 1.0 };
  // Polynomial poly(a1);
  // poly.print_parameters();

  //Declare a PolyPlot
  PolyPlot p2;
  //Use the member functions one at a time
  p2.FillTree(1000,0,1);
  p2.PrintTree();
  p2.WriteRandom("Ali.root");
  p2.ReadRandom("Ali.root");
  p2.FillHist(p1);
  p2.PlotHist("Ali.root");
  p2.MakeGraph(100,0,50,p1);
  p2.PlotGraph("Ali.root");

  return 0;  
}
