//计算几何模板——点、向量、直线与线段相关算法

/**
目录:
#A1.点的定义
#A2.向量的基本运算
#A3.直线、线段定义
#A4.两直线交点
#A5.点到直线的距离
#A6.点到线段的距离
#A7.点在直线上的投影
#A8.判断点是否在线段上
#A9.线段相交判定
#A10.两点式转一般式 Ax + By + C = 0
#A11.判断直线和线段相交
#A12.点的极角排序
**/

/**
#A1.点的定义
需要条件：无
**/

#define Vector Point

typedef double Type;

inline int dcmp(double x)
{
    return (x > EPS) - (x < -EPS);
}

//点的定义
struct Point
{
    Type x, y;
    //int belong;   //属于哪一个圆
    Point(Type x=0,Type y=0):x(x),y(y) {}

    Vector operator + (const Vector& rhs) const
    {
        return Vector(x + rhs.x, y + rhs.y);
    }
    Vector operator - (const Point& rhs) const
    {
        return Vector(x - rhs.x, y - rhs.y);
    }
    Vector operator * (Type p) const
    {
        return Vector(x * p, y * p);
    }
    Vector operator / (Type p) const
    {
        return Vector(x / p, y / p);
    }
    bool operator < (const Point& rhs) const
    {
        return dcmp(x - rhs.x) < 0 || (dcmp(x-rhs.x)==0 && dcmp(y-rhs.y) < 0);
    }
    /*
    bool operator < (const Point& rhs) const
    {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
    */
    bool operator == (const Point& rhs) const
    {
        return dcmp(x - rhs.x) == 0 && dcmp(y - rhs.y) == 0;
    }
    bool operator > (const Point& rhs) const
    {
        return !(*this < rhs || *this == rhs);
    }
    bool operator >= (const Point& rhs) const
    {
        return !(*this < rhs);
    }
    bool operator <= (const Point& rhs) const
    {
        return (*this < rhs || *this == rhs);
    }
    double operator * (const Vector& rhs) const //点积
    {
        return x * rhs.x + y * rhs.y;
    }
    double operator ^ (const Vector& rhs) const //叉积
    {
        return x * rhs.y - y * rhs.x;
    }

    void read()
    {
        scanf("%lf%lf",&x,&y);
    }

    void print() const
    {
        printf("(%f, %f)",x,y);
    }
};


/**
#A2.向量的基本运算
需要条件：A1
**/
//距离
Type Length(Point p1,Point p2)
{
    Type x = p1.x - p2.x, y = p1.y - p2.y;
    return sqrt(x * x + y * y);
}

//向量的模
Type Length(Vector v)
{
    return sqrt(v * v);
}

