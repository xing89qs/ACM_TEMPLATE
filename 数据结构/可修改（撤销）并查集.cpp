
const int MAXN = 100005;


/* 单点修改并查集 */

int fa[MAXN << 1], rk[MAXN << 1];   //结点数量（集合的秩）

void init(int n)
{
    for(int i = 1; i <= n; i++)
    {
        fa[i] = fa[i + n] = i + n;
        rk[i + n] = 1;
    }
}

int findSet(int x)
{
    if(x != fa[x])
        return fa[x] = findSet(fa[x]);
    return fa[x];
}

void unionSet(int x, int y)
{
    int fx = findSet(x);
    int fy = findSet(y);
    if(fx != fy)
    {
        //if(rk[fx] > rk[fy]) //可以不按秩合并
        //    swap(fx, fy);
        fa[fx] = fy;
        rk[fy] += rk[fx];
    }
}

void modifyNode(int x, int y)   //修改结点的归属集合（将结点x从原集合取出，加入到结点y所在的集合）
{
    int fx = findSet(x);
    int fy = findSet(y);
    if(fx != fy)
    {
        fa[x] = fy;
        rk[fx]--;
        rk[fy]++;
    }
}


/* 可撤销的并查集 */

//按秩合并，不可路径压缩
class Undo_DSU
{
public:
    int fa[MAXN << 1], rk[MAXN << 1]; //结点数量（集合的秩）
    PII sta[MAXN << 1];  //手动模拟栈
    int top;
    //stack<PII> sta;

    void init(int n)
    {
        top = -1;
        //while(!sta.empty())
        //    sta.pop();
        for(int i = 1; i <= n; i++)
        {
            fa[i] = i;
            rk[i] = 1;
        }
    }

    int findSet(int x)
    {
        if(x != fa[x])
            return findSet(fa[x]);  //不可路径压缩
        return x;   //return fa[x];
    }

    bool unionSet(int x, int y)
    {
        int fx = findSet(x);
        int fy = findSet(y);
        if(fx == fy)
            return false;
        if(rk[fx] > rk[fy])
        {
            swap(fx, fy);
            swap(x, y);
        }
        fa[fx] = fy;    //按秩合并
        rk[fy] += rk[fx];
        sta[++top] = MP(fx, fy);
        //sta.push(MP(fx, fy));
        return true;
    }

    void undo()
    {
        /*if(!sta.empty())
        {
            PII cur = sta.top();
            sta.pop();
        */
        if(~top)    //有可以撤销的合并记录
        {
            PII cur = sta[top--];
            fa[cur.first] = cur.first;
            rk[cur.second] -= rk[cur.first];
        }
    }
} dsu;
