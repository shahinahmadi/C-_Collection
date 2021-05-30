#include "TROOT.h"    // to use gROOT point
#include "TObject.h" 
#include "TFile.h"
#include "TTree.h"
void example2()
{


    TTree t("t","a Tree");

	/*
	|	suppose: 2 brothers, A and B
	|	Brother A have 2 bank accounts.
	|	Brother B have 3 bank accounts.	
    */
	
	Int_t A_account[2] = {0};
    Int_t B_account[3] = {0};



	
	/*
    |   create a branch, and a leaf to store the array
    |   a branch "A", linked to arrary A_account, 
    |   with one leaf "bank" .
    */
    t.Branch("A", A_account, "bankfromA[2]/I");.
    t.Branch("B", B_account, "bankfromB[3]/I");

    
    A_account[0] = 10;  
    A_account[1] = 110;  

    B_account[0] = 9;  
    B_account[1] = 99; 
    B_account[2] = 999; 
    t.Fill();


    A_account[0] =  20;  
    A_account[1] = 120;  
 
    B_account[0] = 7;  
    B_account[1] = 77; 
    B_account[2] = 777; 
    t.Fill();

	//-----Save to file------//
	TFile f("example2.root","recreate");   
	t.Write();
	f.Close();
	
}

