#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cstdio>
#include "TGraph.h"
#include "TAxis.h"
#include "TGraphErrors.h"
using namespace std;

/* fix the following comments to describe what the function does --

   also it probably should be renamed to be more meaningful

   I notice the file read in has "stddev".  Instead of making and returning a TGraph *, it 
   would be better to make a TGraphErrors* and use the stddev values for the y errors.  You
   can use a vector of zeros for the x errors.
*/

//so that the function plot() gets renamed to something with
//declaration like:
// TGraph * get_graph( const string & infile = "/home/shahin/Desktop/NEW.CSV" );
TGraph* plot(string filename){

  vector<double> wavelengths;
  vector<double> transmissions;
  //Change the line that opens the ifstream to use infile instead of
  //the hard coded file name, and at the end of the function return gr
  //(which is a TGraph *).
  ifstream myfile(filename); //file opening constructor

  //Operation to check if the file opened
  if ( myfile.is_open() ){
    
    double wavelength, transmission, stddev;
    char delimiter;
        
    // Reading the file
    myfile.ignore(1000, '\n');
    while(myfile >> wavelength >> delimiter >> transmission >> delimiter >> stddev){

      //putting data into the vector
      wavelengths.push_back(wavelength);
      transmissions.push_back(transmission);

    }
  }

    
  /* You shouldn't have to copy the array, just use directly!
  //   Writing for loop here to loop through wavelength and
  //   transmission vectors and store their information in an array
  int n=wavelengths.size();
  double x[n],y[n];
  for (int i=0; i<wavelengths.size();i++){
  x[i]=wavelengths.at(i);
  y[i]=transmissions.at(i);

  }
  //
  auto gr = new TGraph(n,x,y);

  also you can get n from the length of the vectors instead of assuming it is 911 long
  */
  TGraph * gr = new TGraph( wavelengths.size(), &wavelengths[0], &transmissions[0] );
  gr->SetTitle("Transmittance measurement(Three repeated measurements are averaged);Light wavelength(nm);Transmittance(%)");
  gr->GetXaxis()->CenterTitle();
  gr->GetYaxis()->CenterTitle();
  /* make default line width bigger */
  gr->SetLineWidth(3);
  return gr;
}


/* fix the following comments to describe what the function does*/

//Then you can modify the function I said you should make to take
//const std::vector< TGraph* > & as an argument, and return a
//TGraphErrors* that is the average and RMS for error bar of the
//vector of TGraph* you give it.

TGraphErrors* Errors(vector<TGraph*> GS){
  /* better to use vector here... below works in root cint, but
     wouldn't work if we tried to compile it 
     double wave[GS.at(0)->GetN()];
     double trans[GS.at(0)->GetN()];
     double waveE[GS.at(0)->GetN()];
     double transE[GS.at(0)->GetN()];

     for(int i = 0; i < GS.at(0)->GetN(); i++){
     wave[i]=0;
     trans[i]=0;
     waveE[i] = 0;
     transE[i] = 0;		
     }
  */

  /* describe first what the algorithm you are going to follow is,
     using comments.  For example here is what I think the correct
     algorithm is:

     1) Initialize the vector that will be used for the final
     TGraphErrors to be same length as input graph datapoints.

     2) Loop over datapoints, and for each datapoint calculate mean
     and rms over all of the graphs

  */

  int ndata = GS.at(0)->GetN();
   
  vector< double > wave(ndata,0);  // note round brackets for fill constructor
  vector< double > trans(ndata,0);
  vector< double > waveE(ndata,0);
  vector< double > transE(ndata,0);
  
  for(int ix = 0; ix < ndata; ++ix){ // datapoint index ix
    double mean=0.;
    double sigma=0.;
    for (unsigned int jgr=0;jgr<GS.size();jgr++){ // graph index jgr
      double x,y;
      GS.at(jgr)->GetPoint(ix,x,y);
      mean += y;
      wave[ix] = x;
    }
    mean /=GS.size();
    for (unsigned int jgr=0;jgr<GS.size();jgr++){
      double x,y;
      GS.at(jgr)->GetPoint(ix,x,y);		
		
      sigma += (y-mean)*(y-mean);
    }
    sigma = sqrt(sigma/GS.size());
    trans[ix] = mean;
    transE[ix] = sigma;	

  }

  TGraphErrors* gr1 = new TGraphErrors(GS.at(0)->GetN(),&wave[0],&trans[0]);//,&waveE[0],&transE[0]);
  gr1->SetTitle("Transmittance measurement for baked and unbaked gels (Three repeated measurements are averaged);Light wavelength(nm);Transmittance(%)");
  gr1->GetXaxis()->CenterTitle();
  gr1->GetYaxis()->CenterTitle();
  /* make default line width bigger */
  gr1->SetLineWidth(1);
  return gr1;
}

