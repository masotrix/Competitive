#include <bits/stdc++.h>
using namespace std;



void build_tree(vector<int>& tree, vector<int>& v,
    int node, int i, int j) {

    if (i == j) {

    if (v[i]>0) tree[node] = 1;
    else if (v[i]<0) tree[node] = -1;
    else tree[node] = 0;

    return;
  }
  
  build_tree(tree, v, node*2, i, (i+j)/2); 
  build_tree(tree, v, node*2+1, 1+(i+j)/2, j);
  
  tree[node] = tree[node*2] * tree[node*2+1];
}



void update(vector<int>& tree, int node,
    int index, int val, int i, int j) {

  if (index<i || index>j) return;
  if (i==j){ tree[node]=val; return; }

  update(tree, 2*node, index, val, i, (i+j)/2);
  update(tree, 2*node+1, index, val, (i+j)/2+1, j);
  tree[node]=tree[2*node]*tree[2*node+1];
}



int query_tree(vector<int>& tree, int node,
       int i, int j, int start, int end) {
  
  if (i > end || j < start) return 1;
  if (i >= start && j <= end) return tree[node];

  return  query_tree(tree, 2*node, i, (i+j)/2, start, end) *
      query_tree(tree, 2*node+1, (i+j)/2+1, j, start, end);
}


int main(){

  int n, k, in, val, node;
  char c;

  while (scanf("%d %d", &n, &k)==2){

    vector<int> v(n+1), tree(pow(2,ceil(1+log2(n))));

    for (int i=1; i<=n; i++)  
      scanf("%d", &v[i]);

    build_tree(tree, v, 1, 1, n);

    for (int i=0; i<k; i++){
      
      do {
        c = getchar();
      } while (c=='\n');

      scanf("%d %d", &in, &val);
      
      if (c=='C'){
        
        if (val>0) val=1;
        else if (val<0) val=-1;
        
        update(tree, 1, in, val, 1, n);
      }

      else if (c=='P'){
      
        switch (query_tree(tree, 1, 1, n, in, val)){
        
          case 0: printf("0"); break;
          case 1: printf("+"); break;
          case -1: printf("-");
        }
      }
    }

    puts("");
  
  }
  

  return 0;
}
