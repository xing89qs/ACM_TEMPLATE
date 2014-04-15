class TwoSat{
public:
	int mark[MAXN<<1],s[MAXN<<1];
	int c,cnt;

	//使用前调用
	void init(int n){
		cnt = 0;
		for(int i = 0;i<2*n;i++) head[i] = -1,mark[i] = 0;
	}

	bool dfs(int x){
		if(mark[x^1]) return false;
		if(mark[x]) return true;
		mark[x] = true;
		s[c++] = x;
		for(int i = head[x];~i;i = nxt[i]){
			if(!dfs(e[i])) return false;
		}
		return true;
	}

	inline void addEdge(int u,int v){
		e[cnt] = v;
		int tmp = head[u];
		head[u] = cnt;
		nxt[cnt++] = tmp;
	}

	//n是变量数
	bool solve(int n){
		for(int i = 0;i<n*2;i+=2){
			if(!mark[i]&&!mark[i^1]){
				c = 0;
				if(!dfs(i)){
					while(c>0) mark[s[--c]] = false;
					if(!dfs(i^1)) return false;
				}
			}
		}
		return true;
	}

	void buildGraph(int n){
		init(n);
	}
} twosat;

