
#define MAXN 100005

typedef LL Type;

class SegTree
{
public:
    Type Max[MAXN<<2];
    Type Min[MAXN<<2];
    Type Sum[MAXN<<2];
    Type Lazy[MAXN<<2];

    void init() //初始化（Sum数组和Lazy数组不必初始化）
    {
        memset(Max,0,sizeof(Max));
        memset(Min,0,sizeof(Min));
    }

    void pushDown(int rt,Type val)    //这就是延迟操作，更新当前结点的叶子
    {
        if(Lazy[rt])
        {
            Sum[rt<<1] += Lazy[rt] * (val - (val >> 1));//每个点的需要更新的值乘以的个数
            Sum[rt<<1|1] += Lazy[rt] * (val >> 1);//同上
            Lazy[rt<<1] += Lazy[rt];//这个区间需要更新的个数
            Lazy[rt<<1|1] += Lazy[rt];
            Lazy[rt] = 0;
        }
    }

    void pushUp(int rt)
    {
        Max[rt] = max(Max[rt<<1], Max[rt<<1|1]);
        Min[rt] = min(Min[rt<<1], Min[rt<<1|1]);
        Sum[rt] = Sum[rt<<1] + Sum[rt<<1|1];
    }

    void build(int l,int r,int rt)  //建树
    {
        Lazy[rt] = 0;
        if(l == r)
        {
            scanf("%d",&Max[rt]);
            Min[rt] = Max[rt];
            Sum[rt] = Max[rt];
            return ;
        }
        int mid = (l + r) >> 1;
        build(lson);
        build(rson);
        pushUp(rt);
    }

    //调用方式：function(cur, val, left, right, nodeid);
    //cur--原来的点，val--更新、询问等操作的有关值，left--更新的左边界，right--更新的右边界，nodeid--结点编号
    void updateNode(int x,Type val,int l,int r,int rt)    //单点更新（替换）
    {
        if(l == r)
        {
            Max[rt] = val;
            Min[rt] = val;
            Sum[rt] = val;
            return ;
        }
        int mid = (l + r) >> 1;
        if(x <= mid)
            updateNode(x, val, lson);
        else
            updateNode(x, val, rson);
        pushUp(rt);
    }

    void modifyNode(int x,Type val,int l,int r,int rt)  //单点增减
    {
        if(l == r)
        {
            Sum[rt] += val;
            return ;
        }
        int mid = (l + r) >> 1;
        if(x <= mid)
            addNode(x, val, lson);
        else
            addNode(x, val, rson);
        pushUp(rt);
    }

    Type queryNode(int x,int l,int r,int rt)  //单点查询
    {
        if(l == r)
            return Sum[rt];
        //pushDown(rt,r-l+1);
        int mid = (l + r) >> 1;
        if(x <= mid)
            return queryPoint(val,lson);
        else
            return queryPoint(val,rson);
    }

    void updateInterval(int L,int R,Type val,int l,int r,int rt)    //区间更新
    {
        if(L <= l && r <= R)
        {
            Lazy[rt] += val;
            Sum[rt] += val * (r - l + 1);
            return ;
        }
        pushDown(rt,r-l+1); //向下更新枝叶的值
        int mid = (l + r) >> 1;
        if(L <= mid)
            updateInterval(L,R,val,lson);
        if(R > mid)
            updateInterval(L,R,val,rson);
        pushUp(rt);
    }

    Type queryMax/Min(int L,int R,int l,int r,int rt)   //区间求最值
    {
        if(L <= l && r <= R)
            return Max/Min[rt];
        int mid = (l + r) >> 1;
        Type ret = -1/INF/LINF;
        if(L <= mid)
            ret = max/min(ret, queryMax/Min(L, R, lson));
        if(R > mid)
            ret = max/min(ret, queryMax/Min(L, R, rson));
        return ret;
    }

    Type querySum(int L,int R,int l,int r,int rt)    //区间求和
    {
        if(L <= l && r <= R)
            return Sum[rt];
        pushDown(rt,r-l+1); //向下更新枝叶的值
        int mid = (l + r) >> 1;
        Type ret = 0;
        if(L <= mid)
            ret += querySum(L, R, lson);
        if(R > mid)
            ret += querySum(L, R, rson);
        return ret;
    }
} segtree;


/*离散化 + 线段树*/
typedef int Type;

Type a[MAXN];
Type col[MAXN<<3];  //???这里写成MAXN<<2会WA???
bool vis[MAXN];  //某种颜色是否都被使用
int Hash[MAXN<<1];
int ans;

struct DiscreteNode
{
    int x,y;
} data[MAXN];

void pushDown(int rt)
{
    if(~col[rt])
    {
        col[rt<<1] = col[rt<<1|1] = col[rt];
        col[rt] = -1;
    }
}

void update(Type val,int L,int R,int l,int r,int rt)
{
    if(L <= l && r <= R)
    {
        col[rt] = val;
        return ;
    }
    pushDown(rt);
    int mid = (l + r) >> 1;
    if(L <= mid)
        update(val,L,R,lson);
    if(R > mid)
        update(val,L,R,rson);
}

void query(int l,int r,int rt)
{
    if(~col[rt])    //该结点已被上色
    {
        if(!vis[col[rt]])   //该颜色还没有被统计过
        {
            ans++;
            vis[col[rt]] = true;
        }
        return ;    //返回，因为无论其子结点有没有颜色都只能说明下面的海报都被这一层的海报覆盖了
    }
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    query(lson);
    query(rson);
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        memset(col,-1,sizeof(col));
        memset(vis,false,sizeof(vis));
        int cnt=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d",&data[i].x,&data[i].y);
            Hash[++cnt]=data[i].x;
            Hash[++cnt]=++data[i].y;
        }
        Hash[++cnt]=1;
        Hash[++cnt]=10000001;
        sort(Hash+1,Hash+1+cnt);
        cnt=unique(Hash+1,Hash+1+cnt)-Hash-1;
        cnt--;
        for(int i=1; i<=n; i++)
        {
            int x=lower_bound(Hash+1,Hash+1+cnt,data[i].x)-Hash;
            int y=lower_bound(Hash+1,Hash+1+cnt,data[i].y)-Hash-1;
            update(i,x,y,1,cnt,1);
        }
        ans=0;
        query(1,cnt,1);
        printf("%d\n",ans);
    }
    return 0;
}
