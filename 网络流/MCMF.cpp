//MCMF（费用流）算法

#define MAXN 1005
#define MAXE 100005
#define INF 0x3f3f3f3f

class MCMF{
public:
	typedef int CostType;
	struct Edge{
		int from,to,cap,flow;
		CostType cost;
		Edge(int from,int to,int cap,int flow,CostType cost):from(from),to(to),cap(cap),flow(flow),cost(cost){}
		Edge(){}
	} e[MAXE];

	int head[MAXN],nxt[MAXE],a[MAXN],p[MAXN];
	bool inq[MAXN];
	CostType d[MAXN];
	int cnt,s,t;
	int node;
	int n,m;

	void init(int n,int m){
		cnt = 0;
		this -> n = n;
		this -> m = m;
	}

	void addEdge(int from,int to,int cap,CostType cost){
		e[cnt] = Edge(from,to,cap,0,cost);
		int tmp = head[from];
		head[from] = cnt;
		nxt[cnt++] = tmp;
		e[cnt] = Edge(to,from,0,0,-cost);
		tmp = head[to];
		head[to] = cnt;
		nxt[cnt++] = tmp;
	}

	bool spfa(int &flow,CostType &cost){
		for(int i = 0;i<=node;i++){
			d[i] = INF;
			inq[i] = false;
		}
		d[s] = 0,inq[s] = true,p[s] = 0,a[s] = INF;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int u = q.front();q.pop();
			inq[u] = false;
			for(int i = head[u];~i;i = nxt[i]){
				Edge &ed = e[i];
				if(ed.cap>ed.flow&&d[ed.to]>d[u]+ed.cost){
					d[ed.to] = d[u]+ed.cost;
					p[ed.to] = i;
					a[ed.to] = min(a[u],ed.cap-ed.flow);
					if(!inq[ed.to]){
						inq[ed.to] = true;
						q.push(ed.to);
					}
				}
			}
		}
		if(d[t]==INF) return false;
		flow+=a[t];
		cost+=d[t]*a[t];
		int u = t;
		while(u!=s){
			e[p[u]].flow+=a[t];
			e[p[u]^1].flow-=a[t];
			u = e[p[u]].from;
		}
		return true;
	}

	//Type maxFlow(){
	int maxFlow(){
		int flow = 0;
		CostType cost = 0;
		while(spfa(flow,cost));
		return flow;
		//return cost;
	}

	void buildGraph(){
		memset(head,-1,sizeof(head));
		s = 0;
		t = n;
		node = t;
	}
 } mcmf;
