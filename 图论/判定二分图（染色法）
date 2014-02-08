int color[MAXN];

bool bipartite(int u){
	for(int i = head[u];~i;i = nxt[i]){
		int v = e[i];
		if(color[v]==color[u]) return false;
		if(!color[v]){
			color[v] = 3-color[u];
			if(!bipartite(v)) return false;
		}
	}
	return true;
}

bool checkBipartite(int n){	
	memset(color,0,sizeof(color));
	bool ok = true;
	FOR(i,n){
		if(!color[i]){
			color[i] = 1;
			if(!bipartite(i)) ok = false;
		}
	}
	return ok;
}

