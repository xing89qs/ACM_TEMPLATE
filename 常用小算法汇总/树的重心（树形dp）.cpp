
//建边的时候要建双向边！
#define MAXN 50010

int num[MAXN];  //以每个结点为根子树的结点数（包含自身）
int dp[MAXN];   //dp[i]表示沿树路径到第i个点时子树结点数的最大值（不含自身）
int n;

void dfs(int u, int fa)
{
    dp[u] = 0;
    num[u] = 1;
    for(int i=head[u]; ~i; i=e[i].nxt)
    {
        int v = e[i].to;
        if(v != fa)
        {
            dfs(v, u);
            num[u] += num[v];
            dp[u] = max(dp[u], num[v]);
        }
    }
    dp[u] = max(dp[u], n - num[u]);
}
