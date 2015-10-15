
struct Circle{
	Point p;
	Type r;
	Circle(){}
	Circle(Point p,Type r):p(p),r(r){}
	//通过圆心角获得点坐标
	Point getPoint(double a){
		return Point(p.x+cos(a)*r,p.y+sin(a)*r);
	}
};

//返回切线条数，v为所有的切线，第一个点是A上的切点，第二个点是B上的切点
int getTangents(Circle A,Circle B,vector<Line> &v){
	Point ta[5],tb[5];
	Point *a = ta,*b = tb;
	if(A.r<B.r){
		swap(A,B);
		swap(a,b);
	}
	int cnt = 0;
	Type d2 = sqr(Length(A.p,B.p));
	Type rdiff = A.r-B.r;
	Type rsum = A.r+B.r;
	if(sign(d2-rdiff*rdiff)<0) return 0;//内含
	Vector va = B.p-A.p;
	Type base = atan2(va.y,va.x);
	if(sign(d2)==0&&sign(A.r-B.r)==0) return -1;//无限条切线
	if(sign(d2-rdiff*rdiff)==0){//内切
		a[cnt] = A.getPoint(base);
		b[cnt++] = B.getPoint(base);
		v.PB(Line(ta[0],tb[0]));
		return 1;
	}
	//有外公切线
	Type ang = acos((A.r-B.r)/sqrt(d2));
	a[cnt] = A.getPoint(base+ang);b[cnt++] = B.getPoint(base+ang);
	a[cnt] = A.getPoint(base-ang);b[cnt++] = B.getPoint(base-ang);
	if(sign(d2-rsum*rsum)==0){//一条内公切线
		a[cnt] = A.getPoint(base);b[cnt++] = B.getPoint(PI+base);
	}else if(sign(d2-rsum*rsum)>0){
		Type ang = acos((A.r+B.r)/sqrt(d2));
		a[cnt] = A.getPoint(base+ang);b[cnt++] = B.getPoint(PI+base+ang);
		a[cnt] = A.getPoint(base-ang);b[cnt++] = B.getPoint(PI+base-ang);
	}
	for(int i = 0;i<cnt;i++) v.PB(Line(ta[i],tb[i]));
	return cnt;
}

//直线和圆交点
void getLineCircleIntersection(Line l,Circle C,vector<Point>& ret){
	Vector v = l.b-l.a;
	Type a = v.x,b = l.a.x-C.p.x,c = v.y,d = l.a.y-C.p.y;
	Type e = a*a+c*c,f = 2*(a*b+c*d),g = b*b+d*d-C.r*C.r;
	Type delta = f*f-4*e*g;
	Type t1,t2; 
	if(sign(delta)<0) return;//相离
	if(sign(delta)==0){
		t1 = t2 = -f/(2*e);
		ret.PB(l.a+v*t1);
	}else{
		t1 = (-f-sqrt(delta))/(2*e);
		if(sign(t1-1)<=0&&sign(t1)>=0) //这条判断表示线段
        ret.PB(l.a+v*t1);
		t2 = (-f+sqrt(delta))/(2*e);
		if(sign(t2-1)<=0&&sign(t2)>=0) //这条判断表示线段
        ret.PB(l.a+v*t2);
	}
}

//圆交点
int getCircleInterSection(Circle c1,Circle c2,vector<Point> &ret){
	Type d = Length(c1.p,c2.p);
	if(sign(d)==0){
		if(sign(c1.r-c2.r)==0) return -1;//两圆重合
		return 0;//内含
	}
	if(sign(c1.r+c2.r-d)<0) return 0;//相离
	if(sign(fabs(c1.r-c2.r)-d)>0) return 0;//内含
	Type a = Angle(c2.p-c1.p);
	Type da = acos((c1.r*c1.r+d*d-c2.r*c2.r)/(2*c1.r*d));
	Point p1 = c1.getPoint(a-da),p2 = c1.getPoint(a+da);
	ret.PB(p1);
	if(p1==p2) return 1;
	ret.PB(p2);
	return 2;
}

//两圆面积交
Type getInterArea(Circle a,Circle b){
    Type dis = Length(a.p,b.p);
    if(sign(a.r+b.r-dis)<=0) return 0;
    if(sign(abs(a.r-b.r)-dis)>=0){
        Type r = min(a.r,b.r);
        return PI*r*r;
    }
    Type cosX = (dis*dis+a.r*a.r-b.r*b.r)/(2*dis*a.r);
    Type X = acos(cosX);
    Type cosY = (dis*dis+b.r*b.r-a.r*a.r)/(2*dis*b.r);
    Type Y = acos(cosY);
    return a.r*a.r*X+b.r*b.r*Y-dis*a.r*sin(X);
}

//三角形外接圆
Circle CircumscribedCircle(Point p1,Point p2,Point p3){
	Type Bx = p2.x-p1.x,By = p2.y-p1.y;
	Type Cx = p3.x-p1.x,Cy = p3.y-p1.y;
	Type D = 2*(Bx*Cy-By*Cx);
	Type cx = (Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D+p1.x;
	Type cy = (Bx*(Cx*Cx+Cy*Cy)-Cx*(Bx*Bx+By*By))/D+p1.y;
	Point p(cx,cy);
	return Circle(p,Length(p1,p));
}

//三角形内接圆
Circle InscribedCircle(Point p1,Point p2,Point p3){
	Type a = Length(p2,p3);
	Type b = Length(p1,p3);
	Type c = Length(p1,p2);
	Point p = (p1*a+p2*b+p3*c)/(a+b+c);
	return Circle(p,DistanceToLine(p,Line(p1,p2)));
}

//求圆过某一点的所有切线
void TangentLineThroughPoint(Circle c,Point p,vector<Line> &v){
	Vector u = c.p-p;
	Type dist = Length(u);
	if(sign(dist-c.r)==0){
		Vector vt = Rotate(u,PI/2);
		v.PB(Line(p,p+vt));
	}else if(sign(dist-c.r)>0){
		Type ang = asin(c.r/dist);
		Vector v0 = Rotate(u,-ang),v1 = Rotate(u,ang);
		v.PB(Line(p,p+v0));
		v.PB(Line(p,p+v1));
	}
}


