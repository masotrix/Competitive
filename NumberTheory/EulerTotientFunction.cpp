#include <bits/stdc++.h>
using namespace std;
#define N 1000000
bool comp[N], tracked[N];
vector<int> p;
int n,t,j,v;

void criba(){
  for (int i=2; i<N; i++){
    if (!comp[i]){ v=i+i;
      p.push_back(i);
      while (v<=N){ comp[v]=true; v+=i; }
    }
  }
}

int phi(int n){
    
    int res=n;

    for (int i=0; pow(p[i],2)<=n; i++){
        if (n%p[i]==0){
            while (n%p[i]==0) n/=p[i];
            res -= res/p[i];
        }
    }

    if (n>1) res -= res/n;
    return res;
}

int main(){
  
  criba(); scanf("%d",&t);
  while (t--){
  
    scanf("%d", &v);
    printf("%d\n", phi(v));
  }

  return 0;
}
