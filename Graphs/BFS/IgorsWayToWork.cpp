#include <bits/stdc++.h>
using namespace std;
#define row vector<char>
#define bvis vector<bool>
#define mvis() make_pair(bvis(4,false),3)
#define vis pair<bvis,int>
#define rvis vector<vis>
#define matrix vector<row>
#define vmatrix vector<rvis>
#define coord pair<int,int>
#define node tuple<coord,int,coord,int>
#define mkc(_x,_y) make_pair(_x,_y)
#define mkN(_c,_i,_p,_d) make_tuple(_c,_i,_p,_d)
#define mkn(_x,_y,_d) mkN(mkc(_x,_y),0,mkc(_x,_y),_d)
#define x(_n) get<0>(_n).first
#define y(_n) get<0>(_n).second
#define i(_n) get<1>(_n)
#define c(_n) get<0>(_n)
#define d(_n) get<3>(_n)
#define pc(_n) get<2>(_n)
#define px(_n) get<2>(_n).first
#define py(_n) get<2>(_n).second
#define dir(_v,_p) v[x(_p)][y(_p)].first
#define ite(_v,_p) v[x(_p)][y(_p)].second


vector<node> neighs={mkn(1,0,0),mkn(-1,0,1),mkn(0,-1,2),mkn(0,1,3)};

bool valid(matrix& m, vmatrix& v, node& p, int H, int W){

  if (x(p)>=0 && y(p)>=0 && x(p)<H && y(p)<W &&  
      i(p)<3 && (!dir(v,p)[d(p)] || ite(v,p)>i(p)) &&
      (m[x(p)][y(p)]=='.' || m[x(p)][y(p)]=='T'))
    return true;
  return false;
}

bool bfs(matrix& m, vmatrix& v, int H, int W, node& pi, node& pf){

  deque<node> q; node p; bool found=false; q.push_back(pi); 
  for(int d=0; d<4; d++) dir(v,pi)[d]=true; ite(v,pi)=0;

  while (!q.empty()){
    
    p=q.front();
    q.pop_front();

    for_each (neighs.begin(), neighs.end(), [&](node n){
         
        node ncs = mkn(x(p)+x(n), y(p)+y(n), 0);
        int g = (x(ncs)==px(p)||y(ncs)==py(p))? i(p):i(p)+1;
        node p2 = mkN(c(ncs), g, c(p), d(n));

        if (valid(m,v,p2,H,W)){
          dir(v,p2)[d(p2)]=true; ite(v,p2)=i(p2);
          if (c(p2)==c(pf)) found=true;
          else q.push_back(p2);
        }
    });
  }

  return found;
}

void findEntries(matrix& m, int H, int W, 
    node& pi, node& pf){
    
  for (int i=0; i<H; i++){
    for (int j=0; j<W; j++){
      if (m[i][j]=='S') pi=mkn(i,j,0);
      else if (m[i][j]=='T') pf=mkn(i,j,0);
    }
  }
}


int main(){
 
  int H,W; char c;
  matrix m; vmatrix v;
  
  node pi,pf; 
  scanf("%d %d", &H, &W);
  m = matrix(H,row(W));
  v = vmatrix(H,rvis(W,mvis()));

  for (int i=0; i<H; i++){
    for (int j=0; j<W; j++){
      do {c=getchar();} while (c=='\n');
      m[i][j]=c;
    }
  }

  findEntries(m,H,W,pi,pf);

  if (bfs(m,v,H,W,pi,pf)) puts("YES");
  else puts("NO");

  return 0;
}
