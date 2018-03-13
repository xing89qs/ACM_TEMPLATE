//有向图判环（DFS染色法）

int color[MAXN];

bool findLoop(int u)
{
    color[u] = 1;
    for(int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].to;
        if(color[v] == 1)
            return true;
        if(findLoop(v))
            return true;
    }
    color[u] = 2;
    return false;
}
