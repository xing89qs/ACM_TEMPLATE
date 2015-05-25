LL mul(LL a,LL b){
	if(b==0) return 0;
	LL tmp = mul(a,b/2);
	tmp+=tmp;
	if(tmp>=MOD) tmp-=MOD;
	if(b&1ll){
		tmp = tmp+b;
		if(tmp>=MOD) tmp-=MOD;
	}
	return tmp;
}

LL mul(LL a,LL b){
	LL tmp = (a*b-(LL)((long double)x/MOD*y+1e-8)*MOD);
	return tmp<0?tmp+MOD:tmp;
}
