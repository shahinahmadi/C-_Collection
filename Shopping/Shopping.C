#include <iostream>
#include<vector>

using namespace std;


int main(){

  double  Shahin_sum=0;
  double  Jalal_sum=0;
  double Total_price;
  int S_item_number;
  int J_item_number;
  
 
  

  cout<<"Enter Shahin's item number: "<<endl;
  cin>>S_item_number;
  cout<< "The number of Shahin's items is: "<<S_item_number<<endl;

  cout<<"Enter Jalal's item number: "<<endl;
  cin>>J_item_number;
  cout<<"The number of Jalal's item is:"<<J_item_number<<endl;

  double Shahin_item_price[S_item_number];
  double Jalal_item_price[J_item_number];
  double S;
  double J;
  int i=0;
  int j=0;
  while (i<S_item_number){
      cout<<"Enter the prices of Shahin's items"<<endl;
      cin>>S;
      Shahin_item_price[i]=S;
      i+=1;
 }

  while (j<J_item_number){
    cout<<"Enter the prices of Jalal's items"<<endl;
    cin>>J;
    Jalal_item_price[j]=J;
    j+=1;

  }

  int a=sizeof(Shahin_item_price)/sizeof(Shahin_item_price[0]);
  int b=sizeof(Jalal_item_price)/sizeof(Jalal_item_price[0]);

  for (int i=0; i<a;i++){
    Shahin_sum+=Shahin_item_price[i];
  }

  for (int i=0; i<b; i++){
    Jalal_sum+=Jalal_item_price[i];
  }

  cout<<"The cost of Shahin's stuff: "<<Shahin_sum<<endl;
  cout<<"The cost of Jalal's stuff: "<<Jalal_sum<<endl; 
  cout<<"Enter the total price of shopping: "<<endl;
  cin>>Total_price;
  

   double Shared_shopping=(Total_price-Shahin_sum-Jalal_sum)/2;
  double Shahin_to_Jalal=Shared_shopping+Shahin_sum;
  cout<<"Shahin will pay"<<" "<<Shahin_to_Jalal<<endl;
}
