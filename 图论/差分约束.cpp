//差分约束模板

typedef int Type;

class DCSystem
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
    } e[MAXE];

    bool inq[MAXN];

    void init(int n)
    {
        cnt = 0;
        for(int i = 0; i <= n; i++)
            head[i] = -1;
    }

    inline void addEdge(int u, int v, Type cost)
    {
        e[cnt] = Edge(v, cost);
        int tmp = head[u];
        head[u] = cnt;
        nxt[cnt++] = tmp;
    }

    int inqcnt[MAXN];

    /*
     * 差分约束求 xi 的最大值，化为 xi - xj <= c 的形式，加边 (j->i, 权值c)，求最短路
     * 差分约束求 xi 的最小值，化为 xi - xj >= c 的形式，加边 (j->i, 权值c)，求最长路
     */
    Type spfa(int s, int t, int n)    //n的值一般传的大一些（至少n+1）
    {
        for(int i = 0; i <= n; i++)
        {
            inq[i] = false;
            d[i] = INF; //求最长路的时候值改为-INF
            inqcnt[i] = 0;
        }
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            inq[x] = false;
            for(int i = head[x]; ~i; i = nxt[i])
            {
                Edge ed = e[i];
                if(d[ed.v] > d[x] + ed.cost)    //求最长路的时候改成 < 号
                {
                    d[ed.v] = d[x] + ed.cost;
                    if(!inq[ed.v])
                    {
                        if(++inqcnt[ed.v] > n)
                            return INF;
                        inq[ed.v] = true;
                        q.push(ed.v);
                    }
                }
            }
        }
        return d[t];
    }
} dc;
