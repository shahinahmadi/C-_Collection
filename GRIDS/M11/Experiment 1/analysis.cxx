/*
	Time walk: time difference that appears from different height pulses.
	Constant fraction discriminator
	data->Draw("values[1]:values[2]",  "values[0]>0 && values[3] < 100", "prof");
	val[1]:val[2] - > correlations or x-y plotting
	"prof" -> profile histogram


	example:
	midas_temp->Draw("(tdc_value[2]-tdc_value[1])*0.1-(-2.2-0.005*adc_value[1]-2.3e-6*adc_value[1]*adc_value[1]):adc_value[1]", 
	"adc_value[0]>100 && adc_value[1] < 1000 && abs(tdc_value[1]-tdc_value[1]) < 200", "prof");
	htemp->Fit("pol2", "", x1, x2);
*/

#include <iostream>
#include <TH1.h>
#include <TMath.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLatex.h>

/// Objective: calculate the momemtum with time of flight.
/// 1, 2, 3 tdc_values
/// 0, 1, 2 adc_values from scintillations
/// 3, 4, 5, 6... from calorimeter


void analysis() {
	// These lines read the root file
	TFile f("output_000190.root");
	TTree *midas_data = nullptr;
	f.GetObject("midas_data", midas_data);

	// midas_data->Draw("(tdc_value[2]-tdc_value[1]):adc_value[1]>>hh(1000,100,400)", "adc_value[1] > 200");
	// midas_data->Draw("0.1*(tdc_value[2]-tdc_value[1])", "adc_value[0] > 100 && abs(tdc_value[2] - tdc_value[1]) < 200");

	// midas_data->Draw("0.1*(tdc_value[2]-tdc_value[1]):adc_value[0]", "adc_value[0] > 100 && abs(tdc_value[2] - tdc_value[1]) < 200 && adc_value[4] > 3000", "prof");
	midas_data->Draw("0.1*(tdc_value[2]-tdc_value[1]):adc_value[4]", "adc_value[0] > 100 && abs(tdc_value[2] - tdc_value[1]) < 200");


	midas_data->Draw("0.1*(tdc_value[2]-tdc_value[1])", "adc_value[0] > 100 && abs(tdc_value[2] - tdc_value[1]) < 200 && 0.1*(tdc_value[2]-tdc_value[1]) < 10 && adc_value[4] < 2500");
	auto htemp = (TH1F*)gPad->GetPrimitive("htemp");
	auto p = htemp->Fit("gaus", "", "", -0.5, 1.5);

	// midas_data->Draw("0.1*(tdc_value[2]-tdc_value[1])", "adc_value[0] > 100 && abs(tdc_value[2] - tdc_value[1]) < 200 && adc_value[4] < 3500");
	// htemp = (TH1F*)gPad->GetPrimitive("htemp");
	// htemp->Fit("gaus", "", "", -1.5, -0);

	// Run 5 (190)
	// te = -5.10870e00
	// tMuon = 7.04393e-1 +- 1.03146

	// Run 4 (188)
	// te = -5.16784 +- 8.21584e-1
	// tMuon = 1.61043 +- 1.09695

	// Run 3 (187)
	// Tpion = 1.23002 +- 7.87037e-1
	// TMuon = -2.3694 +- 9.81026e-1

	// Run 2 (186)
	// te = -4.74835 +- 916411e-1
	// tmuon = 1.57195 +- 9.98348e-1

	// Run 1 (185)
	// te = -4.97327 +- 8.07664e-1
	// tmuon = 4.62002e-1 +- 9.62776e-1
	// 
	// htemp->Fit("gaus", "", "", -4, 1);

	// midas_data->Draw("0.1*(tdc_value[2]-tdc_value[1]) - (18.145-0.363*adc_value[0]+0.001975*adc_value[0]*adc_value[0]-4.706e-6*adc_value[0]*adc_value[0]*adc_value[0]+5.221e-9*adc_value[0]*adc_value[0]*adc_value[0]*adc_value[0]-2.195e-12*adc_value[0]*adc_value[0]*adc_value[0]*adc_value[0]*adc_value[0])", "adc_value[0] < 800 && adc_value[0] > 100 && abs(tdc_value[2] - tdc_value[1]) < 200 && adc_value[4] < 3000");


	// htemp->Draw();
	// midas_data->Draw("adc_value[2]", "adc_value[2] > 100 && adc_value[2] < 3000");
} 
