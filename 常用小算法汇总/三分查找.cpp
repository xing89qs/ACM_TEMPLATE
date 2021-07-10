
/*
三分查找主要用来求凸性的函数的极值（最大值/最小值）
精度设置为EPS=1e-9以上不容易WA
*/

typedef double Type;

Type cal(Type val)
{
    /*这里根据凸性函数的表达式进行计算*/
}

pair<double,double> ternarySearch(Type l,Type r)  //三分函数
{
    while(r - l >= EPS)
    {
        double lmid = (l + r) / 2.0, rmid = (lmid + r) / 2.0;
        if(cal(lmid) >= cal(rmid))
            r = rmid;
        else
            l = lmid;
    }
    return MP(l,cal(l));    //返回函数的x值和y值
}
