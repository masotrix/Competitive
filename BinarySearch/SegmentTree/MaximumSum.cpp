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


pair<int,int> intern_node(pair<int,int> p1, pair<int,int> p2){
  
  vector<int> maxes(4);
  maxes[0] = p1.first;
  maxes[1] = p1.second;
  maxes[2] = p2.first;
  maxes[3] = p2.second;
  insertionSort(maxes, 4);

  return make_pair(maxes[0], maxes[1]);
}


void build_tree(vector<pair<int,int>>& tree, vector<int>& v,
    int node, int i, int j) {

    if (i == j) { tree[node] = make_pair(v[i], -1); return; }
  
  build_tree(tree, v, 2*node, i, (i+j)/2); 
  build_tree(tree, v, 2*node+1, (i+j)/2+1, j);
  
  tree[node] = intern_node(tree[2*node], tree[2*node+1]);
}



void update(vector<pair<int,int>>& tree, int node,
    int index, int val, int i, int j) {

  if (index<i || index>j) return;
  if (i==j){ tree[node]=make_pair(val,-1); return; }

  update(tree, 2*node, index, val, i, (i+j)/2);
  update(tree, 2*node+1, index, val, (i+j)/2+1, j);
  
  tree[node] = intern_node(tree[2*node], tree[2*node+1]);
}


pair<int,int> query_tree(vector<pair<int,int>>& tree, int node,
       int i, int j, int start, int end) {
  
  if (start>j || end<i) return make_pair(-1,-1);
  if (i >= start && j <= end) return tree[node];

  return intern_node(
      query_tree(tree, 2*node, i, (i+j)/2, start, end),
        query_tree(tree, 2*node+1, (i+j)/2+1, j, start, end));
}

int pair_sum(pair<int,int> p){ return p.first + p.second; }


int main(){

  int n, o, x, y, node;
  char c;
  scanf("%d", &n);

  vector<int> v(n+1);
     vector<pair<int,int>> tree(pow(2,ceil(1+log2(n))));

  for (int i=1; i<=n; i++)  
    scanf("%d", &v[i]);

  build_tree(tree, v, 1, 1, n);
  scanf("%d", &o);

  while (o--){

    do { c = getchar(); } while (c=='\n');
    scanf("%d %d", &x, &y);
    
    if (c=='U') update(tree, 1, x, y, 1, n);
    else printf("%d\n", pair_sum(query_tree(tree, 1, 1, n, x, y)));
  }

  
  return 0;
}
