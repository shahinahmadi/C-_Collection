#include "Polynomial.h"
#include<iostream>
#include <cmath>

using namespace std;
Polynomial::Polynomial(){a.push_back(0);}

Polynomial::Polynomial( const vector<double>& b ){a=b;}

Polynomial::Polynomial( const Polynomial& p ){a=p.a;}

void Polynomial:: set_parameters( const vector<double> b){

  a=b;
}

void Polynomial:: set_parameter( int i, double b){
  for (int j=a.size(); j<b; j++){
    a.push_back(0.0);
  }
  a[i]=b;
}




double Polynomial:: get_parameter( int i)const {
  if (i<a.size())
    return a[i];
  else
    return 0.0;

} 

double Polynomial:: operator()(double x)const{

  double Function=0;
  double xPow=1.0;
  for (int i=0; i<a.size(); i++){
    Function+=a[i]*pow(x,i);
   
  }
  return Function;
}

// A helper function for loading an operator


int Polynomial:: get_order()const{
  int order=a.size()-1;
  return order;
}

void Polynomial:: print_function(){

  for(int i=0; i<a.size()-1; i++){

    cout<< a[i]<< "x^"<<i<<"+";

  }
  cout<<a.at(a.size()-1)<<"x^"<<a.size()-1;


}


 double  Polynomial::analytical_integral( double xmin, double xmax){
  double integral=0;
  for (int i=0; i<a.size(); i++){
   integral+=(a[i]*pow(xmax,i+1)-a[i]*pow(xmin,i+1))/(i+1);
  
  }
  return integral;
  }


Polynomial  Polynomial:: derivative( ){
  Polynomial p2;
  vector <double> vect;
  for (int i=1; i<=a.size();i++){
    vect.push_back(a[i]*i);
    p2.set_parameters(vect);}
  return p2;}

double  numerical_integral( const Polynomial& p, double xmin, double xmax){
  double integ=0;
  int n=100000;
  double delta;
  delta=(xmax-xmin)/n;
  for(int i=0; i<n; i++){
    double xi;
    xi=xmin+i*delta;
    double function=p.operator()(xi);
    integ+=function*delta;}

  return integ;
}


ostream&  operator<<(ostream& out,  const Polynomial &P){

  int order= P.get_order();
  
  for (int i=0; i<order+1; i++){
    if (P.get_parameter(i)==0){
      out<< P.get_parameter(0);
    }
    if (P.get_parameter(i)>0){
      out<< "+";
      out<< P.get_parameter(i);
      out << "*x^"<< i;}
    else {
      out<< P.get_parameter(i);
      out<<"*x^"<<i;

    }
  }
  return out;
  
}
  



