LL dp[MAXN][MAXN];
int s[MAXN][MAXN];
int a[MAXN];
LL sum[MAXN];

int main(void){
    int n;
    while(scanf("%d",&n)!=EOF){
        for(int i = 1;i<=n;i++){
            scanf("%d",&a[i]);
            a[i+n] = a[i];
        }
        n<<=1;
        for(int i = 1;i<=n;i++) sum[i] = sum[i-1]+a[i];
        for(int i = 1;i<=n;i++){
            dp[i][i] = 0;
            s[i][i] = i;
        }
        for(int len = 1;len<n;len++){
            for(int i = 1;i+len<=n;i++){
                int j = i+len;
                dp[i][j] = LINF;
                for(int k = s[i][j-1];k<=s[i+1][j];k++){
                    LL ret = dp[i][k-1]+dp[k][j]+(sum[j]-sum[i-1]);
                    if(ret<dp[i][j]){
                        s[i][j] = k;
                        dp[i][j] = ret;
                    }
                }
            }
        }
        printf("%lld\n",dp[1][n]);
    }
    return 0;
}

