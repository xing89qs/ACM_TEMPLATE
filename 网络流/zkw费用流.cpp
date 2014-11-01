class ZKW_flow{
public:
	typedef int CostType;
	struct Edge{
		int from,to,cap,flow;
		CostType cost;
		Edge(int from,int to,int cap,int flow,CostType cost):from(from),to(to),
		cap(cap),flow(flow),cost(cost){}
		Edge(){}
	} e[MAXE];

	int node,s,t,cnt;
	int head[MAXN],nxt[MAXE];

    void init(){
		cnt = 0;
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

    int dis[MAXN],use[MAXN];

    void SPFA(){
        for(int i = 0; i<=node;i++) dis[i] = INF;
        priority_queue<pair<int, int> > q;
        dis[s] = 0;
        q.push(MP(0, s));
        while(!q.empty()){
            int u = q.top().second, d = -q.top().first;
            q.pop();
            if(dis[u]!=d) continue;
            for(int i = head[u];~i;i = nxt[i]){
                int &v = e[i].to;
                if(e[i].cap>e[i].flow&&dis[v]>d+e[i].cost){
                    dis[v] = d + e[i].cost;
                    q.push(make_pair(-dis[v], v));
                }
            }
        }
        for(int i = 0;i<node;i++) dis[i] = dis[t] - dis[i];
    }

    int add_flow(int u,int flow,int &maxFlow,int &minCost){
        if(u == t){
            maxFlow+=flow;
            minCost+=dis[s]*flow;
            return flow;
        }
        use[u] = true;
        int now = flow;
        for(int i = head[u];~i;i = nxt[i]){
            int &v = e[i].to;
            if(e[i].cap>e[i].flow&&!use[v]&&dis[u]==dis[v]+e[i].cost){
                int tmp = add_flow(v, min(now,e[i].cap-e[i].flow),maxFlow,minCost);
                e[i].flow+=tmp;
                e[i^1].flow-=tmp;
                now-=tmp;
                if(!now) break;
            }
        }
        return flow-now;
    }

    bool modify_label(){
        int d = INF;
        for(int u = 0;u<node;u++) if(use[u])
            for(int i = head[u];~i;i = nxt[i]){
                int &v = e[i].to;
                if(e[i].cap>e[i].flow&&!use[v]) d = min(d, dis[v]+e[i].cost-dis[u]);
            }
        if(d==INF) return false;
        for(int i = 0;i<node;i++) if(use[i]) dis[i] += d;
        return true;
    }

    int maxFlow(){
        int cost = 0,flow = 0;
        SPFA();
        while(true){
            while(true){
                for(int i = 0;i<node;i++) use[i] = 0;
                if(!add_flow(s, INF,flow,cost)) break;
            }
            if(!modify_label()) break;
        }
        return cost;
    }

	void buildGraph(int n,int m,int x,int y){
	}

} zkw_flow;

