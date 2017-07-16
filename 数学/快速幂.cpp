
#define long long LL

//非递归版
LL quickPow(LL x,LL k,LL mod)
{
    LL res = 1;
    while(k > 0)
    {
        if(k & 1)
            res = res * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return res;
}


//递归版
LL quickPow(LL x,LL k,LL mod)
{
    if(k == 0)
        return 1;
    LL res = quickPow(x*x%mod,n/2,mod);
    if(n & 1)
        res = res * x % mod;
    return res;
}
