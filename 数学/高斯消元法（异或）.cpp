
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
        for(int i = k+1; i < equ; i++)
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
            for(int j = col; j < var+1; j++)    //将第一个第col列系数非零的行换到第k行
                swap(a[k][j],a[max_r][j]);
        }
        for(int i = k+1; i < equ; i++)    //开始消元
        {
            if(a[i][col])   //系数非零
            {
                for(int j = col; j < var+1; j++)    //从当前第col列开始消元
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
    for(int i = var-1; i >= 0; i--)
    {
        x[i] = a[i][var];
        for(int j = i+1; j < var; j++)  //回代求出解集
            x[i] ^= (a[i][j] && x[j]);
    }
    return 0;
}

int solve(int equ, int var) //枚举自由变元
{
    int res = Gauss_xor(equ,var);
    if(res == -1)   //无解
        return -1;
    else if(res == 0)   //唯一解
    {
        int ans = 0;
        for(int i = 0; i < var; i++)
            ans += x[i];
        return ans;
    }
    else    //多解（枚举自由变元）
    {
        int ans = INF;
        for(int i = 0; i < (1<<res); i++)   //枚举所有状态
        {
            int cnt = 0;   //当前涂色方案需要涂的次数
            for(int j = 0; j < res; j++)  //枚举自由变元
            {
                x[free_x[j]] = (i & (1<<j));  //该自由变元取1
                if(x[free_x[j]])
                    cnt++;
            }
            for(int j = var-res-1; j >= 0; j--)   //从消完元矩阵的主对角线非0的最后一行开始回代
            {
                int idx;
                for(idx = j; idx < var; idx++)
                {
                    if(a[j][idx])
                        break;
                }
                x[idx] = a[j][var];
                for(int l = idx+1; l < var; l++)  //回代求出解集
                {
                    if(a[j][l])
                        x[idx] ^= x[l];
                }
                cnt += x[idx];
            }
            ans = min(ans,cnt);
        }
        return ans;
    }
}
