//计算几何模板——圆相关算法

/**
目录:
#B1.圆的定义
#B2.判断点在圆内
#B3.直线与圆的交点
#B4.线段与圆相交判定
#B5.线段和圆的交点
#B6.两圆交点
#B7.两圆面积交
#B8.把角变成0~2PI范围内
#B9.求圆过某一点的所有切线
#B10.求两圆的公切线
#B11.三角形外接圆
#B12.三角形内切圆
#B13.过某一点与直线相切的圆
#B14.与两条直线相切的圆
#B15.与两圆相切的圆
**/


/**
#B1.圆的定义
需要条件：A1
**/
struct Circle
{
    Point p;
    Type r;
    Circle(Point p,Type r):p(p),r(r) {}
    Circle() {}
    Point polarCoordinates(double a)    //求圆边界上某个点相对于圆心的极角坐标
    {
        return Point(p.x + cos(a) * r, p.y + sin(a) * r);
    }
    void read()
    {
        p.read();
        scanf("%lf", &r);
    }
};


/**
#B2.判断点在圆内（圆周上不算）
需要条件：A1,B1
**/
bool isInCircle(Point p, Circle C)
{
    return dcmp((p - C.p) * (p - C.p) - C.r * C.r) < 0;
}


/**
#B3.直线与圆的交点
需要条件：A1,B1
**/
//t1,t2为两个记录变量的参数，使用该函数前定义即可
int getLineCircleIntersection(Line L,Circle C,double& t1,double& t2,vector<Point>& sol)
{
    //t1,t2为从L.p出发的长度，sol保存结果，返回值为交点个数
    double a = L.v.x, b = L.a.x - C.p.x,
           c = L.v.y, d = L.a.y - C.p.y;
    double e = a * a + c * c, f = 2 * (a * b + c * d),
           g = b * b + d * d - C.r * C.r;
    double delta = f * f - 4 * e * g;   //判别式
    if(dcmp(delta) < 0) //相离
        return 0;
    if(dcmp(delta) == 0)    //相切
    {
        t1 = t2 = -f / (2 * e);
        sol.PB(L.a + v * t1);
        return 1;
    }
    //相交
    t1 = (-f - sqrt(delta)) / (2 * e);
    if(dcmp(t1-1) <= 0 && dcmp(t1) >= 0)  //这条判断表示线段
        sol.PB(L.a + L.v * t1);
    t2 = (-f + sqrt(delta)) / (2 * e);
    if(dcmp(t2-1) <= 0 && dcmp(t2) >= 0)  //这条判断表示线段
        sol.PB(L.a + L.v * t2);
    return 2;
}

void getLineCircleIntersection(Line L,Circle C,vector<Point>& ret)
{
    Vector v = L.b - L.a;
    Type a = v.x, b = L.a.x - C.p.x, c = v.y, d = L.a.y - C.p.y;
    Type e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - C.r * C.r;
    Type delta = f * f - 4 * e * g;
    Type t1, t2;
    if(dcmp(delta) < 0) //相离
        return;
    if(dcmp(delta) == 0)    //相切
    {
        t1 = t2 = -f / (2 * e);
        ret.PB(L.a + v * t1);
    }
    else
    {
        t1 = (-f - sqrt(delta)) / (2 * e);
        if(dcmp(t1-1) <= 0 && dcmp(t1) >= 0)  //这条判断表示线段
            ret.PB(L.a + v * t1);
        t2 = (-f + sqrt(delta)) / (2 * e);
        if(dcmp(t2-1) <= 0 && dcmp(t2) >= 0)  //这条判断表示线段
            ret.PB(L.a + v * t2);
    }
}


/**
#B4.线段与圆相交判定（相切不算）
需要条件：A1,A2,B1,B3
**/
///模板待测！！！
//线段不考虑端点
bool CircleIntersectSegment(Segment s,Circle C)
{
    double t1, t2;
    vector<Point> sol;  //线段与圆的交点
    int c = getLineCircleIntersection(Line(s.a,s.b),C,t1,t2,sol);
    if(c <= 1)
        return false;
    if(dcmp(t1) > 0 && dcmp(t1-1) < 0)
        return true;    //端点在圆上
    if(dcmp(t2) > 0 && dcmp(t2-1) < 0)
        return true;
    return false;
}

