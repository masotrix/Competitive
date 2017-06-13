#include <bits/stdc++.h>
using namespace std;

int main(){
 
  vector<vector<int>> v;
  vector<set<int>> E;
  vector<string> m; string s;
  int t,maxi,p; 
  ios::sync_with_stdio(false);
  cin >> t;

  while (t--){
  
    m = vector<string>();
    cin >> s; m.push_back(s);

    for (int i=1; i<m[0].size(); i++){
      cin >> s; m.push_back(s);
    }

    E = vector<set<int>>(m.size());
    for (int i=0; i<m.size(); i++)
      for (int j=0; j<m.size(); j++)
        if (m[i][j]=='Y') E[i].insert(j);
  
    for (int k=0; k<m.size(); k++){
      for (int i=0; i<m.size(); i++){
        for (int j=0; j<m.size(); j++){
          if (i!=j && m[i][j]=='N' && m[i][k]=='Y' && m[k][j]=='Y')
            m[i][j]='P';
        }
      }
    }

    v = vector<vector<int>>(m.size());
    for (int i=0; i<m.size(); i++)
      for (int j=0; j<m.size(); j++)
        if (m[i][j]=='P')
          v[i].push_back(j);
      
    maxi=0; p=0;
    for (int i=0; i<v.size(); i++){
      if (v[i].size()>maxi){ maxi=v[i].size(); p=i; }
    }

    cout << p << ' ' << maxi << endl;
  }

  return 0;
}
