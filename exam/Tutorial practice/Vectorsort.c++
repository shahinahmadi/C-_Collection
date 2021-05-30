#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
 vector<int>vec;
    int n, inp;
    cin >> n;
    
    while (cin >> inp) 
    vec.push_back(inp);
 
    sort(vec.begin(), vec.end());
    
    for(int i=0; i<n; i++)
    cout << vec[i] << " ";    
    return 0;
}
