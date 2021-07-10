//二维树状数组模板

int bit2D[MAXN][MAXN];
int n,m;

void add2D(int x, int y, int val)   //类似于前缀和
{
    for(int i = x; i <= n; i += lowbit(i))  //n为矩阵其中一维的大小
    {
        for(int j = y; j <= m; j += lowbit(j))  //m为矩阵另外一维的大小
            bit2D[i][j] += val;
    }
}

int getSum2D(int x,int y)
{
    int sum = 0;
    for(int i = x; i > 0; i -= lowbit(i))
    {
        for(int j = y; j > 0; j -= lowbit(j))
            sum += bit2D[i][j];
    }
    return sum;
}
