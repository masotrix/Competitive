#include <bits/stdc++.h>
using namespace std;
#define N 10000000
bool comp[N+1];
vector<int> p;
int n,a,b,k,pf,l,v;

void criba(){
  for (int i=2; i<N; i++){
    if (!comp[i]){ 
      p.push_back(i); v=i+i;
      while (v<=N){ 
        comp[v]=true;
        v+=i;
      }
    }
  }
}

int main(){
  
  criba();
  scanf("%d", &n);

  while (n){
  
    for (int i=0; p[i]/2<=n; i++){
      if (binary_search(p.begin(),p.end(),n-p[i])){
        printf("%d = %d + %d\n",n,p[i],n-p[i]);
        break;
      }
    }
    scanf("%d", &n);
  }

  return 0;
}
