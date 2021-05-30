#include <iostream>
#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include <TGraphErrors.h>
#include <TLatex.h>

double time_average(double* vals) {
	return (vals[0] + vals[1]) / 2;
}

double time_error(double* vals) { 
	double x1 = TMath::Abs(vals[0] - vals[1])/2;
	

	return x1;
}

double ti2secs(double min, double sec) {
	return min*60 + sec;
}

double rateTotalFitFnc(double* x, double* p) {
	return p[0]*TMath::Exp(-p[1]*x[0]);
}

void lucas() {

	   	TCanvas *c1 = new TCanvas("c1","the fit canvas", 800, 600);
   c1->SetFillColor(33);
   c1->SetFrameFillColor(255);
   c1->SetGrid();

	const int n = 6;
	// double counts[n] = { 14956, 14380, 3858, 914, 422, 333 };
	double counts[n] = {722, 802, 824, 802, 988, 869};
	// double delay[n] = {50.19, 100.3, 150.3, 200.0, 250.3, 300.2};
	double delay[n] = {99.84, 150.5, 200.1, 250.3, 299.8, 349.3};
	//double delay_err[n] = { 24.5, 24.50, 24.5, 24.7, 24.5, 25.65 };


	double time_data[n][3] =  { 
		{ti2secs(5, 44.60), ti2secs(5, 44.10)},
		{ti2secs(6, 19.02 ), ti2secs(6, 19.31)},
		{ti2secs(5, 22.43), ti2secs(5, 22.6)},
		{ti2secs(5, 00.88), ti2secs(5, 0.87)},
		{ti2secs(5, 33.95), ti2secs(5, 33.95)}, 
		{ti2secs(4, 59.52), ti2secs(5, 00.93)},
	};
	// {ti2secs(3, 13.84), ti2secs(3, 14.08), ti2secs(3, 14.53)},
	// {ti2secs(4, 10.15), ti2secs(4, 11.62), ti2secs(4, 11.44)}, 
	// {ti2secs(3, 25.27), ti2secs(3, 24.67), ti2secs(3, 25.25)},
	// {ti2secs(3, 26.22), ti2secs(3, 25.00), ti2secs(3, 26.57)}, 
	// {ti2secs(3, 1.33), ti2secs(3, 1.09), ti2secs(3, 0.99)},
	// {ti2secs(3, 1.83), ti2secs(3, 1.93), ti2secs(3, 2.27)}};

	double* time_avg = new double[n];
	double* time_err = new double[n];
	int i = 0;
	for(auto time : time_data) {
		time_avg[i] = time_average(time);
		time_err[i] = time_error(time);
		i++;
	}

	double* count_err = new double[n];
	i = 0;
	for(auto count: counts) {
		double r_err_t = time_err[i] / time_avg[i];
		double std = (1/count) + r_err_t*r_err_t;
		counts[i] = count / time_avg[i];
		count_err[i] = TMath::Sqrt(std)*counts[i]; 

		std::cout << (1.0/count) << std::endl;

		i++;
	}

	TGraphErrors* plot = new TGraphErrors(n, delay, counts, nullptr, count_err);
	plot->SetMarkerStyle(21);
	plot->SetMarkerSize(0.8);
	plot->GetXaxis()->CenterTitle();
        plot->GetYaxis()->CenterTitle();
	plot->SetTitle("Total counts without sample; Delay(ns); Counts per second");


   	//auto FitFcn =  new TF1("fitFunction", rateTotalFitFnc, 0, 350, 2);

   	// FitFcn->FixParameter(0, 0.1);
   	// FitFcn->FixParameter(1, 0.1);


	/*FitFcn->SetParameters(0.1, 0.1);
	FitFcn->SetParNames("A", "L Noise");
	plot->Fit("fitFunction", "M");

   	
	FitFcn->DrawClone("Same");*/
	plot->DrawClone("APE");

   	c1->Draw();


	delete [] time_avg, time_err;


   	return c1;
} 
