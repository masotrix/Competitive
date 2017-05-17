#include <bits/stdc++.h>
using namespace std;
#define coord pair<int,int>
#define mkc(_x,_y) make_pair(_x,_y)
#define row vector<int>
#define vis vector<bool>
#define matrix vector<row>
#define vmatrix vector<vis>
#define x(_n) _n.first
#define y(_n) _n.second

vector<coord> neighs={mkc(1,0),mkc(-1,0),mkc(0,-1),mkc(0,1)};

bool valid(matrix& m, vmatrix& v, coord& p, int H, int W){

  if (x(p)>=0 && y(p)>=0 && x(p)<H && y(p)<W && 
      m[x(p)][y(p)]=='.' && v[x(p)][y(p)]==false) return true;
  return false;
}

bool bfs(matrix& m, vmatrix& v, int H, int W, coord& pi, coord& pf){

  deque<coord> q; coord p; bool found=false;
  q.push_back(pi); v[x(pi)][y(pi)]=true;

  while (!q.empty()){

    p=q.front();
    q.pop_front();

    for_each (neighs.begin(), neighs.end(), [&](coord n){
         coord p2 = mkc(x(p)+x(n),y(p)+y(n));
         if (valid(m,v,p2,H,W)){
            v[x(p2)][y(p2)]=true;
            if (p2==pf) found=true;
            else q.push_back(p2);
         }
    });
  }

  return found;
}

bool findEntries(matrix& m, int H, int W, 
    coord& pi, coord& pf, coord& p0){

    for (int i=0; i<H; i++){
      if (m[i][0]=='.'){
        if (pi==p0) pi=mkc(i,0);
        else if (pf==p0) pf=mkc(i,0);
        else return false;
      }
    }

    for (int j=1; j<W; j++){

      if (m[0][j]=='.'){
        if (pi==p0) pi=mkc(0,j);
        else if (pf==p0) pf=mkc(0,j);
        else return false;
      }
    }

    if (W>1) {
      for (int i=1; i<H; i++){
        if (m[i][W-1]=='.'){
          if (pi==p0) pi=mkc(i,W-1);
          else if (pf==p0) pf=mkc(i,W-1);
          else return false;
        }
      }
    }

    if (H>1){
      for (int j=1; j<W-1; j++){
        if (m[H-1][j]=='.'){
          if (pi==p0) pi=mkc(H-1,j);
          else if (pf==p0) pf=mkc(H-1,j);
          else return false;
        }
      }
    }

    if (pi==p0||pf==p0) return false;
    return true;
}


int main(){

  int t,H,W; scanf("%d", &t); char c;
  matrix m; vmatrix v;

  while (t--){

    coord p0=mkc(-1,-1),pi=p0,pf=p0; 
    scanf("%d %d", &H, &W);
    m = matrix(H,row(W));
    v = vmatrix(H,vis(W,false));

    for (int i=0; i<H; i++){
      for (int j=0; j<W; j++){
        do {c=getchar();} while (c=='\n');
        m[i][j]=c;
      }
    }

    if (!findEntries(m,H,W,pi,pf,p0)){
      puts("invalid"); continue; }

    if (bfs(m,v,H,W,pi,pf)) puts("valid");
    else puts("invalid");
  }

  return 0;
} 
