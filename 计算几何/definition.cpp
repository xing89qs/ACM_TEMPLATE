typedef double Type;

int sign(Type x){
	return x<-EPS?-1:(x>EPS?1:0);
}

struct Point{
	Type x,y;
	Point(Type x,Type y):x(x),y(y){}
	Point(){}
	void read(){
		scanf("%lf %lf",&x,&y);
	}	
	bool operator==(const Point& p) const{
		return sign(x-p.x)==0&&sign(y-p.y)==0;
	}
	Point operator-(const Point& p) const{
		return Point(x-p.x,y-p.y);
	}
	Point operator*(const Type t) const{
		return Point(t*x,t*y);
	}
	Point operator+(const Point & p) const{
		return Point(x+p.x,y+p.y);
	}
	bool operator<(const Point& p) const{
		return sign(x-p.x)==0?sign(y-p.y)<0:sign(x-p.x)<0;
	}
};

ostream& operator<<(ostream& out,Point p){
	out<<p.x<<" "<<p.y;
	return out;
}

typedef Point Vector;

struct Line{
	Point a,b;
	Line(){}
	Line(Point a,Point b):a(a),b(b){}
};

typedef Line SegMent;

struct Polygon{
	vector<Point> v;
};

