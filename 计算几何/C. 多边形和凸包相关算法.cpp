//计算几何模板——多边形和凸包相关算法

/**
目录:
#C1.多边形定义
#C2.多边形的有向面积
#C3.点在多边形内判定
#C4.多边形重心
#C5.圆和凸多边形相交的面积
#C6.返回圆盘是否与多边形相交
#C7.删除平面的三点共线
#C8.有向直线切割多边形
#C9.求点集凸包
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
需要条件：A1,7,C1
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
#C5.圆和凸多边形相交的面积（圆心必须在凸多边形内部，不含边）
需要条件：A1,A2 10 12 14 28,C1
**/
double CirclePolygonIntersectionArea(Circle C, Polygon &poly)
{
    poly.push_back(poly[0]);
    double ret = 0;
    for (int i=0; i<poly.size()-1; i++)
    {
        bool flag1 = (dcmp(Length(C.c - poly[i]) - C.r) <= 0);
        bool flag2 = (dcmp(Length(C.c - poly[i+1]) - C.r) <= 0);
        if(flag1 + flag2 == 2)   //两个点都在圆内 算三角形
        {
            ret += fabs((poly[i] - C.c) ^ (poly[i+1] - C.c)) / 2.0;
            continue;
        }
        vector <Point> sol;
        int num = getSegmentCircleIntersection(poly[i],poly[i+1],C,sol);
        if(flag1 + flag2 == 1)  //一个点在圆内一个点在圆外
        {
            if(flag1)
            {
                ret += C.r * C.r * Angle(poly[i+1]-C.c,sol[0]-C.c) / 2.0 + fabs((poly[i]-C.c)^(sol[0]-C.c)) / 2.0;
                continue;
            }
            ret += C.r * C.r * Angle(poly[i]-C.c,sol[0]-C.c) / 2.0 + fabs((poly[i+1]-C.c)^(sol[0]-C.c)) / 2.0;
            continue;
        }
        //两个点都在圆外
        if (num == 2)
        {
            ret += C.r * C.r * (Angle(poly[i]-C.c,sol[0]-C.c) + Angle(poly[i+1]-C.c,sol[1]-C.c)) / 2.0 + fabs((sol[0]-C.c)^(sol[1]-C.c)) / 2.0;
            continue;
        }
        ret += C.r * C.r * Angle(poly[i]-C.c,poly[i+1]-C.c) / 2.0;
    }
    P.pop_back();
    return ret;
}


/**
#C6.返回圆盘是否与多边形相交
需要条件：A1,A2 7 10 12 13 14 15 C1,C3
**/
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
#C7.删除平面的三点共线
需要条件：A1,C1
**/
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
#C8.有向直线切割多边形
需要条件：A1 3 7 C1
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
            Point ip = LineIntersection(A, B-A, C, D-C);
            if(OnSegment(ip, C, D))
                newpoly.PB(ip);
        }
    }
    return newpoly;
}


/**
#C9.Andrew算法求点集凸包
需要条件：A1
**/
/*C9.1: 求得的凸包存在 vector<Point> ch 内*/
//如果不希望在凸包的边上有输入点，把两个 <= 改成 <
//如果不介意点集被修改，可以改成传递引用（不能修改就去掉&）
int ConvexHull(vector<Point> &p,vector<Point> &ch)
{
    sort(p.begin(),p.end());    //两个点比大小，先横坐标再纵坐标，升序
    int n = unique(p.begin(),p.end()) - p.begin();//删除重复点
    int m = 0;
    ch.resize(n+1);
    for(int i=0; i<n; i++)  //找到下凸包
    {
        while(m > 1 && ((ch[m-1] - ch[m-2]) ^ (p[i] - ch[m-2])) <= 0)
            m--;
        ch[m++] = p[i]; //发现右边的点时删除前面的点，再更新
    }
    int k = m;  //下凸包点数，找上凸包时防止误删
    for(int i=n-2; i>=0; i--)
    {
        while(m > k && ((ch[m-1] - ch[m-2]) ^ (p[i] - ch[m-2])) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    ch.resize(m);
    return m;  //返回的点集逆时针排序
}

/*C9.2: 求得的凸包存在 Point *ch 内*/
//求凸包，如果不希望凸包边上有输入点，把<=改成<
int ConvexHull(Point *p,int n,Point *ch)
{
    sort(p,p+n);
    int n = unique(p,p+n) - p;    //删除重复点
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
