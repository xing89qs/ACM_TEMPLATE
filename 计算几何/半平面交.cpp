//有向直线
struct DirLine{
	Point p;//直线上任意一点
	Vector v;//方向向量，左边是对应半平面
	Type ang;//极角
	DirLine(){}
	DirLine(Point p,Vector v):p(p),v(v){ang = atan2(v.y,v.x);}
	bool operator<(const DirLine& l) const{
		return ang<l.ang;
	}
};

bool OnLeft(DirLine l,Point p){
	return sign(Cross(l.v,p-l.p))>0;
}

Point LineIntersection(DirLine &a,DirLine& b){
	Vector u = a.p-b.p;
	Type t = Cross(b.v,u)/Cross(a.v,b.v);
	return a.p+a.v*t;
}

Point halfP[MAXN<<1];
DirLine halfQ[MAXN<<1];

int HalfplaneIntersection(DirLine* l,int n,Point *poly){
	sort(l,l+n);
	int head,tail;
	DirLine *q = halfQ; //双端队列
	Point *p = halfP;   //p[i]表示q[i]和q[i+1]的交点
	halfQ[head = tail = 0] = l[0];
	for(int i = 1;i<n;i++){
		while(head<tail&&!OnLeft(l[i],p[tail-1])) tail--;
		while(head<tail&&!OnLeft(l[i],p[head])) head++;
		q[++tail] = l[i];
		if(sign(Cross(q[tail].v,q[tail-1].v))==0){
			//两向量平行且同向，取内侧的一个
			tail--;
			if(OnLeft(q[tail],l[i].p)) q[tail] = l[i];
		}
		if(head<tail) p[tail-1] = LineIntersection(q[tail-1],q[tail]);
	}
	while(head<tail&&!OnLeft(q[head],p[tail-1])) tail--;
	if(tail-head<=1) return 0;
	p[tail] = LineIntersection(q[tail],q[head]);
	int m = 0;
	for(int i = head;i<=tail;i++) poly[m++] = p[i];
	return m;
}

