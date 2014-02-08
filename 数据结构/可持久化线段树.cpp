
#define MAXN 100005
#define MAXNODE 2000005

int a[MAXN],x[MAXN];

struct Node{
	Node *l,*r;
	int cnt;
	void init(){
		l = r = NULL;
		cnt = 0;
	}
} nd[MAXNODE],*root[MAXN];

class Per_SegTree{
public:
	int tot,m;//tot是结点数，m是离散化后值的个数
	Per_SegTree(int n):tot(0){
		m = disconcrete(n);
		root[0] = build(1,m);
		for(int i = 1;i<=n;i++)
			root[i] = insert(root[i-1],1,m,a[i]);
	}

	Node* newNode(){
		nd[tot].init();
		return &nd[tot++];
	}

	Node* build(int l,int r){
		Node *rt = newNode();
		if(l==r) return rt;
		int mid = (l+r)>>1;
		rt->l = build(l,mid);
		rt->r = build(mid+1,r);
		return rt;
	}

	Node *insert(Node *last,int l,int r,int val){
		Node *rt = newNode();
		*rt = *last;
		rt->cnt++;
		if(l==r) return rt;
		int mid = (l+r)>>1;
		if(val<=mid) rt->l = insert(last->l,l,mid,val);
		else rt->r = insert(last->r,mid+1,r,val);
		return rt;
	}

	int disconcrete(int n){
		for(int i = 1;i<=n;i++) x[i-1] = a[i];
		sort(x,x+n);
		int m = unique(x,x+n)-x;
		for(int i = 1;i<=n;i++)
			a[i] = lower_bound(x,x+m,a[i])-x+1;
		return m;
	}

	int query(Node *ld,Node *rd,int l,int r,int k){
		if(l==r) return x[l-1];
		int mid = (l+r)>>1;
		int lcnt = rd->l->cnt-ld->l->cnt;
		if(lcnt>=k) return query(ld->l,rd->l,l,mid,k);
		else return query(ld->r,rd->r,mid+1,r,k-lcnt);
	}
};
