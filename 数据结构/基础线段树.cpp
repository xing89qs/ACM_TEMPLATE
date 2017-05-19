
#define LL long long
#define MAXN 100005
#define INF 0x3f3f3f3f

typedef LL Type;

class SegTree
{
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

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

    void PushDown(int rt,Type val)    //这就是延迟操作，更新当前结点的叶子
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

    void PushUP(int rt)
    {
        Max[rt] = max(Max[rt<<1], Max[rt<<1|1]);
        Min[rt] = min(Min[rt<<1], Min[rt<<1|1]);
        Sum[rt] = Sum[rt<<1] + Sum[rt<<1|1];
    }

    void build(Type l,Type r,int rt)  //建树
    {
        Lazy[rt] = 0;
        if(l == r)
        {
            scanf("%d",&Max[rt]);
            Min[rt] = Max[rt];
            Sum[rt] = Max[rt];
            return ;
        }
        Type m = (l + r) >> 1;
        build(lson);
        build(rson);
        PushUP(rt);
    }

    //调用方式：function(cur, val, left, right, nodeid);
    //cur--原来的点，val--更新、询问等操作的有关值，left--更新的左边界，right--更新的右边界，nodeid--结点编号
    void updateNode(Type p,Type val,Type l,Type r,int rt)    //单点更新（替换）
    {
        if(l == r)
        {
            Max[rt] = val;
            Min[rt] = val;
            Sum[rt] = val;
            return ;
        }
        Type m = (l + r) >> 1;
        if(p <= m)
            updateNode(p, val, lson);
        else
            updateNode(p, val, rson);
        PushUP(rt);
    }

    void addNode(Type p,Type val,Type l,Type r,int rt)  //单点增加
    {
        if(l == r)
        {
            Sum[rt] = Sum[rt] + val;
            return ;
        }
        int m = (l + r) >> 1;
        if(p <= m)
            addNode(p, val, lson);
        else
            addNode(p, val, rson);
        PushUP(rt);
    }

    void subNode(Type p,Type val,Type l,Type r,int rt)  //单点减少
    {
        if(l == r)
        {
            Sum[rt] = Sum[rt] - val;
            return ;
        }
        Type m = (l + r) >> 1;
        if(p <= m)
            subNode(p, val, lson);
        else
            subNode(p, val, rson);
        PushUP(rt);
    }

    void updateInterval(Type L,Type R,Type val,Type l,Type r,int rt)    //区间更新
    {
        if(L <= l && r <= R)
        {
            Lazy[rt] += val;
            Sum[rt] += val * (r - l + 1);
            return ;
        }
        PushDown(rt,r-l+1);//向下更新枝叶的值
        Type m = (l + r) >> 1;
        if(L <= m)
            updateInterval(L,R,val,lson);
        if(R > m)
            updateInterval(L,R,val,rson);
        PushUp(rt);
    }

    Type queryMax(Type L,Type R,Type l,Type r,int rt)    //区间求最大值
    {
        if(L <= l && r <= R)
        {
            return Max[rt];
        }
        int m = (l + r) >> 1;
        int ret = -1;
        if(L <= m)
            ret = max(ret, queryMax(L, R, lson));
        if(R > m)
            ret = max(ret, queryMax(L, R, rson));
        return ret;
    }

    Type queryMin(Type L,Type R,Type l,Type r,int rt)    //区间求最小值
    {
        if(L <= l && r <= R)
        {
            return Min[rt];
        }
        Type m = (l + r) >> 1;
        Type ret = INF;
        if(L <= m)
            ret = min(ret, queryMin(L, R, lson));
        if(R > m)
            ret = min(ret, queryMin(L, R, rson));
        return ret;
    }

    Type querySum(Type L,Type R,Type l,Type r,int rt)    //区间求和
    {
        if(L <= l && r <= R)
        {
            return Sum[rt];
        }
        //PushDown(rt,r-l+1);   //区间更新中的区间查找需要加上这一句
        Type m = (l + r) >> 1;
        Type ret = 0;
        if(L <= m)
            ret += querySum(L, R, lson);
        if(R > m)
            ret += querySum(L, R, rson);
        return ret;
    }
} segtree;

