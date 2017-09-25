#include <iostream>
#include <vector>
using namespace std;
int main() {
  int n;
  cin >> n;
  vector<int> v(n), d(n);
  for(int i=0;i<n;i++) cin >> v[i];
  int l=0, r=0, ans=0;
  while(r<n) {
    if(v[r]>v[l]) {
      r++;
    } else if(v[r]==v[l]) {
    } else {
      l = r;
      r++;
    }
  }


  return 0;
}
