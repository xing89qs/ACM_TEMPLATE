int bridge[MAXE];
int pre[MAXN],belong[MAXN],bcc_cnt;
int dfs_clock;

int tarjan(int u,int fa){
	int lowu = pre[u] = ++dfs_clock;
	for(int i = head[u];~i;i = nxt[i]){
		int v = e[i];
		if(!pre[v]){
			int lowv = tarjan(v,u);
			lowu = min(lowu,lowv);
			if(lowv>pre[u]){
				bridge[i] = bridge[i^1] = true;
			}
		}else if(pre[v]<pre[u]&&v!=fa){
			lowu = min(lowu,pre[v]);
		}
	}
	return lowu;
}

void dfs(int u,int fa){
	belong[u] = bcc_cnt;
	for(int i = head[u];~i;i = nxt[i]){
		int v = e[i];
		if(v!=fa&&!bridge[i]&&!belong[v]){
			dfs(v,u);
		}
	}
}

//找边-双连通分量
void find_bcc(int n){
	for(int i = 0;i<n;i++) pre[i] = 0;
	//cnt是边数
	for(int i = 0;i<cnt;i++) bridge[i] = false;
	dfs_clock = bcc_cnt = 0;
	for(int i = 0;i<n;i++){
		if(!pre[i]) tarjan(i,-1);
		belong[i] = 0;
	}
	//belong表示所属的边联通分量的id
	for(int i = 0;i<n;i++){
		if(!belong[i]){
			bcc_cnt++;
			dfs(i,-1);
		}
	}
}

