
//建边的时候要建双向边!

/*方法一：两次dfs*/

#define MAXN 50010

int d[MAXN];    //d[i]表示以某个结点为根，结点i的深度
int rt; //第一次dfs后找到的距离临时根结点（1号结点）最远的结点编号，即树的直径的一个端点

void dfs(int u, int fa)
{
    for(int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].to;
        int w = e[i].cost;
        if(v != fa)
        {
            d[v] = d[u] + w;
            if(d[v] > d[rt])    //更新距离临时根结点（1号结点）最远的结点编号
                rt = v;
            dfs(v, u);
        }
    }
}

void solve()    //dfs求树的直径
{
    /*建图等部分代码省略*/
    memset(d, 0, sizeof(d));
    dfs(1, 0);  //从临时根节点开始遍历找到最远端的结点即为树的直径的一个端点
    memset(d, 0, sizeof(d));
    dfs(rt, 0); //从该端点开始遍历找到树的直径的另一个端点
    printf("%d\n", d[rt]);
}


/*方法二：树形dp*/

#define MAXN 50010

//模板一
int dp[MAXN];   //dp[i]表示从节点i出发，往以i为根的子树遍历能够到达的最远距离
int ans;

void dfs(int u, int fa)
{
    for(int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].to;
        int w = e[i].cost;
        if(v != fa)
        {
            dfs(v, u);
            ans = max(ans, dp[u] + dp[v] + w);  //先用dp[u]更新ans
            dp[u] = max(dp[u], dp[v] + w);  //再用dp[v]更新dp[u]，顺序不能改变
        }
    }
}


//模板二

int dp[MAXN][2];    //dp[i][0/1]表示以i点为树根（从i点出发）能到最远儿子的距离和到次远儿子的距离

void dfs(int u, int fa)
{
    dp[u][0] = dp[u][1] = 0;
    for(int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].to;
        int w = e[i].cost;
        if(v != fa)
        {
            dfs(v, u);
            if(dp[u][0] < dp[v][0] + w) //更新到最远儿子的距离
            {
                dp[u][1] = dp[u][0];    //到最远儿子的距离更新为到次远儿子的距离
                dp[u][0] = dp[v][0] + w;
            }
            else if(dp[u][1] < dp[v][0] + w)    //到最远儿子的距离不需要更新，只需要更新到次远儿子的距离
                dp[u][1] = dp[v][0] + w;
        }
    }
    //到最远儿子的距离 + 到次远儿子的距离 = 树的直径
    ans = max(ans, dp[u][0] + dp[u][1]);    //更新最大值
}
