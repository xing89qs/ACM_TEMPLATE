
int a[MAXN];
int dp[MAXN];

void LIS()
{
    fill(dp,dp+n,INF);
    for(int i=0; i<n; i++)
        *lower_bound(dp,dp+n,a[i]) = a[i];
    printf("%d\n",lower_bound(dp,dp+n,INF)-dp);
}
