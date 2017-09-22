//最大流SAP算法

#define MAXN 10010
#define MAXE 1000010
#define INF 0x3f3f3f3f

//SAP算法
class SAP_QuickVersion
{
private:
    struct Edge
    {
        int from,to,next,cap;
        Edge(int from,int to,int next,int cap):from(from),to(to),next(next),cap(cap) {}
        Edge() {}
    } e[MAXE];

    int cnt;
    int head[MAXN];
    int dep[MAXN];
    int gap[MAXN];//gap[x]=y :说明残留网络中dep[i]==x的个数为y

    int n,m;
    int node;  //node是总的点的个数，包括源点和汇点

    void addEdge(int u,int v,int w)
    {
        e[cnt].from=u;
        e[cnt].to=v;
        e[cnt].cap=w;
        e[cnt].next=head[u];
        head[u]=cnt++;
        e[cnt].from=v;
        e[cnt].to=u;
        e[cnt].cap=0;
        e[cnt].next=head[v];
        head[v]=cnt++;
    }

    void bfs(int st,int ed)
    {
        memset(dep,-1,sizeof(dep));
        memset(gap,0,sizeof(gap));
        gap[0] = 1;
        int que[MAXN];
        int fnt,rear;
        fnt = rear = 0;
        dep[ed] = 0;
        que[rear++] = ed;
        while(fnt != rear)
        {
            int u = que[fnt++];
            if(fnt == MAXN)
                fnt = 0;
            for(int i=head[u]; ~i; i=e[i].next)
            {
                int v = e[i].to;
                if(dep[v] != -1)
                    continue;
                que[rear++] = v;
                if(rear == MAXN)
                    rear = 0;
                dep[v] = dep[u] + 1;
                ++gap[dep[v]];
            }
        }
    }

public:
    void init(int n,int m)
    {
        cnt = 0;
        memset(head,-1,sizeof(head));
        this -> n = n;
        this -> m = m;
    }

    int SAP(int st,int ed)
    {
        int res = 0;
        bfs(st,ed);
        int cur[MAXN];
        int S[MAXN];
        int top = 0;
        memcpy(cur,head,sizeof(head));
        int u = st;
        int i;
        while(dep[st] < node)
        {
            if(u == ed)
            {
                int temp = INF;
                int inser;
                for(i=0; i<top; i++)
                {
                    if(temp > e[S[i]].cap)
                    {
                        temp = e[S[i]].cap;
                        inser = i;
                    }
                }
                for(i=0; i<top; i++)
                {
                    e[S[i]].cap -= temp;
                    e[S[i]^1].cap += temp;
                }
                res += temp;
                top = inser;
                u = e[S[top]].from;
            }
            if(u != ed && gap[dep[u]-1] == 0) //出现断层，无增广路
                break;
            for(i=cur[u]; ~i; i=e[i].next)
            {
                if(e[i].cap != 0 && dep[u] == dep[e[i].to] + 1)
                    break;
            }
            if(i != -1)
            {
                cur[u] = i;
                S[top++] = i;
                u = e[i].to;
            }
            else
            {
                int Min = node;
                for(i=head[u]; ~i; i=e[i].next)
                {
                    if(e[i].cap == 0)
                        continue;
                    if(Min > dep[e[i].to])
                    {
                        Min = dep[e[i].to];
                        cur[u] = i;
                    }
                }
                --gap[dep[u]];
                dep[u] = Min+1;
                ++gap[dep[u]];
                if(u != st)
                    u = e[S[--top]].from;
            }
        }
        return res;
    }

    void buildGraph()
    {
        node = n + 1;
    }
} sap;
