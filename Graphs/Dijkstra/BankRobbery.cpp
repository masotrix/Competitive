#include <bits/stdc++.h>
using namespace std;

const int INF=1<<30;
void dijkstra(map<int,map<int,int>>& E, map<int,int>& d,
    vector<int>& s){

  priority_queue<tuple<int,int>,vector<tuple<int,int>>,
    greater<tuple<int,int>>> q;
  
  for (auto si: s) q.push(make_tuple(0,si));
  int t,w, no1,no2;

  while (!q.empty()){
    
    tie(t,no1)=q.top(); q.pop();
    if (d[no1]==INF) d[no1]=t;
    else continue;

    for (auto ne: E[no1]){ tie(no2,w)=ne;
      q.push(make_tuple(t+w,no2));}
  }
}

int main(){
 
  int N,M,B,S, a,b,t, maxi, maxc;
  vector<int> banks; vector<int> s;
  map<int,map<int,int>> E;
  map<int,int> d;

  while (scanf("%d %d %d %d", &N, &M, &B, &S)==4){

    banks=vector<int>(B); s=vector<int>();
    E=map<int,map<int,int>>(); s=vector<int>(S);
    d=map<int,int>();

    for (int i=0; i<M; i++){
      scanf("%d %d %d",&a,&b,&t);
      E[a][b]=E[b][a]=t;
    }

    for (int i=0; i<B; i++)
      scanf("%d", &banks[i]);
    sort(banks.begin(), banks.end());
    for (int i=0; i<S; i++)
      scanf("%d", &s[i]);
    for (int i=0; i<N; i++)
      d[i]=INF;
    
    dijkstra(E,d,s);

    maxi=0,maxc=0;
    for (auto b: banks)
      maxi = max(maxi, d[b]);

    for (auto b: banks)
      maxc += maxi==d[b];

    if (maxi==INF) printf("%d *\n", maxc);
    else printf("%d %d\n", maxc, maxi);
  
    for (auto b: banks){
      if (maxi==d[b]) {
        printf("%d%c",b,--maxc? ' ':'\n');
      }
    }
  }


  return 0;
}
