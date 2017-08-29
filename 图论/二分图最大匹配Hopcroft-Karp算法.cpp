//Hopcroft-Karp（二分图最大匹配）算法

/*将点二分图的点分成两个点集x,y；
首先从所有x的未匹配的点进行bfs，维护x，y距离标号dx,dy；
如果y点是未匹配的点那么就找到一条最短增广路，记录当前长度，大于该长度的结束bfs；
bfs完之后得到最短增广路集，用匈牙利算法对所有允许弧（dy[v]==dx[u]+1）进行增广。
*/

#define MAXN 1005
#define MAXE 100005
#define INF 0x3f3f3f3f


class HopcroftKarp
{
private:
    int head[MAXN];
    struct Edge
    {
        int to,next;
        Edge(int to,int next):to(to),next(next) {}
        Edge() {}
    } edge[MAXE];

    int nx,ny;  //对于要匹配的点，分为x集合的点和y集合的点。nx,ny为两集合中点的数量
    int node;   //总结点数量
    int cnt;
    int mx[MAXN],my[MAXN];  //mx表示与x配对的y编号,my表示与y配对的x编号。即Mx[i]的值表示x集合中i号点的匹配点，My[j]的值就是y集合j点匹配的点
    int dx[MAXN],dy[MAXN];    //这里就是bfs找增广路用的数组，对于u->v可达就有dy[v]=dx[u]+1；dy,dx表示在各自集合里的编号
    int vis[MAXN];  //寻找增广路的标记数组
    int dis;


    void addEdge(int u,int v)
    {
        edge[cnt].to=v;
        edge[cnt].next=head[u];
        head[u]=cnt++;
    }

    bool bfs()   //寻找增广路径集，每次只寻找当前最短的增广路
    {
        queue <int> q;
        dis = INF;
        memset(dx,-1,sizeof(dx));
        memset(dy,-1,sizeof(dy));
        for(int i=1; i<=nx; i++)
        {
            if(mx[i]==-1)   //将未遍历的节点入队，并初始化次节点距离为0
            {
                q.push(i);
                dx[i]=0;
            }
        }
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            if(dx[u]>dis)
                break;
            for(int i=head[u]; i!=-1; i=edge[i].next)
            {
                int v = edge[i].to;
                if(dy[v] == -1)
                {
                    dy[v] = dx[u] + 1;
                    if(my[v] == -1) //找到了一条增广路，dis为增广路终点的标号
                        dis = dy[v];
                    else
                    {
                        dx[my[v]] = dy[v]+1;
                        q.push(my[v]);
                    }
                }
            }
        }
        return dis!=INF;
    }

    bool dfs(int u)
    {
        for(int i=head[u]; i!=-1; i=edge[i].next)
        {
            int v = edge[i].to;
            if(!vis[v] && dy[v]==dx[u]+1)   //如果该点没有被遍历过并且距离为上一节点+1
            {
                vis[v]=1;
                if(my[v]!=-1 && dy[v]==dis) //u已被匹配且已到所有存在的增广路终点的标号，再递归寻找也必无增广路，直接跳过
                    continue;
                if(my[v]==-1 || dfs(my[v])) //这里特别要注意，Mx[u] == -1 && dfs(u)先后顺序千万不能换，dfs之后Mx[u]就会变化
                {
                    my[v]=u;
                    mx[u]=v;
                    return true;
                }
            }
        }
        return false;
    }

public:
    void init()
    {
        cnt = 0;
        memset(mx,-1,sizeof(mx));
        memset(my,-1,sizeof(my));
    }

    int maxMatch()  //最大匹配
    {
        int ans = 0;
        while(bfs())
        {
            memset(vis,0,sizeof(vis));
            for(int i=1; i<=nx; i++)
            {
                if(mx[i]==-1 && dfs(i))
                    ans++;
            }
        }
        return ans;
    }

    void buildGraph()
    {
        memset(head,-1,sizeof(head));
        node = nx + ny;
    }
} hk;
