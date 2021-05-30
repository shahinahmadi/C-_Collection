#include "TROOT.h"    // to use gROOT point
#include "TObject.h" 
#include "TFile.h"
#include "TTree.h"
void example3()
{
    
    TTree t("t","a Tree");

	/*
	|	Declare an array, and set up the size.
    */
	
    Int_t n_maxSize = 100;

    Int_t energy[n_maxSize] = {0};

    Int_t n;
    
    t.Branch("Size", &n, "n/I");
    t.Branch("Energy", energy, "particle_enery[n]/I");
	/*
    |   ! set up a branch to store "n" first
    |
    |   then create a branch "Energy", 
    |   and a leaf to store the array 
    |   with its size linking to variable "n"
    |
    |   
    */

    n=1;
    energy[0]=9;
    t.Fill();

    n=2;
    energy[0]=11;
    energy[1]=111;
    t.Fill();

    n=3;
    energy[0]=3;
    energy[1]=33;
    energy[2]=333;
    t.Fill();

    /*
    |   read the result by following command:
    |   t.Scan("n:particle_enery","","colsize=20")
    */

	//-----Save to file------//
	TFile f("example3.root","recreate");   
	t.Write();
	f.Close();
	
}


    
