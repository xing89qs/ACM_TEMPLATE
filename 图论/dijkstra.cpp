#define MAXN 1005
#define MAXE (MAXN*MAXN)>>1

int head[MAXN],nxt[MAXE],cnt;
Type d[MAXN];
struct Edge{
	int v;
	Type cost;
	Edge(){}
	Edge(int v,Type cost):v(v),cost(cost){}
	bool operator<(const Edge& ed) const{
		return cost>ed.cost;
	}
} e[MAXE];
bool vis[MAXN];

inline void addEdge(int u,int v,Type cost){
	e[cnt] = Edge(v,cost);
	int tmp = head[u];
	head[u] = cnt;
	nxt[cnt++] = tmp;
}

Type dijkstra(int s,int t,int n){
	for(int i = 0;i<n;i++) d[i] = INF,vis[i] = false;
	d[s] = 0;
	priority_queue<Edge> q;
	q.push(Edge(s,0));
	while(!q.empty()){
		Edge ed = q.top();q.pop();
		vis[ed.v] = true;
		if(ed.v==t) return d[t];
		for(int i = head[ed.v];~i;i = nxt[i]){
			Edge ee = e[i];
			if(!vis[ee.v]&&d[ee.v]>d[ed.v]+ee.cost){
				d[ee.v] = d[ed.v]+ee.cost;
				q.push(Edge(ee.v,d[ee.v]));
			}
		}
	}
	return d[t];
}
