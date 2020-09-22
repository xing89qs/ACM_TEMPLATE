//有向图判环（DFS染色法）

int color[MAXN];

bool dfs(int u)
{
    color[u] = 1;
    for(int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].to;
        if(color[v] == 1)
            return true;
        if(!color[v] && dfs(v)) //下一个结点还未被处理过
            return true;
    }
    color[u] = 2;
    return false;
}

bool findLoop(int n)
{
    for(int i = 0; i < n; i++)
    {
        if(!color[i])
        {
            if(dfs(i))
                return true;
        }
    }
    return false;
}
