//最小生成树prim算法


/*朴素prim算法，适合求稠密图上的MST*/
int g[MAXN][MAXN];
int vis[MAXN];
int dis[MAXN];
int n;

int prim()
{
    memset(vis,0,sizeof(vis));
    for(int i=0; i<n; i++)
        dis[i] = g[0][i];
    vis[0] = 1;
    dis[0] = 0;
    int sum = 0;
    for(int i=1; i<n; i++)
    {
        int pos = -1;
        int Min = INF;
        for(int j=0; j<n; j++)
        {
            if(!vis[j] && dis[j] < Min)
            {
                Min = dis[j];
                pos = j;
            }
        }
        //if(pos == -1) return INF;
        sum += Min;
        vis[pos] = 1;
        for(int j=0; j<n; j++)
        {
            if(!vis[j] && g[pos][j] < dis[j])
                dis[j] = g[pos][j];
        }
    }
    return sum;
}


/*优先队列优化prim算法*/
typedef int Type;

struct Edge
{
    int v,nxt;
    Type cost;
    Edge() {}
    Edge(int v,int nxt,Type cost):v(v),nxt(nxt),cost(cost) {}
    bool operator <(const Edge &e) const
    {
        return cost > e.cost;
    }
} e[MAXE];

int head[MAXN];
Type d[MAXN];
bool vis[MAXN];
int cnt;

inline void addEdge(int u,int v,Type w)
{
    e[cnt].v = v;
    e[cnt].cost = w;
    e[cnt].nxt = head[u];
    head[u] = cnt++;
}

Type prim(int n)
{
    priority_queue <Edge> pq;
    for(int i=0; i<n; i++)
    {
        d[i] = INF;
        vis[i] = false;
    }
    for(int i=head[0]; ~i; i=e[i].nxt)
    {
        int v = e[i].v;
        if(e[i].cost < d[v])
        {
            d[v] = e[i].cost;
            Edge tmp;
            tmp.v = v;
            tmp.cost = d[v];
            pq.push(tmp);
        }
    }
    vis[0] = true;
    Type sum = 0;
    while(!pq.empty())
    {
        int u = pq.top().v;
        pq.pop();
        if(vis[u])
            continue;
        vis[u] = true;
        sum += d[u];
        for(int i=head[u]; ~i; i=e[i].nxt)
        {
            int v = e[i].v;
            if(!vis[v] && d[v] > e[i].cost)
            {
                d[v] = e[i].cost;
                Edge tmp;
                tmp.v = v;
                tmp.cost = d[v];
                pq.push(tmp);
            }
        }
    }
    return sum;
}
