//计算几何模板——多边形和凸包相关算法

/**
目录:
#C1.多边形定义
#C2.多边形的有向面积
#C3.点在多边形内判定
#C4.多边形重心
#C5.圆和三角形相交的面积（三角形的一个顶点为圆心）
#C6.圆和多边形相交的面积（利用三角剖分）
#C7.返回圆盘是否与多边形相交
#C8.删除平面的三点共线
#C9.有向直线切割多边形
#C10.求点集凸包
#C11.判断是否是凸包（向量法判断）
#C12.判断圆是否在多边形内
**/


/**
#C1.多边形定义
需要条件：A1
**/
typedef vector<Point> Polygon;  //组成该平面的逆时针点集


/**
#C2.多边形的有向面积（点逆时针旋转为正向，顺时针将求出负值）
需要条件：A1,C1
**/
double PolygonArea(Polygon &poly)
{
    if(poly.size() == 0)
        return 0;
    double area = 0;
    for(int i=1; i<poly.size()-1; i++)
        area += ((poly[i] - poly[0]) ^ (poly[i + 1] - poly[0]));
    return area / 2;
}


/**
#C3.点在多边形内判定（有弧边也可以使用）
需要条件：A1,A3,A8,C1
**/
int isPointInPolygon(Point p,Polygon &poly)
{
    int wn = 0;
    int n = poly.size();
    for(int i = 0; i < n; i++)
    {
        Segment seg(poly[i],poly[(i+1)%n]);
        if(OnSegment(p,seg))
            return -1;  //在多边形边界上
        int k = dcmp((poly[(i+1)%n] - poly[i]) ^ (p - poly[i]));
        int d1 = dcmp(poly[i].y - p.y);
        int d2 = dcmp(poly[(i+1)%n].y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0)
            wn++;
        if(k < 0 && d2 <= 0 && d1 > 0)
            wn--;
    }
    if(wn)
        return 1;   //在多边形内部
    return 0;   //在多边形外部
}


/**
#C4.多边形重心
需要条件：A1,C1
**/
//调用之前应先求得凸包
Point getPolygonCenterOfGravity(Polygon &poly)
{
    int n = poly.size();
    Point ret;
    double area = 0, area2;
    for(int i=1; i<n; i++)
    {
        area2 = (poly[i-1] ^ poly[i]);  //上下都取面积的2倍, 被约掉
        ret = ret + (poly[i-1] + poly[i]) * area2;
        area += area2;
    }
    area2 = (poly[n-1] ^ poly[0]);
    ret = ret + (poly[n-1] + poly[0]) * area2;
    area += area2;
    return ret / (area * 3);
}


/**
#C5.圆和三角形相交的面积（三角形的一个顶点为圆心）
需要条件：A1, A2, A3, B1, B3, C1
**/
double CircleTriangleIntersectionArea(Circle c, Point a, Point b)   //三角形abc与圆心c所围成的面积
{
    double r = c.r;
    if(dcmp((c.p - a) ^ (c.p - b)) == 0)
        return 0.0;
    vector<Point> p, tmp;
    p.PB(a);
    Line l(a, b);
    if(getLineCircleIntersection(l, c, tmp) == 2)   //直线和圆的位置关系  0:相离   1:相切   2:相交
    {
        if(dcmp((a - tmp[0]) * (b - tmp[0])) < 0)
            p.PB(tmp[0]);
        if(dcmp((a - tmp[1]) * (b - tmp[1])) < 0)
            p.PB(tmp[1]);
    }
    p.PB(b);
    if(sz(p) == 4 && dcmp((p[0] - p[1]) * (p[2] - p[1])) > 0)
        swap(p[1], p[2]);
    double res = 0.0;
    for(int i = 0; i < sz(p) - 1; i++)
    {
        Vector v1 = p[i] - c.p, v2 = p[i + 1] - c.p;
        if(dcmp(Length(v1) - c.r) > 0 || dcmp(Length(v2) - c.r) > 0)
        {
            double arg = Angle(v1, v2);
            res += c.r * c.r * arg / 2.0;
        }
        else
            res += fabs((v1 ^ v2) / 2.0);
    }
    return res;
}


/**
#C6.圆和多边形相交的面积（利用三角剖分）
需要条件：A1, C1, C5
**/
double CirclePolygonIntersectionArea(Circle c, Polygon &poly)
{
    double ret = 0;
    for(int i = 0; i < sz(poly); i++)
    {
        Vector v1 = poly[i] - c.p, v2 = poly[(i + 1) % sz(poly)] - c.p;
        ret += 1.0 * dcmp(v1 ^ v2) * CircleTriangleIntersectionArea(c, poly[i], poly[(i + 1) % sz(poly)]);
    }
    return fabs(ret);
}


