
#define MAXN 100005
#define MAXE 400005

class CUT/BRIDGE
{
public:
    int head[MAXN];
    int cnt;
    struct Edge
    {
        int from,to,nxt;
        Edge() {}
        Edge(int from,int to,int nxt):from(from),to(to),nxt(nxt) {}
    } e[MAXE];

    int cut[MAXN],dfn[MAXN],low[MAXN],bridge[MAXN<<1];
    int dfs_clock;

    void init(int n,int m)
    {
        memset(head,-1,sizeof(head));
        cnt = dfs_clock = 0;
        for(int i=0; i<n; i++)
            cut[i] = false;
        for(int i=0; i<m; i++)
            bridge[i] = false;
    }

    inline void addEdge(int u,int v)
    {
        e[cnt].from = u;
        e[cnt].to = v;
        e[cnt].nxt = head[u];
        head[u] = cnt++;
    }

    int dfs(int u,int fa)
    {
        int lowu = dfn[u] = ++dfs_clock;
        int child = 0;
        for(int i=head[u]; ~i; i=e[i].nxt)
        {
            int v = e[i].to;
            if(!dfn[v])
            {
                child++;
                int lowv = dfs(v,u);
                lowu = min(lowu,lowv);
                if(lowv >= dfn[u])
                    cut[u] = true;
                if(lowv > dfn[u])
                    bridge[i] = true;
            }
            else if(dfn[v] < dfn[u] && v != fa)
                lowu = min(lowu,dfn[v]);
        }
        if(fa == -1 && child == 1)
            cut[u] = 0;
        low[u] = lowu;
        return lowu;
    }

    void buildGraph(int m)
    {
        /*建图操作，注意无向图应建双向边*/
    }

    void solve(int n,int m)
    {
        buildGraph(m);
        for(int i=0; i<n; i++)
        {
            if(!dfn[i])
                dfs(i,-1);
        }
    }
} cut/bridge;
