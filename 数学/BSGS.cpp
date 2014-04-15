LL Pow(LL a,LL p,LL md){
	if(p==0) return 1;
	else if(p==1) return a%md;
	else{
		LL tmp = Pow(a,p/2,md);
		tmp = 1ll*tmp*tmp%md;
		if(p&1) tmp = 1ll*tmp*a%md;
		return tmp;
	}
}

//b^x==n(mod p),求x
LL solve(LL p,LL b,LL n){
	if(n==1) return 0;
	int LIMIT = sqrt(p)+1;
	map<LL,int> mp;
	LL now = 1;
	for(int i = 0;i<=LIMIT;i++){
		if(!mp[now]) mp[now] = i;
		now = now*b%p;
	}
	int inv = Pow(Pow(b,LIMIT,p),p-2,p);
	now = n;
	for(int i = 0;i<=LIMIT;i++){
		if(mp[now]) return i*LIMIT+mp[now];
		now = 1ll*now*inv%p;
	}
	return -1;
}
