ass Treap{
public:
#define MAXN 100005
	struct Node{
		Node *ch[2];
		int r,sz;//r是随机优先级，sz是子树的结点个数
		bool operator<(const Node &nd) const{
			return r<nd.r;
		}
		int cmp(int x){
			if(x==v) return -1;
			return x>v;
		}

		//维护的结点信息
		int v;

		void init(int _v){
			v = _v;
			sz = 1;
			ch[0] = ch[1] = NULL;
			r = rand();
		}
	} nd[MAXN];
	int ndcnt;
	void init(){
		ndcnt = 0;
	}

	Node *newNode(int v){
		nd[ndcnt].init(v);
		return &nd[ndcnt++];
	}
	
	void push_Up(Node *rt){
		if(rt==NULL) return;
		rt->sz = 1;
		if(rt->ch[0]!=NULL) rt->sz+=rt->ch[0]->sz;
		if(rt->ch[1]!=NULL) rt->sz+=rt->ch[1]->sz;
	}

	void rotate(Node *&o,int d){
		Node *k = o->ch[d^1];
		o->ch[d^1] = k->ch[d];
		k->ch[d] = o;
		push_Up(o);
		push_Up(k);
		o = k;
	}

	//插入值为val的结点
	void insertVal(Node *&o,int val){
		if(o==NULL) o = newNode(val);
		else{
			int d = (val<o->v?0:1);
			insertVal(o->ch[d],val);
			if(o->ch[d]>o) rotate(o,d^1);
		}
		push_Up(o);
	}

	//删除值为val的结点，只删除一个
	void removeVal(Node *&o,int val){
		if(o==NULL) return;
		int d = o->cmp(val);
		if(d==-1){
			if(o->ch[0]!=NULL&&o->ch[1]!=NULL){
				int d2 = (o->ch[0]>o->ch[1]?1:0);
				rotate(o,d2);removeVal(o->ch[d2],val);
			}else{
				if(o->ch[0]==NULL) o = o->ch[1];
				else o = o->ch[0];
			}
		}else removeVal(o->ch[d],val);
		if(o!=NULL) push_Up(o);
	}

	//返回比结点值比val小的结点个数
	int getRank(Node *o,int val){
		if(o==NULL) return 0;
		int d = o->cmp(val);
		if(d==1){
			int lsz = (o->ch[0]==NULL?0:o->ch[0]->sz);
			return lsz+1+getRank(o->ch[1],val);
		}else return getRank(o->ch[0],val);
	}

	//返回第k大的结点
	Node* Kth(Node *o,int k){
		if(o==NULL||k<=0||k>o->sz) return NULL;
		int s = (o->ch[0]==NULL?0:o->ch[0]->sz);
		if(k==s+1) return o;
		else if(k<=s) return Kth(o->ch[0],k);
		else return Kth(o->ch[1],k-s-1);
	}
} treap;
