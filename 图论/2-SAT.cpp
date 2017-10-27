//2-SAT模板

/*
x : 选x; ~x : 不选x
x AND y = 1 : ~x -> x, ~y -> y  （两个数必须全为1）
x AND y = 0 : x -> ~y, y -> ~x  （两个数至少有一个为0）
x OR y = 1 : ~x -> y, ~y -> x  （两个数至少有一个为1）
x OR y = 0 : x -> ~x, y -> ~y  （两个数全为0）
x XOR y = 1 : x -> ~y, y -> ~x, ~y -> x, ~x -> y  （两个数不同）
x XOR y = 0 : x -> y, ~x -> ~y, y -> x, ~y -> ~x  （两个数相同）

x,y不能都选是 : x -> ~y, y -> ~x
x,y不能都选否 : ~x -> y, ~y -> x
x选是且y选否不能同时发生 : x -> y, ~y -> ~x
x选否且y选是不能同时发生 : ~x -> ~y, y -> x
*/

#define MAXN 10005
#define MAXE 2000005

class TwoSat
{
public:
    int head[MAXN<<1];
    struct Edge
    {
        int to,next;
        Edge() {}
        Edge(int to,int next):to(to),next(next) {}
    } e[MAXE];

    int mark[MAXN<<1];  //mark[i<<1]==1，表示点i被选择；mark[i<<1|1]==1，表示点i没有被选择
    int cnt,scc_cnt,dfs_clock;
    int n,m;
    int top;

    stack <int> sta;
    vector <int> nG[MAXN];    //缩点后建立的新图

    int dfn[MAXN<<1];
    int low[MAXN<<1];
    int belong[MAXN<<1];
    int color[MAXN<<1]; //求解任意一组可行解时记录点的颜色
    int sta[MAXN<<1];   //数组模拟栈
    int conf[MAXN<<1];  //记录新图中的冲突点
    int ind[MAXN<<1];  //入度

    //使用前调用
    void init(int n,int m)
    {
        this -> n = n;
        this -> m = m;
        cnt = scc_cnt = dfs_clock = 0;
        top = 0;
        memset(dfn,0,sizeof(dfn));
        memset(belong,0,sizeof(belong));
        memset(color,0,sizeof(color));
        memset(conf,0,sizeof(conf));
        memset(ind,0,sizeof(ind));
        for(int i=0; i<MAXN; i++)
            nG[i].clear();
        while(!sta.empty())
            sta.pop();
    }

    inline void addEdge(int u,int v)
    {
        e[cnt].to = v;
        e[cnt].next = head[u];
        head[u] = cnt++;
    }


    /*判断2-SAT问题是否有解*/
    void tarjan(int u)  //Tarjan算法求解强连通分量并缩点
    {
        dfn[u] = low[u] = ++dfs_clock;
        mark[u] = 1;
        sta.push(u);
        for(int i = head[u]; ~i; i = e[i].next)
        {
            int v = e[i].to;
            if(!mark[v])
            {
                tarjan(v);
                low[u] = min(low[u],low[v]);
            }
            if(mark[v]==1)
                low[u] = min(low[u],dfn[v]);
        }
        if(dfn[u]==low[u])
        {
            scc_cnt++;
            int temp;
            do
            {
                temp = sta.top();
                belong[temp] = scc_cnt;
                mark[temp] = 2;
                sta.pop();
            }
            while(temp!=u);
        }
    }

    bool check()    //判断缩点后有没有冲突
    {
        for(int i = 0; i<2*n; i++)
        {
            if(!mark[i])
                tarjan(i);
        }
        for(int i = 0; i<n; i++)
        {
            if(belong[i<<1]==belong[i<<1|1])
                return false;
        }
        return true;
    }


    /*求2-SAT问题的任意一组可行解*/
    void cal()  //建立缩点后的新图并为之后的拓扑排序染色做准备
    {
        for(int i = 0; i<n; i++)
        {
            if(!conf[belong[i<<1]])
            {
                conf[belong[i<<1]] = belong[i<<1|1];
                conf[belong[i<<1|1]] = belong[i<<1];
            }
        }
        for(int i = 0; i<2*n; i++)
        {
            for(int j = head[i]; ~j; j = e[j].next)
            {
                int v = e[j].to;
                if(belong[i]!=belong[v])
                {
                    ind[belong[i]]++;
                    nG[belong[v]].push_back(belong[i]);
                }
            }
        }
    }

    void topoSort() //拓扑排序
    {
        queue<int> q;
        for(int i = 1; i<=scc_cnt; i++)
        {
            if(!ind[i])
                q.push(i);
        }
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            if(!color[u])
            {
                color[u] = 1;
                color[conf[u]] = 2; //conf数组记录的是与当前点冲突的点
            }
            for(int i = 0; i<nG[u].size(); i++)
            {
                int v = nG[u][i];
                ind[v]--;
                if(!ind[v])
                    q.push(v);
            }
        }
    }


    /*暴力求2-SAT问题的字典序最小解（复杂度O(n*m)）*/
    bool dfs(int u) //判断当前的强连通分量当中有没有出现矛盾
    {
        if(mark[u^1]) return false; //如果需要被选的不能被选那么矛盾
        if(mark[u]) return true;    //如果需要被选的已经被选，那么当前联通分量一定    不会出现矛盾
        mark[u] = true; //如果当前点需要被选，那么选上它，并且标记
        sta[top++] = u; //当前的强连通分量加上这个点
        //找到与当前点相连点，判断他们的状态
        for(int i = head[u]; ~i; i = e[i].next)
        {
            int v = e[i].to;
            if(!dfs(v))
                return false;
        }
        return true;
    }

    bool solve(int n)   //n是变量数
    {
        for(int i = 0; i<n*2; i+=2)
        {
            if(!mark[i]&&!mark[i^1])
            {
                top = 0;
                if(!dfs(i)) //如果矛盾，那么这个强连通分量里的点都不能选取
                {
                    while(top>0)
                        mark[sta[--top]] = false;
                    if(!dfs(i^1))
                        return false;
                }
            }
        }
        return true;
    }

    void buildGraph()
    {
        memset(head,-1,sizeof(head));
        memset(mark,0,sizeof(mark));
    }
} twosat;
