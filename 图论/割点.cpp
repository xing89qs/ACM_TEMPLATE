class CUT{
public:
	int cut[MAXN],pre[MAXN],low[MAXN],bridge[MAXN<<1];
	int dfs_clock = 0;

	void init(int n,int m){
		dfs_clock = 0;
		for(int i = 0;i<n;i++) cut[i] = false;
		for(int i = 0;i<m;i++) bridge[i] = false;
	}

	int dfs(int u,int fa){
		int lowu = pre[u] = ++dfs_clock;
		int child = 0;
		for(int i = head[u];~i;i = nxt[i]){
			int v = e[i];
			if(!pre[v]){
				child++;
				int lowv = dfs(v,u);
				lowu = min(lowu,lowv);
				if(lowv>=pre[u]) cut[u] = true;
				if(lowv>pre[u]) bridge[i] = true;
				}else if(pre[v]<pre[u]&&v!=fa) lowu = min(lowu,pre[v]);
			}
		if(fa==-1&&child==1) cut[u] = 0;
		low[u] = lowu;
		return lowu;
	}
} cut;
