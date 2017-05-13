#include <bits/stdc++.h>
using namespace std;


void dfs( vector<pair<int,int>>& v,
          vector<bool>& vis, int i, int n ){
    
    if( vis[i] ) return;
    vis[i] = true;
    
    for( int j = 0; j < n; j++ )

        if( v[i].first == v[j].first ||
            v[i].second == v[j].second )
            
            dfs( v, vis, j, n );
}



int main(){
    
    int n, x, y, comp = 0;
    cin >> n;
    vector<pair<int,int>> v(n);
    vector<bool> vis(n,false);

    for( int i = 0; i < n; i++ ){
        scanf( "%d %d", &x, &y );
        v[i] = make_pair(x,y);
    }

    for( int i = 0; i < n; i++ ){
        if( !vis[i] ){
            dfs( v, vis, i, n );
            comp++;
        }
    }

    cout << comp-1 << endl;

    return 0;
}
