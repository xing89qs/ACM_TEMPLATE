
#define MAXN 1005
#define MAXE 100005


//适于稀疏图，边少，BFS增广短
class Hungary_BFS
{
private:
    int head[MAXN];
    struct Edge
    {
        int to,next;
        Edge(int to,int next):to(to),next(next) {}
        Edge() {}
    } e[MAXE];

    int mx[MAXN],my[MAXN];
    int vis[MAXN];
    int pre[MAXN];
    int n;
    int nx,ny;
    int cnt;

    void addEdge(int u,int v)
    {
        e[cnt].to = v;
        e[cnt].next = head[u];
        head[u] = cnt++;
    }


    bool bfs(int st)
    {
        queue <int> q;
        q.push(st);
        pre[st] = -1;
        bool flag = false;
        while(!q.empty() && !flag)
        {
            int u = q.front();
            q.pop();
            for(int i = head[u]; ~i && !flag; i = e[i].next)
            {
                int v = e[i].to;
                if(vis[v] != st)
                {
                    vis[v] = st;
                    q.push(my[v]);
                    if(~my[v])  //my[v]!=-1
                        pre[my[v]] = u;
                    else
                    {
                        int a = u, b = v;
                        flag = true;
                        while(~a)   //a!=-1
                        {
                            int t = mx[a];
                            mx[a] = b;
                            my[b] = a;
                            a = pre[a];
                            b = t;
                        }
                    }
                }
            }
        }
        return mx[st] != -1;
    }

public:
    void init()
    {
        cnt = 0;
    }

    int hungary()
    {
        int res = 0;
        memset(mx, -1, sizeof(mx));
        memset(my, -1, sizeof(my));
        memset(vis, -1, sizeof(vis));
        for(int i = 1; i <= nx; i++)  //number from 1
        {
            if(mx[i] == -1)
            {
                if(bfs(i))
                    res++;
            }
        }
        return res;
    }

    void buildGraph()
    {
        memset(head,-1,sizeof(head));
        n = nx + ny;
    }
} hungaryBFS;
