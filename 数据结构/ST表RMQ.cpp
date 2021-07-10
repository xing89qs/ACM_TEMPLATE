
int logg[MAXN]; //计算log2(i)
int st[21][MAXN];

void init_rmq(int n)
{
    logg[1] = 0;
    for(int i = 2; i <= n; i++) //预处理log2(i)
        logg[i] = logg[i >> 1] + 1;
    for(int i = 1; i <= n; i++) //初始化ST表
    {
        scanf("%d", &st[0][i]);
        //st[0][i] = a[i];
    }
    for(int j = 1; (1 << j) < n; j++)   //预处理计算出ST表
    {
        //for(int i = 0; i < n - (1 << j) + 1; i++)
        for(int i = 1; i + (1 << j) - 1 <= n; i++)
            st[j][i] = max/min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
}

int RMQ(int l, int r)   //利用ST表O(1)复杂度RMQ
{
    int k = logg[r - l + 1];
    return max/min(st[k][l], st[k][r - (1 << k) + 1]);
}
