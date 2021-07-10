//启发式搜索A*算法

/*
 * A*算法是dijkstra最短路算法和BFS的结合
 * 公式：f(n) = g(n) + h(n)
 * g(n)代表起点到任意一个结点n的移动耗费
 * h(n)为结点n到终点的估价值，这个估价值可以用曼哈顿估价函数或欧几里得函数来计算
 * * 曼哈顿函数 = |终点ex - 当前点x| + |终点ey - 当前点y| * 10
 * * 欧几里得函数 = sqrt((终点ex - 当前点x) * (终点ex - 当前点x) + (终点ey - 当前点y) * (终点ey - 当前点y)) * 10
 * BFS是h(n) = 0的A*算法，并没有用到启发式；
 * Dijkstra算法是g(n) = 0的A*算法，从起点到终点用启发式；
 * 两者结合在一起就是A*算法。
 * 估价函数很明显我们选择最小的，所以用优先队列来维护最小值，每次取最优解，一直迭代直到到达目标。
*/

#define MAXN 305

struct Node
{
    int x,y;
    int step;
    int g,h,f;
    bool operator <(const Node &a) const
    {
        return f>a.f;
    }
};

bool vis[MAXN][MAXN];
int dx[]={1,-1,-2,-2,-1,1,2,2};
int dy[]={-2,-2,-1,1,2,2,1,-1};
int sx,sy;
int ex,ey;
int n;
int ans;

bool inMap(int x,int y)
{
    if(x>=0 && x<n && y>=0 && y<n)
        return true;
    return false;
}

int Abs(int x)
{
    return x>0?x:-x;
}

int getH(const Node &a)  //启发式函数h()
{
    return (int)sqrt((a.x - ex) * (a.x - ex) + (a.y - ey) * (a.y - ey)) * 10;   //使用欧氏距离估值
    //return Abs(a.x - ex) + Abs(a.y - ey) * 10;    //使用曼哈顿距离估值
}

void Astar()    //A*算法
{
    priority_queue <Node> pq;
    Node cur,nxt;
    cur.x = sx, cur.y = sy;
    cur.g = cur.step = 0;
    cur.h = getH(cur);
    cur.f = cur.g + cur.h;
    pq.push(cur);
    vis[sx][sy] = true;
    while(!pq.empty())
    {
        cur = pq.top();
        pq.pop();
        if(cur.x==ex && cur.y==ey)
        {
            ans = cur.step;
            return;
        }
        for(int i=0; i<8; i++)
        {
            nxt.x = cur.x + dx[i];
            nxt.y = cur.y + dy[i];
            if(inMap(nxt.x,nxt.y) && !vis[nxt.x][nxt.y])
            {
                nxt.step = cur.step + 1;
                nxt.g = cur.g + (len) * 10; //(len)为走一步的距离
                //nxt.g = cur.g + ceil((len) * 10); //向上取整
                nxt.h = getH(nxt);
                nxt.f = nxt.g + nxt.h;
                vis[nxt.x][nxt.y] = true;
                pq.push(nxt);
            }
        }
    }
}
