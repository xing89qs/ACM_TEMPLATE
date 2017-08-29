
//两点距离的平方
Type SqrLength(Vector v)
{
    return v.x*v.x+v.y*v.y;
}

//点在直线上的投影
Point Project(SegMent s,Point p)
{
    Vector x=s.b-s.a;
    Type r=Dot(p-s.a,x)/SqrLength(x);
    return s.a+x*r;
}

//点关于直线的映象
Point Reflect(SegMent s,Point p)
{
    return p+(Project(s,p)-p)*2.0;
}


//判断两个共点向量的相对位置（v1相对v2逆时针旋转、顺时针旋转、反向、正向v1长于v2、正向v2长于v1等
static const int COUNTER_CLOCKWISE = 1; //v2相对于v1逆时针旋转
static const int CLOCKWISE = -1;    //v2相对于v1顺时针旋转
static const int ONLINE_BACK = 2;   //v2相对v1反向
static const int ONLINE_FRONT = -2; //v1、v2同向且v2比v1长
static const int ON_SEGMENT = 0;    //v1、v2同向且v1比v2长

int CCW(Point p0,Point p1,Point p2)
{
    Vector a=p1-p0;
    Vector b=p2-p0;
    if(Cross(a,b)>EPS)
        return COUNTER_CLOCKWISE;
    if(Cross(b,a)>EPS)
        return CLOCKWISE;
    if(Dot(a,b)<-EPS)
        return ONLINE_BACK;
    if(Length(a)<Length(b))
        return ONLINE_FRONT;
    if(Length(a)>Length(b))
        return ON_SEGMENT;
}

//判断两线段是否相交
bool Intersect(SegMent s1,SegMent s2)
{
    if(CCW(s1.a,s1.b,s2.a)*CCW(s1.a,s1.b,s2.b)<=0 && CCW(s2.a,s2.b,s1.a)*CCW(s2.a,s2.b,s1.b)<=0)
        return true;
    return false;
}

//两线段之间的距离
Type DistanceBetweenTwoSegMent(SegMent s1,SegMent s2)
{
    if(Intersect(s1,s2))
        return 0.0;
    return min(min(DistanceToSegMent(s1.a,s2),DistanceToSegMent(s1.b,s2)),min(DistanceToSegMent(s2.a,s1),DistanceToSegMent(s2.b,s1)));
}

//两线段的交点
Point CrossPoint(SegMent s1,SegMent s2)
{
    Vector x=s2.b-s2.a;
    double d1=fabs(Cross(x,s2.a-s1.a));
    double d2=fabs(Cross(x,s2.b-s1.b));
    double t=d1/(d1+d2);
    return s1.a+(s1.b-s1.a)*t;
}

//点与多边形的关系（内包、在边上、在多边形外）
int Contains(Polygon g, Point p)
{
    int sz=g.v.size();
    bool flag=false;
    for(int i=0; i<sz; i++)
    {
        Vector a=g.v[i]-p;
        Vector b=g.v[(i+1)%sz]-p;
        if(fabs(Cross(a,b))==0 && Dot(a,b)<EPS)
            return 1;   //点在多边形边上
        if(a.y>b.y)
            swap(a,b);
        if(a.y<EPS && b.y>EPS && Cross(a,b)>EPS)
            flag=!flag;
    }
    return flag?2:0;   //点在多边形内/点在多边形外
}
