#include <bits/stdc++.h>
using namespace std;


void insertionSort(vector<int>& v, int n){
	
	int i, j, tmp;
 	for (i=1; i<n; i++){

    	j=i;
     	tmp=v[i];

     	while (j>0 && tmp>v[j-1]){
           v[j]=v[j-1];
           j--;
     	}
    	v[j] = tmp;
	}
}


void time(clock_t begin){
    clock_t now = clock();
	cout <<"Time: "<<(double(now-begin) / CLOCKS_PER_SEC) << endl;
}


bool inc(vector<int>& v){
    
    for (int i=1; i<v.size(); i++){
    
        if (v[i] < v[i-1]){ 

            for (int j=0; j<i; j++)

                if (v[j] > v[i]){ // Increment here

                    swap(v[j], v[i]);
                    insertionSort(v, i);
                    //v.sort()
                    
                    return true;
                }
        }
    }

    return false;
}


int main(){

    int t, k, sum, n=10;
    bool b;
    cin >> t;

    while (t--){

        b = false;
        vector<int> v(n);
        for (int i=0; i<n; i++)
            scanf("%d", &v[i]);

        vector<int> vi(n);
        cin >> k;

        for (int i=0; i<n; i++)
            vi[i] = n-i-1;

        

        clock_t begin = clock();

        do { // Main Cycle 
        
            sum=0;
            for (int i=n-1; i>=0; i--)
                sum+=vi[i]*v[n-i-1];
            
            if (sum <= k){

                for (int i=n-1; i>=0; i--)
                    printf("%d ", vi[i]);
                puts("");
        
                b = true;
              
                time(begin);
                break;
            } 
        
        } while (inc(vi));

        if(!b) puts("-1");

        time(begin);
    
    }

	return 0;
}
