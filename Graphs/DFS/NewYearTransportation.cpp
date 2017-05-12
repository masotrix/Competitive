#include <bits/stdc++.h>
using namespace std;

const int max_n = 3 * pow(10,4);
int a[max_n], i, x, t, n;

int main(){

    cin >> n >> t;
    n--;
    t--;

    for( i = 0; i < n; i++ ){
        scanf( "%d", &a[i] );
    }


    x = 0;
    while( x < t ){
        x += a[x];
    }


    if( x == t )
        cout << "YES\n";
    else
        cout << "NO\n";


    return 0;
}
