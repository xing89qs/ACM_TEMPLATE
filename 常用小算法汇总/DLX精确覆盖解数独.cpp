
const int MAXN = 9 * 9 * 9 * 4 + 5;
const int MAXM = 9 * 9 + 5;
const int MAXNODE = 9 * 9 * 9 * 9 * 4 + 5;
//�б�Ŵ�1��ʼ���б��Ϊ1~n�����0�Ǳ�ͷ���; ���1~n�Ǹ��ж�����������

class DLX
{
public:
    int m, sz;  //�����������
    int nds[MAXN];  //ÿ�н����

    int row[MAXNODE], col[MAXNODE]; //row/col����������¼ĳ����ŵĽ���ھ����е��кź��к�
    int L[MAXNODE], R[MAXNODE], U[MAXNODE], D[MAXNODE]; //U/D/R/L����������¼ĳ����ŵĽ����������ҽ��ı�ţ�ʮ������

    int ansd, ans[MAXM];    //��������ͽ�

    void init(int m)    //mΪ����
    {
        this -> m = m;
        //������
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

    //ɾ����
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

    //�ָ���
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
        if(R[0] == 0)   //�ҵ���
        {
            ansd = d;
            return true;
        }
        //��S��С������ɾ������
        int c = R[0];   // ��һ��δɾ������
        for(int i = R[0]; i != 0; i = R[i])
        {
            if(nds[i] < nds[c])
                c = i;
        }
        removeCol(c);   //ɾ����c��
        for(int i = D[c]; i != c; i = D[i]) //�ý��i�����и��ǵ�c��
        {
            ans[d] = row[i];
            for(int j = R[i]; j != i; j = R[j]) //ɾ�����i�������ܸ��ǵ�����������
                removeCol(col[j]);
            if(dfs(d + 1))
                return true;
            for(int j = L[i]; j != i; j = L[j]) //�ָ����i�������ܸ��ǵ�����������
                restoreCol(col[j]);
        }
        restoreCol(c);  //�ָ���c��
        return false;
    }

    int solve(char *str)
    {
        init(9 * 9 + (3 * 9) * 9);  //9*9�ľŹ���ÿ������ֻ����һ������ + 9��9��9��3*3����ÿһ�ֶ�����ֻ����1��1~9������
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                int idx = i * 9 + j;    //ÿ���������ַ����е��±�
                if(str[idx] != '.')   //�ø����Ѿ���������
                {
                    int num = str[idx] - '0';
                    vector<int> v;
                    v.PB(i * 9 + j + 1);    //��i�е�j��ֻ����һ������
                    v.PB(9 * 9 + i * 9 + num);  //��i���Ѿ���������num
                    v.PB(9 * 9 * 2 + j * 9 + num);  //��j���Ѿ���������num
                    v.PB(9 * 9 * 3 + (i / 3 * 3 + j / 3) * 9 + num);  //��(i/3*3+j/3)��3*3�ĸ����Ѿ���������num
                    addRow(9 * 9 * i + 9 * j + num, v);
                }
                else    //�ø���δ������
                {
                    for(int num = 1; num <= 9; num++)
                    {
                        vector<int> v;
                        v.PB(i * 9 + j + 1);    //��i�е�j��ֻ����һ������
                        v.PB(9 * 9 + i * 9 + num);  //��i���Ѿ���������num
                        v.PB(9 * 9 * 2 + j * 9 + num);  //��j���Ѿ���������num
                        v.PB(9 * 9 * 3 + (i / 3 * 3 + j / 3) * 9 + num);  //��(i/3*3+j/3)��3*3�ĸ����Ѿ���������num
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
