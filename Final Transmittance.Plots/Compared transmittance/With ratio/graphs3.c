#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cstdio>
#include "TGraph.h"
using namespace std;

//so that the function plot() gets renamed to something with declaration like:TGraph * get_graph( const string & infile = "/home/shahin/Desktop/NEW.CSV" );

TGraph* plot(string filename){

  vector<double> wavelengths;
  vector<double> transmissions;
  //Change the line that opens the ifstream to use infile instead of the hard coded file name, and at the end of the function return gr (which is a TGraph *).
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

    
  //   Writing a for loop which prints the data in the vectors to screen.
  for (int i; i < wavelengths.size(); ++i){
    // cout<< wavelengths.at(i)<<" "<<transmissions.at(i)<< endl; 
  }

  //   Writing for loop here to loop through wavelength and transmission vectors and store their information in an array
  int n=911;
  double x[n],y[n];
  for (int i=0; i<wavelengths.size();i++){
    x[i]=wavelengths.at(i);
    y[i]=transmissions.at(i);

  }
  //
  auto gr = new TGraph(n,x,y);

  return gr;
}
//Then you can modify the function I said you should make to take const std::vector< TGraph* > & as an argument, and return a TGraphErrors* that is the average and RMS for error bar of the vector of TGraph* you give it.

TGraphErrors* Errors(vector<TGraph*> GS){
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
  for(int i = 0; i < GS.at(0)->GetN(); i++){
    double mean = 0;
    double sigma = 0;
    for (int j=0;j<GS.size();j++){
      double x,y;
      GS.at(j)->GetPoint(i,x,y);
      mean += y;
      wave[i] = x;
    }
    mean /= GS.size();
    for (int j=0;j<GS.size();j++){
      double x,y;
      GS.at(j)->GetPoint(i,x,y);		
		
      sigma += (y-mean)*(y-mean);
    }
    sigma = sqrt(sigma/GS.size());
    trans[i] = mean;
    transE[i] = sigma;	

  }

  TGraphErrors* gr1=new TGraphErrors(GS.at(0)->GetN(),wave,trans,waveE,transE);
  gr1->SetLineColor(kRed+1);
  return gr1;
}
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
	      
