class NodeDiv{
public:
#define MAXN 10005
#define MAXE 20005
	int n,k;
	int head[MAXN],nxt[MAXE],dis[MAXN],ret[MAXN];
	struct Edge{
		int v,w;
		Edge(){}
		Edge(int v,int w):v(v),w(w){}
	} e[MAXE];
	int cnt;
	int sz[MAXN],mx[MAXN],fa[MAXN];
	bool vis[MAXN];

	void init(int n){
		cnt = 0;
		for(int i = 0;i<n;i++) head[i] = -1;
	}

	inline void addEdge(int u,int v,int w){
		e[cnt] = Edge(v,w);
		int tmp = head[u];
		head[u] = cnt;
		next[cnt++] = tmp;
	}

	int mxDis;

	void getRoot(int u,int _fa,int& root,int n){
		sz[u] = 1;
		mx[u] = 0;
		fa[u] = _fa;
		for(int i = head[u];~i;i = nxt[i]){
			int v = e[i].v;
			if(v==_fa||vis[v]) continue;
			getRoot(v,u,root,n);
			sz[u]+=sz[v];
			mx[u] = max(mx[u],sz[v]);
		}
		mx[u] = max(mx[u],n-sz[u]);
		if(mx[u]<mxDis){
			root = u;
			mxDis = mx[u];
		}
	}

	void getDis(int u,int fa,int d,int& cnt){
		dis[cnt++] = d;
		for(int i = head[u];~i;i = next[i]){
			Edge& ed = e[i];
			if(ed.v==fa||vis[ed.v]) continue;
			getDis(ed.v,u,d+ed.w,cnt);
		}
	}

	int solve(int u,int fa,int d){
		int cnt = 0;
		getDis(u,-1,d,cnt);
		sort(dis,dis+cnt);
		int l = 0,r = cnt-1,ret = 0;
		while(l<r){
			if(dis[l]+dis[r]<=k){
				ret+=r-l;
				l++;
			}else r--;
		}
		return ret;
	}

	int dfs(int u){
		mxDis = INF;
		int root;getRoot(u,-1,root,sz[u]);
		if(~fa[root]) sz[fa[root]] = sz[u]-sz[root];
		int cnt = 0;
		getDis(root,-1,0,cnt);
		sort(dis,dis+cnt);
		//处理以root为根的子树
		ret[root] = solve(root,-1,0);
		vis[root] = true;
		for(int i = head[root];~i;i = nxt[i]){
			int v = e[i].v;
			if(vis[v]) continue;
			ret[root]-=solve(v,-1,e[i].w);
			dfs(v);
		}
		return root;
	}
};
