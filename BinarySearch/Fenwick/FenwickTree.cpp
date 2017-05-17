#include <bits/stdc++.h>
using namespace std;
#define ll long long int


ll sum(vector<ll>& v, int y) {
    ll sum = 0;
    
    while (y){
        sum += v[y];
        y -= y & -y;
    } 
    return sum;
}

ll range(vector<ll>& v, int x, int y) {

    return sum(v, y) - (x==1? 0 : sum(v, x-1));
}

void update(vector<ll>& v, int x, int val) {

    while (x <= v.size()){
        v[x] += val;
        x += x & -x;
    }
}


int main() {

    int n, x, y, q;
    char op;
    scanf("%d", &n);

  vector<ll> v(n+1);

  for (int i=1; i<=n; i++){
    scanf("%d", &y);
    update(v, i, y);
  }
  

  scanf("%d", &q);

  while (q--){

    do {
      op = getchar();
    } while (op!='q' && op!='u');
    
    scanf("%d %d", &x, &y);


    if (op == 'u') update(v, x, y);
    else cout << range(v, x, y) << '\n';
    
  }


    return 0;
}
