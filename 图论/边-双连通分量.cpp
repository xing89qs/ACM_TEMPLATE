//边-双联通分量（桥）

#define MAXN 1005
#define MAXE 2000005

class Edge_BCC
{
public:
    int head[MAXN];
    struct Edge
    {
        int to,next;
        Edge() {}
        Edge(int to,int next):to(to),next(next) {}
    } e[MAXE];

    int bridge[MAXE];
    int dfn[MAXN];
    int low[MAXN];
    int belong[MAXN];
    int cnt;
    int bcc_cnt;
    int dfs_clock;

    void init()
    {
        cnt = 0;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
    }

    void addEdge(int u,int v)
    {
        e[cnt].to = v;
        e[cnt].next = head[u];
        head[u] = cnt++;
    }

    void tarjan(int u,int fa)
    {
        low[u] = dfn[u] = ++dfs_clock;
        for(int i = head[u]; ~i; i = e[i].next)
        {
            if(v==fa) continue;
            int v = e[i].to;
            if(!dfn[v])
            {
                tarjan(v,u);
                low[u] = min(low[u],low[v]);
                if(low[v]>dfn[u])
                    bridge[i] = bridge[i^1] = true;
            }
            else if(dfn[v]<dfn[u])
                low[u] = min(low[u],dfn[v]);
        }
    }

    void dfs(int u,int fa)
    {
        belong[u] = bcc_cnt;
        for(int i = head[u]; ~i; i = e[i].next)
        {
            if(i==fa) continue;
            int v = e[i].to;
            if(!bridge[i]&&!belong[v])
                dfs(v,i^1);
        }
    }

    //找边-双连通分量
    void find_bcc(int n)
    {
        for(int i = 0; i<n; i++)
            dfn[i] = 0;
        for(int i = 0; i<cnt; i++)  //cnt是边数
            bridge[i] = false;
        dfs_clock = bcc_cnt = 0;
        for(int i = 0; i<n; i++)
        {
            if(!dfn[i])
                tarjan(i,-1);
            belong[i] = 0;
        }
        //belong表示所属的边联通分量的id
        for(int i = 0; i<n; i++)
        {
            if(!belong[i])
            {
                bcc_cnt++;
                dfs(i,-1);
            }
        }
    }
} edge_bcc;
