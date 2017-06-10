#include <bits/stdc++.h>
using namespace std;

void dijkstra(map<char,map<char,int>>& E, map<char,int>& d, char ini){

  priority_queue<tuple<int,char>,vector<tuple<int,char>>,
    greater<tuple<int,char>>> q; 

  q.push(make_tuple(0,ini));
  int t,w; char no1,no2;

  while (!q.empty()){
    
    tie(t,no1)=q.top(); q.pop();
    if (d.find(no1)==d.end()) d[no1]=t;
    else continue;

    for (auto ne: E[no1]){ tie(no2,w)=ne;
      q.push(make_tuple(t+w,no2));}
  }
}


int main(){
 
  int E, mini, t;
  char ini1,ini2, a,b,m,w, no;
  map<char,map<char,int>> EY, EM;
  map<char,int> dy, dm;
  scanf("%d", &E);

  while (E){

    EY=map<char,map<char,int>>(); EM=map<char,map<char,int>>();
    dy=map<char,int>(); dm=map<char,int>();

    for (int i=0; i<E; i++){
      scanf("\n%c %c %c %c %d",&m,&w,&a,&b,&t);
      if (m=='Y'){
        EY[a][b]=t;
        if (w=='B') EY[b][a]=t;
      } else {
        EM[a][b]=t;
        if (w=='B') EM[b][a]=t;
      }
    }
    scanf("\n%c %c",&ini1,&ini2);
    dijkstra(EY,dy,ini1);
    dijkstra(EM,dm,ini2);
    
    mini=-1;
    for (auto ne: dy){
      if (dm.find(ne.first)!=dm.end()){ 
        if (mini==-1 || mini > ne.second+dm[ne.first]) 
          mini = ne.second+dm[ne.first];
      }
    }

    if (mini==-1) puts("You will never meet.");
    else {

      vector<char> places;
      for (auto ne: dy){
        if (dm.find(ne.first)!=dm.end() &&
            ne.second+dm[ne.first] == mini){
          places.push_back(ne.first);
        }
      }

      printf("%d", mini);
      for (auto c: places)
        printf(" %c", c);
      puts("");
    }


    scanf("%d", &E);
  }
  return 0;
}
