
class EdgeDiv
{
public:
    #define MAXN 200005
    #define MAXE MAXN << 4  //边至少开到点的16倍

    int _head[MAXN], head[MAXN];
    struct Edge
    {
        int to, cost, nxt, pre;
        Edge() {}
        Edge(int to, int cost, int nxt, int pre) : to(to), cost(cost), nxt(nxt), pre(pre) {}
    } _e[MAXE], e[MAXE];   //原图，重构得到的新图

    int tail[MAXN];
    int sz[MAXN];   //子树包含的结点数
    int maxval; //记录子树的最大答案
    int rt; //根结点
    int midedge;    //中心边
    int n, node;    //原图结点数，重构得到的新图的结点数
    int _cnt, cnt;

    void _init()    //原图初始化
    {
        _cnt = 0;
        memset(_head, -1, sizeof(_head));
    }

    void init() //重构后新图的初始化
    {
        cnt = 0;
        memset(head, -1, sizeof(head));
    }

    inline void _addEdge(int u, int v, int w)   //原图的加边
    {
        _e[_cnt].to = v;
        _e[_cnt].cost = w;
        _e[_cnt].nxt = _head[u];
        _head[u] = _cnt++;
    }

    inline void addEdge(int u, int v, int w)    //重构后新图的加边
    {
        e[cnt].to = v;
        e[cnt].cost = w;
        e[cnt].nxt = head[u];
        head[u] = cnt++;
    }

    void delEdge(int u, int i)  //删除结点u的i号边
    {
        if(head[u] == i)
            head[u] = e[i].nxt;
        else    //跳过该边
            e[e[i].pre].nxt = e[i].nxt;
        if(tail[u] == i)    //指向u结点的最后一条边，相当于尾指针
            tail[u] = e[i].pre;
        else
            e[e[i].nxt].pre = e[i].pre; //双向链表修改前驱
    }

    void build(int u, int fa)   //重构新图，保证每个点的度都不超过2
    {
        int father = 0;
        for(int i = _head[u]; ~i; i = _e[i].nxt)
        {
            int v = _e[i].to, w = _e[i].cost;
            if(v != fa)
            {
                if(!father) //还没有增加子结点，直接连接
                {
                    addEdge(u, v, w);
                    addEdge(v, u, w);
                    father = u;
                }
                else    //已经有一个子结点，则新建一个虚拟结点，把结点v连新结点上
                {
                    //虚拟结点到父结点建立权值为0的边
                    node++;
                    addEdge(node, father, 0);
                    addEdge(father, node, 0);
                    //虚拟结点到子结点建立权值为w的边
                    father = node;
                    addEdge(v, father, w);
                    addEdge(father, v, w);
                }
                build(v, u);
            }
        }
    }

    inline void getPre()   //得到每条边的前驱，nxt是下一条边的编号，pre是上一条边的编号
    {
        memset(tail, -1, sizeof(tail));
        for(int i = 1; i <= node; i++)
        {
            for(int j = head[i]; ~j; j = e[j].nxt)
            {
                e[j].pre = tail[i];
                tail[i] = j;    //指向结点u的最后一条边，相当于尾指针
            }
        }
    }

    struct Point
    {
        int u, dis;
        Point() {}
        Point(int u, int dis) : u(u), dis(dis) {}
        bool operator < (const Point &p) const
        {
            return dis < p.dis; //优先弹出距离最小的点（保留距离最大的）
            //return dis > p.dis; //优先弹出距离最大的点（保留距离小的点）
        }
    };

    struct Node
    {
        int rt, midlen, ans;   //根结点，中心边权值，答案（最长树链）
        int ls, rs; //左右子树编号
        priority_queue<Point> pq;
    } tr[MAXN << 1];

    void dfsSize(int u, int fa, int d)  //求解每棵子树的大小，建立距离树
    {
        _addEdge(u, rt, d); //添加每个点到root的距离到距离树（有向边 u -> root）
        //if()  //根据题目条件让点入队
        tr[rt].pq.push(Point(u, d));
        sz[u] = 1;
        for(int i = head[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].to, w = e[i].cost;
            if(v != fa)
            {
                dfsSize(v, u, d + w);
                sz[u] += sz[v];
            }
        }
    }

    void dfsMidEdge(int u, int eid)  //找中心边
    {
        if(max(sz[u], sz[tr[rt].rt] - sz[u]) < maxval)
        {
            maxval = max(sz[u], sz[tr[rt].rt] - sz[u]); //sz[tr[rt].rt]为该子树的结点总数
            midedge = eid;  //中心边编号
        }
        for(int i = head[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].to;
            if(i != (eid ^ 1))  //不是中心边的反向边
                dfsMidEdge(v, i);   //递归寻找子树中的中心边
        }
    }

    void pushUp(int rt) //更新编号为id边的答案（根据题目要求进行修改）
    {
        //tr[rt].ans = -1;
        while(!tr[rt].pq.empty())   //优先队列弹出结点的条件
            tr[rt].pq.pop();
        /*int ls = tr[rt].ls, rs = tr[rt].rs; //ls为左儿子，rs为右儿子
        if(!ls && !rs)  //该结点没有左右儿子
        {
            //if()  //根据题目条件修改答案
            tr[rt].ans = 0;
        }
        else
        {
            if(tr[ls].ans > tr[rt].ans) //左儿子的答案大于根的答案
                tr[rt].ans = tr[ls].ans;
            if(tr[rs].ans > tr[rt].ans) //右儿子的答案大于根的答案
                tr[rt].ans = tr[rs].ans;
            if(!tr[ls].pq.empty() && !tr[rs].pq.empty())    //左右子树的优先队列都不为空
                tr[rt].ans = max(tr[rt].ans, tr[ls].pq.top().dis + tr[rs].pq.top().dis + tr[rt].midlen);    //左子树的最远距离+右子树的最远距离+中心边的长度
        }*/
    }

    void dfs(int u, int id) //边分治求解答案
    {
        rt = id, maxval = node, midedge = -1;
        tr[id].rt = u;
        dfsSize(u, 0, 0);   //dfs求解每棵子树的大小
        dfsMidEdge(u, -1);  //找中心边
        if(~midedge)
        {
            int p1 = e[midedge].to, p2 = e[midedge ^ 1].to; //中心边的两个端点
            tr[id].midlen = e[midedge].cost;    //中心边长度
            tr[id].ls = ++cnt, tr[id].rs = ++cnt;   //左右子树
            //删除中心边
            delEdge(p1, midedge ^ 1);
            delEdge(p2, midedge);
            dfs(p1, tr[id].ls);
            dfs(p2, tr[id].rs);
        }
        pushUp(id);
    }

    void update(int u)  //根据题意对结点进行修改
    {
        for(int i = _head[u]; ~i; i = _e[i].nxt)
        {
            int v = _e[i].to, w = _e[i].cost;
            //if()    //根据题目条件修改
            tr[v].pq.push(Point(u, w));
            pushUp(v);
        }
    }

    void buildGraph()   //建图
    {
        //
    }

    void solve(int n)
    {
        this -> n = n;
        _init(); //原树的初始化
        buildGraph();
        init(); //初始化原树
        node = n;
        build(1, 0);    //重建树
        getPre();   //得到每条边的前驱
        _init();    //重建树后的原树不再需要，将其初始化用来存储距离树
        dfs(1, cnt = 1);    //求解答案
    }
} edgediv;
