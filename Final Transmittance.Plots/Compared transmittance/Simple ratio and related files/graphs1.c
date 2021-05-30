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
TGraph* scale(TGraph* SC){
  double wavelength[SC->GetN()];
  double transmittance[SC->GetN()];
  double t;
  double scaling;
   
    for (int i=0; i<SC->GetN();i++)
    {
    double x,y;
    SC->GetPoint(i,x,y);
    wavelength[i]=x;
    transmittance[i]=y;
    
     if (wavelength[i]==600)
    {
    t=transmittance[i];// 
    }
    }

    

    if (t!=1)
	    {
	      for (int i=0; i<SC->GetN();i++)
		{
		  double x,y;
		  SC->GetPoint(i,x,y);
		  scaling=y;
		  scaling/=t;
		  wavelength[i]=x;
		  transmittance[i]=scaling;
		}
		  
	   } 
	      
	TGraph* g1 = new TGraph(SC->GetN(), wavelength, transmittance);
	return g1;	     
}

TGraph* test(vector<TGraph*>TR) {
TCanvas *c1 = new TCanvas("c1","3 Graphs",1200,1200);

   auto *p2 = new TPad("p2","p2",0.,0.,1.,0.3); p2->Draw();
   p2->SetTopMargin(0.001);
   p2->SetBottomMargin(0.3);
  // p2->SetLogx ();
  // p2->SetGrid();

   auto *p1 = new TPad("p1","p1",0.,0.3,1.,1.);  p1->Draw();
   p1->SetBottomMargin(0.001);
   p1->cd();
   p1->SetGrid();
   //p1->SetLogx ();
   //p1->SetLogy();
  //for (int j=0; j<2; j++){
 /* int i=911;
  float x[TR.at(0)->GetN()]= TR.at(0)->GetX();
  float y1[TR.at(0)->GetN()]=TR.at(0)->GetY();  
  float y2[TR.at(0)->GetN()]=TR.at(1)->GetY();*/
  double *x= TR.at(0)->GetX();
  double *y1=TR.at(0)->GetY();  
  double *y2=TR.at(1)->GetY(); 
  //TR.at(0)->GetPoint(i,x,y1);
  //TR.at(1)->GetPoint(i,x,y2);
  //int n=661;
  //TGraph*TR.at(0)=new TGraph(TR.at(0)->GetN(),x,y1);
  //TGraph*TR.at(1)=new TGraph(TR.at(0)->GetN(),x,y2);
   TR.at(0)->SetLineColor(4);
   TR.at(0)->SetMarkerColor(1);
   TR.at(0)->SetMarkerStyle(8);
   TR.at(0)->SetMarkerSize(0.8);
   TR.at(0)->SetTitle("");

   TR.at(0)->SetTitle("Ratio plot for comparing the transmittance of two different gels");

   TR.at(0)->GetXaxis()->SetTitle("");
   TR.at(0)->GetXaxis()->CenterTitle();

   TR.at(0)->GetYaxis()->SetTitle("");
   TR.at(0)->GetYaxis()->CenterTitle();
  // TR.at(0)->GetYaxis()->SetRangeUser(0.8E-03,30);//
   TR.at(0)->GetYaxis()->SetTitleOffset(1.5);
   TR.at(0)->GetXaxis()->SetTickSize(0.);

   TR.at(0)->Draw("AL");

   TR.at(1)->SetMarkerColor(kRed);
   TR.at(1)->SetMarkerStyle(33);
   TR.at(1)->SetMarkerSize(0.8);
   TR.at(1)->Draw("L");

   TLegend *leg = new TLegend(0.15,0.75,0.5,0.85);

   leg->AddEntry(TR.at(0),"The first sample of gel","lp");
   leg->AddEntry(TR.at(1),"The second sample of gel","lp");
   leg->Draw();

   // ratio
   p2->cd();
   TGraph*r = new TGraph(TR.at(0)->GetN()); r->SetTitle("");
   int n=911;
   for (int i=0; i<TR.at(0)->GetN(); i++) r->SetPoint(i, x[i], y2[i]/y1[i]);//);
      r->GetXaxis()->SetLabelSize(0.075);
      r->GetYaxis()->SetLabelSize(0.075);
      r->Draw("AL");
      
   return r;
//}
}
  
	      

//Then make a new plot() function that calls get_graph.  You can call it multiple times on different files to get multiple graphs.  Store the pointers to graphs that you read in and make in a std::vector:< TGraph* > graphs;


void graphs1(){
	std::vector<TGraph*> graphs1;
	string filename [3]={"NEW1.CSV","NEW5.CSV","NEW4.CSV"};
	int lineColors[3]={1,2,4};
	string plotOpt[3] = {"AL", "same", "same"};
	
	for(int i=0;i<3;i++){
		graphs1.push_back(plot(filename[i]));
		graphs1.at(i)->SetLineColor(lineColors[i]);
		graphs1.at(i)->Draw(plotOpt[i].c_str());
	}
	
	TGraphErrors* graphs2= Errors(graphs1);
	//graphs2->SetMarkerStyle(22);
	graphs2->Draw("Psame");
	TGraph*  graphs3=test(graphs1);
	graphs3->Draw();
	TLegend *leg2 = new TLegend(0.0,0.0,.8,0.3);//0.01,0.02,0.03,0.04//);
        leg2->AddEntry(graphs3,"Tranmittance ratio of second sample to the first sample","lp");
        leg2->Draw();
	
}

