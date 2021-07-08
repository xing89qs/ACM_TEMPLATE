
//建边的时候要建双向边！
#define MAXN 50010

int sz[MAXN];  //以每个结点为根子树的结点数（包含自身）
int dp[MAXN];   //dp[i]表示沿树路径到第i个点时子树结点数的最大值（不含自身）
int nodecnt;    //当前子树中所有结点数
int rt; //求得当前子树的重心

void dfs(int u, int fa)
{
    dp[u] = 0, sz[u] = 1;
    for(int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].to;
        if(v != fa)
        {
            dfs(v, u);
            sz[u] += sz[v];
            dp[u] = max(dp[u], sz[v]);
        }
    }
    dp[u] = max(dp[u], nodecnt - sz[u]);      //树的重心的定义：以该点为根的有根树，最大子树的结点数最小
    if(dp[u] < dp[rt])
        rt = u;
}
