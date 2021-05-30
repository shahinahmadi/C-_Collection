// This program opens a CSV file, takes the data from that and plots that
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cstdio>
#include "TGraph.h"
using namespace std;

//function protoypes. Our data returning data type here is void. That is why that we use void function. We call this function void.

void plot(){

    vector<double> wavelengths;
    vector<double> transmissions;

    ifstream myfile("/home/shahin/Desktop/NEW.CSV"); //file opening constructor

    //Operation to check if the file opened
    if ( myfile.is_open() ){
    
        double wavelength, transmission, stddev;
        char delimiter;
        
        // Read the file.
        myfile.ignore(1000, '\n');
        while(myfile >> wavelength >> delimiter >> transmission >> delimiter >> stddev){

            //putting data into the vector
            wavelengths.push_back(wavelength);
            transmissions.push_back(transmission);

        }
    }

    
    //   Writing a for loop which prints the data in the vectors to screen.
    for (int i; i < wavelengths.size(); ++i){
        cout<< wavelengths.at(i)<<" "<<transmissions.at(i)<< endl; 
        }

    
    //   Conversion of vector to array 
    int n=911;
    double x[n],y[n];
    for (int i=0; i<wavelengths.size();i++){
    x[i]=wavelengths.at(i);
    y[i]=transmissions.at(i);
auto gr = new TGraph(n,x,y);
gr->Draw();
}

}

    //3. Write code here to plot the information in the arrays using a TGraph

