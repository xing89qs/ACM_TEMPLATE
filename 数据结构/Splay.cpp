ass SplayTree{
public:
	struct Node{
		int sz;
		Node *ch[2],*fa;

		//结点维护信息
		int v;
		bool rev;

		void init(Node *_fa,Node *EMPTY,int va){
			sz = 1;
			fa = _fa;
			v = va;
			rev = false;
			ch[0] = ch[1] = EMPTY;
		}
	} nd[MAXN];
    
	struct Node *root,*TOP,*EMPTY;

	int ndcnt;
 
    void init(){
		root = NULL;
        EMPTY = &nd[0];
        EMPTY->init(NULL,EMPTY,-INF);
        EMPTY->sz = 0;
		//初始化EMPTY相关的结点值
		EMPTY->v = 0;

        ndcnt = 1;
        TOP = newNode(NULL,0);
    }
    Node *newNode(Node *fa,int va){
        nd[ndcnt].init(fa,EMPTY,va);
        return &nd[ndcnt++];
    }
	//初始化建树
    Node *build(int l,int r,Node *fa,int *a){
        if(l>r) return EMPTY;
        int mid = (l+r)>>1;
        Node *x = newNode(fa,a[mid]);
        if(root==NULL) root = x;
        x->ch[0] = build(l,mid-1,x,a);
        x->ch[1] = build(mid+1,r,x,a);
        push_Up(x);
        return x;
    }
    void rotate(Node *x,int d){
        Node *fax = x->fa;
        push_Down(fax);
        push_Down(x);
        fax->ch[d^1] = x->ch[d];
        x->ch[d]->fa = fax;
        Node *ffax = fax->fa;
        if(ffax!=TOP)
            ffax->ch[ffax->ch[1]==fax] = x;
        x->fa = ffax;
        x->ch[d] = fax;
        fax->fa = x;
        push_Up(fax);
        push_Up(x);
    }
    void reverse(Node* x){
        if(x==EMPTY) return;
        swap(x->ch[0],x->ch[1]);
        x->rev^=1;
    }
    Node *lower_bound(Node *x,LL va){
		if(x==EMPTY) return EMPTY;
		if(x->v>=va){
			Node *ret = lower_bound(x->ch[0],va);
			if(ret==EMPTY) return x;
			else return ret;
		}else return lower_bound(x->ch[1],va);
    }
    void push_Down(Node *x){
        if(x->rev){
            reverse(x->ch[0]);
            reverse(x->ch[1]);
            x->rev^=1;
        }
    }
    void push_Up(Node *x){
        x->sz = 1;
        for(int i = 0;i<2;i++){
            x->sz+=x->ch[i]->sz;
        }
    }
    void splay(Node *x,const Node *goal){
        push_Down(x);
        while(x->fa!=goal){
            if(x->fa->fa==goal){
                push_Down(x->fa);
                push_Down(x);
                rotate(x,x->fa->ch[0]==x);
            }else{
                Node *fax = x->fa;
                push_Down(fax->fa);
                push_Down(fax);
                push_Down(x);
                int d = fax->fa->ch[0]==fax;
                if(fax->ch[d]==x){
                    rotate(x,d^1);
                    rotate(x,d);
                }else{
                    rotate(fax,d);
                    rotate(x,d);
                }
            }
        }
        push_Up(x);
        if(goal==TOP) root = x;
    }
    Node *findKth(int k){
        Node *x = root;
        push_Down(x);
        while(x!=EMPTY){
            push_Down(x);
            if(x->ch[0]->sz>=k) x = x->ch[0];
            else if(x->ch[0]->sz==k-1){
                splay(x,TOP);
                return x;
            }else{
                k-=x->ch[0]->sz+1;
                x = x->ch[1];
            }
        }
        return EMPTY;
    }
	Node* getSegMent(int l,int r){
        Node *x = findKth(l-1);
        Node *y = findKth(r+1);
        splay(x,TOP);splay(y,x);
		return y;
	}
	void reverse(int l,int r){
		Node *y = getSegMent(l,r);
        reverse(y->ch[0]);
		splay(y->ch[0],TOP);
	}
	//在pos位置之后插入结点rt
	void insertNode(int pos,Node *rt){
        Node *x = findKth(pos);
        Node *y = findKth(pos+1);
        splay(x,TOP);splay(y,x);
        y->ch[0] = rt;
        rt->fa = y;
        push_Up(y);
        push_Up(x);
		splay(y->ch[0],TOP);
	}
	//在pos位置之后插入一段长度为n的子树
    void insertSubTree(int pos,int n,int *a){
        Node *rt = build(1,n,TOP,a);
		insertNode(pos,rt);
    }
    void remove(int pos,int n){
        Node *x = findKth(pos-1);
        Node *y = findKth(pos+n);
        splay(x,TOP);splay(y,x);
        y->ch[0] = EMPTY;
        push_Up(y);
        push_Up(x);
	}

	bool first;

	void inorder(Node *x){
		first = true;
		__inorder(x);
	}

	//中序遍历整棵树
    void __inorder(Node *rt){
        if(rt==EMPTY) return;
        push_Down(rt);
        __inorder(rt->ch[0]);
        printf("%d",rt->v);
		printf(" ");
        __inorder(rt->ch[1]);
    }
	//获得x的前驱
    Node *getPre(Node *x){
		push_Down(x);
		Node *ret = x->ch[0];
		push_Down(ret);
		if(ret==EMPTY) return EMPTY;
		while(ret->ch[1]!=EMPTY){
			push_Down(ret);
			ret = ret->ch[1];
		}
		return ret;
	}
	//获得x的后继
	Node *getNext(Node *x){
		push_Down(x);
		Node *ret = x->ch[1];
		push_Down(ret);
		if(ret==EMPTY) return EMPTY;
		while(ret->ch[0]!=EMPTY){
			push_Down(ret);
			ret = ret->ch[0];
		}
		return ret;
	}
	//删除结点x
    void remove(Node *x){
        if(x==EMPTY) return;
        splay(x,TOP);
        Node *fax = x->fa;
        if(x->ch[0]==EMPTY){
            fax->ch[fax->ch[1]==x] = x->ch[1];
            if(x->ch[1]!=EMPTY) x->ch[1]->fa = fax;
            push_Up(fax);
            root = x->ch[1];
        }else{
            Node *pre = getPre(x);
            splay(pre,x);
            fax->ch[fax->ch[1]==x] = pre;
            pre->fa = fax;
            pre->ch[1] = x->ch[1];
            if(pre->ch[1]!=EMPTY) pre->ch[1]->fa = pre;
            push_Up(pre);
            push_Up(fax);
            root = pre;
        }
    }
} splay;
