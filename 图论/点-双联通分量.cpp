class BCC{
public:
	stack<PII> s;//存储在当前BCC中的边
	int dfs_clock,bcc_cnt;
	int pre[MAXN],cut[MAXN],bccno[MAXN];
	vector<int> bcc_nodes;
	PII bcc_edges[MAXE];

	//返回边数
	int get_bcc(PII ed){
		bcc_cnt++;
		bcc_nodes.clear();
		int tot = 0;
		while(true){
			PII x = s.top();s.pop();
			int u = x.first,v = x.second;
			if(bccno[u]!=bcc_cnt){
				bccno[u] = bcc_cnt;
				bcc_nodes.PB(u);
			}
			if(bccno[v]!=bcc_cnt){
				bccno[v] = bcc_cnt;
				bcc_nodes.PB(v);
			}
			bcc_edges[tot++] = x;
			if(x==ed) break;
		}
		return tot;
	}

	int dfs(int u,int fa){
		int lowu = pre[u] = ++dfs_clock;
		int child = 0;
		for(int i = head[u];~i;i = nxt[i]){
			int v = e[i];
			PII ed = MP(u,v);
			if(!pre[v]){
				s.push(ed);
				child++;
				int lowv = dfs(v,u);
				lowu = min(lowu,lowv);
				if(lowv>=pre[u]){
					cut[u] = true;
					int m = get_bcc(ed);
					//m为当前bcc的边数，bcc_nodes记录结点，bcc_edges记录边
				}
			}else if(pre[v]<pre[u]&&v!=fa){
				s.push(ed);
				lowu = min(lowu,pre[v]);
			}
		}
		if(fa==-1&&child==1) cut[u] = false;
		return lowu;
	}

	//找点-双连通分量
	void find_bcc(int n){
		for(int i = 0;i<n;i++) pre[i] = cut[i] = bccno[i] = 0;
		dfs_clock = bcc_cnt = 0;
		for(int i = 0;i<n;i++)
			if(!pre[i]) dfs(i,-1);
	}
};
