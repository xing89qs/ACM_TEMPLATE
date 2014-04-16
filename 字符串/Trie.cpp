
class Trie{
public:
	#define CHAR_NUM 26
	#define MAXNODE 500005

	struct node{
	    int next[CHAR_NUM];
	    int val;
	    void init(){
	        memset(next,-1,sizeof(next));
	        val = 0;
		}
	} nd[MAXNODE];

	int root = 0;
	int cnt = 0;

    void init(){
		cnt = 0;
        root = newnode();
    }

	int newnode(){
		nd[cnt].init();
		return cnt++;
	}

    void insert(char *s){
        int temp = root;
        for(int i = 0;s[i];i++){
            int pos = s[i]-'a';
            if(nd[temp].next[pos]==-1) nd[temp].next[pos] = newnode();
            temp = nd[temp].next[pos];
            nd[temp].val++;
        }
    }

    int find(char *s){
        int temp = root;
		for(int i = 0;s[i];i++){
            int pos = s[i]-'a';
            if(nd[temp].next[pos]==-1){
                return 0;
            }else 
                temp = nd[temp].next[pos];
        }
        return nd[temp].val;
    }
} trie;
