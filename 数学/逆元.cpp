//求逆元

int modInv(int a,int m)
{
    int x,y;
    exgcd(a,m,x,y);
    return (m + x % m) % m;
}
