//《挑战程序设计竞赛》版
int exgcd(int a,int b,int &x,int &y)
{
    int d=a;
    if(b!=0)
    {
        d=exgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else
    {
        x=1;
        y=0;
    }
    return d;
}

//递归版
int exgcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    int d=exgcd(b,a%b,x,y);
    int t=x;
    x=y;
    y=t-a/b*y;
    return d;
}

//x,y全局变量版
int x;
int y;
int exgcd(int a,int b)
{
    if(b==0)
    {
        x=1;
        y=0;
        return a;
    }
    int d=exgcd(b,a%b);
    int t=x;
    x=y;
    y=t-a/b*y;
    return d;
}
