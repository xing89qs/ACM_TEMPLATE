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
    void match(char *s){
		Node *x = root;//x为当前走到的结点位置
		int now = 0;//now为当前匹配长度
		for(int i = 0;s[i];i++){
			int c = s[i]-'a';
			if(x->ch[c]){
				now++;
				x = x->ch[c];
			}else{
				while(x&&x->ch[c]==NULL) x = x->pre;
				if(x==NULL){
					x = root;
					now = 0;
				}else{
					now = x->len+1;
					x = x->ch[c];
				}
			}
		}
	}
    //拓扑排序所有节点，n为len的最大值
    void topSort(int n){
        for(int i = 0;i<=n;i++) c[i] = 0;
        for(int i = 0;i<cnt;i++) c[nd[i].len]++;
        for(int i = 1;i<=n;i++) c[i]+=c[i-1];
        for(int i = 0;i<cnt;i++){
            b[--c[nd[i].len]] = &nd[i];
        }
    }
};
