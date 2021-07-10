//Hopcroft-Karp������ͼ���ƥ�䣩�㷨

/*�������ͼ�ĵ�ֳ������㼯x,y��
���ȴ�����x��δƥ��ĵ����bfs��ά��x��y������dx,dy��
���y����δƥ��ĵ���ô���ҵ�һ���������·����¼��ǰ���ȣ����ڸó��ȵĽ���bfs��
bfs��֮��õ��������·�������������㷨������������dy[v]==dx[u]+1���������㡣
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

    int nx,ny;  //����Ҫƥ��ĵ㣬��Ϊx���ϵĵ��y���ϵĵ㡣nx,nyΪ�������е������
    int node;   //�ܽ������
    int cnt;
    int mx[MAXN],my[MAXN];  //mx��ʾ��x��Ե�y���,my��ʾ��y��Ե�x��š���Mx[i]��ֵ��ʾx������i�ŵ��ƥ��㣬My[j]��ֵ����y����j��ƥ��ĵ�
    int dx[MAXN],dy[MAXN];    //�������bfs������·�õ����飬����u->v�ɴ����dy[v]=dx[u]+1��dy,dx��ʾ�ڸ��Լ�����ı��
    int vis[MAXN];  //Ѱ������·�ı������
    int dis;


    void addEdge(int u,int v)
    {
        edge[cnt].to=v;
        edge[cnt].next=head[u];
        head[u]=cnt++;
    }

    bool bfs()   //Ѱ������·������ÿ��ֻѰ�ҵ�ǰ��̵�����·
    {
        queue <int> q;
        dis = INF;
        memset(dx,-1,sizeof(dx));
        memset(dy,-1,sizeof(dy));
        for(int i=1; i<=nx; i++)
        {
            if(mx[i]==-1)   //��δ�����Ľڵ���ӣ�����ʼ���νڵ����Ϊ0
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
                    if(my[v] == -1) //�ҵ���һ������·��disΪ����·�յ�ı��
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
            if(!vis[v] && dy[v]==dx[u]+1)   //����õ�û�б����������Ҿ���Ϊ��һ�ڵ�+1
            {
                vis[v]=1;
                if(my[v]!=-1 && dy[v]==dis) //u�ѱ�ƥ�����ѵ����д��ڵ�����·�յ�ı�ţ��ٵݹ�Ѱ��Ҳ��������·��ֱ������
                    continue;
                if(my[v]==-1 || dfs(my[v])) //�����ر�Ҫע�⣬Mx[u] == -1 && dfs(u)�Ⱥ�˳��ǧ���ܻ���dfs֮��Mx[u]�ͻ�仯
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

    int maxMatch()  //���ƥ��
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
