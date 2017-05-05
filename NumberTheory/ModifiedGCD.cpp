#include <bits/stdc++.h>
using namespace std;


int main(){
  int a, b, t;
  cin >> a >> b >> t;
  set<int>::iterator it;
  set<int> divisors;
  
  b = __gcd(a,b);
  a = sqrt(b);
  
  for (int i=1; i<=a; i++){
    if (b%i==0){
      divisors.insert(i);
      divisors.insert(b/i);
    }
  }

  while (t--) {

    scanf("%d %d", &a, &b);
    it = --divisors.upper_bound(b);
    if (a<=*it && b>=*it) cout << *it << endl;
    else cout << "-1\n";
  }
  
  return 0;
}
