#define LETTER 2
#define MAXN 600005
#define MAXNODE 20000005

class Per_Trie{
public:
	int a[MAXN];
	const int DEPTH;
	struct Node *EMPTY;
	struct Node{
		Node *ch[LETTER];
		int cnt;
		void init(){
			for(int i = 0;i<LETTER;i++) ch[i] = EMPTY;
			cnt = 0;
		}
	} nd[MAXNODE],*root[MAXN];
	int cnt;
	
	Per_Trie():DEPTH(24){
	}

	void init(int n){
		cnt = 0;
		EMPTY = newNode();
		EMPTY->ch[0] = EMPTY->ch[1] = EMPTY;
		root[0] = newNode();
		for(int i = 1;i<=n;i++)
			root[i] = insert(root[i-1],a[i],DEPTH);
	}

	Node *newNode(){
		nd[cnt].init();
		return &nd[cnt++];
	}

	Node* insert(Node *last,int val,int d){
		Node *rt = newNode();
		*rt = *last;
		++rt->cnt;
		if(d<0) return rt;
		if(val&(1<<d)) rt->ch[1] = insert(last->ch[1],val,d-1);
		else rt->ch[0] = insert(last->ch[0],val,d-1);
		return rt;
	}

	int query(Node *ld,Node *rd,int val,int d){
		if(d<0) return 0;
		int pos = (val&(1<<d))?1:0;
		int mxcnt = rd->ch[pos^1]->cnt-ld->ch[pos^1]->cnt;
		if(mxcnt) return (1<<d)+query(ld->ch[pos^1],rd->ch[pos^1],val,d-1);
		else return query(ld->ch[pos],rd->ch[pos],val,d-1);
	}
} per_trie;
