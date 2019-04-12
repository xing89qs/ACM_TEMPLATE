
#define MAXN 105

int a[MAXN][MAXN];  //增广矩阵
int x[MAXN];    //解集
int free_x[MAXN]; //用来存储自由变元（多解枚举自由变元可以使用）
int free_num; //自由变元的个数

/*
高斯消元解异或方程组（对2取模的01方程组）
返回值为-1表示无解，返回值为0表示有唯一解，否则返回自由变元个数
*/
int Gauss_xor(int equ, int var) //equ为方程数，var为未知数个数
{
    int col, k;
    free_num = 0;
    for(k = 0, col = 0; k < equ && col < var; k++, col++)
    {
        int max_r = k;
        for(int i = k + 1; i < equ; i++)
        {
            if(abs(a[i][col]) > abs(a[max_r][col])) //记录第一个第col列系数非零的行
                max_r = i;
        }
        if(a[max_r][col] == 0)
        {
            k--;
            free_x[free_num++] = col;   //这个是自由变元
            continue;
        }
        if(max_r != k)
        {
            for(int j = col; j < var + 1; j++)    //将第一个第col列系数非零的行换到第k行
                swap(a[k][j],a[max_r][j]);
        }
        for(int i = k + 1; i < equ; i++)    //开始消元
        {
            if(a[i][col])   //系数非零
            {
                for(int j = col; j < var + 1; j++)    //从当前第col列开始消元
                    a[i][j] ^= a[k][j];
            }
        }
    }
    /*无解*/
    for(int i = k; i < equ; i++)
    {
        if(a[i][col])
            return -1;
    }
    /*有无穷多解*/
    if(k < var) //
        return var - k; //返回自由变元个数
    /*有唯一解*/
    for(int i = var - 1; i >= 0; i--)
    {
        x[i] = a[i][var];
        for(int j = i + 1; j < var; j++)  //回代求出解集
            x[i] ^= (a[i][j] && x[j]);
    }
    return 0;
}
