
int ap[MAXN];   //����������

void init() //��ʽɸ��������
{
    for(int i = 1; i < MAXN; i++)
    {
        for(int j = 1; i * j < MAXN; j++)
            ap[i * j]++;
    }
}
