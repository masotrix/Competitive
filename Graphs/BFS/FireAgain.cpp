#include <bits/stdc++.h>
using namespace std;

const int INF=1<<30;
int cx(int n, int M){ return n/M; }
int cy(int n, int M){ return n%M; }
int n(int i, int j, int M){ return M*i+j; }

void bfs(vector<int> &ini, vector<int> &d, int N, int M){

  deque<int> q; int no1,no2,x,y;
  for (auto &i: ini) q.push_back(i);
  vector<vector<int>> neig={{1,0},{0,1},{-1,0},{0,-1}};

  while (!q.empty()){
  
    no1=q.front(); q.pop_front();

    for (auto &nei: neig){
      x=cx(no1,M)+nei[0], y=cy(no1,M)+nei[1]; 
      if (x>=0 && x<N && y>=0 && y<M){
        no2=n(x,y,M); if (d[no2]!=INF) continue;
        d[no2]=d[no1]+1;
        q.push_back(no2);
      }
    }
  }
}

int main(){
 
  int N,M,S,K,a,b,maxi=0,tmaxi=0;
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%d %d %d",&N,&M,&K); S=N*M;
  vector<int> d(S,INF),ini;

  for (int i=0; i<K; i++){
    scanf("%d %d",&a,&b);
    ini.push_back(n(a-1,b-1,M));
    d[n(a-1,b-1,M)]=0;
  }

  bfs(ini,d,N,M);
  for (int i=0; i<S; i++)
    if (d[i]>tmaxi) { tmaxi=d[i]; maxi=i; }

  printf("%d %d\n", cx(maxi,M)+1, cy(maxi,M)+1);


  return 0;
}
