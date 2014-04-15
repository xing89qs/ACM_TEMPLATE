class China{
public:
	LL a[15],b[15];

	void ex_gcd(LL a,LL b,LL d,LL &x,LL &y){
		if(!b){d = a;x = 1;y = 0;}
		else{ex_gcd(b,a%b,d,y,x);y-=x*(a/b);}
	}

	//n个方程 x == a[i] (mod b[i]),且b[i]两两互质
	LL china(int n){
		LL m = 1,d,y,x = 0;
		for(int i = 0;i<n;i++) m*=b[i];
		for(int i = 0;i<n;i++){
			LL w = m/b[i];
			ex_gcd(b[i],w,d,d,y);
			x = (x+y*w*a[i])%m;
		}
		return (x+m)%m;
	}
} china;
