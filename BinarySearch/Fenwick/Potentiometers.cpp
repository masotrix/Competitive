#include <bits/stdc++.h>
using namespace std;


int sum(vector<int>& v, int y) {
    int sum = 0;
    
    while (y){
        sum += v[y];
        y -= y & -y;
    } 
    return sum;
}

int range(vector<int>& v, int x, int y) {

    return sum(v, y) - (x==1? 0 : sum(v, x-1));
}

void update(vector<int>& v, int x, int val) {

    while (x <= v.size()){
        v[x] += val;
        x += x & -x;
    }
}


int main() {

    int n, x, y, c=1;
    char op;
    scanf("%d", &n);

    do {
     
        printf("Case %d:\n", c);
        vector<int> v(n+1), v1(n+1, 0);

        for (int i=1; i<=n; i++){
            scanf("%d", &y);
            update(v, i, y);
            v1[i]=y;
        }
        

        do {

            do {
                op = getchar();
            } while (op!='M' && op!='S' && op!='E');
            
            if (op == 'E'){
                op = getchar();
                op = getchar();
                break; 
            }

            else if (op == 'S'){
            
                scanf("%d %d", &x, &y);
                update(v, x, -v1[x]);
                v1[x]=y;
                update(v, x, v1[x]);
            }

            else if (op == 'M'){
            
                scanf("%d %d", &x, &y);
                printf("%d\n", range(v, x, y));
            }
        } while (true);


        scanf("%d", &n);

        if (!n) return 0;
        else puts("");
        c++;

    } while (true);

    return 0;
}
