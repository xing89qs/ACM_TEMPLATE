//LCA在线倍增（需要<cmath>头文件）

const int MAXN = 100005;
const int MAXE = 200005;

class LCA_Online_Multiplication
{
public:

    int head[MAXN], nxt[MAXE], e[MAXE];
    int cnt;

    void init(int n)
    {
        this -> n = n;
        cnt = 0;
        memset(head, -1, sizeof(head));
    }

    inline void addEdge(int u, int v)
    {
        e[cnt] = v;
        int tmp = head[u];
        head[u] = cnt;
        nxt[cnt++] = tmp;
    }

    int dep[MAXN];
    int p[MAXN][20];
    int n;

    void dfs(int u, int fa, int d)
    {
        dep[u] = d;
        p[u][0] = fa;
        for(int i = 1; (1 << i) <= n; i++)
        {
            if(~p[u][i - 1])
                p[u][i] = p[p[u][i - 1]][i - 1];
            else
                p[u][i] = -1;
        }
        for(int i = head[u]; ~i; i = nxt[i])
        {
            int v = e[i];
            if(v == fa)
                continue;
            dfs(v, u, d + 1);
        }
    }

    int LCA(int u, int v)
    {
        if(dep[u] > dep[v])
            swap(u, v);
        if(dep[u] < dep[v])
        {
            int offset = dep[v] - dep[u];
            for(int i = 0; (1 << i) <= n; i++)
            {
                if(offset & (1 << i))
                    v = p[v][i];
            }
        }
        if(u != v)
        {
            for(int i = log2(n); i >= 0; i--)
            {
                if(p[u][i] != p[v][i])
                    u = p[u][i], v = p[v][i];
            }
            u = p[u][0], v = p[v][0];
        }
        return u;
    }

    //求树上两点距离
    int treeDis(int u, int v)
    {
        return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
    }

    void buildGraph()
    {
        for(int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
    }

    void solve()
    {
        buildGraph();
        dfs(1, -1, 0);
    }
} lca_multi;
