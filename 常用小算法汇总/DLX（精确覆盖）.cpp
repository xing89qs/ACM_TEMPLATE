
const int MAXN = 9 * 9 * 9 * 4 + 5;
const int MAXM = 9 * 9 + 5;
const int MAXNODE = 9 * 9 * 9 * 9 * 4 + 5;
//行编号从1开始，列编号为1~n，结点0是表头结点; 结点1~n是各列顶部的虚拟结点

class DLX
{
public:
    int m, sz;  //列数，结点数
    int nds[MAXN];  //每列结点数

    int row[MAXNODE], col[MAXNODE]; //row/col数组用来记录某个标号的结点在矩阵中的行号和列号
    int L[MAXNODE], R[MAXNODE], U[MAXNODE], D[MAXNODE]; //U/D/R/L数组用来记录某个标号的结点的上下左右结点的编号（十字链表）

    int ansd, ans[MAXM];    //解的数量和解

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
        memset(nds, 0, sizeof(nds));
    }

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
            nds[c]++;
            sz++;
        }
        R[sz - 1] = first;
        L[first] = sz - 1;
    }

    void removeNode(int c)
    {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
    }

    //删除列
    void removeCol(int c)
    {
        removeNode(c);
        for(int i = D[c]; i != c; i = D[i])
            removeRow(i);
    }

    void restoreNode(int c)
    {
        L[R[c]] = c;
        R[L[c]] = c;
    }

    //恢复列
    void restoreCol(int c)
    {
        for(int i = U[c]; i != c; i = U[i])
            restoreRow(i);
        restoreNode(c);
    }

    void removeRow(int r)
    {
        for(int j = R[r]; j != r; j = R[j])
        {
            U[D[j]] = U[j];
            D[U[j]] = D[j];
            --nds[col[j]];
        }
    }

    void restoreRow(int r)
    {
        for(int j = L[r]; j != r; j = L[j])
        {
            ++nds[col[j]];
            U[D[j]] = j;
            D[U[j]] = j;
        }
    }


    int ret;
    int vis[MAXN];

    void dfs(int d, int cost)
    {
        if(R[0] == 0)
        {
            ret = cost;
            return;
        }
        //找S最小的列来删除加速
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
        {
            if(nds[i] < nds[c])
                c = i;
        }
        removeCol(c);
        for(int i = D[c]; i != c; i = D[i])
        {
            for(int j = R[i]; j != i; j = R[j])
                removeCol(col[j]);
            dfs(d + 1, cost + ::c[row[i] - 1]);
            for(int j = L[i]; j != i; j = L[j])
                restoreCol(col[j]);
        }
        restoreCol(c);
    }

    int solve()
    {
        ret = INF;
        dfs(0, 0);
        return ret;
    }
} dlx;
