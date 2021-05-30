#include "TROOT.h"    // to use gROOT point
#include "TObject.h" 
#include "TFile.h"
#include "TTree.h"


// .L demo1.C


void example1()
{


    TTree t("t","a simple Tree");
    // key = t
	// title = a simple tree

	
	/*
	|	suppose we have 3 brothers, A, B, and C
	|	each time the mother will distribute $100 to them,
	|	Let use: 
	|	money_A for brother A
	|	money_B for brother B
	|	money_C for brother C	
	*/
	
	Int_t money_A, money_B, money_C;


	// now, link variables "money_A", "money_B", money_C
	/*
	|	
	|	3 branchs, and each branch has 1 leaf.
	|	b1->
	|	b2->
	|	b3->
    |
	|	or 1 branch, 3 leaves. ( discuss latter)
	|	b->lv1
	|	 ->lv2
	|	 ->lv3
	*/


	/* 
	|	use Branch method, to set up a branch.
    |  (key for the branch, address of variable, leaf and its type)  	 |
	*/
	
	// a branch "mA", linked to variable money_A, with one leaf.
    t.Branch("mA", &money_A, "money_A/I");
    t.Branch("mB", &money_B, "money_B/I");
    t.Branch("mC", &money_C, "money_C/I");

    money_A = 10;   money_B = 30;   money_C = 60;   t.Fill();
    money_A = 20;   money_B = 30;   money_C = 50;   t.Fill();
    money_A = 50;   money_B = 35;   money_C = 15;   t.Fill();


	//-----Save to file------//
	TFile f("example1.root","recreate");   
	t.Write();
	f.Close();


    /*
    |   I: 	32 bit signed integer 
    |   i: 	32 bit unsigned integer 
    |   F: 	32 bit floating point 
    |   D: 	64 bit floating point 
    */

	
}
