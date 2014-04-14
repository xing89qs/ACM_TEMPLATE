#define MAXN 100005

typedef int Type;

Type ans[MAXN];

const int sq_n = 333;

struct Query{
	int l,r,idx;
	bool operator<(const Query& q) const{
		int l1 = l/sq_n,l2 = q.l/sq_n;
		if(l1==l2) return r<q.r;
		else return l1<l2;
	}
} q[MAXN];

//添加一个位置
void addPos(int pos){
}

//移除一个位置
void removePos(int pos){
}

int solve(Query& q,int last,int l,int r){
	while(l<q.l){
		removePos(l);
		l++;
	}
	while(l>q.l){
		l--;
		addPos(l);
	}
	while(r<q.r){
		r++;
		addPos(r);
	}
	while(r>q.r){
		removePos(r);
		r--;
	}
	return last;
}

//m是询问个数
void mo(int m){
	sort(q,q+m);
	int l = q[0].l,r = q[0].l-1;
	int last = 0;
	for(int i = 0;i<m;i++){
		last = solve(q[i],last,l,r);
		l = q[i].l,r = q[i].r;
		//处理ans[q[i].idx]
	}
	//输出ans
}