//##28##: 线段和圆的交点 结果保存在sol中
//需要条件: 1 2 10 12 14
/**
#B5.线段和圆的交点
需要条件：A1,A2,A3,B1,B3
**/
///模板待测！！！
//结果保存在sol中
int getSegmentCircleIntersection(Line L,Circle C,vector<Point>& sol)
{
    double t1, t2;
    vector<Point> tmp;
    int m = getLineCircleIntersection(L,C,t1,t2,tmp);
    if(m == 0)
        return 0;
    if(m <= 2)
    {
        if(dcmp((L.a-tmp[0])*(L.b-tmp[0])) <= 0)
            sol.PB(tmp[0]);
        if(m == 1)
            return sol.size();
    }
    if(dcmp((L.a-tmp[1])*(L.b-tmp[1])) <= 0)
        sol.PB(tmp[1]);
    return sol.size();
}


/**
#B6.两圆交点
需要条件：A1,A2,B1
**/
int getTwoCirclesIntersection(Circle c1,Circle c2,vector<Point> &ret)
{
    Type d = Length(c1.p,c2.p);
    if(dcmp(d) == 0)
    {
        if(dcmp(c1.r - c2.r) == 0)
            return -1;  //两圆重合
        return 0;   //内含
    }
    if(dcmp(c1.r + c2.r-d) < 0)
        return 0;   //相离
    if(dcmp(fabs(c1.r - c2.r) - d) > 0)
        return 0;   //内含
    Type a = Angle(c2.p - c1.p);
    Type da = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    Point p1 = c1.polarCoordinates(a - da), p2 = c1.polarCoordinates(a + da);
    ret.PB(p1);
    if(p1 == p2)
        return 1;
    ret.PB(p2);
    return 2;
}

//两圆相交的交点相对于圆1圆心的极角保存在rad中
///模板待测！！！
void getTwoCirclesIntersection(Circle C1,Circle C2,vector<double>& rad)
{
    double d = Length(C1.p-C2.p);
    if(dcmp(d) == 0)
        return; //不管是内含还是重合，都不相交
    if(dcmp(C1.r+C2.r-d) < 0)
        return;
    if(dcmp(fabs(C1.r-C2.r)-d) > 0)
        return;
    double a = Angle(C2.p-C1.p);
    double da = acos((C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));
    rad.PB(NormalizeAngle(a-da));   //相交弧为从减到加（逆时针
    rad.PB(NormalizeAngle(a+da));
}


/**
#B7.两圆面积交
需要条件：A2,B1
**/
Type getInterArea(Circle a,Circle b)
{
    Type dis = Length(a.p,b.p);
    if(dcmp(a.r+b.r-dis) <= 0)
        return 0;
    if(dcmp(abs(a.r-b.r)-dis) >= 0)
    {
        Type r = min(a.r,b.r);
        return PI * r * r;
    }
    Type cosX = (dis * dis + a.r * a.r - b.r * b.r) / (2 * dis * a.r);
    Type X = acos(cosX);
    Type cosY = (dis * dis + b.r * b.r - a.r * a.r) / (2 * dis * b.r);
    Type Y = acos(cosY);
    return a.r * a.r * X + b.r * b.r * Y - dis * a.r * sin(X);
}


/**
#B8.把角变成0~2PI范围内
需要条件：无
**/
///模板待测！！！
//负数也可以使用
double NormalizeAngle(double rad)
{
    return rad - 2 * PI * floor(rad / (2 * PI));
}


/**
#B9.求圆过某一点的所有切线
需要条件：A1,A2,B1
**/
void getTangentPoint(Point p, Circle c, vector<Point> &v)
{
    double dis = Length(p, c.p);
    double base = Angle(p - c.p);
    double ang = acos(c.r / dis);
    v.PB(Point(c.p.x + cos(base - ang) * c.r, c.p.y + sin(base - ang) * c.r));
    v.PB(Point(c.p.x + cos(base + ang) * c.r, c.p.y + sin(base + ang) * c.r));
}

///模板待测！！！
//返回切线条数，也可以把int改成void不返回切线条数
int TangentLineThroughPoint(Circle c,Point p,vector<Line> &v)
{
    Vector u = c.p - p;
    Type dist = Length(u);
    if(dist < c.r)
        return 0;
    if(dcmp(dist-c.r) == 0)
    {
        Vector vt = Rotate(u,PI/2);
        v.PB(Line(p,p+vt));
        return 1;
    }
    else if(dcmp(dist-c.r) > 0)
    {
        Type ang = asin(c.r/dist);
        Vector v0 = Rotate(u,-ang), v1 = Rotate(u,ang);
        v.PB(Line(p,p+v0));
        v.PB(Line(p,p+v1));
        return 2;
    }
}


