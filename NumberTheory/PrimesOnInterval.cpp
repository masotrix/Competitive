#include <bits/stdc++.h>
using namespace std;
#define N 1000030
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
  
  criba(); scanf("%d %d %d",&a,&b,&k);
  vector<int>::iterator ite; l=-1; 
  pf=(lower_bound(p.begin(),p.end(),a)-p.begin())+k-1;
  if (pf<p.size()){
    while (p[pf]<=b){
      l=max(l,p[pf]-a+1);
      ite=lower_bound(p.begin(),p.end(),a); 
      a=*ite+1; pf=ite-p.begin()+k;
    }
  }

  if (l!=-1) l=max(l,b-a+2);

  printf("%d\n", l);

  return 0;
}
