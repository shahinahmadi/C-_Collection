// Stand-alone program based on AnalyzeVariables.C
#include <TSelector.h>
#include <TFile.h>
#include <TTree.h>
//**********Definition************
int main(int argc, char *argv[])
{
  // Open the root file
  TFile* file1 = new TFile("experiment.root"); 
  // Read tree1 from that file 
   TTree* tree1 = (TTree*) file1->Get("tree1"); 
  // Check if you have read
   if  (tree1 != NULL){
      // Process the created class
      tree1->Process("AnalyzeVariables.C");
    
  }
}

  
