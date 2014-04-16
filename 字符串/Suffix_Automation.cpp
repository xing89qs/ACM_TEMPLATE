class Suffix_AutoMation{
public:
	int cnt;
	Node *root,*last;

	#define LETTER 26
	#define MAXN 500005

	struct Node{
		Node *pre;
		Node *ch[LETTER];
		int len;
		void init(int l){
			len = l;
			memset(ch,0,sizeof(ch));
		}
	} nd[MAXN];

	void init(){
		cnt = 0;
		last = root = newNode(0);
		root->pre = NULL;
	}
	Node *newNode(int len){
		nd[cnt].init(len);
		return &nd[cnt++];
	}
	void addChar(char ch){
		int c = ch-'a';
		Node *p = last;
		Node *np = newNode(p->len+1);
		last = np;
		for(;p&&p->ch[c]==NULL;p = p->pre) p->ch[c] = np;
		if(p==NULL) np->pre = root;
		else{
			Node *q = p->ch[c];
			if(p->len+1==q->len) np->pre = q;
			else{
				Node *nq = newNode(p->len+1);
				*nq = *q;
				nq->len = p->len+1;
				np->pre = q->pre = nq;
				for(;p&&p->ch[c]==q;p = p->pre) p->ch[c] = nq;
			}
		}
	}
};
