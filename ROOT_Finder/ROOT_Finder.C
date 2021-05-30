// This code is written to calculate the roots of quadratic equation

#include <iostream>
#include <cmath>

using namespace std;

int main(){

  //The variables used in the equation
  double a,b,c,x,delta;
  double eq;
  double x1,x2,x3;
  cin>>a;
  cin>>b;
  cin>>c;

  //The equation and delta
  eq=a*pow(x,2)+b*x+c;
  delta=pow(b,2)-4*a*c;

  // Roots for the first senario (delta=0)
  x1=b/(2*a);

  //Roots for the second senario(delta>0)
  x2=(b-sqrt(delta))/2*a;
  x3=(b+sqrt(delta))/2*a;

  if (delta<0){
    cout<<"There is no root for the given equation"<<endl;}
  else if (delta=0){
    cout<<"There is one root for the given equation, which is: "<<endl;
    cout<<x1<<endl;}
  else{
    cout<<"There are two roots for the given equations, which are: "<<endl;
    cout<<x2<<" "<<x3<<" "<<endl;}
    
}
