#include <bits/stdc++.h>
using namespace std;



int main() {

  int n, C, t1, t2, temp, mini, count1, count2;

  while (scanf("%d %d %d %d", &n, &C, &t1, &t2)==4) {

    vector<int> h(n), dp(n+1);

    for (int i=0; i<n; i++)
      scanf("%d", &h[i]);
    
    mini = C;
    sort(h.begin(), h.end());

    for (int i=0; i<n; i++) {  
    
      for (int j=1; j<=n; j++)
        dp[j] = C;
      dp[0]=0;
      count1=count2=1;

      for (int j=0; j<n; j++){
        while (count1<n && h[count1]-h[j]<=t1) count1++;
        while (count2<n && h[count2]-h[j]<=t2) count2++;
        dp[count1]=min(dp[count1],dp[j]+t1);
        dp[count2]=min(dp[count2],dp[j]+t2);
      }
      
      temp = h[n-1];
      for (int j=n-1; j>0; j--)
        h[j]=h[j-1]+C;
      h[0] = temp;

      mini = min(mini, dp[n]);
    }

    printf("%d\n", mini);
  }

  return 0;
}
