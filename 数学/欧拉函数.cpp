
/* 求某个数的欧拉函数值（复杂度O(sqrt(n))） */
int getPhi(int x)
{
    int ans = x;
    int cnt = sqrt(x + 0.5) + 1;
    for(int i = 2; i < cnt; i++)
    {
        if(x % i == 0)
        {
            ans -= ans / i;
            while(x % i == 0)
                x /= i;
        }
        if(x == 1)
            break;
    }
    if(x > 1)
        ans -= ans / x;
    return ans;
}


/* 埃氏筛求欧拉函数表（复杂度O(nlogn)） */
int phi[MAXN];

void getEuler()
{
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for(int i = 2; i < MAXN; i++)
    {
        if(!phi[i]) //满足该条件的为素数
        {
            for(int j = i; j < MAXN; j += i)
            {
                if(!phi[j])
                    phi[j] = j;
                phi[j] -= phi[j] / i;
            }
        }
    }
}


/* 线性筛求欧拉函数表（复杂度O(n)） */
bool isprime[MAXN];
int prime[MAXN];
int phi[MAXN];
int phicnt;

void fastEuler()
{
    memset(isprime, true, sizeof(isprime));
    isprime[0] = isprime[1] = false;
    phi[1] = 1;
    phicnt = 0;
    for(int i = 2; i < MAXN; i++)
    {
        if(isprime[i])
        {
            prime[phicnt++] = i;
            phi[i] = i - 1; //如果 n = p ^ k 且 p 为素数，则 phi(n) = p ^ k - p ^ (k - 1) = (p - 1) * p ^ (k - 1)
        }
        for(int j = 0; j < phicnt; j++)
        {
            if(i * prime[j] > MAXN)
                break;
            isprime[i * prime[j]] = false;
            if(i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];  //欧拉函数递推式
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        }
    }
}
