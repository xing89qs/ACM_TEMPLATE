//计算几何模板——半平面交

/**
目录:
#E1.半平面交
**/


/**
#E1.半平面交
需要条件：A1,A2,A3,A4,C1
**/
///模板待测！！！
/*直线版模板*/
//点p在有向直线L的左边（线上不算）
bool onLeft(const Line& L, const Point& p)
{
    return (L.v ^ (p-L.p)) > 0;
}
// 如果不介意边被修改 可以改为传引用
Polygon HalfplaneIntersection(vector<Line> L)
{
    int n = L.size();
    sort(L.begin(), L.end());   //按极角排序
    int first, last;    //双端队列的第一个元素和最后一个元素的下标
    vector<Point> p(n); //p[i]为q[i]和q[i+1]的交点
    vector<Line> q(n);  //双端队列
    Polygon ans;    //结果
    q[first=last=0] = L[0]; //双端队列初始化为只有一个半平面L[0]
    for(int i=1; i<n; i++)
    {
        while(first < last && !onLeft(L[i], p[last-1]))
            last--;
        while(first < last && !onLeft(L[i], p[first]))
            first++;
        q[++last] = L[i];
        if(fabs(q[last].v ^ q[last-1].v) < eps)
        {
            //两向量平行且同向 取内侧一个
            last--;
            if(onLeft(q[last], L[i].p))
                q[last] = L[i];
        }
        if(first<last)
            p[last-1] = LineIntersection(q[last-1], q[last]);
    }
    while(first<last && !onLeft(q[first], p[last-1]))
        last--;//删除无用平面
    if(last - first <= 1)
        return ans; // 空集
    //计算首尾两个半平面的交点
    p[last] = LineIntersection(q[last], q[first]);
    // 从deque复制到输出中
    for(int i = first; i <= last; i++)
        ans.push_back(p[i]);
    return ans;
}


/*有向直线版模板*/
//有向直线
struct DirLine
{
    Point p;    //直线上任意一点
    Vector v;   //方向向量，左边是对应半平面
    Type ang;   //极角
    DirLine() {}
    DirLine(Point p,Vector v):p(p),v(v)
    {
        ang = atan2(v.y,v.x);
    }
    bool operator <(const DirLine& l) const
    {
        return ang < l.ang;
    }
};

bool OnLeft(DirLine l,Point p)
{
    return dcmp(Cross(l.v,p-l.p)) > 0;
}

Point LineIntersection(DirLine &a,DirLine& b)
{
    Vector u = a.p - b.p;
    Type t = Cross(b.v,u) / Cross(a.v,b.v);
    return a.p + a.v * t;
}

Point halfP[MAXN<<1];
DirLine halfQ[MAXN<<1];

int HalfplaneIntersection(DirLine* l,int n,Point *poly)
{
    sort(l,l+n);
    int head,tail;
    DirLine *q = halfQ; //双端队列
    Point *p = halfP;   //p[i]表示q[i]和q[i+1]的交点
    halfQ[head = tail = 0] = l[0];
    for(int i=1; i<n; i++)
    {
        while(head < tail && !OnLeft(l[i],p[tail-1]))
            tail--;
        while(head < tail && !OnLeft(l[i],p[head]))
            head++;
        q[++tail] = l[i];
        if(dcmp(Cross(q[tail].v,q[tail-1].v)) == 0)
        {
            //两向量平行且同向，取内侧的一个
            tail--;
            if(OnLeft(q[tail],l[i].p))
                q[tail] = l[i];
        }
        if(head < tail)
            p[tail-1] = LineIntersection(q[tail-1],q[tail]);
    }
    while(head < tail && !OnLeft(q[head],p[tail-1]))
        tail--;
    if(tail - head <= 1)
        return 0;
    p[tail] = LineIntersection(q[tail],q[head]);
    int m = 0;
    for(int i=head; i<=tail; i++)
        poly[m++] = p[i];
    return m;
}
