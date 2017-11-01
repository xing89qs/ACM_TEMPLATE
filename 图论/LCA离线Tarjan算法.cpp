//LCA离线Tarjan算法

#define PB push_back
#define MAXN 40005
#define MAXQ 100005

class LCA_Offline_Tarjan
{
public:
    struct Edge
    {
        int to,cost,next;
        Edge() {}
        Edge(int to,int cost,int next):to(to),cost(cost),next(next) {}
    } e[MAXN<<1];

    int head[MAXN];
    int dep[MAXN];
    int fa[MAXN];
    bool vis[MAXN];
    int ans[MAXQ];
    int cnt;
    int n,q;

    void addEdge(int u,int v,int w)
    {
        e[cnt].to = v;
        e[cnt].cost = w;
        e[cnt].next = head[u];
        head[u] = cnt++;
    }

    struct Query
    {
        int idx;
        int u,v;
    };

    vector <Query> qry[MAXN];

    void init(int n,int q)
    {
        this -> n = n;
        this -> q = q;
        cnt = 0;
        for(int i = 1; i<=n; i++)
        {
            head[i] = -1;
            qry[i].clear();
            fa[i] = i;
            vis[i] = false;
        }
    }

    int findset(int u)
    {
        return u==fa[u]?u:fa[u] = findset(fa[u]);
    }

    int treeDis(int u,int v,int lca)
    {
        return dep[u] + dep[v] - 2 * dep[lca];
    }

    void dfs(int u,int d)
    {
        dep[u] = d;
        vis[u] = true;
        for(int i = head[u]; ~i; i = e[i].next)
        {
            int v = e[i].to;
            if(!vis[v])
            {
                dfs(v,d+e[i].cost);
                fa[findset(v)] = findset(u);
            }
        }
        int sz = qry[u].size();
        for(int i = 0; i<sz; i++)
        {
            int v = qry[u][i].v;
            if(vis[v])
            {
                int lca = findset(v);
                //ans[qry[u][i].idx] = treeDis(u,v,lca);  //输入需要记录的查询内容
            }
        }
    }

    void buildGraph()
    {
        for(int i = 1; i<n; i++)
        {
            int u,v,w;
            scanf("%d %d %d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
    }

    void initQuery()
    {
        for(int i = 0; i<q; i++)
        {
            Query query;
            scanf("%d %d",&query.u,&query.v);
            query.idx = i;
            qry[query.u].PB(query);
            swap(query.u,query.v);
            qry[query.u].PB(query);
        }
    }

    void solve()
    {
        buildGraph();
        initQuery();
        dfs(1,0);
    }
} lca_tarjan;
