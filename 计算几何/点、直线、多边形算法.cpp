//距离
Type Length(Point a,Point b){
	Type x = a.x-b.x,y = a.y-b.y;
	return sqrt(x*x+y*y);
}

//长度
Type Length(Vector v){
    return sqrt(v.x*v.x+v.y*v.y);
}

//计算向量极角
Type Angle(Vector v){
	return atan2(v.y,v.x);
}

//叉积
Type Cross(Vector a,Vector b){
	return a.x*b.y-a.y*b.x;
}

Type Cross(Point &a,Point &b,Point &c){
	return Cross(a-c,b-c);
}

//点积
Type Dot(Vector a,Vector b){
	return a.x*b.x+a.y*b.y;
}

//逆时针旋转向量
Vector Rotate(Vector A,Type rad){
	return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}

//两个向量的夹角
Type Angle(Vector A,Vector B){
	return acos(Dot(A,B)/Length(A)/Length(B));
}

//单位法线
Vector Normal(Vector A){
	Type L = Length(A);
	return Vector(-A.y/L,A.x/L);
}


//单位向量
Vector ToUnit(Vector A){
	Type l = Length(A);
	return Vector(A.x/l,A.y/l);
}

//两点式转一般式Ax+By+C = 0
void toNormalLine(Line &l,Type &A,Type& B,Type &C){
	A = l.a.y-l.b.y;
	B = l.b.x-l.a.x;
	C = -B*l.a.y-A*l.a.x;
}

//判断直线和线段相交
bool LineIntersectSegMent(Line &l,SegMent &seg){
	Vector a(seg.a-l.a);
	Vector b(seg.b-l.a);
	Vector c(l.b-l.a);
	int signA = sign(Cross(c,a));
	int signB = sign(Cross(c,b));
	return signA*signB<=0;
}

//求直线交点
Point LineInterSection(Line &l1,Line& l2){
	Vector u = l1.a-l2.a;
	Vector v1 = l1.b-l1.a,v2 = l2.b-l2.a;
	if(sign(Cross(v1,v2))==0){
		if(sign(Cross(u,v1))) return Point(-INF,-INF);//平行
		else return Point(-INF,-INF);//在一条线上
	}
	Type t = Cross(v2,u)/Cross(v1,v2);
	return l1.a+v1*t;
}

//线段规范相交
bool SegMentProperIntersect(SegMent &s1,SegMent& s2){
	Type c1 = Cross(s1.b-s1.a,s2.a-s1.a),c2 = Cross(s1.b-s1.a,s2.b-s1.a),
		 c3 = Cross(s2.b-s2.a,s1.a-s2.a),c4 = Cross(s2.b-s2.a,s1.b-s2.a);
	return sign(c1)*sign(c2)<0&&sign(c3)*sign(c4)<0;
}

//判断点在线段上
bool OnSegMent(Point &p,SegMent& s){
	//小于0不包含端点，小于等于包含端点
	return sign(Cross(s.a-p,s.b-p))==0&&sign(Dot(s.a-p,s.b-p))<=0;
}

//线段不规范相交
bool SegMentNotProperIntersect(SegMent& s1,SegMent& s2){
	return OnSegMent(s1.a,s2)||OnSegMent(s1.b,s2)
		||OnSegMent(s2.a,s1)||OnSegMent(s2.b,s1);
}

//点到直线距离
Type DistanceToLine(Point p,Line l){
	Vector v1 = l.b-l.a,v2 = p-l.a;
	return fabs(Cross(v1,v2))/Length(v1);
}

//点到线段距离
Type DistanceToSegMent(Point p,SegMent seg){
	if(seg.a==seg.b) return Length(p,seg.a);
	Vector v1 = seg.b-seg.a,v2 = p-seg.a,v3 = p-seg.b;
	if(sign(Dot(v1,v2))<0) return Length(v2);
	else if(sign(Dot(v1,v3))>0) return Length(v3);
	else return fabs(Cross(v1,v2))/Length(v1);
}

