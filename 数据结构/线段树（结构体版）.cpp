//线段树（结构体版）

typedef LL Type;

struct Node
{
    int l,r;
    Type sum,lazy;
} tree[MAXN<<2];

void pushUp(int rt)
{
    tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
}

void build(int l,int r,int rt)  //建树
{
    tree[rt].l = l, tree[rt].r = r;
    if(tree[rt].l == tree[rt].r)
    {
        scanf("%d",&tree[rt].sum);
        return;
    }
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
    pushUp(rt);
}

void pushDown(int rt)// 标记下传
{
    if(tree[rt].lazy)
    {
        tree[rt<<1].lazy += tree[rt].lazy;
        tree[rt<<1|1].lazy += tree[rt].lazy;
        tree[rt<<1].sum += tree[rt].lazy * (tree[rt<<1].r - tree[rt<<1].l + 1);
        tree[rt<<1|1].sum += tree[rt].lazy * (tree[rt<<1|1].r - tree[rt<<1|1].l + 1);
        tree[rt].lazy = 0;
    }
}

Type queryPoint(Type val,int rt)  //单点查询
{
    if(tree[rt].l == tree[rt].r)
        return tree[rt].sum;
    pushDown(rt);
    int mid = tree[rt].l + (tree[rt].r - tree[rt].l) >> 1;
    if(x <= mid)
        return queryPoint(val,rt<<1);
    else
        return queryPoint(val,rt<<1|1);
}

void updatePoint(int x,Type val,int rt)  //单点修改
{
    if(tree[rt].l == tree[rt].r)
    {
        tree[rt].sum += val;
        return;
    }
    int mid = tree[rt].l + (tree[rt].r - tree[rt].l) >> 1;
    if(x <= mid)
        updatePoint(x,val,rt<<1);
    else
        updatePoint(x,val,rt<<1|1);
    pushUp(rt);
}

Type queryInterval(int ll,int rr,int rt)   //区间查询
{
    if(ll <= tree[rt].l && tree[rt].r <= rr)
        return tree[rt].sum;
    pushDown(rt);
    int mid = tree[rt].l + (tree[rt].r - tree[rt].l) >> 1;
    Type ans = 0;
    if(ll <= mid)
        ans += queryInterval(ll,rr,rt<<1);
    if(rr > mid)
        ans += queryInterval(ll,rr,rt<<1|1);
    return ans;
}

void updateInterval(Type val,int ll,int rr,int rt)  //区间修改
{
    if(ll <= tree[rt].l && tree[rt].r <= rr)
    {
        tree[rt].sum += val * (tree[rt].r - tree[rt].l + 1);
        tree[rt].lazy += val;
        return ;
    }
    pushDown(rt);
    int mid = tree[rt].l + (tree[rt].r - tree[rt].l) >> 1;
    if(ll <= mid)
        updateInterval(val,ll,rr,rt<<1);
    if(rr > mid)
        updateInterval(val,ll,rr,rt<<1|1);
    pushUp(rt);
}

int main()
{
    scanf("%d",&n); //n个节点
    build(1,1,n);   //建树
    scanf("%d",&m); //m种操作
    for(int i=1; i<=m; i++)
    {
        scanf("%d",&p);
        ans=0;
        if(p==1)
        {
            scanf("%d",&x);
            queryPoint(1);//单点查询,输出第x个数
            printf("%d",ans);
        }
        else if(p==2)
        {
            scanf("%d%d",&x,&y);
            updatePoint(1);//单点修改
        }
        else if(p==3)
        {
            scanf("%d%d",&a,&b);//区间查询
            queryInterval(1);
            printf("%d\n",ans);
        }
        else
        {
            scanf("%d%d%d",&a,&b,&y);//区间修改
            updateInterval(1);
        }
    }
}


//线段树+离散化
typedef int Type;

struct Node
{
    int l,r;
    Type sum,lazy;
} tree[MAXN<<3];

struct DiscreteNode
{
    int x,y,op;
} data[MAXN<<1];    //离散化用

int Hash[MAXN<<1];  //对应离散化前点的序号
int pref[MAXN<<1];  //前缀和数组

void pushDown(int rt)
{
    int l = tree[rt].l, r = tree[rt].r;
    int mid = (l + r) >> 1;
    if(~tree[rt].lazy)
    {
        tree[rt<<1].sum = tree[rt].lazy * (Hash[mid+1] - Hash[l]);
        tree[rt<<1|1].sum = tree[rt].lazy * (Hash[r+1] - Hash[mid+1]);
        tree[rt<<1].lazy = tree[rt<<1|1].lazy = tree[rt].lazy;
        tree[rt].lazy = -1;
    }
}

void pushUp(int rt)
{
    tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
}

void build(int l,int r,int rt)
{
    tree[rt].l = l, tree[rt].r = r;
    tree[rt].lazy = -1;
    if(l == r)
    {
        tree[rt].sum = pref[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
    pushUp(rt);
}

void updateInterval(Type val,int ll,int rr,int rt)
{
    int l = tree[rt].l, r = tree[rt].r;
    if(ll <= tree[rt].l && tree[rt].r <= rr)
    {
        tree[rt].sum = val * (Hash[r+1] - Hash[l]);
        tree[rt].lazy = val;
        return ;
    }
    pushDown(rt);
    int mid = (l + r) >> 1;
    if(ll <= mid)
        updateInterval(val,ll,rr,rt<<1);
    if(rr > mid)
        updateInterval(val,ll,rr,rt<<1|1);
    pushUp(rt);
}

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    /*sort+unique离散化*/
    int cnt=0;
    for(int i=1; i<=q; i++)
    {
        scanf("%d%d%d",&data[i].x,&data[i].y,&data[i].op);
        Hash[++cnt]=data[i].x;
        Hash[++cnt]=++data[i].y;
    }
    Hash[++cnt]=1;
    Hash[++cnt]=n+1;
    sort(Hash+1,Hash+1+cnt);
    cnt=unique(Hash+1,Hash+1+cnt)-Hash-1;
    cnt--;
    for(int i=1; i<=cnt; i++)
        pref[i] = Hash[i+1] - Hash[i];
    for(int i=1; i<=q; i++)
    {
        data[i].x=lower_bound(Hash+1,Hash+1+cnt,data[i].x)-Hash;
        data[i].y=lower_bound(Hash+1,Hash+1+cnt,data[i].y)-Hash-1;
    }
    build(1,cnt,1);
    for(int i=1; i<=q; i++)
    {
        updateInterval(data[i].op-1,data[i].x,data[i].y,1);
        printf("%d\n",tree[1].sum);
    }
    return 0;
}
