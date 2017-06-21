#include <bits/stdc++.h>
using namespace std;
#define lli long long int

const lli INF=1LL<<60;
void init_capacities(vector<vector<lli>> &c,vector<set<int>> &ne,
    vector<lli> &p, int N, int M, int G, int t){
  
  int k=1,a,b, ma=N*(N-1)/2, given=0, tnode; char r;
  vector<int> t1(ma+1), t2(ma+1);
  vector<vector<int>> m(N,vector<int>(N)); 

  for (int i=0; i<N-1; i++){
    for (int j=i+1; j<N; j++){
      t1[k]=i+ma+1; t2[k]=j+ma+1;
      m[i][j]=k; m[j][i]=k++;
    }
  }

  for (int u=1; u<=ma; u++){
    c[0][u]=2*M; ne[u].insert(0); ne[0].insert(u);
    c[u][t1[u]]=2*M; c[u][t2[u]]=2*M;
    ne[u].insert(t1[u]); ne[u].insert(t2[u]);
    ne[t1[u]].insert(u); ne[t2[u]].insert(u);
  }

  for (int i=0; i<G; i++){
    scanf("%d %c %d", &a,&r,&b);

    if (r=='='){ p[a]++; p[b]++; }
    else if (r=='>') p[a]+=2;
    else p[b]+=2;
    c[0][m[a][b]]-=2;

    if (a==0 && r=='<' || b==0 && r=='>')
      given+=2;
    if ((a==0 || b==0) && r=='=')
      given++;
  }
  p[0]=2*M*(N-1)-given;

  for (int i=1; i<N; i++)
    c[0][m[0][i]]=0;

  for (int team=1; team<N; team++){
    tnode=team+ma+1;
    c[tnode][t]=max((int)(p[0]-1-p[team]),0);
    ne[tnode].insert(t);
    ne[t].insert(tnode);
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
 
  int N,M,G,s,t,ma,pt,pi,px; lli mxf;
  scanf("%d %d %d", &N,&M,&G); s=0;
 
  while (N){

    ma=N*(N-1)/2; t=ma+N+1;
    vector<vector<lli>> c(t+1,vector<lli>(t+1,0)),
      f(t+1,vector<lli>(t+1,0));
    vector<set<int>> ne(t+1);
    vector<int> h(t+1), ch(2*(t+1));
    vector<lli> e(t+1), p(N,0);

    init_capacities(c,ne,p,N,M,G,t); 
    pi=0; px=0;
    for (int i=1; i<N; i++){
      px=max((int)px,(int)p[i]);
      pi+=p[i];
    }
    if (px>=p[0]) puts("N"); 
    else {

      pi+=p[0];

      init_flow(c,f,ne,h,ch,e,s,N,M);
      fifo_push_relabel(c,f,ne,h,ch,e,s,t,N);
      mxf=0;
      for (auto &v: ne[s])
        mxf+=f[s][v];


      pt = M*N*(N-1);
      if (mxf+pi==pt) puts("Y");
      else puts("N");
    }

    scanf("%d %d %d", &N,&M,&G);
  }
  return 0;
}
