#include <bits/stdc++.h>
using namespace std;

const int max_n = 500;
deque<pair<int,int>> d;
pair<int,int> q;
string mp[max_n];
int n, m, i, j, val, x, y;
bool ready, b1, b2, b3, b4;

bool filled( int i, int j ){
    if( i < 0 || i >= n ||
        j < 0 || j >= m ||
        mp[i][j] == 'X' ||
        mp[i][j] == '#' ||
        mp[i][j] == ' ')

        return true;
    return false;
}


bool dfs( int i, int j ){
    
    if( !val ) return false;

    if( filled(i,j) ) return true;

    mp[i][j] = ' ';
    b1 = dfs( i-1, j );
    b2 = dfs( i+1, j );
    b3 = dfs( i, j-1 );
    b4 = dfs( i, j+1 );

    if( val && b1 && b2 && b3 && b4){
        mp[i][j] = 'X';
        val--;
        return true;
    }
    mp[i][j] = '.';
    return false;

}



int main(){

    scanf( "%d %d %d", &n, &m, &val );

    for( i = 0; i < n; i++ ){
        cin >> mp[i];
    }

    for( i = 0; i < n; i++ ){
        for( j = 0; j < m; j++ ){
            if( mp[i][j] == '.' ){
                x = i; y = j;
                ready = true;
                break;
            } 
        }
        if( ready ) break;
    }

    dfs( x, y );

    for( i = 0; i < n; i++ ){
        cout << mp[i] << endl;
    }

    return 0;
}
