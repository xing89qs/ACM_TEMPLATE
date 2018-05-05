//计算几何模板——旋转卡壳

/**
目录:
#D1.旋转卡壳求平面最远点对
#D2.旋转卡壳求两个凸包的最近点对
#D3.旋转卡壳求平面点集构成的最大三角形面积
#D4.旋转卡壳求包围点的最小面积（周长）的矩形
**/


/**
#D1.旋转卡壳求平面最远点对
需要条件：A1,A2,C9
**/
Type RotatingCalipers(Point *p,int n)
{
    int q = 1;
    Type ans = 0;
    p[n] = p[0];
    for(int i=0; i<n; i++)
    {
        while(dcmp(Cross(p[i+1],p[q+1],p[i])-Cross(p[i+1],p[q],p[i])) > 0)
            q = (q + 1) % n;
        ans = max(ans,Length(p[i],p[q]));
        ans = max(ans,Length(p[i+1],p[q+1]));
    }
    return ans;
}


/**
#D2.旋转卡壳求两个凸包的最近点对
需要条件：A1,A2,A6,C9
**/
//p,q是两个凸包，np,nq分别是两个凸包的点数
//使用时要调用min(RotatingCalipers(p,np,q,np),RotatingCalipers(q,nq,p,np));
Type RotatingCalipers(Point *p,int np,Point *q,int nq)
{
    int sp = 0,sq = 0;
    for(int i=0; i<np; i++)
        if(dcmp(p[i].y-p[sp].y) < 0)
            sp = i;
    for(int i = 0; i<nq; i++)
        if(dcmp(q[i].y-q[sq].y) > 0)
            sq = i;
    double tmp, ans = INF;
    p[np] = p[0], q[nq] = q[0];
    for(int i = 0; i<np; i++)
    {
        while(dcmp(tmp = Cross(p[sp],p[sp+1],q[sq])-Cross(p[sp],p[sp+1],q[sq+1])) < 0)
            sq = (sq + 1) % nq;
        if(dcmp(tmp) > 0)
            ans = min(ans,DistanceToSegment(q[sq],Segment(p[sp],p[sp+1])));
        else
        {
            Segment segp(p[sp],p[sp+1]), segq(q[sq],q[sq+1]);
            ans = min(ans,DistanceToSegment(p[sp],segq));
            ans = min(ans,DistanceToSegment(p[sp+1],segq));
            ans = min(ans,DistanceToSegment(q[sq],segp));
            ans = min(ans,DistanceToSegment(q[sq+1],segp));
        }
        sp = (sp + 1) % np;
    }
    return ans;
}


/**
#D3.旋转卡壳求平面点集构成的最大三角形面积
需要条件：A1,A2,C9
**/
Type RotatingCalipers(Point *p,int n)
{
    int j = 1, k = 2;
    Type ans = 0;
    for(int i=0; i<n; i++)
    {
        while(dcmp(Cross(p[i],p[j],p[(k+1)%n])-Cross(p[i],p[j],p[k])) > 0)
            k = (k + 1) % n;
        ans = max(ans,Cross(p[i],p[j],p[k])/2.0);
        while(dcmp(Cross(p[i],p[(j+1)%n],p[k])-Cross(p[i],p[j],p[k])) > 0)
            j = (j + 1) % n;
        ans = max(ans,Cross(p[i],p[j],p[k])/2.0);
    }
    return ans;
}


/**
#D4.旋转卡壳求包围点的最小面积（周长）的矩形
需要条件：A1,A2,A5,C9
**/
//p是凸包，n是凸包点数
pair<Type,Type> RotatingCalipers(Point *p,int n)
{
    p[n] = p[0];
    Type minS = 1e99, minC = 1e99;  //最小的矩形面积和矩形周长
    int l = 1, r = 1, u = 1;
    for(int i=0; i<n; i++)
    {
        Vector v = ToUnit(p[i+1] - p[i]);
        while(dcmp(v*(p[r%n]-p[i])-v*(p[(r+1)%n]-p[i])) < 0)    //右边
            r++;
        while(u < r || dcmp(v^(p[u%n]-p[i])-v^(p[(u+1)%n]-p[i])) < 0)   //上边
            u++;
        while(l < u || dcmp(v*(p[l%n]-p[i])-v*(p[(l+1)%n]-p[i])) > 0)   //左边
            l++;
        Type w = v * (p[r%n] - p[i]) - v * (p[l%n] - p[i]);
        Type h = DistanceToLine(p[u%n],Line(p[i],p[i+1]));
        minS = min(minS,w*h);
        minC = min(minC,2*(w+h));
    }
    return MP(minS,minC);
}
