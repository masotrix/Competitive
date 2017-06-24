#include <bits/stdc++.h>
using namespace std;
#define lli int

const int INF=1<<30;
void bfs(vector<set<int>> &ne, vector<vector<lli>> &c,
    vector<vector<int>> &d, int s){

  deque<int> q; q.push_back(s);
  int u; d[s][s]=0;

  while (!q.empty()){  

    u=q.front(); q.pop_front();
    for (auto &v: ne[u]){
      if (c[u][v] && d[s][v]==INF){ 
        d[s][v]=d[s][u]+1; 
        q.push_back(v); 
      }
    }
  }
}

bool init_capacities(vector<vector<int>> &c, vector<set<int>> &ne,
    int N, int M, int day){
  
  int a,b;
  while (M--){
    scanf("%d %d",&a,&b);
    c[a-1][b-1]=1;
    ne[a-1].insert(b-1);
    ne[b-1].insert(a-1);
  }

  vector<vector<int>> d(N,vector<int>(N,INF));
  for (int i=0; i<N-1; i++)
    bfs(ne,c,d,i);

  for (int u=1; u<N-1; u++){
    if (day < d[0][u]+d[u][N-1]){
      for (int v=0; v<N; v++){
        c[v][u]=0;
        ne[v].erase(u);
        ne[u].erase(v);
      }
    }
  }

  d = vector<vector<int>>(N,vector<int>(N,INF));
  for (int i=0; i<N-1; i++)
    bfs(ne,c,d,i);

  for (int u=1; u<N-1; u++){
    if (d[0][u]!=INF && d[u][N-1]==INF){
      for (int v=0; v<N; v++)
        c[v][u]=0;
    }
  }

  for (int u=1; u<N-1; u++){
    for (auto &v: ne[u]){
      if (c[u][v]){
        c[u][v]=0;
        c[u+N-1][v]=1;
        ne[u+N-1].insert(v);
        ne[v].insert(u+N-1);
      }
    }
    c[u][u+N-1]=1;
    ne[u].insert(u+N-1);
    ne[u+N-1].insert(u);
  }

  if (d[0][N-1]==INF) return false;
  return true;
}

void init_flow(vector<vector<lli>> &c, vector<vector<lli>> &f,
    vector<set<int>> &ne, vector<int> &h, vector<int> &ch,
    vector<lli> &e, int s){

  for (auto &v: ne[s]) {
    f[s][v]=c[s][v]; f[v][s]=-c[s][v];
    e[v]=c[s][v]; e[s]-=e[v];
  }
  int N = ne.size();
  h[s]=N; ch[N]=1; ch[0]=N-1;
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
  vector<vector<lli>> f(N,vector<lli>(2*N-2,0));
  vector<int> h(2*N-2,0), ch(4*N,0); vector<lli> e(2*N-2,0);
  init_flow(c,f,ne,h,ch,e,s);

  deque<int> q;
  for (auto &v: ne[s])
    if (v != t) q.push_back(v);
  
  while (!q.empty()){
    u=*q.begin(); q.pop_front();
    discharge(c,f,ne,h,ch,e,q,u,s,t,N);
  }

  for (auto &v: ne[s]) mxf+=f[s][v];
  return mxf;
}



int main(){

  int N,M,day; bool need;
  scanf("%d %d %d",&N,&M,&day);

  while (N){

    vector<vector<int>> c(2*N-2,vector<int>(2*N-2,0));
    vector<set<int>> ne(2*N-2);

    need=init_capacities(c,ne,N,M,day);
    if (!need) puts("0");
    else printf("%d\n", fifo_push_relabel(c,ne,0,N-1));
    scanf("%d %d %d",&N,&M,&day);
  }
 
  return 0;
}
