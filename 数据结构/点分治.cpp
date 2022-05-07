/* 我的模板 */

class NodeDiv
{
public:
#define MAXN 10005

    int head[MAXN];
    struct Edge
    {
        int to, cost, nxt;
        Edge() {}
        Edge(int to, int cost, int nxt) : to(to), cost(cost), nxt(nxt) {}
    } e[MAXN << 1];

    int sz[MAXN];   //以每个结点为根子树的结点数（包含自身）
    int dp[MAXN];   //dp[i]表示沿树路径到第i个点时子树结点数的最大值（不含自身）
    int dis[MAXN];  //存储各个点到重心的距离（单纯存储距离值，不对应结点）
    bool vis[MAXN];
    int cnt, tot;
    int nodecnt;    //当前子树中所有结点数
    int rt; //求得当前子树的重心
    int ans;
    int n, k;

    void init(int n, int m)
    {
        this -> n = n;
        this -> m = m;
        cnt = rt = 0;
        memset(head, -1, sizeof(head));
        memset(vis, false, sizeof(vis));
    }

    inline void addEdge(int u, int v, int w)
    {
        e[cnt].to = v;
        e[cnt].cost = w;
        e[cnt].nxt = head[u];
        head[u] = cnt++;
    }

    void dfs(int u, int fa) //树形dp求树的重心
    {
        dp[u] = 0, sz[u] = 1;
        for(int i = head[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].to;
            if(v != fa && !vis[v])
            {
                dfs(v, u);
                sz[u] += sz[v];
                dp[u] = max(dp[u], sz[v]);
            }
        }
        dp[u] = max(dp[u], nodecnt - sz[u]);    //树的重心的定义：以该点为根的有根树，最大子树的结点数最小
        if(dp[u] < dp[rt])
            rt = u;
    }

    void getDis(int u, int fa, int d)
    {
        dis[++tot] = d;
        for(int i = head[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].to, w = e[i].cost;
            if(v != fa && !vis[v] && d + w <= k)
                getDis(v, u, d + w);
        }
    }

    int cal(int u, int d)
    {
        tot = 0;
        int sum = 0;
        getDis(u, 0, d);
        sort(dis + 1, dis + 1 + tot);
        int l = 1, r = tot;
        while(l < r)
        {
            /* 计算符合条件的路径数 */
        }
        return sum;
    }

    void solve(int u)
    {
        vis[u] = true;
        ans += cal(u, 0);
        for(int i = head[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].to;
            if(!vis[v])
            {
                ans -= cal(v, e[i].cost);
                rt = 0;
                nodecnt = sz[v];
                dfs(v, 0);  //dfs(v, u) 也可
                solve(rt);
            }
        }
    }

    void main() //调用方法
    {
        memset(vis, false, sizeof(vis));
        dp[0] = INF;
        nodecnt = n;
        ans = rt = 0;
        dfs(1, 0);
        solve(rt);
    }
} nodediv;


/* 发神的模板 */

class NodeDiv
{
public:
#define MAXN 10005
#define MAXE 20005
    int n, k;
    int head[MAXN], nxt[MAXE], dis[MAXN], ret[MAXN];
    struct Edge
    {
        int v, w;
        Edge() {}
        Edge(int v, int w) : v(v), w(w) {}
    } e[MAXE];
    int cnt;
    int sz[MAXN], mx[MAXN], fa[MAXN];
    bool vis[MAXN];

    void init(int n)
    {
        cnt = 0;
        for(int i = 0; i <= n; i++)
        {
            head[i] = -1;
            vis[i] = 0;
        }
    }

    inline void addEdge(int u, int v, int w)
    {
        e[cnt] = Edge(v, w);
        int tmp = head[u];
        head[u] = cnt;
        nxt[cnt++] = tmp;
    }

    int mxDis;

    void getRoot(int u, int _fa, int& root, int n)
    {
        sz[u] = 1;
        mx[u] = 0;
        fa[u] = _fa;
        for(int i = head[u]; ~i; i = nxt[i])
        {
            int v = e[i].v;
            if(v == _fa || vis[v])
                continue;
            getRoot(v, u, root, n);
            sz[u] += sz[v];
            mx[u] = max(mx[u], sz[v]);
        }
        mx[u] = max(mx[u], n - sz[u]);
        if(mx[u] < mxDis)
        {
            root = u;
            mxDis = mx[u];
        }
    }

    void getDis(int u, int fa, int d, int& cnt)
    {
        dis[cnt++] = d;
        for(int i = head[u]; ~i; i = next[i])
        {
            Edge& ed = e[i];
            if(ed.v == fa || vis[ed.v])
                continue;
            getDis(ed.v, u, d + ed.w, cnt);
        }
    }

    int solve(int u, int fa, int d)
    {
        int cnt = 0;
        getDis(u, -1, d, cnt);
        sort(dis, dis + cnt);
        int l = 0, r = cnt - 1, ret = 0;
        while(l < r)
        {
            if(dis[l] + dis[r] <= k)
            {
                ret += r - l;
                l++;
            }
            else
                r--;
        }
        return ret;
    }

    int dfs(int u)
    {
        mxDis = INF;
        int root;
        getRoot(u, -1, root, sz[u]);
        if(~fa[root])
            sz[fa[root]] = sz[u] - sz[root];
        //处理以root为根的子树
        ret[root] = solve(root, -1, 0);
        vis[root] = true;
        for(int i = head[root]; ~i; i = nxt[i])
        {
            int v = e[i].v;
            if(vis[v])
                continue;
            ret[root] -= solve(v, -1, e[i].w);
            dfs(v);
        }
        return root;
    }
};