int isPointInPolygon(Point p,Polygon& poly){
	vector<Point>& v = poly.v;
	int n = v.size();
	int w = 0;
	for(int i = 0;i<n;i++){
		if(OnSegMent(p,SegMent(v[i],v[(i+1)%n]))) return -1;//边界上
		int k = sign(Cross(v[(i+1)%n]-v[i],p-v[i]));
		int d1 = sign(v[i].y-p.y);
		int d2 = sign(v[(i+1)%n].y-p.y);
		if(k>0&&d1<=0&&d2>0) w++;
		if(k<0&&d2<=0&&d1>0) w--;
	}
	if(w) return 1;//在内部
	return 0;//在外面
}

//求凸包，如果不希望凸包边上有输入点，把<=改成<
int ConvexHull(Point *p,int n,Point *ch){
	sort(p,p+n);
	int m = 0;
	for(int i = 0;i<n;i++){
		while(m>1&&sign(Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]))<=0) m--;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n-2;i>=0;i--){
		while(m>k&&sign(Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]))<=0) m--;
		ch[m++] = p[i];
	}
	if(n>1) m--;
	return m;
}

//旋转卡壳求平面最远点对
Type Rotating_Calipers(Point *p,int n){
	int q = 1;
	Type ans = 0;
	p[n] = p[0];
	for(int i = 0;i<n;i++){
		while(sign(Cross(p[i+1],p[q+1],p[i])-Cross(p[i+1],p[q],p[i]))>0)
			q = (q+1)%n;
		ans = max(ans,Length(p[i],p[q]));
		ans = max(ans,Length(p[i+1],p[q+1]));
	}
	return ans;
}

//旋转卡壳求两个凸包的最近点对，使用时要调用min(RC(p,np,q,np),RC(q,nq,p,np));
Type Rotating_Calipers(Point *p,int np,Point *q,int nq){
	int sp = 0,sq = 0;
	for(int i = 0;i<np;i++)
		if(sign(p[i].y-p[sp].y)<0) sp = i;
	for(int i = 0;i<nq;i++)
		if(sign(q[i].y-q[sq].y)>0) sq = i;
	double tmp,ans = INF;
	p[np] = p[0],q[nq] = q[0];
	for(int i = 0;i<np;i++){
		while(sign(tmp = Cross(p[sp],p[sp+1],q[sq])-Cross(p[sp],p[sp+1],q[sq+1]))<0)
			sq = (sq+1)%nq;
		if(sign(tmp)>0){
			ans = min(ans,DistanceToSegMent(q[sq],SegMent(p[sp],p[sp+1])));
		}else{
			SegMent segp(p[sp],p[sp+1]),segq(q[sq],q[sq+1]);
			ans = min(ans,DistanceToSegMent(p[sp],segq));
			ans = min(ans,DistanceToSegMent(p[sp+1],segq));
			ans = min(ans,DistanceToSegMent(q[sq],segp));
			ans = min(ans,DistanceToSegMent(q[sq+1],segp));
		}
		sp = (sp+1)%np;
	}
	return ans;
}

//旋转卡壳求包围点的最小面积（周长）的矩形，p是凸包，n是凸包点数
pair<Type,Type> Rotating_Calipers(Point *p,int n){
	p[n] = p[0];
	Type min_area = 1e99,min_c = 1e99;//最小的矩形面积和矩形周长
	int l = 1,r = 1,u = 1;
	for(int i = 0;i<n;i++){
		Vector v = ToUnit(p[i+1]-p[i]);
		while(sign(Dot(v,p[r%n]-p[i])-Dot(v,p[(r+1)%n]-p[i]))<0) r++;
		while(u<r||sign(Cross(v,p[u%n]-p[i])-Cross(v,p[(u+1)%n]-p[i]))<0) u++;
		while(l<u||sign(Dot(v,p[l%n]-p[i])-Dot(v,p[(l+1)%n]-p[i]))>0) l++;
		Type w = Dot(v,p[r%n]-p[i])-Dot(v,p[l%n]-p[i]);
		Type h = DistanceToLine(p[u%n],Line(p[i],p[i+1]));
		min_area = min(min_area,w*h);
		min_c = min(min_c,2*(w+h));
	}
	return MP(min_area,min_c);
}


