#define MAXN 105
#define MAXM 100005

int w[MAXN],cnt[MAXN];
int dp[MAXM];
int n,m;

void ZeroOnePack(int value,int weight)  //01背包
{
    for(int i=m; i>=weight; i--)
    {
        dp[i]=max(dp[i],dp[i-weight]+value);
    }
}

void CompletePack(int value,int weight) //完全背包
{
    for(int i=weight; i<=m; i++)
    {
        dp[i]=max(dp[i],dp[i-weight]+value);
    }
}

void MultiPack(int value,int weight,int cnt)
{
    if(weight*cnt>=m)  //转化为完全背包
        CompletePack(value,weight);
    else    //转化为01背包
    {
        int k=1;
        while(k<=cnt) //二进制优化
        {
            ZeroOnePack(value*k,weight*k);
            cnt-=k;
            k*=2;
        }
        for(int i=m; i>=cnt*weight; i--)
            dp[i]=max(dp[i],dp[i-cnt*weight]+cnt*value);
    }
}