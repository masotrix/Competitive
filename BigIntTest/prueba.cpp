#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <ctime>
using namespace std;

//#define KARATSUBA

// Global Declarations

const int BASE = 1000000000, BASE_DIGITS = 9;

void bigPrint( vector<int> );
vector<int> bigSum( vector<int>, vector<int> );
vector<int> bigMult( vector<int>, vector<int> );
vector<int> bigKaratsuba( vector<int> a, vector<int> b );



// Function Definitions


/**
 * Create new BigInt
 *
 * @param n     initial value
 * @return      new BigInt
 */
vector<int> bigNew( int n ){

    vector<int> c;
    c.push_back( n );

    return c;
}

/*-> bigSum <-*/
vector<int> bigSum( vector<int> a, vector<int> b ){

    vector<int> c;

    vector<int>::iterator it1 = a.begin(), it2 = b.begin();	
    int temp, carry = 0;

    while( it1 != a.end() && it2 != b.end() ){
        
        temp = *it1 + *it2 + carry;
        if( temp >= BASE ){
            carry = 1;
            temp -= BASE;        
        }
        else carry = 0;

        c.push_back( temp );

        it1++;
        it2++;
    }

    vector<int>::iterator it, limit;

    if( it1 != a.end() ){
        it = it1;
        limit = a.end();
    }
    else {
        it = it2;
        limit = b.end();
    } 

    while( it != limit ){
    
        temp = *it + carry;
        if( temp >= BASE ){
            carry = 1;
            temp -= BASE;
        }
        else carry = 0;

        c.push_back( temp );

        it++;
    }

    if( carry ) c.push_back( 1 );

    return c;
}



/*-> bigRest <-*/
vector<int> bigRest( vector<int> a, vector<int> b ){

    if( a.size() < b.size() ){
        
        cout << "ERROR: bigRest, a < b\n";
        exit(1);
    }

    vector<int> c;

    vector<int>::iterator it1 = a.begin(), it2 = b.begin();	
    int temp, carry = 0;

    while( it1 != a.end() && it2 != b.end() ){
        
        temp = *it1 - *it2 - carry;
        if( temp < 0 ){
            carry = 1;
            temp += BASE;        
        }
        else carry = 0;

        c.push_back( temp );

        it1++;
        it2++;
    }

    while( it1 != a.end() ){
    
        temp = *it1 - carry;
        
        if( temp < 0 ){
            carry = 1;
            c.push_back( temp + BASE );
        }
        else if( temp || it1+1 != a.end() ){
            carry = 0;
            c.push_back( temp );
        }

        it1++;
    }

    vector<int>::reverse_iterator itr = c.rbegin();
    while( !*itr ){
        c.pop_back();
        itr++;
    }

    return c;
}

#ifdef KARATSUBA
/*-> bigKaratsuba <-*/
vector<int> bigKaratsuba( vector<int> a, vector<int> b ){

    vector<int> c;
    vector<int> x1, x2, y1, y2;

    int i;
    vector<int>::iterator it1 = a.begin(), it2 = b.begin();
    for( i = 0; i < 9; i++ ){

        y1.push_back( *it1 );
        y2.push_back( *it2 );
        
        it1++;
        it2++;
    }
    
    vector<int>::iterator itr;

    for( itr = a.begin() + 9; itr != a.end(); itr++ )
        x1.push_back( *itr );
    for( itr = b.begin() + 9; itr != b.end(); itr++ )
        x2.push_back( *itr );
        
    vector<int> z0 = bigMult( y1, y2 ),
                z2 = bigMult( x1, x2 );

    vector<int> z1 = bigRest(
                        bigMult( bigSum( x1, y1 ), bigSum( x2, y2 ) ),
                        bigSum( z2, z0 ) );
    
    vector<int> z1b, z2b2;

    for( i = 0; i < 9; i++ )
        z1b.push_back( 0 );
    
    for( itr = z1.begin(); itr < z1.end(); itr++ )
        z1b.push_back( *itr );

    for( i = 0; i < 18; i++ )
        z2b2.push_back( 0 );

    for( itr = z2.begin(); itr < z2.end(); itr++ )
        z2b2.push_back( *itr );

    
    return bigSum( z2b2, bigSum( z1b, z0 ) );
}

#endif


/*-> bigMult <-*/
vector<int> bigMult( vector<int> a, vector<int> b ){


#ifdef KARATSUBA

    if( a.size() > 9 && b.size() > 9 )
        return bigKaratsuba( a, b );

#endif

    vector<int> c;
    vector<int>::iterator it1, it2 = b.begin();
    
    unsigned long long int temp_int;
    int carry = 0, pos = 0;

    while( it2 != b.end() ){
        
        it1 = a.begin();

        vector<int> temp_vec;
        for( int i = 0; i < pos; i++ )
            temp_vec.push_back( 0 );

        while( it1 != a.end() ){
    
            temp_int = *it1;
            temp_int *= *it2;
            temp_int += carry;

            if( temp_int >= BASE ){
                carry = temp_int / BASE;
                temp_int %= BASE;
            }
            else carry = 0;

            temp_vec.push_back( temp_int );

            it1++;
        }

        if( carry ){
            temp_vec.push_back( carry );
            carry = 0;
        }

        c = bigSum( c, temp_vec );

        it2++;
        pos++;
    }


    return c;
}



/*-> fiboAdv <-*/
vector<int> fiboAdv( vector<int> a, vector<int> b, int n ){

    vector<int> result, temp;
    int i = 0;
    n -= 2;

    while( i < n){
    
        result = bigSum( bigMult( b, b ), a );
        a = b;
        b = result;

        i++;
    }

    return result;
}



/*-> bigFactorial  <-*/
vector<int> bigFactorial( int n ){

    vector<int> result { 1 };
    
    for( int i = 2; i <= n; i++ )
        result = bigMult( result, { i } );

    return result;
}

/*-> bigRead <-*/
vector<int> bigRead( string number ){

    string::reverse_iterator it;
    vector<int> c;

    for( it = number.rbegin(); it != number.rend(); it++ )
        c.push_back( *it - '0' );
    

    return c;
}



/*-> bigPrint <-*/
void bigPrint( vector<int> c ){

    vector<int>::reverse_iterator it;
    cout << *c.rbegin();
    for( it = c.rbegin()+1; it != c.rend(); it++ ){

        if( *it ){
            int temp = *it, subB = BASE / 10;
            while( temp <  subB ){
                cout << 0;
                temp *= 10;
            }
        cout << *it;
        }
        else {
            for( int i = 0; i < BASE_DIGITS; i++ )
                cout << 0;
        }
    }

    cout << endl;
}



// Main Function

int main(){

  //const clock_t begin_time = clock();

/* fibo
  unsigned long long int ai, bi;
  int n;
  cin >> ai;
  cin >> bi;
  cin >> n;

  vector<int> a = bigRead( to_string( ai ) ), b = bigRead( to_string( bi ) );
*/  
  //bigPrint( fiboAdv( a, b, n ) );
  //fiboAdv( a, b, n );


  /* factorial */

  int n;
  cin >> n;

  bigPrint( bigFactorial( n ) );
  //bigFactorial( n );


  //cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
  
  return 0;
}

