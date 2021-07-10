
/*
直接调用checkBipartite(n)函数
注意点的下标从0开始
*/

#define MAXN 1005
#define MAXE 200005

struct Edge
{
    int to,nxt;
    Edge() {}
    Edge(int to,int nxt):to(to),nxt(nxt) {}
} e[MAXE];

int head[MAXN];
int cnt;

inline void addEdge(int u,int v)
{
    e[cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt++;
}

int color[MAXN];

bool bipartite(int u)
{
    for(int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].to;
        if(color[v] == color[u])
            return false;
        if(!color[v])
        {
            color[v] = 3 - color[u];
            if(!bipartite(v))
                return false;
        }
    }
    return true;
}

bool checkBipartite(int n)
{
    memset(color,0,sizeof(color));
    bool ok = true;
    for(int i=0; i<n; i++)  //如果点的下标从1开始，则这里需要修改
    {
        if(!color[i])
        {
            color[i] = 1;
            if(!bipartite(i))
                ok = false;
        }
    }
    return ok;
}

