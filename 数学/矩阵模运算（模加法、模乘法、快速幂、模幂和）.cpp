
typedef LL Type;

const int MAXN = 55;
const LL MOD = 1000000007;

int n;
Type mod;

/* 矩阵类 */
struct Matrix
{
    Type x[MAXN][MAXN];
    void init()
    {
        memset(x, 0, sizeof(x));
    }
    /* 初始化为单位矩阵 */
    void toIdentity()
    {
        memset(x, 0, sizeof(x));
        for(int i = 0; i < n; i++)
            x[i][i] = 1;
    }
    /* 输出矩阵 */
    void print()
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                printf("%lld%c", x[i][j], j == n - 1 ? '\n' : ' ');
    }
} A;

/* 矩阵模乘法 */
Matrix mul(Matrix a, Matrix b)  //(a * b) % mod
{
    Matrix ans;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            ans.x[i][j] = 0;
            for(int k = 0; k < n; k++)
                ans.x[i][j] += a.x[i][k] * b.x[k][j];
            ans.x[i][j] %= mod;
        }
    }
    return ans;
}

/* 矩阵模加法 */
Matrix add(Matrix a, Matrix b)  //(a + b) % mod
{
    int i, j;
    Matrix ans;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            ans.x[i][j] = a.x[i][j] + b.x[i][j];
            ans.x[i][j] %= mod;
        }
    }
    return ans;
}

/* 矩阵快速幂 */
Matrix pow(Matrix a, Type k)    //(a ^ n) % mod
{
    Matrix ans;
    ans.toIdentity();
    while(k)
    {
        if(k & 1)   //k % 2
            ans = mul(ans, a);
        k /= 2;
        a = mul(a, a);
    }
    return ans;
}

/* 矩阵模幂和 */
Matrix sum(Matrix a, Type k)    //(a + a ^ 2 + a ^ 3 + ... + a ^ n) % mod
{
    Type m;
    Matrix ans, pre;
    if(k == 1)
        return a;
    m = k / 2;
    pre = sum(a, m);    //[1, n / 2]
    ans = add(pre, mul(pre, pow(a, m)));    //ans = [1, n / 2] + a ^ (n / 2) * [1, n / 2]
    if(n & 1)
        ans = add(ans, pow(a, k));  // ans = ans + a ^ n
    return ans;
}
