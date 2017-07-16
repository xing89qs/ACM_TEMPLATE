//可以直接使用__gcd(int x,int y)函数
int gcd(int a,int b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}
