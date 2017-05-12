#include <bits/stdc++.h>
using namespace std;

int a, b, c, n;

bool dfs( int nodo, int ante,
        vector<vector<bool>>& mp, vector<bool>& vis ){
   
    vis[nodo] = true;                   // visited
    for( int i = 0; i < n; i++ ){

        if( mp[nodo][i] ){                      // if path
            if( ante != -1 && mp[i][ante] ){    // if ante and this to ante
                a = ante; b = nodo; c = i;      // save and go
                return true;
            }

            if( !vis[i] && dfs( i, nodo, mp, vis ) ){  // if this free, do
                return true;
            }
        }
    }

    return false;
}

int main( int argc, char* argv[] ){
    
    int i, j;
    char ch;

    cin >> n;
    vector<vector<bool>> mp(n,vector<bool>(n));
    vector<bool> vis(n,false);

    for( i = 0; i < n; i++ ){       // for everyone, take
        for( j = 0; j < n; j++ ){
            
            do{ ch = getchar();
            } while( ch != '0' && ch != '1' );

            mp[i][j] = ch-'0';
        }
    }

    for( i = 0; i < n; i++ ){                       // for node
        if( !vis[i] && dfs( i, -1, mp, vis ) ){    // if not vis
            printf( "%d %d %d\n", a+1, b+1, c+1 );
            return 0;
        }
    }

    puts("-1");
    
    return 0;
}
