#include <bits/stdc++.h>
using namespace std;
#define par pair<int,int>
#define neigh par
#define mkp(_t,_g) make_pair(_t,_g)
#define t(_i) _i.first
#define mkt(_t,_p,_no) make_tuple(_t,_p,_no)
#define input tuple<int,int,int>

#define neighd map<int,int>
#define node pair<int,pair<vector<int>,neighd>>
#define mkn() mkp(-1,mkp(vector<int>(),neighd()))
#define ne(_n) _n.second.second
#define p(_n) _n.second.first
#define l(_n,_no) ne(_n)[_no]
#define r(_n,_no) ne(_n).erase(_no)

#define i(_ne) _ne.first
#define w(_ne) _ne.second


bool closer(int t1, int t2){
  if (t2 && (t1==-1 || t1>=t2)) return true;
  return false;
} 

vector<node> makeGraph(int N, int E){
  vector<node> nodes;
  int a, b, l;
  for (int i=0; i<N; i++)
    nodes.push_back(mkn());
  for (int i=0; i<E; i++){
    scanf("%d %d %d", &a, &b, &l);
    l(nodes[a],b) = l;
  }
  return nodes;
}

void removeShort(vector<node>& nodes, int ini, int fin){

  queue<int> q; q.push(fin);
  while (!q.empty()){
    
    int no = q.front(); q.pop();  
    for (auto noi: p(nodes[no])){
      q.push(noi); 
      r(nodes[noi],no);
    }
  }
  for (auto &n: nodes){
    t(n)=-1;
    p(n)=vector<int>();
  }
  t(nodes[ini])=0;
}

int dijkstra(vector<node>& nodes, int ini, int fin, bool yes){

  priority_queue<input,vector<input>,greater<input>> q; 
  for (auto ne: ne(nodes[ini])) q.push(mkt(w(ne),ini,i(ne)));
  node n; int t,p,no;

  while (!q.empty()){
    
    tie(t,p,no) = q.top();
    n=nodes[no]; q.pop();
    if (t(nodes[no])!=-1){
      if (t(nodes[no])==t)
        p(nodes[no]).push_back(p);
      continue;
    }
    t(nodes[no])=t;
    p(nodes[no]).push_back(p);
    if (no==fin){
      if (yes) return t;
      continue;
    }
  
    for (auto ne: ne(n)) {
      if (closer(t(nodes[i(ne)]),t+w(ne))){
        q.push(mkt(t+w(ne),no,i(ne)));
      }
    }
  }

  return -1;
}


int main(){
 
  int N,E,ini,fin;
  scanf("%d %d", &N, &E);

  while (N!=0){
    scanf("%d %d", &ini, &fin);
    vector<node> nodes = makeGraph(N,E);
    t(nodes[ini])=0;
  
    dijkstra(nodes,ini,fin,false);
    removeShort(nodes,ini,fin);
    printf("%d\n", dijkstra(nodes,ini,fin,true));
  
    scanf("%d %d", &N, &E);
  }

  return 0;
}
