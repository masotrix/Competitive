#include <bits/stdc++.h>
using namespace std;
#define ul unsigned long long int
#define N 1000000
int compound[N+1], d[N+1];
set<int> p, sp;
ul l,h; int val,t;
vector<int> v;

void criba(){
  for (int i=2; i<N; i++){
    if (!compound[i]){
      p.insert(i);
      compound[i]=i;
      val=i+i;
      while (val<=N){
        compound[val]=i;
        val+=i; }
    }
  }
}

void divisors(){
  compound[1]=1;
  for (int i=2; i<N; i++){
    
    map<int,int> m;
    val = i;
    while (val!=1){
      if (m.find(compound[val])==m.end())
        m.insert(make_pair(compound[val],1));
      else m[compound[val]]=m[compound[val]]+1;
      val /= compound[val];
    }

    if (m.size()==2 &&
        p.find((*m.begin()).first)!=p.end() &&
        (*m.begin()).second==1 &&
        p.find((*(next(m.begin(),1))).first)!=p.end() &&
        (*(next(m.begin(),1))).second==1)

      sp.insert(i);


    d[i] = 1;
    for (auto ite = m.begin(); ite!=m.end(); ite++)
      d[i]*=((*ite).second+1);
  }

}

int main(){
  
  criba();
  divisors();
  
  for (int i=0; i<N; i++)
    if (sp.find(d[i])!=sp.end())
      v.push_back(i);

  for (int i=8; i<v.size(); i+=9)
    printf("%d\n", v[i]);



  return 0;
}
