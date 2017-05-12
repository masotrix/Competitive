#include <bits/stdc++.h>
using namespace std;

int area = 0;

bool verify( int x, int y, vector<vector<char>>& mp ){

    if( x >= 0 && x < mp.size() &&
        y >= 0 && y < mp[x].size() &&
        mp[x][y] == '.' )
    
       return true;

    return false;
}


void clean( int x, int y, char dir,
        vector<vector<char>>& vis,
        vector<vector<char>>& mp ){

    if( vis[x][y] == 'E' ){
        
        area++;
        vis[x][y] = dir;
    }

    else if( vis[x][y] == dir )
        return;


    if( dir == 'U' ){

        if( verify(x-1,y,mp) )
            clean( x-1, y, dir, vis, mp );
        else
            clean( x, y, 'R', vis, mp );
    }
    else if( dir == 'R' ){
    
        if( verify(x,y+1,mp) )
            clean( x, y+1, dir, vis, mp );
        else
            clean( x, y, 'D', vis, mp );
    }
    else if( dir == 'D' ){
    
        if( verify(x+1,y,mp) )
            clean( x+1, y, dir, vis, mp );
        else
            clean( x, y, 'L', vis, mp );
    }
    else if( dir == 'L' ){
    
        if( verify(x,y-1,mp) )
            clean( x, y-1, dir, vis, mp );
        else
            clean( x, y, 'U', vis, mp );
    }

}




int main( int argc, char* argv[] ){

    int n, m, x, y;
    cin >> n >> m;

    char dir, c;
    vector<vector<char>> vis(n,vector<char>(m,'E')),
        mp(n,vector<char>(m));

    for( int i = 0; i < n; i++ ){
        for( int j = 0; j < m; j++ ){
        
            do{ c = getchar(); }while( c == '\n' );
            if( c == '.' || c == '*' )
                mp[i][j] = c;
            else {
                mp[i][j] = '.';
                dir = c; x = i; y = j;
            }
        }
    }

    clean( x, y, dir, vis, mp );
    
    cout << area << endl;

    return 0;
}
