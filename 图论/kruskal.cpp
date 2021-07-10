
/*最小生成树kruskal算法，适合求稀疏图上的MST*/

struct Edge
{
    int u,v,w;
    Edge() {}
    Edge(int u,int v,int w):u(u),v(v),w(w) {}
    bool operator <(const Edge &ed) const
    {
        return w < ed.w;
    }
} e[MAXE];

int fa[MAXN];
int n,m;

int findset(int x)
{
    if(x != fa[x])
        return fa[x] = findset(fa[x]);
    return fa[x];
}

int kruskal()
{
    sort(e,e+m);
    int cnt = n - 1;
    int ans = 0;
    for(int i=0; i<=n; i++)
        fa[i] = i;
    for(int i=0; i<m; i++)
    {
        int fu = findset(e[i].u);
        int fv = findset(e[i].v);
        if(fu != fv)
        {
            fa[fu] = fv;
            ans += e[i].w;
            cnt--;
            if(!cnt)
                break;
        }
    }
    return cnt ? INF : ans;
}
