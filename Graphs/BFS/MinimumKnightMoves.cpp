#include <bits/stdc++.h>
using namespace std;
#define coord pair<int,int>
#define neigh vector<int>
#define node pair<pair<coord,int>,neigh>
#define mkc(_x,_y) make_pair(_x,_y)
#define mkn(_x,_y,_i) mkc(mkc(mkc(_x,_y),_i),neigh())
#define c(_n) _n.first.first
#define x(_n) c(_n).first
#define y(_n) c(_n).second
#define i(_n) _n.first.second
#define n(_n) _n.second
#define addN(_n,_nv) n(_n).push_back(_nv)


bool valid(node p, int H, int W){

  if (x(p)>=0 && y(p)>=0 && x(p)<H && y(p)<W)
    return true;
  return false;
}

vector<node> sides =
  {mkn(2,1,0),mkn(1,2,0),mkn(-2,1,0),mkn(2,-1,0),
   mkn(-1,2,0),mkn(1,-2,0),mkn(-1,-2,0),mkn(-2,-1,0)};

vector<node> makeGraph(int H, int W){
  vector<node> nodes;
  map<coord,int> coords;
  for (int i=0; i<H; i++){
    for (int j=0; j<W; j++){
      coords[mkc(i,j)] = i*W+j;
    }
  }
  for (int i=0; i<H; i++){
    for (int j=0; j<W; j++){
      node n = mkn(i,j,0);
      for_each(sides.begin(), sides.end(), [&](node s){
        node nv = mkn(i+x(s),j+y(s), 0);
        if (valid(nv,H,W)) addN(n,coords[c(nv)]);   
      });
      nodes.push_back(n);
    }
  }
  return nodes;
}

int bfs(vector<node>& nodes, node& pi, node& pf){

  deque<node> q; q.push_back(pi);  
  int mov=-1; node p;

  while (true){
    
    p=q.front(); q.pop_front();

    for_each (n(p).begin(), n(p).end(), [&](int i){
         i(nodes[i])=i(p)+1; q.push_back(nodes[i]);
         if (c(nodes[i])==c(pf)) { mov=i(nodes[i]); return; }
    });

    if (mov!=-1) return mov;
  }
}


int main(){
 
  int t; string ini, fin;
  int i1,j1,i2,j2; node pi, pf;
  vector<node> nodes = makeGraph(8,8);
  scanf("%d", &t);

  while (t--){
    cin >> ini >> fin;
    if (ini == fin) {puts("0"); continue;}
    i1=ini[0]-'a'; j1=ini[1]-'1';
    i2=fin[0]-'a'; j2=fin[1]-'1';
    coord c1=mkc(i1,j1), c2=mkc(i2,j2);
    for_each(nodes.begin(), nodes.end(), [&](node n){
      if (c(n)==c1){ pi=n; i(pi)=0; } if (c(n)==c2) pf=n;
    });
    printf("%d\n", bfs(nodes, pi, pf));
  }

  return 0;
}
