#include <bits/stdc++.h>
using namespace std;
#define par pair<int,int>
#define neigh pair<int,par>
#define neighd map<int,par>
#define node pair<int,neighd>
#define mkp(_t,_g) make_pair(_t,_g)
#define mkn() mkp(-1,neighd())
#define n(_n) _n.second
#define t(_n) _n.first
#define ne(_n,_no) n(_n)[_no]
#define g(_n,_no) n(_n)[_no].second
#define l(_n,_no) n(_n)[_no].first
#define i(_ne) _ne.first
#define w(_ne) _ne.second.first


int available(int  g, int t, int w){

  if (g==-1 || t<g-w || g<=t) return t+w;
  return g+w;
}

bool closer(node n, int avT){
  if (t(n)==-1 || t(n)>avT)
    return true;
  return false;
}

vector<node> makeGraph(int N, int E){
  vector<node> nodes;
  int a, b, l;
  for (int i=0; i<N; i++)
    nodes.push_back(mkn());
  for (int i=0; i<E; i++){
    scanf("%d %d %d", &a, &b, &l);
    ne(nodes[a-1],b-1) = mkp(l,-1);
    ne(nodes[b-1],a-1) = mkp(l,-1);
  }
  return nodes;
}

int dijkstra(vector<node>& nodes, int ini, int fin){

  priority_queue<par,vector<par>,greater<par>> q; 
  q.push(mkp(t(nodes[ini]),ini));
  node v,n; int g1,g2,avT,no1,no2;

  while (!q.empty()){
    
    no1 = q.top().second; if (no1==fin) return q.top().first;
    v=nodes[no1]; q.pop();

    for_each (n(v).begin(), n(v).end(), [&](neigh ne){
      
      no2=i(ne); n=nodes[no2];
      g1=g(v,no2); g2=g(n,no1); g1-=(g1-g2)&(g1>>31);
      avT = available(g1,t(v),w(ne));
      if (closer(nodes[no2],avT)){
        t(nodes[no2])=avT; q.push(mkp(avT,no2));
      }
    });
  }

  return t(nodes[fin]);
}


int main(){
 
  int N,E,ini,fin,G,K,tm;
  scanf("%d %d", &N, &E);
  scanf("%d %d %d %d", &ini, &fin, &K, &G);
  vector<int> gr(G);
  for (int i=0; i<G; i++) { scanf("%d", &tm); gr[i]=tm-1; }
  vector<node> nodes = makeGraph(N,E);
  
  t(nodes[ini-1])=K;
  int time=0;
  for (int i=1; i<G; i++){
    time+=l(nodes[gr[i-1]],gr[i]);
    g(nodes[gr[i-1]],gr[i])=time;
  }

  printf("%d\n", dijkstra(nodes, ini-1, fin-1)-K);

  return 0;
}
