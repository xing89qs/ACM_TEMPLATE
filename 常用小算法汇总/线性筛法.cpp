int prime[MAXN];
int vis[MAXN];
int prime_cnt = 0;

for(int i = 2;i<MAXN;i++){
    if(!vis[i]) prime[prime_cnt++] = i;
    for(int j = 0;j<prime_cnt&&i*prime[j]<MAXN;j++){
        vis[i*prime[j]] = 1;
        if(i%prime[j]==0) break;
    }
}