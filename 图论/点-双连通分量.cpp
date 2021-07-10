//点-双连通分量

#define MAXN 1005
#define MAXE 1000005

class Vertex_BCC
{
public:
    int head[MAXN];
    struct Edge
    {
        int to,next;
        Edge() {}
        Edge(int to,int next):to(to),next(next) {}
    } e[MAXE];

    stack <PII> s;//存储在当前BCC中的边
    int dfs_clock,bcc_cnt;
    int dfn[MAXN];
    int low[MAXN];
    int cut[MAXN];
    int bccno[MAXN];
    vector <int> bcc_nodes;
    PII bcc_edges[MAXE];
    int n,m;
    int cnt;

    void init(int n,int m)
    {
        this -> n = n;
        this -> m = m;
        cnt = 0;
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(bccno,0,sizeof(bccno));
        memset(cut,0,sizeof(cut));
    }

    void addEdge(int u,int v)
    {
        e[cnt].to = v;
        e[cnt].next = head[u];
        head[u] = cnt++;
    }

    //返回边数
    int get_bcc(PII ed)
    {
        bcc_cnt++;
        bcc_nodes.clear();
        int tot = 0;
        while(true)
        {
            PII x = s.top();
            s.pop();
            int u = x.first,v = x.second;
            if(bccno[u]!=bcc_cnt)
            {
                bccno[u] = bcc_cnt;
                bcc_nodes.PB(u);
            }
            if(bccno[v]!=bcc_cnt)
            {
                bccno[v] = bcc_cnt;
                bcc_nodes.PB(v);
            }
            bcc_edges[tot++] = x;
            if(x==ed)
                break;
        }
        return tot;
    }

    void tarjan(int u,int fa)
    {
        low[u] = dfn[u] = ++dfs_clock;
        int child = 0;
        for(int i = head[u]; ~i; i = e[i].next)
        {
            int v = e[i].to;
            PII ed = MP(u,v);
            if(!dfn[v])
            {
                s.push(ed);
                child++;
                tarjan(v,u);
                low[u] = min(low[u],low[v]);
                if(low[v]>=dfn[u])
                {
                    cut[u] = true;
                    int m = get_bcc(ed);
                    //m为当前bcc的边数，bcc_nodes记录结点，bcc_edges记录边
                }
            }
            else if(dfn[v]<dfn[u]&&v!=fa)
            {
                s.push(ed);
                low[u] = min(low[u],dfn[v]);
            }
        }
        if(fa==-1&&child==1)
            cut[u] = false;
    }

    //找点-双连通分量
    void find_bcc()
    {
        for(int i = 0; i<n; i++) dfn[i] = cut[i] = bccno[i] = 0;
        dfs_clock = bcc_cnt = 0;
        for(int i = 0; i<n; i++)
        {
            if(!dfn[i])
                tarjan(i,-1);
        }
    }
} vertex_bcc;