/**
#B10.求两圆的公切线
需要条件：A1,B1
**/
///模板待测！！！
//返回切线条数，v为所有的切线，第一个点是A上的切点，第二个点是B上的切点
int getTangents(Circle A,Circle B,vector<Line> &v)
{
    Point ta[5], tb[5];
    Point *a = ta, *b = tb;
    if(A.r<B.r)
    {
        swap(A,B);
        swap(a,b);
    }
    int cnt = 0;
    Type d2 = sqr(Length(A.p,B.p));
    Type rdiff = A.r - B.r;
    Type rsum = A.r + B.r;
    if(dcmp(d2-rdiff*rdiff) < 0)
        return 0;   //内含
    Vector va = B.p - A.p;
    Type base = atan2(va.y,va.x);
    if(dcmp(d2) == 0 && dcmp(A.r-B.r) == 0)
        return -1;  //无限条切线
    if(dcmp(d2-rdiff*rdiff) == 0)   //内切
    {
        a[cnt] = A.getPoint(base);
        b[cnt++] = B.getPoint(base);
        v.PB(Line(ta[0],tb[0]));
        return 1;
    }
    //有外公切线
    Type ang = acos((A.r-B.r)/sqrt(d2));
    a[cnt] = A.getPoint(base+ang);
    b[cnt++] = B.getPoint(base+ang);
    a[cnt] = A.getPoint(base-ang);
    b[cnt++] = B.getPoint(base-ang);
    if(dcmp(d2-rsum*rsum) == 0) //一条内公切线
    {
        a[cnt] = A.getPoint(base);
        b[cnt++] = B.getPoint(PI+base);
    }
    else if(dcmp(d2-rsum*rsum) > 0)
    {
        Type ang = acos((A.r+B.r)/sqrt(d2));
        a[cnt] = A.getPoint(base+ang);
        b[cnt++] = B.getPoint(PI+base+ang);
        a[cnt] = A.getPoint(base-ang);
        b[cnt++] = B.getPoint(PI+base-ang);
    }
    for(int i=0; i<cnt; i++)
        v.PB(Line(ta[i],tb[i]));
    return cnt;
}


/**
#B11.三角形外接圆
需要条件：A1,A2,B1
**/
Circle TriangleCircumscribedCircle(Point p1,Point p2,Point p3)
{
    double Bx = p2.x - p1.x, By = p2.y - p1.y;
    double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    double D = 2 * (Bx * Cy - By * Cx);
    double cx = (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy)) / D + p1.x;
    double cy = (Bx * (Cx * Cx + Cy * Cy) - Cx * (Bx * Bx + By * By)) / D + p1.y;
    Point p = Point(cx, cy);
    return Circle(p, Length(p1, p));
}


/**
#B12.三角形内切圆
需要条件：A1,A2,A5,B1
**/
Circle TriangleInscribedCircle(Point p1,Point p2,Point p3)
{
    double a = Length(p2, p3);
    double b = Length(p1, p3);
    double c = Length(p1, p2);
    Point p = (p1 * a + p2 * b + p3 * c) / (a + b + c);
    return Circle(p, DistanceToLine(p, Line(p1, p2)));
}


/**
#B13.过某一点与直线相切的圆（半径为r）
需要条件：A1,A2,A5,B1,B3
**/
///模板待测！！！
//返回所求圆的圆心
vector<Point> CircleThroughPointTangentLine(Point p,Line L,double r)
{
    vector<Point> ans;
    double t1, t2;
    getLineCircleIntersection(L.translation(-r),Circle(p,r),t1,t2,ans);
    getLineCircleIntersection(L.translation(r),Circle(p,r),t1,t2,ans);
    return ans;
}


/**
#B14.与两条直线相切的圆（半径为r）
需要条件：A1,A2,A3,A4
**/
///模板待测！！！
//返回所求圆的圆心
vector<Point> CircleTangent2Lines(Line a,Line b,double r)
{
    vector<Point> ans;
    Line L1 = a.translation(-r), L2 = a.translation(r);
    Line L3 = b.translation(-r), L4 = b.translation(r);
    ans.PB(LineIntersection(L1,L3));
    ans.PB(LineIntersection(L1,L4));
    ans.PB(LineIntersection(L2,L3));
    ans.PB(LineIntersection(L2,L4));
    return ans;
}


/**
#B15.与两圆相切的圆（半径为r）
需要条件：A1,A2,B1,B6
**/
///模板待测！！！
//返回所求圆的圆心
vector<Point> CircleTangent2Circles(Circle c1, Circle c2, double r)
{
    vector<Point> ans;
    Vector v = c2.c - c1.c;
    double dist = Length(v);
    int d = dcmp(dist-c1.r-c2.r-r*2);   //两圆相距太远
    if(d > 0)
        return ans;
    getTwoCirclesIntersection(Circle(c1.c, c1.r+r),Circle(c2.c, c2.r+r),ans);
    return ans;
}
