#include <bits/stdc++.h>
using namespace std;

const int max_n = 50;
bool vis[max_n][max_n];
string mp[max_n];
int n, m, i, j;

bool dfs( int i, int j, int d, char c ){
    
    if( i<0 || i>=n || j<0 || j>=m || mp[i][j] != c )    
        return false;

    if( vis[i][j] ) return true;

    vis[i][j] = true;

    return d != 1 && dfs( i+1, j, 2, c) ||
           d != 2 && dfs( i-1, j, 1, c) ||
           d != 3 && dfs( i, j+1, 4, c) ||
           d != 4 && dfs( i, j-1, 3, c);
}


int main(){
	
    cin >> n >> m;
    for( i = 0; i < n; i++ ){
        cin >> mp[i];
    }

    for( i = 0; i < n; i++ ){
        for( j = 0; j < m; j++ ){
            if( vis[i][j] ) continue;
            vis[i][j] = true;

            if( dfs( i,j+1,4,mp[i][j] ) ||
                dfs( i+1,j,2,mp[i][j] ) ){

                cout << "Yes\n";
                return 0;
            }
        }
    }

    cout << "No\n";

    return 0;
}
