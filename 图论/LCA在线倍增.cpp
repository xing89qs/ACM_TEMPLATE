class Tree{
public:
	#define MAXN 100005
	#define MAXE 200005

	int head[MAXN],nxt[MAXE],e[MAXE];
	int cnt;

	void init(int n){
		cnt = 0;
		for(int i = 0;i<n;i++) head[i] = -1;
        this->n = n;
	}

	inline void addEdge(int u,int v){
		e[cnt] = v;
		int tmp = head[u];
		head[u] = cnt;
		nxt[cnt++] = tmp;
	}

	int dep[MAXN];
	int p[MAXN][20];
	int n;

	void dfs(int u,int fa,int d){
		dep[u] = d;
		p[u][0] = fa;
		for(int i = 1;(1<<i)<=n;i++){
			if(~p[u][i-1]) p[u][i] = p[p[u][i-1]][i-1];
			else p[u][i] = -1;
		}
        for(int i = head[u];~i;i = nxt[i]){
			int v = e[i];
			if(v==fa) continue;
			dfs(v,u,d+1);
		}
	}

	int LCA(int u,int v){
		if(dep[u]>dep[v]) swap(u,v);
		if(dep[u]<dep[v]){
			int offset = dep[v]-dep[u];
			for(int i = 0;(1<<i)<=n;i++) if(offset&(1<<i)) v = p[v][i];
		}
		if(u!=v){
			for(int i = log2(n);i>=0;i--){
				if(p[u][i]!=p[v][i])
					u = p[u][i],v = p[v][i];
			}
			u = p[u][0],v = p[v][0];
		}
		return u;
	}
} lca;
