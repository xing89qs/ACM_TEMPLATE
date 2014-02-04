#define MAXN 505

int mx[MAXN<<2][MAXN<<2];
int mi[MAXN<<2][MAXN<<2];
int a[MAXN][MAXN];

#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
#define para pl,pr,pa

class SegTree2D{
public:
	int n,m;
	int x,y,x1,y1,x2,y2,v;
	SegTree2D(int n,int m){
		this->n = n;
		this->m = m;
		build1D(1,n,1);
	}

	void build1D(int l,int r,int rt){
		if(l==r) build2D(l,r,rt,1,m,1);
		else{
			int mid = (l+r)>>1;
			build1D(lson);
			build1D(rson);
			build2D(l,r,rt,1,m,1);
		}
	}

	void build2D(int pl,int pr,int pa,int l,int r,int rt){
		if(l!=r){
			int mid = (l+r)>>1;
			build2D(para,lson);
			build2D(para,rson);
		}
		if(pl==pr){
			if(l==r) mx[pa][rt] = mi[pa][rt] = a[pl][l];
			else{
				mx[pa][rt] = max(mx[pa][rt<<1],mx[pa][rt<<1|1]);
				mi[pa][rt] = min(mi[pa][rt<<1],mi[pa][rt<<1|1]);
			}
		}else{
			mx[pa][rt] = max(mx[pa<<1][rt],mx[pa<<1|1][rt]);
			mi[pa][rt] = min(mi[pa<<1][rt],mi[pa<<1|1][rt]);
		}
	}

	int query1DMax(int l,int r,int rt){
		if(x1<=l&&r<=x2){
			int ret = query2DMax(l,r,rt,1,m,1);
			return ret;
		}
		else{
			int mid = (l+r)>>1;
			int ans = -INF;
			if(x1<=mid) ans = max(ans,query1DMax(lson));
			if(mid<x2) ans = max(ans,query1DMax(rson));
			return ans;
		}
	}
	
	int query1DMin(int l,int r,int rt){
		if(x1<=l&&r<=x2) return query2DMin(l,r,rt,1,m,1);
		else{
			int mid = (l+r)>>1;
			int ans = INF;
			if(x1<=mid) ans = min(ans,query1DMin(lson));
			if(mid<x2) ans = min(ans,query1DMin(rson));
			return ans;
		}
	}

	int query2DMin(int pl,int pr,int pa,int l,int r,int rt){
		if(y1<=l&&r<=y2) return mi[pa][rt];
		else{
			int mid = (l+r)>>1;
			int ans = INF;
			if(y1<=mid) ans = min(ans,query2DMin(para,lson));
			if(mid<y2) ans = min(ans,query2DMin(para,rson));
			return ans;
		}
	}
	
	int query2DMax(int pl,int pr,int pa,int l,int r,int rt){
		if(y1<=l&&r<=y2) return mx[pa][rt];
		else{
			int mid = (l+r)>>1;
			int ans = -INF;
			if(y1<=mid) ans = max(ans,query2DMax(para,lson));
			if(mid<y2) ans = max(ans,query2DMax(para,rson));
			return ans;
		}
	}

	void update1D(int l,int r,int rt){
		if(l==r) update2D(l,r,rt,1,m,1);
		else{
			int mid = (l+r)>>1;
			if(x<=mid) update1D(lson);
			else update1D(rson);
			update2D(l,r,rt,1,m,1);
		}
	}

	void update2D(int pl,int pr,int pa,int l,int r,int rt){
		if(l!=r){
			int mid = (l+r)>>1;
			if(y<=mid) update2D(para,lson);
			else update2D(para,rson);
		}
		if(pl==pr){
			if(l==r) mx[pa][rt] = mi[pa][rt] = v;
	     	else{
				mx[pa][rt] = max(mx[pa][rt<<1],mx[pa][rt<<1|1]);
				mi[pa][rt] = min(mi[pa][rt<<1],mi[pa][rt<<1|1]);
	     	}
		}else{
			mx[pa][rt] = max(mx[pa<<1][rt],mx[pa<<1|1][rt]);
			mi[pa][rt] = min(mi[pa<<1][rt],mi[pa<<1|1][rt]);
		}
	}
};
