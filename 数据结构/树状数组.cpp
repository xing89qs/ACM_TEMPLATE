//树状数组模板

int bit[MAXN];  //注意，当数值范围太大的时候应该先离散化

void add(int i, int x)
{
    while(i <= MaxVal)   //MaxVal等于数值的最大值而不是数组的大小
    {
        bit[i] += x;
        i += lowbit(i);
    }
}

int getsum(int i)
{
    int sum = 0;
    while(i > 0)
    {
        sum += bit[i];
        i -= lowbit(i);
    }
    return sum;
}
