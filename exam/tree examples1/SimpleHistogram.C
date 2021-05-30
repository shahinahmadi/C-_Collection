#include "TH1.h"
#include "TRandom.h"
#include "TStyle.h"

void SimpleHistogram() { 

   TH1D * h1 = new TH1D("h1","h1",50,0,10);

   for (int i = 0; i < 10000; ++i) {
      double x = gRandom->Gaus(5,2);
      h1->Fill(x); 
   }

   h1->Draw();

   gStyle->SetOptStat(111111110);

}
