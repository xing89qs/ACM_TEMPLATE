
/* 线性预处理逆元 */

LL inv[MAXN];
LL res[MAXN];
LL fac[MAXN];

void initInv()
{
    inv[1] = 1;
    fac[1] = 1;
    res[1] = 1;
    for(int i = 2; i<MAXN; i++)
    {
        inv[i] = 1LL * MOD / i * (MOD - inv[MOD % i]) % MOD;
        res[i] = (inv[i] * res[i - 1]) % MOD;
        fac[i] = 1LL * (fac[i - 1] * i) % MOD;
    }
}

LL C(int n, int m)  //求组合数C(n,m)
{
    if(n < m || m < 0)  //过滤不合法的输入
        return 0;
    if(m == 0 || m == n)
        return 1;
    return fac[n] * res[n - m] % MOD * res[m] % MOD;
}


/* Lucas定理求逆元 */

LL inv[MAXN];
LL fac[MAXN];

void initInv()
{
    inv[0] = fac[0] = inv[1] = fac[1] = 1;
    for(int i = 1; i < MAXN; i++)
    fac[i] = fac[i - 1] * i % MOD;
    for(int i = 2; i < MAXN; i++)
    inv[i] = (MOD - (MOD / i)) * inv[MOD % i] % MOD;    //Lucas定理
    for(int i = 1; i < MAXN; i++)
    inv[i] = inv[i - 1] * inv[i] % MOD;
}

LL C(int n, int m)  //求组合数C(n,m)
{
    if(n < m || m < 0)  //过滤不合法的输入
        return 0;
    return (fac[n] * inv[m] % MOD) * inv[n - m] % MOD;
}