/**
#C7.返回圆盘是否与多边形相交
需要条件：A1,A2 7 10 12 13 14 15 C1,C3
**/
///模板待测！！！
bool DiscIntersectPolygon(Polygon poly,Point p,double R)
{
    if(isPointInPolygon(p,poly))
        return true;
    if(isInCircle(poly[0],p,R))
        return true;
    int n = poly.size();
    for(int i=0; i<n; i++)
    {
        if(CircleIntersectSegment(poly[i],poly[(i+1)%n],p,R))
            return true;    //不考虑线段端点
        if(isInCircle((poly[i]+poly[(i+1)%n])/2.0,p,R))
            return true;    //两个端点都在圆上
    }
    return false;
}


/**
#C8.删除平面的三点共线
需要条件：A1,C1
**/
///模板待测！！！
//假定poly没有相邻点重合的情况，只需要删除三点共线的情况
Polygon DeleteCollinearPoints(Polygon &poly)
{
    Polygon ans;
    int n = poly.size();
    //测试每一个点是否和前后两点共线，如果不是就加入
    for(int i = 0; i < n; i++)
    {
        Point a = poly[i];
        Point b = poly[(i+1)%n];
        Point c = poly[(i+2)%n];
        if(dcmp((a-b)^(c-b)))
            ans.PB(b);
    }
    return ans;
}


/**
#C9.有向直线切割多边形
需要条件：A1 A3 A4 A8 C1
**/
//用有向直线A->B切割多边形poly，返回“左侧”。 如果退化，可能会返回一个单点或者线段
Polygon CutPolygon(Polygon& poly,Point A,Point B)
{
    Polygon newpoly;
    int n = poly.size();
    for(int i = 0; i < n; i++)
    {
        Point C = poly[i];
        Point D = poly[(i+1)%n];
        if(dcmp((B-A)^(C-A)) >= 0)
            newpoly.PB(C);
        if(dcmp((B-A)^(C-D)) != 0)
        {
            Line l1 = Line(A,B);
            Line l2 = Line(C,D);
            Point ip = LineIntersection(l1,l2);
            Segment seg = Segment(C,D);
            if(OnSegment(ip,seg))
                newpoly.PB(ip);
        }
    }
    return newpoly;
}


/**
#C10.Andrew算法求点集凸包
需要条件：A1
**/
/*C10.1: 求得的凸包存在 vector<Point> ch 内*/
//如果不希望在凸包的边上有输入点，把两个 <= 改成 < （说明：这里lrj可能写错了，应该是凸包边上无点：<= ；有点：<）
//如果不介意点集被修改，可以改成传递引用（不能修改就去掉&）
int ConvexHull(vector<Point> &p,vector<Point> &ch)
{
    sort(p.begin(),p.end());    //两个点比大小，先横坐标再纵坐标，升序
    int n = unique(p.begin(),p.end()) - p.begin();//删除重复点
    int m = 0;
    ch.resize(n+1);
    for(int i=0; i<n; i++)  //找到下凸包
    {
        while(m > 1 && dcmp((ch[m-1]-ch[m-2])^(p[i]-ch[m-2])) <= 0)
            m--;
        ch[m++] = p[i]; //发现右边的点时删除前面的点，再更新
    }
    int k = m;  //下凸包点数，找上凸包时防止误删
    for(int i=n-2; i>=0; i--)
    {
        while(m > k && dcmp((ch[m-1]-ch[m-2])^(p[i]-ch[m-2])) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    ch.resize(m);
    return m;  //返回的点集逆时针排序
}

/*C10.2: 求得的凸包存在 Point *ch 内*/
//求凸包，如果不希望凸包边上有输入点，把<=改成< （说明：这里lrj可能写错了，应该是凸包边上无点：<= ；有点：<）
int ConvexHull(Point *p,int n,Point *ch)
{
    sort(p,p+n);
    n = unique(p,p+n) - p;    //删除重复点
    int m = 0;
    for(int i=0; i<n; i++)
    {
        while(m > 1 && dcmp((ch[m-1]-ch[m-2])^(p[i]-ch[m-2])) <= 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i=n-2; i>=0; i--)
    {
        while(m > k && dcmp((ch[m-1]-ch[m-2])^(p[i]-ch[m-2])) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    return m;
}


/**
#C11.判断是否是凸包（向量法判断）
需要条件：A1
**/
bool isConvexHull(Point *p,int n)
{
    int flag = 0;   //记录顺时针还是逆时针
    for(int i=0; i<n; i++)
    {
        int temp = dcmp((p[(i+1)%n] - p[i%n]) ^ (p[(i+2)%n] - p[(i+1)%n]));
        if(!flag)
            flag = temp;
        if(flag * temp < 0)
            return false;
    }
    return true;
}


/**
#C12.判断圆是否在多边形内
需要条件：A1,A5,B1,C1
**/
//如果圆边界上的点可以与凸包的边重合，则把<改为<=
bool isCircleInPolygon(Circle C,int n,Polygon &poly)
{
    for(int i=0; i<n; i++)
    {
        if(dcmp(DistanceToLine(C.p,Line(poly[i%n],poly[(i+1)%n]))-C.r)<0)
            return false;
    }
    return true;
}
