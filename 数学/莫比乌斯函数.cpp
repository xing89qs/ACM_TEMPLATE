//sigma(mu[d]) d|n = (n==1)
void initMu(){
	for(int i = 1;i<MAXN;i++){
		int t = (i==1?1:0);
		int d = t-mu[i];
		mu[i] = d;
		for(int j = i+i;j<MAXN;j+=i)
			mu[j]+=d;
	}
}

//线性
mu[1] = 1;
int tot = 0;
for(int i = 2; i < N ; i++){
    if(!check[i]){
        prime[tot ++] = i;
        mu[i] = -1;
    }
    for(int j = 0 ;j < tot; j ++){
        if(i * prime[j] >= N)break;
        check[i * prime[j]] = true;
        if(i % prime[j] == 0){
            mu[i * prime[j]] = 0;
            break;
        }else{
            mu[i * prime[j]] = -mu[i];
        }
    }
}