///
/// void scale_fix( vector<TGraph* > SC, double scale=1.0,
///                 double xmin=599.9,   double xmax=600.1 )
/// Function to scale TGraphs pointed to in SC
/// Scaling set value to scale for
/// average from xmin to xmax
void scale_fix(vector<TGraph*> SC, double scale=100,
	       double xmin=599.9,  double xmax=600.1 ){ /* note default parameters can be passed */

  for (unsigned int i=0; i<SC.size(); ++i ) { // loop over graphs

    TGraph * curgraph = SC[i];

    // Loop to calculate value of scaling
    // Note change loop index to j (so it doesn't hide outer loop index i)
    double scaling = 0.0;
    int nbinscale = 0;
    for (int j=0; j < curgraph->GetN(); ++j ) {
      double x,y;
      curgraph->GetPoint(j, x, y);
      if ( x > xmin && x < xmax ){
	scaling += y;
	++nbinscale;
      }
    }
    
    // Loop a second time to do the scaling if we
    // found any bins in the requested range
    if (nbinscale>0){
      scaling /= nbinscale; // average over bins
      scaling = scale / scaling; // calculate scaling factor
      for ( int j=0; j < curgraph->GetN(); ++j ){
	double x,y;
	curgraph->GetPoint( j, x, y );
	curgraph->SetPoint( j, x, y * scaling );
      }
    }	  	     
  }
}
	      

/* It would be good to rename graphs1 to be more meaningful and
   fix the comments */
  
//Then make a new plot() function that calls get_graph.  You can call
//it multiple times on different files to get multiple graphs.  Store
//the pointers to graphs that you read in and make in a std::vector:<
//TGraph* > graphs;

//Main function
void graphs(){
  vector<TGraph*> graphs1;
  vector<TGraph*> graphs2;
  string filename [6]={"612_6040_1_0.CSV","612_6040_1_1.CSV","612_6040_1_2.CSV","612_6040_oven_double_1_0.CSV","612_6040_oven_double_1_1.CSV","612_6040_oven_double_1_2.CSV"};
  int lineColors[6]={1,2,4,5,6,7};
  string plotOpt[6] = {"AL", "same", "same","same","same","same"};
	
  for(int i=0;i<3;i++){ 
    graphs1.push_back( plot( filename[i] ) );  /* add spaces to improve readability */
    graphs1.at(i)->SetLineColor( lineColors[i] );
    //graphs1.at(i)->Draw(plotOpt[i].c_str());
  }
  for(int i=3;i<6;i++){
    graphs2.push_back( plot( filename[i] ) );
    graphs2.at(i-3)->SetLineColor( lineColors[i] );
    //graphs5.at(i)->Draw(plotOpt[i].c_str());
  }

  /* I would call scale_fix here: note that it takes a vector< TGraph* > which is what you have  */
  scale_fix( graphs1 );
  scale_fix( graphs2 );

  /* Reserve cerr for actual error messages, rather than general output 
     cerr << graphs5.size() <<endl;	
  
     also, I would just plot the final graphs 
  */
  
  TGraphErrors* graphs3= Errors( graphs1 );
  TGraphErrors* graphs4= Errors( graphs2 );
  graphs3->SetMarkerStyle(22);
  /* We made errorbars, so lets display them, and change colors so we can tell the difference.
     Also, since the points are so close together, we may as well just do colour bands...
     Have a look at TGraphPainter for the options to use in the Draw command.*/

  
  graphs3->SetLineColor( kRed+1 );
  graphs3->SetFillStyle( 3004 ); 
  graphs4->SetLineColor( kYellow+1 );
  graphs4->SetFillStyle( 3005 );
  
   /*graphs2->SetFillColor(6);
   graphs2->SetFillStyle(3005);
   graphs2->Draw("a4");
   graphs6->SetFillColor(5);
   graphs6->SetFillStyle(3005);
   graphs6->Draw("a5");*/
   
   
  
  graphs3->Draw("AL");//"A4");
  graphs4->Draw("LSame");//"4");
  auto legend=new TLegend(0.2,0.6,0.4,0.8);
  legend->AddEntry(graphs3,"612_6040","l");
  legend->AddEntry(graphs4,"612_6040_oven_double","l");
  legend->Draw("AP");
  /*
    TGraph*  graphs3=scale(graphs2);  
    TGraph*  graphs7=scale(graphs6);
    graphs3->Draw("Lsame");
    graphs7->Draw("Lsame");
  */	
}

