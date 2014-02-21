#define MAXN 105

int w[MAXN][MAXN],match[MAXN],slack[MAXN],lx[MAXN],ly[MAXN];
int visx[MAXN],visy[MAXN];
int nx,ny;//左右集合的点数

bool find(int u){
    visx[u] = true;
    for(int i = 0;i<ny;i++){
        if(visy[i]) continue;
        int t = lx[u]+ly[i]-w[u][i];
        if(!t){
            visy[i] = true;
            if(match[i]==-1||find(match[i])){
                match[i] = u;
                return true;
            }
        }
        else slack[i] = min(slack[i],t);
    }
    return false;
}

bool update(){
    int d =	INF;
    for(int i = 0;i<ny;i++) if(!visy[i]) d = min(d,slack[i]);
    if(d==INF) return false;//说明无法匹配了 
    for(int i = 0;i<nx;i++){
        if(visx[i]) lx[i]-=d,visx[i] = false;
	}
	for(int i = 0;i<ny;i++){
        if(visy[i]) ly[i]+=d,visy[i] = false;
        else slack[i]-=d;
    }
	return true;
}

int km(){
    memset(match,-1,sizeof(int)*ny);
    memset(ly,0,sizeof(int)*ny);
    for(int i = 0;i<nx;i++){
        lx[i] = -INF;
        for(int j = 0;j<ny;j++) lx[i] = max(lx[i],w[i][j]);
    }
    for(int i = 0;i<nx;i++){
        for(int j = 0;j<ny;j++) slack[j] = INF;
        memset(visx,0,sizeof(int)*nx);
        memset(visy,0,sizeof(int)*ny);
        while(!find(i))
			if(!update()) break;//无法匹配
	}
    int ans = 0;
    for(int i = 0;i<ny;i++){
		if(match[i]!=-1) ans+=w[match[i]][i];
	}
    return ans;
}

