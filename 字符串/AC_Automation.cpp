class ACauto{
public:	
	#define LETTER 26
	#define MAXNODE 500005

	char key[51],s[1000001];

	int n,cnt = 0,root;

	struct node{
	    int count;
	    int fail;
	    int next[LETTER];
		void init(){memset(next,-1,sizeof(next));count = 0;}
	} nd[MAXNODE];
    
	void init(){cnt = 0;root = newnode();nd[root].fail = root;}

	int newnode(){
		nd[cnt].init();
		return cnt++;
	}

	void insert(const char *str){
		int temp = root;
	    for(int i = 0;str[i];i++){
			int c = str[i]-'a';
		    if(nd[temp].next[c]==-1) nd[temp].next[c] = newnode();
			temp = nd[temp].next[c];
		}
	    nd[temp].count++;
	}

    void getFail(){
        queue<int> q;
        for(int i = 0;i<LETTER;i++){
            int node = nd[root].next[i];
            if(~node){
                nd[node].fail = root;
                q.push(node);
            }
        }
        while(!q.empty()){
            int node = q.front();q.pop();
            for(int i = 0;i<LETTER;i++){
                int nx = nd[node].next[i];
                if(~nx){
                    int nt = nd[node].fail;
                    while(nt!=root&&nd[nt].next[i]==-1) nt = nd[nt].fail;
                    nd[nx].fail = nd[nt].next[i]==-1?root:nd[nt].next[i];
                    q.push(nx);
                }
            }
        }
    }
    int find(){
        int ans = 0;
        int cur = root;
        for(int i = 0;s[i];i++){
            int c = s[i]-'a';
            while(cur!=root&&nd[cur].next[c]==-1) cur = nd[cur].fail;
            cur = nd[cur].next[c]==-1?root:nd[cur].next[c];
            int ptr = cur;
            while(ptr!=root){
                if(nd[ptr].count>=0){
                    ans+=nd[ptr].count;
                    nd[ptr].count = -1;
                    ptr = nd[ptr].fail;
                }else break;
            }
        }
        return ans;
    }
};
