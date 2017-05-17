#include <bits/stdc++.h>
using namespace std;


void insertion_sort(vector<pair<int,int>>& v){
  
  int i, j;
  pair<int,int> tmp;

   for (i=1; i<v.size(); i++){

      j=i;
       tmp=v[i];

       while (j>0 && tmp.second>v[j-1].second){
           v[j]=v[j-1];
           j--;
       }
      v[j] = tmp;
  }
}



vector<pair<int,int>> intern_node(
    vector<pair<int,int>> v1,
       vector<pair<int,int>> v2){

  vector<pair<int,int>> v3, v4;
  
  for (int i=0; i<v1.size(); i++)
    v3.push_back(v1[i]);

  for (int i=0; i<v2.size(); i++)
    v3.push_back(v2[i]);

  for (int i=0; i<v3.size()-1; i++){
  
    if (v3[i].first==v3[i+1].first){
      v4.push_back(make_pair(v3[i].first,
            v3[i].second +
            v3[i+1].second));
      i++;
    }
    else v4.push_back(v3[i]);
  }

  if (v4[v4.size()-1].first!=v3[v3.size()-1].first)
    v4.push_back(v3[v3.size()-1]);

  if (v4.size() > 3){
    
    vector<pair<int,int>> v5, v6(3);
    for (int i=1; i<v4.size()-1; i++)
      v5.push_back(v4[i]);
    insertion_sort(v5);

    v6[0]=v4[0];
    v6[2]=v4[v4.size()-1];
    v6[1]=v5[0];

    return v6;
  }
  return v4;
}



void build_tree(vector<vector<pair<int,int>>>& tree,
    vector<int>& v, int node, int i, int j) {

    if (i == j) {
    tree[node].push_back(make_pair(v[i],1));
    return; 
  }

  build_tree(tree, v, 2*node, i, (i+j)/2); 
  build_tree(tree, v, 2*node+1, (i+j)/2+1, j);
  
  tree[node] = intern_node(tree[2*node], tree[2*node+1]);
}



void update(vector<vector<pair<int,int>>>& tree, int node,
    int index, int val, int i, int j){

  if (index<i || index>j) return;
  if (i==j){ 
    tree[node][0] = make_pair(val,1);
  }

  update(tree, 2*node, index, val, i, (i+j)/2);
  update(tree, 2*node+1, index, val, (i+j)/2+1, j);
  
  tree[node] = intern_node(tree[2*node], tree[2*node+1]);
}



vector<pair<int,int>> query_tree(
    vector<vector<pair<int,int>>>& tree,
       int node, int i, int j, int start, int end){
  
  if (start>j || end<i)
       return vector<pair<int,int>>(1,make_pair(0,0));

  if (i >= start && j <= end) return tree[node];

  return intern_node(
      query_tree(tree, 2*node, i, (i+j)/2, start, end),
        query_tree(tree, 2*node+1, (i+j)/2+1, j, start, end));
}



int tree_max(vector<pair<int,int>>& v){
  
  int maxi=0;

  for (int i=0; i<v.size(); i++)
    maxi=max(maxi, v[i].second);
  
  return maxi;
}



int main(){

  int n, o, x, y, node;

  while (scanf("%d %d", &n, &o)==2){

    vector<int> v(n+1);
    vector<vector<pair<int,int>>> tree(
        pow(2,ceil(1+log2(n))), vector<pair<int,int>>(0));

    for (int i=1; i<=n; i++)  
      scanf("%d", &v[i]);

    build_tree(tree, v, 1, 1, n);

    while (o--){

      scanf("%d %d", &x, &y);
      vector<pair<int,int>> q = query_tree(tree, 1, 1, n, x, y);
      printf("%d\n", tree_max(q));
    }
  }

  
  return 0;
}
