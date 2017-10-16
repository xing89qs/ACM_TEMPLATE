//字典树（Trie）模板

#define DIGIT_NUM 32    //数位数量，int为32，long long为64
#define INF 0x3fffffff

class Trie
{
public:
#define CHAR_NUM 26 //2--01（异或）字典树，10--只有数字，26--只有大写/小写字母，52--大小写字母都有，62--数字+大小写字母
#define MAXNODE 500005

    struct node
    {
        int next[CHAR_NUM];
        int val;
        bool flag;  //字符串结束标记
        void init()
        {
            memset(next,-1,sizeof(next));
            val = 0;
            flag = false;
        }
    } nd[MAXNODE];

    int root;
    int cnt;

    void init()
    {
        cnt = 0;
        root = newnode();
    }

    int newnode()
    {
        nd[cnt].init();
        return cnt++;
    }

    void insert(char *s)
    {
        int temp = root;
        for(int i = 0; s[i]; i++)
        {
            int pos = s[i] - 'a';
            //int pos = s[i] - '0';
            if(nd[temp].next[pos]==-1) nd[temp].next[pos] = newnode();
            temp = nd[temp].next[pos];
            nd[temp].val++;
        }
        nd[temp].flag = true;
    }

    int find(char *s)
    {
        int temp = root;
        for(int i = 0; s[i]; i++)
        {
            int pos = s[i] - 'a';
            //int pos = s[i] - '0';
            if(nd[temp].next[pos]==-1)
            {
                return 0;
            }
            else
                temp = nd[temp].next[pos];
        }
        return nd[temp].val;
    }

    /*以下为01（异或）字典树需要增加的操作（用query函数替代find函数）*/
    /*求与给定数异或的最大值，不要把0插入字典树*/
    /*求与给定数异或的最大值，不要把0插入字典树*/
    /*求一段区间的最大（小）异或值和，类似前缀和的形式预处理：sum[i] ^= sum[i-1]
    一段区间[l,r]的异或值就等于：sum[r]^sum[l-1]
    然后问题就转化成了求区间两端的数
    注意要先把0插入字典树
    */

    //转换函数（十进制转换为二进制）
    void trans(char *s, int val)    //val为需要转换的十进制值
    {
        memset(s,0,sizeof(s));
        for(int i=DIGIT_NUM-1; i>=0; i--)   //从高位往低位考虑
            s[i] = ((val >> i) & 1) + '0';
        reverse(s,s+DIGIT_NUM-1);
        s[DIGIT_NUM] = '\0';
    }

    //查询最大（小）值函数
    //如果要求最大值，就尽量往反方向走（如果是0，就往1走，如果是1，就往0走）
    //如果要求最小值，就尽量往同方向走（如果是0，就往0走，如果是1，就往1走）
    int query(char *s, int val, int flag)  //val为要参与运算的数值（或预处理求出的某个前缀和），flag为求最大（小）值标记
    {
        int temp = root;
        for(int i = 0; s[i]; i++)
        {
            int pos = s[i] - '0';
            pos ^= flag;    //求最大值时设定flag=1，实现往反方向走；求最小值时设定flag=0，实现往同方向走
            if(nd[temp].next[pos]==-1)
                pos ^= 1;   //找最后一个的时候要去掉自己本身
            temp = nd[temp].next[pos];
        }
        return nd[temp].val ^ val;  //sum[r-l] = sum[r] ^ sum[l-1];
    }
} trie;
