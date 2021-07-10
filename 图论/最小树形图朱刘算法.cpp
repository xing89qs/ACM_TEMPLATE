
#define MAXN 1005
#define MAXE MAXN*MAXN

typedef LL Type;

struct Edge//边的权和顶点
{
    int u,v;
    Type w;
    Edge() {}
    Edge(int u,int v,Type w):u(u),v(v),w(w) {}
} e[MAXE];

int pre[MAXN],id[MAXN],vis[MAXN];
int n,m,pos;
Type in[MAXN];  //存最小入边权，pre[v]为该边的起点

Type DMST(int root, int n, int m)   //n为总结点数，m为总边数
{
    Type ret = 0;   //存最小树形图总权值
    while(true)
    {
        //1.找每个节点的最小入边
        for(int i=0; i<n; i++)
            in[i] = INF;    //初始化为无穷大
        for(int i=0; i<m; i++)  //遍历每条边
        {
            int u = e[i].u;
            int v = e[i].v;
            if(e[i].w < in[v] && u != v)    //说明顶点v有条权值较小的入边  记录之
            {
                pre[v] = u; //节点u指向v
                in[v] = e[i].w; //最小入边
                if(u == root)   //这个点就是实际的起点
                    pos = i;
            }
        }
        for(int i=0; i<n; i++)  //判断是否存在最小树形图
        {
            if(i == root)
                continue;
            if(in[i] == INF)
                return -1;  //除了根以外有点没有入边,则根无法到达它  说明它是独立的点 一定不能构成树形图
        }
        //2.找环
        int cnt = 0;    //记录环数
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        in[root] = 0;
        for(int i=0; i<n; i++)  //标记每个环
        {
            ret += in[i];   //记录权值
            int v = i;
            while(vis[v] != i && id[v] == -1 && v != root)
            {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1)
            {
                for(int u = pre[v]; u != v; u = pre[u])
                    id[u] = cnt;    //标记节点u为第几个环
                id[v] = cnt++;
            }
        }
        if(cnt == 0)    //无环
            break;
        for(int i=0; i<n; i++)
            if(id[i] == -1)
                id[i] = cnt++;
        //3.建立新图：缩点，重新标记
        for(int i=0; i<m; i++)
        {
            int u = e[i].u;
            int v = e[i].v;
            e[i].u = id[u];
            e[i].v = id[v];
            if(id[u] != id[v])
                e[i].w -= in[v];
        }
        n = cnt;
        root = id[root];
    }
    return ret;
}
