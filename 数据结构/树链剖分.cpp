class TreeChain{
public:
    struct Edge{
        int u,v;
        Edge(){}
        Edge(int u,int v):u(u),v(v){}
    } e[MAXN<<1];
    int cnt,ql,qr,val;
    int node[MAXN];
    int fa[MAXN],pos[MAXN],dep[MAXN],top[MAXN],son[MAXN],sz[MAXN];
    int head[MAXN],nxt[MAXN<<1];
    int mx[MAXN<<2],p[MAXN<<2];
    int seg_nd;
    
    void init(int n){
        cnt = seg_nd = 0;
        fa[1] = -1;
        for(int i = 0;i<=n;i++) head[i] = -1;
    }
    
    void addEdge(int u,int v){
        e[cnt] = Edge(u,v);
        int tmp = head[u];
        head[u] = cnt;
        nxt[cnt++] = tmp;
    }
    
    void dfs1(int u,int d){
        dep[u] = d;sz[u] = 1;son[u] = -1;
        int mx = 0;
        for(int i = head[u];~i;i = nxt[i]){
            Edge& ed = e[i];
            if(ed.v==fa[u]) continue;
            fa[ed.v] = u;
            dfs1(ed.v,d+1);
            sz[u]+=sz[ed.v];
            if(mx<sz[ed.v]){
                son[u] = ed.v;
                mx = sz[ed.v];
            }
        }
    }
    
    void dfs2(int u,int tp){
        pos[u] = ++seg_nd;
        node[seg_nd] = u;
        top[u] = tp;
        if(~son[u]) dfs2(son[u],tp);
        for(int i = head[u];~i;i = nxt[i]){
            int v = e[i].v;
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    
    void _add(int l,int r,int z){
        v[l].PB(z);
        if(r+1<=seg_nd) v[r+1].PB(-z);
    }
    
    void add(int u,int v,int z){
        int fu = top[u],fv = top[v];
        while(fu!=fv){
            if(dep[fu]<dep[fv]){
                swap(u,v);
                swap(fu,fv);
            }
            ql = pos[fu],qr = pos[u];
            _add(ql,qr,z);
            u = fa[fu];fu = top[u];
        }
        //		if(u==v) return;//边分治
        if(u==v);//点分治
        if(dep[u]>dep[v]) swap(u,v);
        //		ql = pos[son[u]],qr = pos[v];//边分治
        ql = pos[u],qr = pos[v];//点分治
        _add(ql,qr,z);
    }
    
    int find(int u,int v){
        int ans = 0;
        int fu = top[u],fv = top[v];
        while(fu!=fv){
            if(dep[fu]<dep[fv]){
                swap(u,v);
                swap(fu,fv);
            }
            ql = pos[fu],qr = pos[u];//
            u = fa[fu];fu = top[u];
        }
        if(u==v) return ans;
        if(dep[u]>dep[v]) swap(u,v);
        ql = pos[son[u]],qr = pos[v];//
        return ans;
    }
    
    void push_Up(int l,int r,int rt){
        if(mx[rt<<1]>=mx[rt<<1|1]){
            mx[rt] = mx[rt<<1];
            p[rt] = p[rt<<1];
        }else{
            mx[rt] = mx[rt<<1|1];
            p[rt] = p[rt<<1|1];
        }
    }
    
    void build(int l,int r,int rt){
        if(l==r){
            p[rt] = l;
            mx[rt] = 0;
        }else{
            int mid = (l+r)>>1;
            build(lson);
            build(rson);
            push_Up(l,r,rt);
        }
    }
    
    void update(int l,int r,int rt){
        if(l==r) mx[rt]+=val;
        else{
            int mid = (l+r)>>1;
            if(ql<=mid) update(lson);
            else update(rson);
            push_Up(l,r,rt);
        }
    }
    
    int query(int l,int r,int rt){
        if(mx[rt]==0) return 0;
        return p[1];
    }
} tc;

/*
    int main(void){
        tc.dfs1(1,0);
        tc.dfs2(1,1);
    }
 */
