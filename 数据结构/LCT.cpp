class LCT{
public:
    int head[MAXN],nxt[MAXN<<1],e[MAXN<<1];
    int cnt;

    struct Node{
        Node *ch[2],*pre;
        int add,mx,v;
        bool rev,rt;
        void init(int val,Node* f,Node *EMPTY){
            mx = v = val;
            pre = f;
            add = 0;
            rev = false;
            rt = true;
            ch[0] = ch[1] = EMPTY;
        }
    } nd[MAXN];

    struct Node *EMPTY;

    void init(int n){
        for(int i = 1;i<=n;i++) head[i] = -1;
        cnt = 0;
        EMPTY = &nd[0];
        EMPTY->init(0,NULL,EMPTY);
        EMPTY->rt = true;
    }

    void addEdge(int u,int v){
        e[cnt] = v;
        int tmp = head[u];
        head[u] = cnt;
        nxt[cnt++] = tmp;
    }

    void dfs(int u,int fa){
        if(fa!=-1)
            nd[u].init(val[u],&nd[fa],EMPTY);
        else nd[u].init(val[u],EMPTY,EMPTY);
        for(int i = head[u];~i;i = nxt[i]){
            int v = e[i];
            if(v==fa) continue;
            dfs(v,u);
        }
    }

    void rotate(Node *x){
        Node *y = x->pre;
        int d = (y->ch[1]==x);
        y->ch[d] = x->ch[d^1];
        y->ch[d]->pre = y;
        x->pre = y->pre;
        y->pre = x;
        x->ch[d^1] = y;
        if(y->rt){
            y->rt = false,x->rt = true;
        }else{
            x->pre->ch[x->pre->ch[1]==y] = x;
        }
        push_Up(y);
    }

    void DOWN(Node *x){
        if(x->rt!=EMPTY&&!x->rt) DOWN(x->pre);
        push_Down(x);
    }

    void splay(Node *x){
        DOWN(x);
        while(x->rt!=EMPTY&&!x->rt){
            Node *f = x->pre;Node *ff = f->pre;
            if(f->rt) rotate(x);
            else if((ff->ch[1]==f)==(f->ch[1]==x)){
                rotate(f),rotate(x);
              }else rotate(x),rotate(x);
        }
        push_Up(x);
    }

    Node *access(Node *x){
        Node *y = EMPTY;
        for(;x!=EMPTY;x = (y = x)->pre){
            splay(x);
            x->ch[1]->rt = true;
            (x->ch[1] = y)->rt = false;
            push_Up(x);
        }
        return y;
    }

    void ADD(Node *rt,int val){
        rt->add+=val;
        rt->mx+=val;
        rt->v+=val;
    }

    void push_Down(Node *rt){
        if(rt->add){
            for(int i = 0;i<2;i++)
                if(rt->ch[i]!=EMPTY) ADD(rt->ch[i],rt->add);
            rt->add = 0;
        }
        if(rt->rev){
            for(int i = 0;i<2;i++)
                if(rt->ch[i]!=EMPTY) reverse(rt->ch[i]);
            rt->rev^=1;
        }
    }

    void push_Up(Node *rt){
        rt->mx = rt->v;
        for(int i = 0;i<2;i++)
            if(rt->ch[i]!=EMPTY) rt->mx = max(rt->mx,rt->ch[i]->mx);
    }

    void reverse(Node *rt){
        swap(rt->ch[0],rt->ch[1]);
        rt->rev^=1;
    }

    void makeRoot(Node *x){
        access(x);
        splay(x);
        reverse(x);
    }

    Node *getRoot(Node *x){
        access(x);
        splay(x);
        while(x->ch[0]!=EMPTY) x = x->ch[0];
        return x;
    }

    void link(Node* u,Node *v){
        makeRoot(u);
        makeRoot(v);
        u->pre = v;
    }

    void cut(Node *x){
        access(x);
        splay(x);
        if(x->ch[0]==EMPTY) puts("-1");
        else{
            x->ch[0]->pre = EMPTY;
            x->pre = EMPTY;
            x->ch[0]->rt = true;
            x->ch[0] = EMPTY;
            push_Up(x);
        }
    }
} lct;
