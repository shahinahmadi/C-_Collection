// The main function to tese the created class of Polynomial

#include <iostream>
#include "Polynomial.h"
#include<vector>
#include <iostream>
#include <complex>
#include<cmath>

using namespace std;


int main(){


 
    
  /*  vector <double> a5{1.0,7.0,2.0,1.0};
    Polynomial p5(a5);
    cout<<p5;
   double integral=numerical_integral(p5,0,4);
   cout << "The integral result is " << integral << endl;


  Polynomial p6;
  vector <double> a6{1.0,3.0,2.0,9.0};
  p6.set_parameters(a6);
  double integral2=numerical_integral(p6,0,4);
  cout << "The integral2  result is " << integral2 << endl;


  Polynomial drivation= p6.derivative();
  cout<<"The result of drivation is: "<<drivation<<endl; */


  Polynomial p6;
  vector<double>a6{-6.0, -5.0, 2.0, 1.0};
  p6.set_parameters(a6);
  cout<<p6<<endl;
  double analytical_integrate=p6.analytical_integral(0.0,4.0);
  cout<<"The result of analytical integral is: "<<analytical_integrate<<endl;
  double numerical_integrate=numerical_integral(p6,0.0,4.0);
  cout<<"The result of numerical integral is: "<<numerical_integrate<<endl;
 Polynomial p7= p6.derivative();
 cout<<p7<<endl;
  
}
