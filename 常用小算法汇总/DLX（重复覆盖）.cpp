
class DLX
{
public:
    int m, sz;  //列数，结点数
    int S[MAXN];    //每列结点数

    int row[MAXNODE], col[MAXNODE]; //row/col数组用来记录某个标号的结点在矩阵中的行号和列号
    int L[MAXNODE], R[MAXNODE], U[MAXNODE], D[MAXNODE]; //U/D/R/L数组用来记录某个标号的结点的上下左右结点的编号（十字链表）

    int ansd, ans[MAXN];    //解的数量和解

    void init(int m)    //m为列数
    {
        this -> m = m;
        //虚拟结点
        for(int i = 0; i <= m; i++)
        {
            U[i] = i, D[i] = i, L[i] = i - 1, R[i] = i + 1;
            col[i] = i;
        }
        R[m] = 0, L[0] = m;
        sz = m + 1;
        memset(S, 0, sizeof(S));
    }

    //行列都是从1开始标号
    void addRow(int r, vector<int>& columns)
    {
        int first = sz;
        for(int i = 0; i < (int)columns.size(); i++)
        {
            int c = columns[i];
            L[sz] = sz - 1;
            R[sz] = sz + 1;
            D[sz] = c;
            U[sz] = U[c];
            D[U[c]] = sz;
            U[c] = sz;
            row[sz] = r;
            col[sz] = c;
            S[c]++;
            sz++;
        }
        R[sz - 1] = first;
        L[first] = sz - 1;
    }

    void removeNode(int c)
    {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        --S[col[c]];
    }

    //删除列
    void removeCol(int c)
    {
        for(int i = D[c]; i != c; i = D[i])
            removeNode(i);
    }

    void restoreNode(int c)
    {
        ++S[col[c]];
        L[R[c]] = c;
        R[L[c]] = c;
    }

    //恢复列
    void restoreCol(int c)
    {
        for(int i = U[c]; i != c; i = U[i])
            restoreNode(i);
    }

    int ret;
    int vis[MAXN];

    int h() //估价函数：模拟删除列，函数返回的是至少还需要多少行才能完成重复覆盖
    {
        memset(vis, 0, sizeof(vis));
        int res = 0;
        for(int i = R[0]; i != 0; i = R[i])
        {
            if(vis[col[i]])
                continue;
            vis[col[i]] = 1;
            ++res;
            for(int j = D[i]; j != i; j = D[j])
            {
                if(col[j])
                {
                    for(int k = R[j]; k != j; k = R[k])
                        vis[col[k]] = 1;
                }
            }
        }
        return res;
    }

    bool dfs(int d, int cost)
    {
        if(cost + h() > k)
            return false;
        if(R[0] == 0)
        {
            //ansd = min(ansd, d);
            return true;
        }
        //找S最小的列来删除加速
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
        {
            if(S[i] < S[c])
                c = i;
        }
        for(int i = D[c]; i != c; i = D[i])
        {
            //ans[d] = row[i];  //记录解
            removeCol(i);
            for(int j = R[i]; j != i; j = R[j])
                removeCol(j);
            if(dfs(d + 1, cost + 1))
                return true;
            for(int j = L[i]; j != i; j = L[j])
                restoreCol(j);
            restoreCol(i);
        }
        return false;
    }

    void solve()
    {
        for(ansd = 0; ansd <= m; ansd++)
        {
            if(dfs(0, 0))
                break;
        }
        /*
        ansd = INF;
        dfs(0, 0);
        */
        printf("%d\n", ansd);
    }
} dlx;
