//dfs序模板

#define MAXN 100005
#define MAXE 100005


struct Edge
{
    int v,nxt;
    Edge() {}
    Edge(int v,int nxt):v(v),nxt(nxt) {}
} e[MAXE<<1];

int head[MAXN];
int cnt;

void addEdge(int u,int v)
{
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    head[u] = cnt++;
}

int dfs_clock;  //dfs序时间戳
int lnd[MAXN],rnd[MAXN];    //为每一个结点赋一个左值lnd和一个右值rnd，这个区间表示这个结点的管辖结点范围。

void init()
{
    memset(head,-1,sizeof(head));
    cnt = 0;
    dfs_clock = 0;
}

void dfs(int u,int fa)  //dfs序
{
    lnd[u] = ++dfs_clock;   //记录dfs序下该结点被访问的起始时间戳
    for(int i=head[u]; ~i; i=e[i].nxt)
    {
        int v = e[i].v;
        if(v != fa)
            dfs(v,u);
    }
    rnd[u] = dfs_clock; //记录dfs序下该结点被访问的结束时间戳
}
