class ACautomation
{
public:
#define LETTER 26
#define MAXNODE 500005

    char key[51];   //模板串（待插入字典树中的单词）
    char s[1000001];    //主串（待查询的串）

    int n, cnt = 0, root;

    struct node
    {
        int cnt;
        int fail;
        int next[LETTER];
        void init()
        {
            memset(next, -1, sizeof(next));
            cnt = 0;
        }
    } nd[MAXNODE];

    void init()
    {
        cnt = 0;
        root = newnode();
        nd[root].fail = root;
    }

    int newnode()
    {
        nd[cnt].init();
        return cnt++;
    }

    void insert(const char *str)
    {
        int temp = root;
        for(int i = 0; str[i]; i++)
        {
            int c = str[i] - 'a';
            if(nd[temp].next[c] == -1)
                nd[temp].next[c] = newnode();
            temp = nd[temp].next[c];
        }
        nd[temp].cnt++;
    }

    void getFail()
    {
        queue<int> q;
        for(int i = 0; i < LETTER; i++)
        {
            int node = nd[root].next[i];
            if(~node)
            {
                nd[node].fail = root;
                q.push(node);
            }
        }
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int i = 0; i < LETTER; i++)
            {
                int v = nd[u].next[i];
                if(~v)
                {
                    int fa = nd[u].fail;
                    while(fa != root && nd[fa].next[i] == -1)
                        fa = nd[fa].fail;
                    nd[v].fail = nd[fa].next[i] == -1 ? root : nd[fa].next[i];
                    q.push(v);
                }
            }
        }
    }

    int find()
    {
        int ans = 0;
        int cur = root;
        for(int i = 0; s[i]; i++)
        {
            int c = s[i] - 'a';
            while(cur != root && nd[cur].next[c] == -1)
                cur = nd[cur].fail;
            cur = nd[cur].next[c] == -1 ? root : nd[cur].next[c];
            int ptr = cur;
            while(ptr != root)
            {
                if(nd[ptr].cnt >= 0)
                {
                    ans += nd[ptr].cnt;
                    nd[ptr].cnt = -1;
                    ptr = nd[ptr].fail;
                }
                else
                    break;
            }
        }
        return ans;
    }
} ac_auto;
