const int MAXN = 1005;
const int MAXE = (MAXN * MAXN);

typedef int Type;

class Dijkstra
{
public:
    int head[MAXN], nxt[MAXE], cnt;
    Type d[MAXN];
    struct Edge
    {
        int v;
        Type cost;
        Edge() {}
        Edge(int v, Type cost) : v(v), cost(cost) {}
        bool operator < (const Edge& ed) const
        {
            return cost > ed.cost;
        }
    } e[MAXE];
    bool vis[MAXN];
    int n, m;

    //初始化，n为点数，m为边数
    void init(int n, int m)
    {
        this -> n = n;
        this -> m = m;
        cnt = 0;
        memset(head, -1, sizeof(head));
    }

    inline void addEdge(int u, int v, Type cost)
    {
        e[cnt] = Edge(v, cost);
        int tmp = head[u];
        head[u] = cnt;
        nxt[cnt++] = tmp;
    }

    //void dijkstra(int s)
    Type dijkstra(int s, int t)
    {
        for(int i = 0; i <= n; i++)
        {
            d[i] = INF;
            vis[i] = false;
        }
        d[s] = 0;
        priority_queue<Edge> q;
        q.push(Edge(s, 0));
        while(!q.empty())
        {
            Edge ed = q.top();
            q.pop();
            if(vis[ed.v])   //没有该判断会TLE
                continue;
            vis[ed.v] = true;
            //if(ed.v == t)
            //    return d[t];
            for(int i = head[ed.v]; ~i; i = nxt[i])
            {
                Edge ee = e[i];
                if(!vis[ee.v] && d[ee.v] > d[ed.v] + ee.cost)
                {
                    d[ee.v] = d[ed.v] + ee.cost;
                    /*
                     *  最短路树
                    	p[ee.v] = MP(u,i);
                    */
                    q.push(Edge(ee.v, d[ee.v]));
                }
            }
        }
        return d[t];
    }

    void solve()
    {
        buildGraph();   //建图
        dijkstra(1, n);
    }
} dij;
