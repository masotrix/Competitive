#include <bits/stdc++.h>
using namespace std;
#define lli int

const int INF=1<<30;

int init_capacities(vector<vector<int>> &c, vector<vector<int>> &cost,
    vector<set<int>> &ne, int N, int M, int d){
  
  int a,b,ca,co,e,tf=0,t=d*(N-1)+1;
  while (M--){
    scanf("%d %d %d %d %d",&a,&b,&ca,&co,&e);
    if (a==N || e==d-1 && b!=N) continue;
    a = d*(a-1)+e+1; b = b==N? t : d*(b-1)+e+2;
    c[a][b]=ca; cost[a][b]=co;
    ne[a].insert(b); ne[b].insert(a);
  }

  for (int i=0; i<N; i++){
    scanf("%d", &c[0][d*i+1]);
    ne[0].insert(d*i+1);
    ne[d*i+1].insert(0);
    tf+=c[0][d*i+1];
  }

  for (int i=1; i<N; i++){
    for (int j=0; j<d-1; j++){
      a=d*(i-1)+j+1; b=a+1;
      c[a][b]=INF; cost[a][b]=0;
      ne[a].insert(b); ne[b].insert(a);
    }
  }

  return tf;
}

void bfs(vector<set<int>> &ne, vector<vector<lli>> &c,
    vector<vector<int>> &d, int s){

  deque<int> q; q.push_back(s); d[s][s]=0; int u;
  while (!q.empty()) {
    
    u=q.front(); q.pop_front();
    for (auto &v: ne[u]){
      if (d[s][v]==INF && c[u][v]){
        q.push_back(v);
        d[s][v]=d[s][u]+1;
      }
    }
  }
}

void limitate(vector<vector<int>> &c2, vector<vector<int>> &c,
   vector<vector<int>> &cost, vector<set<int>> &ne, int k){

  int S=c.size();
  for (int i=0; i<S; i++)
    for (int j=0; j<S; j++)
      c2[i][j] = cost[i][j]<=k? c[i][j]:0;

  vector<vector<int>> d(S,vector<int>(S,INF));
  for (int u=1; u<S-1; u++)
    bfs (ne,c2,d,u);

  for (int u=1; u<S-1; u++)
    if (d[u][S-1]==INF)
      for (auto &v: ne[u])
        c2[v][u]=0;
}

void relabel_node(vector<vector<lli>> &c, vector<vector<lli>> &f,
    vector<set<int>> &ne, vector<int> &h, int u){

  lli mini=INF; int v;
  for (auto &v: ne[u])
    if (c[u][v]-f[u][v]>0)
      mini=min(mini,(lli)h[v]);
  h[u]=mini+1;
}

void push_flow(vector<vector<lli>> &c, vector<vector<lli>>&f,
    vector<lli> &e, int u, int v){

  lli df = min(e[u], c[u][v]-f[u][v]);
  f[u][v]+=df; f[v][u]-=df;
  e[u]-=df; e[v]+=df;
}

void discharge(vector<vector<lli>> &c, vector<vector<lli>> &f,
    vector<set<int>> &ne, vector<int> &h, vector<int> &ch,
    vector<lli> &e, deque<int> &q, int u, int s, int t, int N){

  auto it = ne[u].begin(); 
  int v, e1; bool gapDone=false;

  while (e[u]>0){
  
    v = *it;

    if (it==ne[u].end()){
      if (ch[h[u]]==1 && !gapDone){
        gapDone=true;
        for (int v=0; v<N; v++){
          if (h[v]>h[u] && v!=s){
            ch[h[v]]--; h[v]=max(h[v],N+1); ch[h[v]]++; }
        }
        ch[h[u]]--; h[u]=N; ch[h[u]]++;
      }

      ch[h[u]]--; relabel_node(c,f,ne,h,u); ch[h[u]]++;
      it = ne[u].begin();
    }
    else if (c[u][v]-f[u][v]>0 && h[u]==h[v]+1){
      e1=e[v];
      push_flow(c,f,e,u,v);
      if (e1<=0 && e[v]>0 && v!=t)
        q.push_back(v);
    }
    else it++;
  }
}

lli fifo_push_relabel(vector<vector<lli>> &c, vector<set<int>> &ne,
    int s, int t){
  
  int N=ne.size(), u; lli mxf=0;
  vector<vector<lli>> f(N,vector<lli>(N,0));
  vector<int> h(N,0), ch(2*N,0); vector<lli> e(N,0);
  for (auto &v: ne[s]) {
    f[s][v]=c[s][v]; f[v][s]=-c[s][v];
    e[v]=c[s][v]; e[s]-=e[v];
  }
  h[s]=N; ch[N]=1; ch[0]=N-1;

  deque<int> q;
  for (auto &v: ne[s])
    if (v != t) q.push_back(v);
  
  while (!q.empty()){
    u=*q.begin(); q.pop_front();
    discharge(c,f,ne,h,ch,e,q,u,s,t,N);
  }

  for (auto &v: ne[t]) mxf+=f[v][t];

  mxf=0;
  for (auto &v: ne[s]) mxf+=f[s][v];
  return mxf;
}



int main(){

  int N,M,d,mini,tf,T,i,j,k,mxf;
  scanf("%d", &T);

  for (int t=1; t<=T; t++){

    scanf("%d %d %d",&N,&d,&M);
    vector<vector<int>> c(d*(N-1)+2,vector<int>(d*(N-1)+2,0)), 
      c2(c.size(),vector<int>(c.size())),
      cost(c.size(),vector<int>(c.size()));
    vector<set<int>> ne(c.size());
    tf=init_capacities(c,cost,ne,N,M,d);

    mini=INF; i=0; j=100001;
    while (i!=j){
      k=(i+j)/2;
      limitate(c2,c,cost,ne,k);
      mxf=fifo_push_relabel(c2,ne,0,c.size()-1);
      if (mxf==tf){
        j=k; mini=k; 
      } else i=k+1;
    }
    if (mini==INF) printf("Case #%d: Impossible\n", t);
    else printf("Case #%d: %d\n", t, mini);

  }
 
  return 0;
}
