#include <iostream>
using namespace std;
int main(){
vector<double> numbers;
double number;

ifstream myfile("example.txt"); //file opening constructor

//Operation to check if the file opened
if ( myfile.is_open() ){
    
  while(myfile >>number ){

    //putting data into the vector
    numbers.push_back(number);
          

  }
 }
//   Conversion of vector to array 
int n=numbers.size();
double a[n];
int i;
for (int i=0; i<numbers.size();i++){
  a[i]=numbers.at(i);
 }
double maximum=0;

for ( i=0; i<a[n] ; i++){
  if (a[i]>maximum)
    maximum=a[i];
 }
cout<<"The maximum is"<<maximum<<endl;
if a[i]=maximum;
cout<<"The lable of maximum is"<<i<<endl;
}
