class SPFA{
public:
	int head[MAXN],nxt[MAXE],cnt;
	Type d[MAXN];
	struct Edge{
		int v;
		Type cost;
		Edge(){}
		Edge(int v,Type cost):v(v),cost(cost){}
	} e[MAXE];

	bool inq[MAXN];

	void init(int n){
		cnt = 0;
		for(int i = 0;i<=n;i++) head[i] = -1;
	}

	inline void addEdge(int u,int v,Type cost){
		e[cnt] = Edge(v,cost);
		int tmp = head[u];
		head[u] = cnt;
		nxt[cnt++] = tmp;
	}

	Type spfa(int s,int t,int n){
		for(int i = 0;i<n;i++) inq[i] = false,d[i] = INF;
		d[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int x = q.front();q.pop();
			inq[x] = false;
			for(int i = head[x];~i;i = nxt[i]){
				Edge ed = e[i];
				if(d[ed.v]>d[x]+ed.cost){
					d[ed.v] = d[x]+ed.cost;
					if(!inq[ed.v]){
						inq[ed.v] = true;
						q.push(ed.v);
					}
				}
			}
		}
		return d[t];
	}
} spfa;
