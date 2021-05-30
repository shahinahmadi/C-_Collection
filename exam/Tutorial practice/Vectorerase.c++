#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
  int n,i=0;
  cin>>n;
  vector  <int> v(n);
  while(n--){
    cin >>  v[i++];  
  }
  int x,a,b;
  cin >>  x ;
  v.erase(v.begin()+x);
  cin >>  a >>b;
  v.erase(v.begin()+a,v.begin()+b);
  i=0;
  cout  <<  v.size()  <<endl;
  while(v.size()!=i){
    cout  <<  v[i++]  <<  " ";
  }
  return  0;
}

