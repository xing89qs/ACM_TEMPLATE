//计算几何模板——平面直线图

/**
目录:
#F1.平面直线图
**/


/**
#F1.平面直线图
需要条件：A1,C1,C2
**/
/*调用方法:给出点和边，求面
 * init(n) n为点数
 * addPoint(const vector<Point>& V) 传入点集
 * addEdge(u, v) 添加u到v的变 u,v为点的序号
 * get_face(),得到如下东西
 * faces 保存每个面（面是由逆时针点构成）
 * left[i] 每条边 左边的面的编号
 * area[i] 每个面的面积
 * 对于内部区域来说，无限面的各个顶点是顺时针的
 * 无限面多边形上可能会有相邻共线点
 * 对于连通图，唯一一个面积小于0的面是无限面
*/
struct Edge
{
    int u,v;
    //double ang;
    Edge() {}
    Edge(int u,int v):u(u),v(v) {}
};

const int MAXN = 10000 + 10;

//平面直线图
static double *xp, *yp;
static vector<Edge>* ep;

struct PSLG
{
    int n, m, face_cnt;
    double x[MAXN], y[MAXN];
    vector<Edge> edges;
    vector<int> G[MAXN];
    int vis[MAXN*2];    //每条边是否已经访问过
    int left[MAXN*2];   //左边的编号
    int prev[MAXN*2];   //相同起点的上一条边（右边的边）的变化
    vector<Polygon> faces;
    double area[MAXN]; //每个polygon的面积
    void init(int n)
    {
        this -> n = n;
        for(int i=0; i<n; i++)
            G[i].clear();
        edges.clear();
        faces.clear();
        xp = x;
        yp = y;
        ep = &edges;
    }
    /*double getAngle(int u,int v)
    {
        return atan2(y[v]-y[u],x[v]-x[u]);
    }*/
    void addPoint(const vector<Point>& V)
    {
        for(int i=0; i<n; i++)
        {
            x[i] = V[i].x;
            y[i] = V[i].y;
        }
    }
    void addEdge(int u, int v)
    {
        edges.PB((Edge){u,v/*,getAngle(u, v)*/});
        edges.PB((Edge){v,u/*,getAngle(v, u)*/});
        m = edges.size();
        G[u].PB(m-2);
        G[v].PB(m-1);
    }
    static bool cmp(int i, int j)   //极角排序，辅助排序
    {
        //return (*ep)[i].ang < (*ep)[j].ang;
        double x1 = xp[(*ep)[i].v] - xp[(*ep)[i].u];
        double x2 = xp[(*ep)[j].v] - xp[(*ep)[j].u];
        double y1 = yp[(*ep)[i].v] - yp[(*ep)[i].u];
        double y2 = yp[(*ep)[j].v] - yp[(*ep)[j].u];
        if(y1 * y2 > 0)
            return (Vector(x1,y1) ^ Vector(x2,y2)) > 0;
        if(y1 * y2 < 0)
            return y1 < 0;
        if(y1 == 0 && y2 == 0)
            return x1 > x2;
        if(y1 == 0 && x1 > 0)
            return y2 > 0;
        if(y1 == 0 && x1 <= 0)
            return false;
        if(x2 > 0)
            return y1 < 0;
        return true;
    }
    //找出faces, 并计算面积
    void getFaces()
    {
        for(int u=0; u<n; u++)
        {
            //给从u出发的各条边按极角排序
            sort(G[u].begin(),G[u].end(),cmp);
            int d = G[u].size();
            /*for(int i=0; i<d; i++)
            {
                for(int j=i+1; j<d; j++)
                {
                    if(edges[G[u][i]].ang > edges[G[u][j]].ang)
                        swap(G[u][i],G[u][j]);
                }
            }*/
            for(int i=0; i<d; i++)
                prev[G[u][(i+1)%d]] = G[u][i];
        }
        memset(vis,0,sizeof(vis));
        face_cnt=0;
        for(int u=0; u<n; u++)
        {
            for(int i=0; i<G[u].size(); i++)
            {
                int e = G[u][i];
                if(!vis[e]) //逆时针找圈
                {
                    face_cnt++;
                    Polygon poly;
                    for(;;)
                    {
                        vis[e] = 1;
                        left[e] = face_cnt;
                        int from = edges[e].u;
                        poly.PB(Point(x[from],y[from]));
                        e = prev[e^1];
                        if(e == G[u][i])
                            break;
                    }
                    faces.PB(poly);
                }
            }
        }
        for(int i=0; i<faces.size(); i++)
            area[i] = PolygonArea(faces[i]);
    }
} g;
