// Overview on sringstream
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

int main(){

  stringstream ss;
  string  s={'1','2','3','4'};
  vector<int>myvector;
  int integer;
  char ch;
  ss<<s;
  
  while (ss>>integer){
    myvector.push_back(integer);
    ss>>ch;}
  cout<<myvector.size()<<endl;
  
  for (int i=0;i<myvector.size();i++){
  
    cout<<myvector[i]<<endl;}
}



