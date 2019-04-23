
#define MAXN 105

int a[MAXN][MAXN];  //增广矩阵
int x[MAXN];    //解集
bool free_x[MAXN];  //标记是否是不确定的变元（1为不确定，0为确定）

/*
void print(int equ, int var)
{
    for(int i = 0; i < equ; i++)
    {
        for(int j = 0; j < var + 1; j++)
            printf("%d ",a[i][j]);
        puts("");
    }
    puts("");
}
*/

inline int lcm(int a,int b)
{
    return a / __gcd(a,b) * b;  //先除后乘防止溢出
}

/*
返回-2表示有浮点数解，但无整数解；
返回-1表示无解；
返回0表示有唯一解；
返回大于0表示无穷解，返回值为自由变元的个数
*/
int Gauss(int equ,int var)  //equ为方程个数，var为变元个数。增广矩阵为 equ 行 * (var+1) 列（下标均从0开始）
{
    int k, col;
    int free_x_num;
    int free_index;
    memset(free_x,true,sizeof(free_x));
    /*化为阶梯矩阵*/
    for(k = 0, col = 0; k < equ && col < var; k++,col++) //枚举当前处理的行
    {
        int max_r = k;  //当前这列绝对值最大的行
        //找到该col列元素绝对值最大的那行
        for(int i = k + 1; i < equ; i++)
        {
            if(abs(a[i][col]) > abs(a[max_r][col]))
                max_r = i;
        }
        if(a[max_r][col] == 0)  //第col列第k行以下全是0，处理当前行的下一列即可
        {
            k--;
            continue;
        }
        if(max_r != k)
        {
            for(int j = col; j < var + 1; j++)    //与第k行交换，减小除法时的误差
                swap(a[k][j],a[max_r][j]);
        }
        for(int i = k + 1; i < equ; i++)    //消元，化为行阶梯矩阵
        {
            if(a[i][col])   //非零元素
            {
                int LCM = lcm(abs(a[i][col]),abs(a[k][col]));
                int ta = LCM / abs(a[i][col]);
                int tb = LCM / abs(a[k][col]);
                if(a[i][col] * a[k][col] < 0)   //两行对应元素异号
                    tb = -tb;   //其中一个元素系数取反
                for(int j = col; j < var + 1; j++)
                    a[i][j] = a[i][j] * ta - a[k][j] * tb;
            }
        }
    }

    /*1.无解（行阶梯矩阵中存在(0,0,...;a)这样的行，其中 a != 0 */
    for(int i = k; i < equ; i++)
    {
        if(a[i][col])
            return -1;
    }
    /*2.无穷多解（行阶梯矩阵中出现(0,0,...,0;0)这样的行，则存在自由变元；出现的行数即为自由变元的个数*/
    if(k < var)
    {
        //自由变元有 (var - k) 个，即不确定的变元至少有 (var - k) 个
        for(int i = k - 1; i >= 0; i--)
        {
            //第0行到第k-1行不会是(0,0,...0;0)
            free_x_num = 0; //用于判断该行中的不确定的变元的个数
            for(int j = 0; j < var; j++)
            {
                if(a[i][j] && free_x[j])
                {
                    free_x_num++;
                    free_index = j;
                }
            }
            if(free_x_num > 1)  //变元的个数超过1个，无法求解（它们仍然为不确定的变元）
                continue;
            //说明就只有一个不确定的变元free_index，那么可以求解出该变元，且该变元是确定的
            int tmp = a[i][var];
            for(int j = 0; j < var; j++)
            {
                if(a[i][j] != 0 && j != free_index)
                    tmp -= a[i][j] * x[j];
            }
            x[free_index] = tmp / a[i][free_index];    //求出该变元
            free_x[free_index] = 0; //该变元是确定的
        }
        return var - k; //返回自由变元数量
    }
    /*3.唯一解*/
    for(int i = var - 1; i >= 0; i--)
    {
        int tmp = a[i][var];
        for(int j = i + 1; j < var; j++)
        {
            if(a[i][j])
                tmp -= a[i][j] * x[j];
        }
        if(tmp % a[i][i])
            return -2;  //有浮点数解，但无整数解
        x[i] = tmp / a[i][i];
    }
    return 0;
}
