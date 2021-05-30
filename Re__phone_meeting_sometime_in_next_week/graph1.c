// Two sets of data on one graph
#include <iostream>
#include"TAttLine.h"
{
 auto gr = new TGraph("~/products/root/macros/11.txt");
for (int i=0;i<gr->GetN();i++) gr->GetY()[i]*=2;//Scaling
 gr->SetLineColor(kBlue+2);
gr->SetMarkerColor(kBlue+2);
 gr->SetTitle("Transmittance measurement(Three repeated measurements are averaged);Light wavelength(nm);Transmittance(%)");
gr->GetXaxis()->CenterTitle();
gr->GetYaxis()->CenterTitle();
 gr->Draw();
 auto f = new TGraph("~/products/root/macros/12.txt");
for (int i=0;i<f->GetN();i++) f->GetY()[i]*=2;//Scaling
f->SetLineColor(kRed);
f->SetMarkerColor(kRed);
f->SetTitle("Transmittance investigation;Light wavelength(nm); Transmittance(%)");
f->Draw("SAME");
auto legend=new TLegend(0.2,0.6,0.4,0.8);
legend->AddEntry(gr,"604_9505_square","l");
legend->AddEntry(f,"604_9505_oven_square","l");
legend->Draw("AP");
const int n = 661;
Double_t x[n],y[n];
for (Int_t i=0;i<f->GetN();i++)
{
x[i]=gr->GetX()[i];
y[i]=(gr->GetY()[i]+f->GetY()[i])*0.5;
}
auto gr1 = new TGraph(n,x,y);
gr1->SetLineColor(kGreen+1);
gr1->Draw("SAME");
}

