#include <bits/stdc++.h>
using namespace std;


vector<int> cycle;


int findCycle( int node, int last,
        vector<vector<int>>& neighbors,
        vector<bool>& vis, vector<bool>& in_cycle ){


    vis[node] = true;
    int end_node;

    for( int i = 0; i < neighbors[node].size(); i++ ){
    
        if( neighbors[node][i] != last ){

            if( vis[neighbors[node][i]] )
                end_node = neighbors[node][i];

            else
                end_node = findCycle( neighbors[node][i],
                    node, neighbors, vis, in_cycle );
            
            if( end_node != -1 ){

                cycle.push_back( node );
                in_cycle[node] = true;
                
                if( node != end_node ) return end_node;
                else return -1;
            }
        }
    }

    return -1;
}


void distance( int node, int last, int d,
        vector<vector<int>>& neighbors,
        vector<int>& distances ){

    distances[node] = d+1;
    for( int i = 0; i < neighbors[node].size(); i++ ){
    
        if( neighbors[node][i] != last ){
        
            distance( neighbors[node][i], node, d+1,
                    neighbors, distances );
        }
    }
}


int main( int argc, char* argv[] ){

    int n, x, y;
    cin >> n;

    vector<int> distances(n,0);
    vector<bool> vis(n,false), in_cycle(n,false);
    vector<vector<int>> neighbors(n);
    

    for( int i = 0; i < n; i++ ){
        scanf( "%d %d", &x, &y );
        neighbors[x-1].push_back(y-1);
        neighbors[y-1].push_back(x-1);
    }


    findCycle( 0, -1, neighbors, vis, in_cycle );


    for( int i = 0; i < cycle.size(); i++ ){
        for( int j = 0; j < neighbors[cycle[i]].size(); j++ ){
            if( !in_cycle[neighbors[cycle[i]][j]] ){

                distance( neighbors[cycle[i]][j], cycle[i], 0,
                        neighbors, distances );
            }
        }
    }


    for( int i = 0; i < n; i++ )
        printf( "%d ", distances[i] );

    cout << endl;
    return 0;
}
    
