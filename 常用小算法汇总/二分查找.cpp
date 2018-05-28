
typedef int Type;

Type cal(Type val)
{
    /*这里写相关函数的表达式*/
}

//对于整数
Type biSearch(Type l,Type r,Type val)
{
    Type ans = -1;
    while(l <= r)   //对于整数
    {
        Type mid = (l + r) >> 1;    //对于整数
        if(cal(mid) < val)  //对于左边界能取到，右边界不能取到
        //if(cal(mid) <= val)   //对于右边界能取到，左边界不能取到
        {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    return ans;
}

//对于浮点数
Type biSearch(Type l,Type r,Type val)
{
    while(r - l >= EPS)   //对于浮点数
    {
        Type mid = (l + r) / 2.0;   //对于浮点数
        if(cal(mid) < val)  //对于左边界能取到，右边界不能取到
        //if(cal(mid) <= val)   //对于右边界能取到，左边界不能取到
            l = mid;
        else
            r = mid;
    }
    return l;   //对于左边界能取到，右边界不能取到
    //return r; //对于右边界能取到，左边界不能取到
}
