#include <bits/stdc++.h>
using namespace std;
#define lli long long int

const lli INF=1LL<<60;
void init_capacities(vector<vector<lli>> &c,
    vector<set<int>> &ne, int M){
  
  int a,b,t;
  for (int i=0; i<M; i++){
    scanf("%d %d %d", &a,&b,&t);
    if (a==b) continue;

    a--; b--;
    ne[a].insert(b);
    ne[b].insert(a);
    c[a][b]+=t;
    c[b][a]+=t;
  }
}

void init_flow(vector<vector<lli>> &c, vector<vector<lli>> &f,
    vector<set<int>> &ne, vector<int> &h, vector<int> &ch,
    vector<lli> &e, int s, int N, int M){

  int v;

  for (int u=0; u<N; u++)
    h[u]=ch[u]=e[u]=0;

  for (auto  &v: ne[s]) {
    f[s][v]=c[s][v]; f[v][s]=-c[s][v];
    e[v]=c[s][v]; e[s]-=e[v];
  }
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

void fifo_push_relabel(vector<vector<lli>> &c, vector<vector<lli>> &f,
    vector<set<int>> &ne, vector<int> &h, vector<int> &ch, 
    vector<lli>& e, int s, int t, int N){

  deque<int> q; int u;
  for (auto &v: ne[s])
    if (v != t) q.push_back(v);
  
  while (!q.empty()){
    u=*q.begin(); q.pop_front();
    discharge(c,f,ne,h,ch,e,q,u,s,t,N);
  }
}



int main(){
 
  int N,M,s,t; lli mxf=0;
  //scanf("%d %d %d %d", &N,&M,&s,&t);
  scanf("%d %d", &N,&M); s=0; t=N-1;
  vector<vector<lli>> c(N,vector<lli>(N,0)), f(N,vector<lli>(N,0));
  vector<set<int>> ne(N);
  vector<int> h(N), ch(2*N); vector<lli> e(N);

  init_capacities(c,ne,M); 
  init_flow(c,f,ne,h,ch,e,s,N,M);
  fifo_push_relabel(c,f,ne,h,ch,e,s,t,N);

  for (auto &v: ne[s])
    mxf+=f[s][v];

  printf("%lld\n", mxf);
  return 0;
}
