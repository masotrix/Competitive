#include <bits/stdc++.h>
using namespace std;
#define coord pair<int,int>
#define node pair<coord,int>
#define mkc(_x,_y) make_pair(_x,_y)
#define mkn(_x,_y,_i) mkc(mkc(_x,_y),_i)
#define x(_n) _n.first.first
#define y(_n) _n.first.second
#define i(_n) _n.second
#define c(_n) _n.first

vector<node> neighs =
  {mkn(2,1,0),mkn(1,2,0),mkn(-2,1,0),mkn(2,-1,0),
   mkn(-1,2,0),mkn(1,-2,0),mkn(-1,-2,0),mkn(-2,-1,0)};

bool valid(node p){

  if (x(p)>=0 && y(p)>=0 && x(p)<8 && y(p)<8)
    return true;
  return false;
}

int bfs(int i1,int j1,int i2,int j2){

  deque<node> q; int mov=-1;
  q.push_back(mkn(i1,j1,0));
  node p, pf=mkn(i2,j2,0); 

  while (true){
    
    p=q.front();
    q.pop_front();

    for_each (neighs.begin(), neighs.end(), [&](node n){
         node p2 = mkn(x(p)+x(n),y(p)+y(n),i(p)+1);
         if (valid(p2)){
            if (c(p2)==c(pf)) { mov=i(p2); return; }
            else q.push_back(p2);
         }
    });

    if (mov!=-1) return mov;
  }
}


int main(){
 
  int t; scanf("%d", &t);
  string ini, fin;
  int i1,j1,i2,j2;

  while (t--){
    cin >> ini >> fin;
    if (ini == fin) {puts("0"); continue;}
    i1=ini[0]-'a'; j1=ini[1]-'1';
    i2=fin[0]-'a'; j2=fin[1]-'1';
    printf("%d\n", bfs(i1,j1,i2,j2));
  }

  return 0;
}
