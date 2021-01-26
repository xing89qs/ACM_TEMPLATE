
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

    bool dfs(int d)
    {
        if(R[0] == 0)   //找到解
        {
            ansd = d;
            return true;
        }
        //找S最小的列来删除加速
        int c = R[0];   // 第一个未删除的列
        for(int i = R[0]; i != 0; i = R[i])
        {
            if(nds[i] < nds[c])
                c = i;
        }
        removeCol(c);   //删除第c列
        for(int i = D[c]; i != c; i = D[i]) //用结点i所在行覆盖第c列
        {
            ans[d] = row[i];
            for(int j = R[i]; j != i; j = R[j]) //删除结点i所在行能覆盖的所有其他列
                removeCol(col[j]);
            if(dfs(d + 1))
                return true;
            for(int j = L[i]; j != i; j = L[j]) //恢复结点i所在行能覆盖的所有其他列
                restoreCol(col[j]);
        }
        restoreCol(c);  //恢复第c列
        return false;
    }

    int solve(char *str)
    {
        init(9 * 9 + (3 * 9) * 9);  //9*9的九宫格每个格子只能填一个数字 + 9行9列9个3*3方格每一种都限制只能有1个1~9的数字
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                int idx = i * 9 + j;    //每个格子在字符串中的下标
                if(str[idx] != '.')   //该格子已经填了数字
                {
                    int num = str[idx] - '0';
                    vector<int> v;
                    v.PB(i * 9 + j + 1);    //第i行第j列只能填一个数字
                    v.PB(9 * 9 + i * 9 + num);  //第i行已经填了数字num
                    v.PB(9 * 9 * 2 + j * 9 + num);  //第j行已经填了数字num
                    v.PB(9 * 9 * 3 + (i / 3 * 3 + j / 3) * 9 + num);  //第(i/3*3+j/3)个3*3的格子已经填了数字num
                    addRow(9 * 9 * i + 9 * j + num, v);
                }
                else    //该格子未填数字
                {
                    for(int num = 1; num <= 9; num++)
                    {
                        vector<int> v;
                        v.PB(i * 9 + j + 1);    //第i行第j列只能填一个数字
                        v.PB(9 * 9 + i * 9 + num);  //第i行已经填了数字num
                        v.PB(9 * 9 * 2 + j * 9 + num);  //第j行已经填了数字num
                        v.PB(9 * 9 * 3 + (i / 3 * 3 + j / 3) * 9 + num);  //第(i/3*3+j/3)个3*3的格子已经填了数字num
                        addRow(9 * 9 * i + 9 * j + num, v);
                    }
                }
            }
        }
        dfs(0);
        int sud[10][10];
        for(int i = 0; i < ansd; i++)
        {
            int tmp = ans[i];
            tmp--;
            int val = tmp % 9 + 1;
            tmp /= 9;
            int c = tmp % 9;
            tmp /= 9;
            int r = tmp;
            sud[r][c] = val;
        }
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
                printf("%d", sud[i][j]);
            puts("");
        }
    }
} dlx;
