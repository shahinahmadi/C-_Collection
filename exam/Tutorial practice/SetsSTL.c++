#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;



/* Enter your code here. Read input from STDIN. Print output to STDOUT */  
int main() {
  int q, n, i,x,y;
  cin >> q;
  set<int> s;
  for (i=0;i<q;i++) {
    cin >> y >> x;
    if (y == 1) {
      s.insert(x);
    }
    if (y ==2) {
      s.erase(x);
    }
    if (y == 3) {
      set<int>::iterator itr = s.find(x);
      if (itr != s.end()) cout << "Yes" << endl;
      else cout << "No" << endl;
    }
  }
 
  return 0;
}



