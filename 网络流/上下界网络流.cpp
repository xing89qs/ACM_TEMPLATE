//上下界可行流
//du[i]为i流出去的下界和减去流进来的下界和
//求s到t的最大流，如果最大流等于所有du[i]>0的和则有可行流
void buildGraph(int n,int m){
		for(int i = 0;i<m;i++){
			int u,v,l,c;
			//c为上界,l为下界
			down[i] = l;
			du[u]-=l;
			du[v]+=l;
			addEdge(u,v,c-l);
		}
		for(int i = 1;i<=n;i++){
			if(du[i]>0) addEdge(s,i,du[i]);
			else if(du[i]<0) addEdge(i,t,-du[i]);
		}
}

//上下界最大流
//S和T为源汇点
//s和t为超级源点和超级汇点
//先按如下构图判断是否有可行流
//然后head[s] = -1,head[t] = -1;s = S,t = T;
//求一遍S->T的最大流即为答案
int buildGraph(int n,int m){
		for(int i = 0;i<m;i++){
			int u,v,l,c;
			//c为上界,l为下界
			down[i] = l;
			du[u]-=l;
			du[v]+=l;
			addEdge(u,v,c-l);
		}
		int T = node-1,S = node-2;
		addEdge(T,S,INF);
		int sum = 0;
		for(int i = 0;i<=t;i++){
			if(du[i]>0){
				addEdge(s,i,du[i]);
				sum+=du[i];
			}
			else if(du[i]<0) addEdge(i,t,-du[i]);
		}
		return sum;
}


//上下界最小流
//S和T为源汇点
//s和t为超级源点和超级汇点
//先按如下构图求一遍s->t的最大流
//然后addEdge(T,S,INF),再求一次s->t的最大流
//当st->du[i]的所有边满流时有解，答案是T->S这条边的反向边的流量
int buildGraph(int n,int m){
		for(int i = 0;i<m;i++){
			int u,v,l,c;
			//c为上界,l为下界
			down[i] = l;
			du[u]-=l;
			du[v]+=l;
			addEdge(u,v,c-l);
		}
		int T = node-1,S = node-2;
		//这里不需要加addEdge(T,S,INF);
		int sum = 0;
		for(int i = 0;i<=t;i++){
			if(du[i]>0){
				addEdge(s,i,du[i]);
				sum+=du[i];
			}
			else if(du[i]<0) addEdge(i,t,-du[i]);
		}
		return sum;
}
