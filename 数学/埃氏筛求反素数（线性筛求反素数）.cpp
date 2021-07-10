
int ap[MAXN];   //反素数数组

void init() //埃式筛法求反素数
{
    for(int i = 1; i < MAXN; i++)
    {
        for(int j = 1; i * j < MAXN; j++)
            ap[i * j]++;
    }
}
