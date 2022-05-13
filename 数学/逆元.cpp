
/** 扩展欧几里得算法求逆元 **/
int modInv(int a, int m)
{
    int x, y;
    exgcd(a, m, x, y);
    return (m + x % m) % m;
}


/** 费马小定理 / 欧拉定理求逆元 **/
LL modInv(LL x, LL mod)
{
    return quickPow(x, mod - 2, mod);
}