//叉积
Type Cross(Vector v1,Vector v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

Type Cross(Point &p1,Point &p2,Point &p3)
{
    return Cross(p1-p3,p2-p3);
}

//点积
Type Dot(Vector v1,Vector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

//向量的夹角 a*b=|a||b|cosα
Type Angle(Vector v1,Vector v2)
{
    return acos(v1 * v2 / Length(v1) / Length(v2));
}

//AB x AC组成的空间
double Area2(Point p1,Point p2,Point p3)
{
    return (p2 - p1) ^ (p3 - p1);
}

//向量逆时针旋转rad弧度
Vector Rotate(Vector v,double rad)
{
    return Vector(v.x * cos(rad) - v.y * sin(rad), v.x * sin(rad) + v.y * cos(rad));
}

//计算A的法线（A不是0向量）
//左转90° 长度归一化
Vector Normal(Vector v)
{
    Type l = Length(v);
    return Vector(-v.y / l, v.x / l);
}

//计算向量极角（需要<cmath>头文件）
double Angle(Vector v)
{
    return atan2(v.y, v.x);
}


/**
#A3.直线、线段定义（它的左边是对应的半平面）
需要条件：A1
**/
struct Line
{
    Point a,b;  //直线（线段）的两个端点（线段的时候可把a当作起点）
    Vector v;   //方向向量，v = b - a
    //double ang;//极角
    Line() {}
    Line(Point a,Point b):a(a),b(b)
    {
        v = b - a; /*ang = atan2(v.y, v.x);*/
    }
    Line move(double d)
    {
        return Line(a + Normal(v)*d, v);
    }
    bool operator < (const Line& rhs) const
    {
        //根据原点极角排序（小的在前；极角相同，长度小的在前）
        //return ang < L.ang;
        if (v.y * rhs.v.y > 0)  //同上同下
        {
            if ((v ^ rhs.v) != 0)
                return (v ^ rhs.v) > 0;
            return Length(v) > Length(rhs.v);   //极角相同，长的小
        }
        if (v.y * rhs.v.y < 0)
            return v.y < 0; //一上一下
        if (v.y == 0)
        {
            if (rhs.v.y == 0)
            {
                if (v.x * rhs.v.x < 0)
                    return v.x > rhs.v.x;
                return Length(v) > Length(rhs.v);   //极角相同长的小
            }
            if (v.x > 0)
                return rhs.v.y > 0;
            return false;
        }
        if (rhs.v.x > 0)
            return v.y < 0;
        return true;
    }
};

typedef Line Segment;


/**
#A4.两直线交点
需要条件：A1,A2,A3
**/
Point LineIntersection(Line &L1,Line& L2)
{
    Vector u = L1.a - L2.a;
    Vector v1 = L1.b - L1.a, v2 = L2.b - L2.a;
    if(dcmp(v1 ^ v2) == 0)
    {
        if(dcmp(u ^ v1))
            return Point(-INF,-INF);//平行
        else
            return Point(-INF,-INF);//在一条线上
    }
    Type t = (v2 ^ u) / (v1 ^ v2);
    return L1.a + v1 * t;
}


/**
#A5.点到直线的距离
需要条件：A1,A2,A3
**/
Type DistanceToLine(Point p,Line L)
{
    Vector v1 = L.b - L.a, v2 = p - L.a;
    return fabs(v1 ^ v2) / Length(v1);
}


/**
#A6.点到线段的距离
需要条件：A1,A2,A3
**/
Type DistanceToSegment(Point p,Segment seg)
{
    if(seg.a == seg.b)
        return Length(p,seg.a);
    Vector v1 = seg.b - seg.a, v2 = p - seg.a, v3 = p - seg.b;
    if(dcmp(v1 * v2) < 0)
        return Length(v2);
    else if(dcmp(v1 * v3) > 0)
        return Length(v3);
    else
        return fabs(v1 ^ v2) / Length(v1);
}


/**
#A7.点在直线上的投影
需要条件：A1,A2,A3
**/
Point LineProjection(Point p,Line L)
{
    Vector v = L.b - L.a;
    return L.a + v * (v * (p - L.a) / (v * v));
}


/**
#A8.判断点是否在线段上
需要条件：A1,A2,A3
**/
bool OnSegment(Point &p,Segment& S)
{
    //小于0不包含端点，小于等于包含端点
    return dcmp((S.a-p)^(S.b-p)) == 0 && dcmp((S.a-p)*(S.b-p)) <= 0;
}

/**
#A9.线段相交判定 
需要条件：A1,A2,A3
**/
/*线段规范相交*/
//两条线段恰有一个不是端点的公共点。（即如果一条线段的一个端点恰在另一条线段上则不视为相交；如果两条线段部分重合，也不视为相交。）
bool SegmentProperIntersect(Segment &s1,Segment& s2)
{
    Type c1 = (s1.b - s1.a) ^ (s2.a - s1.a), c2 = (s1.b - s1.a) ^ (s2.b - s1.a),
         c3 = (s2.b - s2.a) ^ (s1.a - s2.a), c4 = (s2.b - s2.a) ^ (s1.b - s2.a);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

/*线段不规范相交（使用的时候结合线段规范相交的函数一起判断）*/
//两条线段存在公共部分。（上述两种情况都可视为非规范相交）
bool SegmentNotProperIntersect(Segment& s1,Segment& s2)
{
    return OnSegment(s1.a,s2) || OnSegment(s1.b,s2) || OnSegment(s2.a,s1) || OnSegment(s2.b,s1);
}


/**
#A10.两点式转一般式 Ax + By + C = 0
需要条件：A1,A2,A3
**/
void toNormalLine(Line &L,Type &A,Type& B,Type &C)
{
    A = L.a.y - L.b.y;
    B = L.b.x - L.a.x;
    C = -B * L.a.y - A * L.a.x;
}


/**
#A11.判断直线和线段相交
需要条件：A1,A2,A3
**/
bool LineIntersectSegment(Line &L,Segment &S)
{
    Vector a(S.a-L.a);
    Vector b(S.b-L.a);
    Vector c(L.b-L.a);
    int dcmpA = dcmp(c ^ a);
    int dcmpB = dcmp(c ^ b);
    return dcmpA * dcmpB <= 0;
}


/**
#A12.点的极角排序
需要条件：A1,A2
**/
/*A12.1常用版*/
//利用叉积进行极角排序，极角相同的，距离原点近的小）
int pos;
Point p[100];
bool AngleCmp(Point a,Point b)
{
    Type temp = (a - p[pos]) ^ (b - p[pos]);
    if(dcmp(temp) == 0)
        return Length(p[pos],a) < Length(p[pos],b);
    else if(dcmp(temp) < 0)
        return false;
    else
        return true;
}

/*A12.2*/
//利用叉积的正负排序
bool AngleCmp(const point &a,const point &b)    //逆时针排序
{
    point O;
    O.x = O.y = 0;
    return (b - O) ^ (a - O) < 0;
}

/*A12.3*/
//利用complex的内建函数排序（需要<complex>头文件）
bool AngleCmp(const Point& a,const Point& b)
{
    return arg(a) < arg(b);
}

/*A12.4*/
//利用arctan计算极角大小排序（范围[-180，180]）
bool AngleCmp(const Point& a,const Point& b)
{
    return atan2(a.y, a.x) < atan2(b.y, b.x);
}

/*A12.5*/
//利用象限加上极角，叉积排序
bool AngleCmp(const Point &a,const Point &b)    //先按象限排序，再按极角排序，再按远近排序
{
    if (a.y == 0 && b.y == 0 && a.x * b.x <= 0)
        return a.x > b.x;
    if (a.y == 0 && a.x >= 0 && b.y != 0)
        return true;
    if (b.y == 0 && b.x >= 0 && a.y != 0)
        return false;
    if (b.y*a.y <= 0)
        return a.y>b.y;
    point O;
    O.y = O.x = 0;
    return (a - O) ^ (b - O) > 0 || ((a - O) ^ (b - O) == 0 && a.x < b.x);
}