void test(vector<TGraph*>TR) {
  TCanvas *c1 = new TCanvas("c1","3 Graphs",1400,1400);

  auto *p2 = new TPad("p2","p2",0.,0.,1.,0.3); p2->Draw();
  p2->SetTopMargin(0.001);
  p2->SetBottomMargin(0.4);
  // p2->SetLogx ();
  // p2->SetGrid();

  auto *p1 = new TPad("p1","p1",0.,0.3,1.,0.9);  p1->Draw();
  p1->SetBottomMargin(0.003);
  p1->SetTopMargin(0.002);
  p1->cd();
  p1->SetGrid();
  //p1->SetLogx ();
  //p1->SetLogy();
  //for (int j=0; j<2; j++){
  /* int i=911;
     float x[TR.at(0)->GetN()]= TR.at(0)->GetX();
     float y1[TR.at(0)->GetN()]=TR.at(0)->GetY();  
     float y2[TR.at(0)->GetN()]=TR.at(1)->GetY();*/
  int ndata = TR.at(0)->GetN();

	
  double* wave = new double[ndata];	
  double* y1 = new double[ndata];
  double* y2 = new double[ndata];
  
  double mean=0;
  double sigma=0;
  	
  double x=0;
  double y=0;
  	
  for(int ix = 0; ix < ndata; ++ix){ // datapoint index ix
    mean=0.;
    sigma=0.;
    for (unsigned int jgr=0;jgr<3;jgr++){ // graph index jgr
      TR.at(jgr)->GetPoint(ix,x,y);
      mean += y;
    }
    mean/=3;
    y1[ix]=mean; 
		
    mean=0;
    sigma=0;
    for (unsigned int jgr=3;jgr<6;jgr++){ // graph index jgr
      TR.at(jgr)->GetPoint(ix,x,y);
      mean += y;
      wave[ix] = x;
    }
    mean /=3;
    y2[ix]=mean;
  }

	
  TGraph* r1 = new TGraph(TR.at(0)->GetN(), wave, y1);
  TGraph* r2 = new TGraph(TR.at(0)->GetN(), wave, y2);
  //r1.at(0)->SetTitle("");
  //r1.at(0)->SetLineColor(4);
  //r1.at(1)->SetLineColor(5);
  r1->SetTitle("Optical gel transmittance comparison; ; Transmittance(%)");
  r1->GetXaxis()->SetLabelSize(0.01);
  r1->GetYaxis()->SetLabelSize(0.045);
  r1->GetYaxis()->SetTitleSize(0.055);
  r1->GetXaxis()->CenterTitle();
  r1->GetYaxis()->CenterTitle();
  r1->GetYaxis()->SetTitleOffset(0.7);
  r1->SetLineColor(4);
  r1->Draw("AL");
  r1->GetXaxis()->SetRangeUser(250,650);
  r1->Draw("AL");
  c1->Update();

  r2->SetLineColor(2);
  //r2->SetTitle("Optical gel transmittance comparison; ; Transmittance(%)");
  
  r2->Draw("LSame");
  r2->GetXaxis()->SetRangeUser(250,650);
  r2->Draw("LSame");
  c1->Update();

  TLegend *leg = new TLegend(0.15,0.75,0.5,0.85);

  leg->AddEntry(r1,"SilGel612_60:40 mix","lp");
  leg->AddEntry(r2,"SilGel612_60:40 mix_oven","lp");
  leg->Draw();
  //for (int i=0; i<TR.at(0)->GetN(); i++) r->SetPoint(i, wave[i], (y2[i]/y1[i]));
	
  /* for (unsigned int jgr=0;jgr<GS.size();jgr++){
     double x,y;
     GS.at(jgr)->GetPoint(ix,x,y);		
		
     sigma += (y-mean)*(y-mean);
     }
     sigma = sqrt(sigma/GS.size());
     trans[ix] = mean;
     transE[ix] = sigma;

     }*/
  /*TGraph* gr1 = new TGraph(GS.at(0)->GetN(),&wave[0],&trans[0],&waveE[0],&transE[0]);
    gr1->SetTitle("Transmittance measurement for baked and unbaked gels (Three repeated measurements are averaged and errors included);Light wavelength(nm);Transmittance(%)");
    gr1->GetXaxis()->CenterTitle();
    gr1->GetYaxis()->CenterTitle();
    make default line width bigger*/
  // gr1->SetLineWidth(1);
  //return gr1;
  //}
  /* TLegend *leg = new TLegend(0.15,0.75,0.5,0.85);

     leg->AddEntry(TR.at(0),"The first sample of gel","lp");
     leg->AddEntry(TR.at(1),"The second sample of gel","lp");
     leg->Draw();*/

  // ratio
   
  p2->cd();
  TGraph *r = new TGraph(TR.at(0)->GetN()); r->SetTitle("");
  for (int i=0; i<TR.at(0)->GetN(); i++) r->SetPoint(i, wave[i], (y2[i]/y1[i]));//);
  r->GetXaxis()->SetLabelSize(0.1);
  r->GetYaxis()->SetLabelSize(0.1);
  r->SetTitle("    ;Wavelength(nm);#splitline{Transmittance ratio}{(mix_oven to mix)}");
  //r->SetTitle("#splitline{a simple}{graph}");
  gStyle->SetTitleFontSize(0.5);
  r->GetXaxis()->CenterTitle();
 r->GetYaxis()->CenterTitle();
  r->Draw("AL");
  r->GetXaxis()->SetRangeUser(250,650);
  r->GetXaxis()->SetTitleSize(.105);
 // r->GetYaxis()->SetTitleSize(.30);
  r->Draw("AL");
  c1->Update();
  r->GetYaxis()->SetTitleSize(0.1);
  r->GetYaxis()->SetTitleOffset(0.35);
  r->GetXaxis()->SetTitleOffset(0.7);
  r->Draw("AL");
   c1->Update();
 // TLegend *leg2 = new TLegend(0.0,0.0,.8,0.3);//0.01,0.02,0.03,0.04//);
  //leg2->AddEntry(r,"Tranmittance ratio of 604_9505_oven_double to 604_9505 the ","lp");
  //leg2->Draw();
	
}

  
	      

//Then make a new plot() function that calls get_graph.  You can call it multiple times on different files to get multiple graphs.  Store the pointers to graphs that you read in and make in a std::vector:< TGraph* > graphs;


void graphs3(){
	
  //vector<TGraph*> graphs2;
  vector<TGraph*> graphs;
  string filename [6]={"612_6040_2_0.CSV","612_6040_2_1.CSV","612_6040_2_2.CSV","612_6040_oven_2_0.CSV","612_6040_oven_2_1.CSV","612_6040_oven_2_2.CSV"};
  int lineColors[6]={1,2,4,5,6,7};
  string plotOpt[6] = {"AL", "same", "same","same","same","same"};
	
  for(int i=0;i<6;i++){ 
    graphs.push_back( plot( filename[i] ) );  
    graphs.at(i)->SetLineColor( lineColors[i] );
    //graphs1.at(i)->Draw(plotOpt[i].c_str());
  }
  
  /*for(int i=3;i<6;i++){
    graphs3.push_back( plot( filename[i] ) );
    graphs3.at(i-3)->SetLineColor( lineColors[i] );
    //graphs5.at(i)->Draw(plotOpt[i].c_str());
    }*/
  scale_fix(graphs);
  //TGraphErrors* graphs2= Errors(graphs1);
  //graphs2->SetMarkerStyle(22);
  //graphs2->Draw("Psame");
  test(graphs);
  //TGraph*  graphs6=test(graphs3);
  //graphs6->Draw();
  //TLegend *leg2 = new TLegend(0.0,0.0,.8,0.3);//0.01,0.02,0.03,0.04//);
  //leg2->AddEntry(graphs5,"Tranmittance ratio of second sample to the first sample","lp");
  //leg2->Draw();
}


