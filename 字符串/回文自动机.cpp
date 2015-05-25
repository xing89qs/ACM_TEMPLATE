
#define CHAR_NUM 26
#define MAXN 1000005

class Pa_Tree{
public:
    int S[MAXN],n;//n是字符数个数
    int cnt;
    
    struct Node{
        Node *next[CHAR_NUM];
        Node *fail;
        LL cnt;
        int len;
        void init(int l){
            cnt = 0;
            len = l;
            memset(next,0,sizeof(next));
        }
    } nd[MAXN],*last,*root0,*root1;
    
    void init(){
        cnt = n = 0;
        S[n] = -1;
        root0 = newNode(0);
        root1 = newNode(-1);
        last = root0;
        root0->fail = root1;
        root1->fail = root1;
    }
    
    Node *newNode(int l){
        nd[cnt].init(l);
        return &nd[cnt++];
    }
    
    Node *getFail(Node *x){
        while(S[n-x->len-1]!=S[n]) x = x->fail;
        return x;
    }
    
    void addChar(int c){
        c-='a';
        S[++n] = c;
        Node *cur = getFail(last);
        if(cur->next[c]==NULL){
            Node *now = newNode(cur->len+2);
            cur->next[c] = now;
            if(now->len==1){
                now->fail = root0;
            }else{
                Node *tmp = getFail(cur->fail);
                now->fail = tmp->next[c];
            }
        }
        last = cur->next[c];
        last->cnt++;
    }
    
    void dp(){
        for(int i = cnt-1;i>=0;i--)	nd[i].fail->cnt+=nd[i].cnt;
    }
} ptreeA,ptreeB;