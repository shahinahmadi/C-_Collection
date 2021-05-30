// This script is a good practice to understand stringstream

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

int main(){
//converting the elements of a vector to string and saving the result to a file
  
  vector<int> v = {10,200,3000,40000};
  int i;
  stringstream sw;
  string stringword;

  for (i=0;i<v.size();i++) 
    {
      sw << v[i] << ',';
    }
  stringword = sw.str();
  cout << "Vector in string : "<< stringword << endl;



  ofstream myfile;
  myfile.open ("written.txt");
  myfile << stringword;
  myfile.close();


//Reading the string from the file and putting the elements into a vector

  ifstream yourfile;
  yourfile.open ("written.txt");
  getline (yourfile,stringword);

  cout <<"This is the length of the string: "<<endl;
  cout<<stringword.length()<<endl;
  cout << "Read From File = " << stringword << endl;

  cout << "Convert back to vector = "<<endl ;
  for (int i=0;i<stringword.length();i++)
    {
      if (stringword.find(','))
      {
	  int value;
	  char ch;
	  istringstream (stringword) >> value;
	  v.push_back(value);
	  
	  stringword.erase(0, stringword.find(','));
	}
    }
  cout<<"Lets see if it works"<<endl;
  for (int j=0;j<v.size()-1;j++) 
    {
      cout << v.at(j) << " " ;
    }

}
