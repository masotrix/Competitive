#include <bits/stdc++.h>
using namespace std;


int bfs( vector<vector<char>>& mp, int x, int y,
         vector<vector<int>>& dist, int n, int m ){

    int sum = 0, dAnte, l = -2;
    deque<pair<pair<int,int>,int>> d;
    d.push_back( make_pair(make_pair(x,y),-1) );

    while( !d.empty() ){
    
        x = d.front().first.first;
        y = d.front().first.second;
        dAnte = d.front().second;
        d.pop_front();

        if( dAnte == l ) break;

        if( x<0 || x>=n || y<0 || y>=m ||
            mp[x][y]=='T' || dist[x][y] != -1 )
            continue;

        dist[x][y] = dAnte+1;

        if( mp[x][y] >= '0' && mp[x][y] <= '9' )
            sum += mp[x][y]-'0';

        else if( mp[x][y] == 'S' )
            l = dist[x][y];

        d.push_back( make_pair(make_pair(x-1,y),dist[x][y]) );
        d.push_back( make_pair(make_pair(x+1,y),dist[x][y]) );
        d.push_back( make_pair(make_pair(x,y-1),dist[x][y]) );
        d.push_back( make_pair(make_pair(x,y+1),dist[x][y]) );

    }
    
    return sum;
}



int main(){
    
    int n, m, x, y;
    cin >> n >> m;
    vector<vector<char>> mp(n,vector<char>(m));
    vector<vector<int>> dist(n,vector<int>(m,-1));
    char c;

    for( int i = 0; i < n; i++ ){
        for( int j = 0; j < m; j++ ){
            
            do { c = getchar(); 
            } while( c == '\n' );
            
            mp[i][j] = c;
            
            if( c == 'E' ){
                x = i;
                y = j;
            }
        }
    }

    printf( "%d\n", bfs(mp,x,y,dist,n,m) );

    return 0;
}
