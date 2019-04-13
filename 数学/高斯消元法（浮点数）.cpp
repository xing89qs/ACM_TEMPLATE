
//EPS设置到1e-9
#define MAXN 205

/*模板1*/
double a[MAXN][MAXN];   //系数矩阵
double x[MAXN]; //解集（初始化时存储增广矩阵的常系数）

/*
高斯消元解浮点数系数方程
返回0表示无解，返回1表示有解
*/
int Gauss(int equ, int var) //equ为方程数，var为未知数个数
{
    int k, col;
    for(k = 0, col = 0; k < equ && col < var; k++,col++)
    {
        int max_r = k;
        for(int i = k + 1; i < equ; i++)
        {
            if(fabs(a[i][col]) > fabs(a[max_r][col]))
                max_r = i;
        }
        if(fabs(a[max_r][col]) < EPS)
            return 0;
        if(k != max_r)
        {
            for(int j = col; j < var; j++)
                swap(a[k][j],a[max_r][j]);
            swap(x[k],x[max_r]);
        }
        x[k] /= a[k][col];
        for(int j = col + 1; j < var; j++)
            a[k][j] /= a[k][col];
        a[k][col] = 1;
        for(int i = 0; i < equ; i++)
        {
            if(i != k)
            {
                x[i] -= x[k] * a[i][col];
                for(int j = col + 1; j < var; j++)
                    a[i][j] -= a[k][j] * a[i][col];
                a[i][col] = 0;
            }
        }
    }
    return 1;
}



/*模板2*/
double a[maxn][maxn];   //增广矩阵
double x[maxn]; //解集

/*
高斯消元解浮点数系数方程
返回0表示无解，返回1表示有解
*/
int Gauss(int equ, int var) //equ为方程数，var为未知数个数
{
    int k, col;
    for(k = 0, col = 0; k < equ && col < var; k++, col++)
    {
        int max_r = k;
        for(int i = k + 1; i < equ; i++)    //找到最大的数所在的行
        {
            if(fabs(a[i][col]) > fabs(a[max_r][col]))
                max_r = i;
        }
        if(fabs(a[max_r][col]) < EPS)
            return 0;
        if(k != max_r)  //交换行
        {
            for(int j = col; j < var + 1; j++)
                swap(a[k][j], a[max_r][j]);
        }
        for(int i = k+1; i < equ; i++)  //消去
        {
            if(a[i][col])
            {
                double tmp = -a[i][col] / a[k][col];
                for(int j = col; j < var + 1; j++)
                    a[i][j] += tmp * a[k][j];
            }
        }
    }
    for(int i = equ - 1; i >= 0; i--)   //回代
    {
        double tmp = a[i][var];
        for(int j = i + 1; j < var; j++)
            tmp -= x[j] * a[i][j];
        x[i] = tmp / a[i][i];
    }
    return 1;
}
