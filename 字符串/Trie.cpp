
class Trie{
public:
	#define CHAR_NUM 26 //10--只有数字，26--只有大写/小写字母，52--大小写字母都有，62--数字+大小写字母
	#define MAXNODE 500005

	struct node{
	    int next[CHAR_NUM];
	    int val;
	    void init(){
	        memset(next,-1,sizeof(next));
	        val = 0;
		}
	} nd[MAXNODE];

	int root;
	int cnt;

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
            //int pos = s[i]-'0';
            if(nd[temp].next[pos]==-1) nd[temp].next[pos] = newnode();
            temp = nd[temp].next[pos];
            nd[temp].val++;
        }
    }

    int find(char *s){
        int temp = root;
		for(int i = 0;s[i];i++){
            int pos = s[i]-'a';
            //int pos = s[i]-'0';
            if(nd[temp].next[pos]==-1){
                return 0;
            }
            else
                temp = nd[temp].next[pos];
        }
        return nd[temp].val;
    }
} trie;
