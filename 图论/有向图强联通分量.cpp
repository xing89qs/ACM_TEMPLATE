//有向图强连通分量Tarjan算法

#define MAXN 10005
#define MAXE 2000005

class SCC
{
public:
    int head[MAXN];
    struct Edge
    {
        int to,next;
        Edge() {}
        Edge(int to,int next):to(to),next(next) {}
    } e[MAXE];

    void addEdge(int u,int v)
    {
        e[cnt].to = v;
        e[cnt].next = head[u];
        head[u] = cnt++;
    }

    int belong[MAXN];
    int dfn[MAXN];
    int low[MAXN];
    //bool instack[MAXN];
    int ind[MAXN];  //入度
    int outd[MAXN]; //出度

    stack <int> sta;

    int n,m;
    int cnt;
    int dfs_clock,scc_cnt;

    void init(int n,int m)
    {
        this -> n = n;
        this -> m = m;
        dfs_clock = scc_cnt = 0;
        memset(dfn,0,sizeof(dfn));
        memset(belong,0,sizeof(belong));
    }

    void tarjan(int u)
    {
        dfn[u] = low[u] = ++dfs_clock;
        sta.push(u);
        //instack[u] = true;
        for(int i = head[u]; ~i; i = e[i].next)
        {
            int v = e[i].to;
            if(!dfn[v])
            {
                tarjan(v);
                low[u] = min(low[u],low[v]);
            }
            //else if(instack[v])
            else if(!belong[v])
                low[u] = min(low[u],dfn[v]);
        }
        if(dfn[u]==low[u])
        {
            scc_cnt++;
            while(!sta.empty())
            {
                int temp = sta.top();
                //instack[v] = false;
                belong[temp] = scc_cnt;
                sta.pop();
                if(u==temp)
                    break;
            }
        }
    }

    void find_scc()    //缩点
    {
        memset(ind,0,sizeof(ind));
        memset(outd,0,sizeof(outd));
        for(int i = 1; i<=n; i++)
        {
            for(int j = head[i]; ~j; j = e[j].next)
            {
                int v = e[j].to;
                if(belong[i]!=belong[v])
                {
                    ind[belong[v]]++;
                    outd[belong[i]]++;
                }
            }
        }
    }

    void buildGraph()
    {
        cnt = 0;
        memset(head,-1,sizeof(head));
    }

    void solve()    //求有向图的强连通分量
    {
        buildGraph();
        for(int i = 0; i<n; i++)
        {
            if(!dfn[i])
                tarjan(i);
        }
    }
} scc;
