#include "TROOT.h"    // to use gROOT point
#include "TObject.h" 
#include "TFile.h"
#include "TTree.h"
//  to store in a the "struct" data type.
void example4()


{

	/*
	|	you can set up multiple leaves in a branch,
	|   
	|    "struct" or "class", 
	|   here I demonstrate the "struct" first 
    |	But it is recommended to use "class"
    |
	*/

    struct particle_STRUCT { 
        Float_t energy; 
        Float_t position[3];
        
    };

    
     particle_STRUCT sParticle;

    TTree t("t","a simple Tree with struct");

    t.Branch("Energy",  &sParticle.energy,  "p_energy/F");
    t.Branch("Position", sParticle.position,"pos[3]/F");

	/*
	|	use "." operator to access the element inside struct
	|   
	|   the rules of setup the leaf and branach are the same.
    |
    |   or 
    |   t.Branch("Particle_info", &sParticle, "e/F:pos[3]/F")
    |   t->Scan("e:pos")
	*/
    
    sParticle.energy = 11.;
    sParticle.position[0] = 7.7;
    sParticle.position[1] = 2.2;
    sParticle.position[2] = 3.3;
    t.Fill();    

    sParticle.energy = 99.;
    sParticle.position[0] = 191.;
    sParticle.position[1] = 291.;
    sParticle.position[2] = 391.;
    t.Fill();
    //-----Save to file------//
    TFile f("example4.root","recreate");  
    t.Write();
    f.Close();

}





