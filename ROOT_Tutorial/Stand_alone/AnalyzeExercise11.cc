// Stand-alone program based on AnalyzeExercise10.C
// To compile this:
//   g++ -o AnalyzeExercise11 AnalyzeExercise11.cc `root-config --cflags` `root-config --glibs`

#include <TFile.h>
#include <TTree.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TH2.h>
#include <TStyle.h>
#include <TH1.h>
#include <TMath.h>
#include <TSelector.h>
#include <TFile.h>
#include <TTree.h>

// Main program.
int main(int argc, char *argv[])
{
    //******** Definition section *********

    TH1* ptHist = NULL;

    TH1* thetaHist = NULL;

    //******** Initialization section *********
    ptHist = new TH1D("pt","Histogram of pt",100,0,35);
    ptHist->GetXaxis()->SetTitle("pt [GeV]");
    ptHist->GetYaxis()->SetTitle("number of events");

    thetaHist = new TH1D("theta","Histogram of Theta",100,0,.240);
    thetaHist->GetXaxis()->SetTitle("theta [radians]");
    thetaHist->GetYaxis()->SetTitle("number of events");



    // Open the file that the TSelector class will process.
    TFile* inputfile = new TFile("experiment.root");
    // Read tree1 from the input file.
    TTree* tree1 = (TTree*) inputfile->Get("tree1"); 


    Float_t px, py, pz;
    tree1->SetBranchAddress("px",&px);
    tree1->SetBranchAddress("py",&py);
    tree1->SetBranchAddress("pz",&pz);



    for(int entry=0; entry<tree1->GetEntries(); entry++){

        //******** Loop section *********
        //* You will probably want to put a GetEntry here. 
        tree1->GetEntry(entry);

        Double_t pt = TMath::Sqrt((px)*(px) + (py)*(py)); // Exercise 6
        Double_t theta = TMath::ATan2(pt,pz);                // Exercise 7

        ptHist->Fill(pt);
        thetaHist->Fill(theta);




    }

    //******** Wrap-up section *********
    TFile* outputfile = new TFile("analysis.root","recreate");
    ptHist->Write();
    thetaHist->Write();
    outputfile->Close();



}
