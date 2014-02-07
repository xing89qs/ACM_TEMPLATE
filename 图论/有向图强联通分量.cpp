int pre[MAXN],lowlink[MAXN],sccno[MAXN];
int dfs_clock,scc_cnt;
stack<int> s;

void tarjan(int u){
	pre[u] = lowlink[u] = ++dfs_clock;
	s.push(u);
	for(int i = head[u];~i;i = nxt[i]){
		int v = e[i];
		if(!pre[v]){
			tarjan(v);
			lowlink[u] = min(lowlink[u],lowlink[v]);
		}else if(!sccno[v]){
			lowlink[u] = min(lowlink[u],pre[v]);
		}
	}
	if(lowlink[u]==pre[u]){
		scc_cnt++;
		for(;;){
			int x = s.top();s.pop();
			sccno[x] = scc_cnt;
			if(x==u) break;
		}
	}
}

//求有向图的强联通分量
void find_scc(int n){
	dfs_clock = scc_cnt = 0;
	for(int i = 0;i<n;i++) sccno[i] = pre[i] = 0;
	for(int i = 0;i<n;i++)
		if(!pre[i]) tarjan(i);
}
