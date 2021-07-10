
/* C++大数加减乘除取模模板 */


/* 模板一 */

struct BigInteger
{
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    BigInteger& clean()
    {
        while(!s.back() && s.size() > 1)
            s.pop_back();
        return *this;
    }
    BigInteger(ULL num = 0)
    {
        *this = num;
    }
    BigInteger(string s)
    {
        *this = s;
    }
    BigInteger& operator = (long long num)
    {
        s.clear();
        do
        {
            s.push_back(num % BASE);
            num /= BASE;
        }
        while(num > 0);
        return *this;
    }
    BigInteger& operator = (const string& str)
    {
        s.clear();
        int x, len = (str.length() - 1) / WIDTH + 1;
        for(int i = 0; i < len; i++)
        {
            int end = str.length() - i * WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(str.substr(start, end - start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return (*this).clean();
    }

    BigInteger operator + (const BigInteger& b) const
    {
        BigInteger c;
        c.s.clear();
        for(int i = 0, g = 0; ; i++)
        {
            if(g == 0 && i >= s.size() && i >= b.s.size())
                break;
            int x = g;
            if(i < s.size())
                x += s[i];
            if(i < b.s.size())
                x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }
    BigInteger operator - (const BigInteger& b) const
    {
        assert(b <= *this); // 减数不能大于被减数
        BigInteger c;
        c.s.clear();
        for(int i = 0, g = 0; ; i++)
        {
            if(g == 0 && i >= s.size() && i >= b.s.size())
                break;
            int x = s[i] + g;
            if(i < b.s.size())
                x -= b.s[i];
            if(x < 0)
            {
                g = -1;
                x += BASE;
            }
            else
                g = 0;
            c.s.push_back(x);
        }
        return c.clean();
    }
    BigInteger operator * (const BigInteger& b) const
    {
        int i, j;
        ULL g;
        vector<ULL> v(s.size() + b.s.size(), 0);
        BigInteger c;
        c.s.clear();
        for(i = 0; i < s.size(); i++)
            for(j = 0; j < b.s.size(); j++)
                v[i + j] += ULL(s[i]) * b.s[j];
        for(i = 0, g = 0; ; i++)
        {
            if(g == 0 && i >= v.size())
                break;
            ULL x = v[i] + g;
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c.clean();
    }
    BigInteger operator / (const BigInteger& b) const
    {
        assert(b > 0);  // 除数必须大于0
        BigInteger c = *this;       // 商:主要是让c.s和(*this).s的vector一样大
        BigInteger m;               // 余数:初始化为0
        for(int i = s.size() - 1; i >= 0; i--)
        {
            m = m * BASE + s[i];
            c.s[i] = bsearch(b, m);
            m -= b * c.s[i];
        }
        return c.clean();
    }
    BigInteger operator % (const BigInteger& b) const   //方法与除法相同
    {
        BigInteger c = *this;
        BigInteger m;
        for(int i = s.size() - 1; i >= 0; i--)
        {
            m = m * BASE + s[i];
            c.s[i] = bsearch(b, m);
            m -= b * c.s[i];
        }
        return m;
    }
    // 二分法找出满足bx<=m的最大的x
    int bsearch(const BigInteger& b, const BigInteger& m) const
    {
        int L = 0, R = BASE - 1, x;
        while(1)
        {
            x = (L + R) >> 1;
            if(b * x <= m)
            {
                if(b * (x + 1) > m)
                    return x;
                else
                    L = x;
            }
            else
                R = x;
        }
    }
    BigInteger& operator += (const BigInteger& b)
    {
        *this = *this + b;
        return *this;
    }
    BigInteger& operator -= (const BigInteger& b)
    {
        *this = *this - b;
        return *this;
    }
    BigInteger& operator *= (const BigInteger& b)
    {
        *this = *this * b;
        return *this;
    }
    BigInteger& operator /= (const BigInteger& b)
    {
        *this = *this / b;
        return *this;
    }
    BigInteger& operator %= (const BigInteger& b)
    {
        *this = *this % b;
        return *this;
    }

    bool operator < (const BigInteger& b) const
    {
        if (s.size() != b.s.size())
            return s.size() < b.s.size();
        for (int i = s.size() - 1; i >= 0; i--)
            if (s[i] != b.s[i])
                return s[i] < b.s[i];
        return false;
    }
    bool operator > (const BigInteger& b) const
    {
        return b < *this;
    }
    bool operator <= (const BigInteger& b) const
    {
        return !(b < *this);
    }
    bool operator >= (const BigInteger& b) const
    {
        return !(*this < b);
    }
    bool operator != (const BigInteger& b) const
    {
        return b < *this || *this < b;
    }
    bool operator == (const BigInteger& b) const
    {
        return !(b < *this) && !(b > *this);
    }
};

ostream& operator << (ostream& out, const BigInteger& x)
{
    out << x.s.back();
    for (int i = x.s.size() - 2; i >= 0; i--)
    {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]);
        for (int j = 0; j < strlen(buf); j++)
            out << buf[j];
    }
    return out;
}

istream& operator >> (istream& in, BigInteger& x)
{
    string s;
    if (!(in >> s))
        return in;
    x = s;
    return in;
}

int main()
{
    int n;
    scanf("%d", &n);
    BigInteger x = 2;
    for(int i = 1; i <= n; i++)
    {
        cout << x << endl;
        x = x * (x - 1) + 1;
    }
    return 0;
}


/* 模板二（能解决更大数的运算且速度更快） */

const int DEFAULT_SIZE = 100;
struct BigInteger : vector<long long>
{
    static const long long BASE = 100000000;
    static const int BASE_DIGIT = 8;
    int sign;

    // constructor
    BigInteger(long long num = 0) : vector<long long>(DEFAULT_SIZE, 0), sign(1)
    {
        if (num < 0) sign = -1, num = -num;
        (*this)[0] = num;
        this->normalize();
    }
    BigInteger(int size, long long num) : vector<long long>(size, num), sign(1) {}
    BigInteger& normalize()
    {
        long long c = 0;
        bool exist = false;
        for (int i = 0;; ++i)
        {
            if (i >= this->size()) this->push_back(0);
            if ((*this)[i] < 0 && i+1 >= this->size()) this->push_back(0);
            while ((*this)[i] < 0)
            {
                (*this)[i+1] -= 1;
                (*this)[i] += BASE;
            }
            long long a = (*this)[i] + c;
            (*this)[i] = a % BASE;
            if ((*this)[i]) exist = true;
            c = a / BASE;
            if (c == 0 && i == this->size()-1) break;
        }
        if (!exist) sign = 1;
        return (*this);
    }
    friend BigInteger abs(const BigInteger &x)
    {
        BigInteger z = x;
        if (z.sign == -1) z.sign = 1;
        return z;
    }
    friend ostream &operator << (ostream &os, const BigInteger &x)
    {
        if (x.sign == -1) os << '-';
        int d = x.size()-1;
        for (d = x.size()-1; d >= 0; --d) if (x[d] > 0) break;
        if (d == -1) os << 0;
        else os << x[d];
        for (int i = d-1; i >= 0; --i)
        {
            os.width(BigInteger::BASE_DIGIT);
            os.fill('0');
            os << x[i];
        }
        return os;
    }

    // operation
    BigInteger operator - () const
    {
        BigInteger res = *this;
        bool allzero = true;
        for (int i = 0; i < this->size(); ++i)
        {
            if (res[i] != 0)
            {
                allzero = false;
                break;
            }
        }
        if (!allzero) res.sign = -res.sign;
        return res;
    }
    BigInteger& operator += (const BigInteger& r)
    {
        while (size() < r.size()) this->emplace_back(0);
        if (sign == r.sign)
        {
            for (int i = 0; i < r.size(); ++i) (*this)[i] += r[i];
        }
        else
        {
            if (sign == 1 && abs(*this) < abs(r)) sign = -1;
            else if (sign == -1 && abs(*this) <= abs(r)) sign = 1;
            if (abs(*this) >= abs(r))
            {
                for (int i = 0; i < r.size(); ++i) (*this)[i] -= r[i];
            }
            else
            {
                for (int i = 0; i < size(); ++i) (*this)[i] = -(*this)[i];
                for (int i = 0; i < r.size(); ++i) (*this)[i] += r[i];
            }
        }
        return this->normalize();
    }
    BigInteger& operator -= (const BigInteger& r)
    {
        while (size() < r.size()) this->emplace_back(0);
        if (sign == -r.sign)
        {
            for (int i = 0; i < r.size(); ++i) (*this)[i] += r[i];
        }
        else
        {
            if (sign == 1 && abs(*this) < abs(r)) sign = -1;
            else if (sign == -1 && abs(*this) <= abs(r)) sign = 1;
            if (abs(*this) >= abs(r))
            {
                for (int i = 0; i < r.size(); ++i) (*this)[i] -= r[i];
            }
            else
            {
                for (int i = 0; i < size(); ++i) (*this)[i] = -(*this)[i];
                for (int i = 0; i < r.size(); ++i) (*this)[i] += r[i];
            }
        }
        return this->normalize();
    }
    BigInteger& operator *= (long long r)
    {
        if ( (sign == 1 && r >= 0) || (sign == -1 && r < 0) ) sign = 1;
        else sign = -1;
        if (r < 0) r = -r;
        for (int i = 0; i < size(); ++i) (*this)[i] *= r;
        return this->normalize();
    }
    BigInteger& operator *= (const BigInteger& r)
    {
        int tx = (int)size()-1, ty = (int)r.size()-1;
        for (tx = size()-1; tx >= 0; --tx) if ((*this)[tx] > 0) break;
        for (ty = r.size()-1; ty >= 0; --ty) if (r[ty] > 0) break;
        BigInteger res(0);
        res.resize(tx+ty+2);
        if (sign == r.sign) res.sign = 1;
        else res.sign = -1;
        for (int i = 0; i <= tx; ++i)
        {
            for (int j = 0; j <= ty && i+j < (int)res.size()-1; ++j)
            {
                long long val = (*this)[i] * r[j] + res[i+j];
                res[i+j+1] += val / BigInteger::BASE;
                res[i+j] = val % BigInteger::BASE;
            }
        }
        return (*this) = res.normalize();
    }
    friend BigInteger pow(const BigInteger& a, long long n)
    {
        BigInteger res(1), b = a;
        while (n > 0)
        {
            if (n & 1) res = res * b;
            b = b * b;
            n >>= 1;
        }
        return res;
    }
    BigInteger operator + (const BigInteger& r) const
    {
        return BigInteger(*this) += r;
    }
    BigInteger operator - (const BigInteger& r) const
    {
        return BigInteger(*this) -= r;
    }
    BigInteger operator * (long long r) const
    {
        return BigInteger(*this) *= r;
    }
    BigInteger operator * (const BigInteger& r) const
    {
        return BigInteger(*this) *= r;
    }

    // divide
    BigInteger& operator /= (long long r)
    {
        if (r < 0) sign *= -1, r = -r;
        long long c = 0, t = 0;
        for (int i = (int)size()-1; i >= 0; --i)
        {
            t = BigInteger::BASE * c + (*this)[i];
            (*this)[i] = t / r;
            c = t % r;
        }
        this -> normalize();
        return (*this);
    }
    long long operator %= (long long r)
    {
        if(r < 0)
            sign *= -1, r = -r;
        long long c = 0, t = 0;
        for(int i = (int)size() - 1; i >= 0; --i)
        {
            t = BigInteger :: BASE * c + (*this)[i];
            (*this)[i] = t / r;
            c = t % r;
        }
        return c;
    }
    BigInteger operator / (long long r) const
    {
        return BigInteger(*this) /= r;
    }
    long long operator % (long long r) const
    {
        return BigInteger(*this) %= r;
    }
    friend pair<BigInteger, BigInteger> divmod(const BigInteger &a, const BigInteger &r)
    {
        BigInteger zero = 0, s = 0, t = 0;
        if (abs(a) < abs(r)) return {zero, a};
        BigInteger ar = abs(r);
        s.resize((int)a.size()), t.resize((int)r.size());
        int tx = (int)a.size()-1;
        for (; tx >= 0; --tx) if (a[tx] > 0) break;
        for (int i = tx; i >= 0; --i)
        {
            t = t * BigInteger :: BASE + a[i];
            long long lo = 0, hi = BigInteger::BASE;
            if(t >= ar)
            {
                while(hi - lo > 1)
                {
                    int mid = (hi + lo) / 2;
                    if(ar * mid > t)
                        hi = mid;
                    else
                        lo = mid;
                }
                t -= ar * lo;
            }
            s[i] = lo;
        }
        if(a.sign == r.sign)
            s.sign = 1, t.sign = 1;
        else
            s.sign = -1, t.sign = 1;
        return make_pair(s.normalize(), t.normalize());
    }
    BigInteger operator / (const BigInteger& r) const
    {
        return divmod((*this), r).first;
    }
    BigInteger operator % (const BigInteger& r) const
    {
        return divmod((*this), r).second;
    }
    BigInteger& operator /= (const BigInteger& r)
    {
        return (*this) = (*this) / r;
    }
    BigInteger& operator %= (const BigInteger& r)
    {
        return (*this) = (*this) % r;
    }

    // equality
    friend bool operator < (const BigInteger &x, const BigInteger& y)
    {
        if(x.sign < y.sign)
            return true;
        else if(x.sign > y.sign)
            return false;
        else
        {
            int tx = (int)x.size() - 1, ty = (int)y.size() - 1;
            for(tx = x.size() - 1; tx >= 0; --tx)
            {
                if(x[tx] > 0)
                    break;
            }
            for(ty = y.size() - 1; ty >= 0; --ty)
            {
                if(y[ty] > 0)
                    break;
            }
            if(tx < ty)
                return true;
            else if(tx > ty)
                return false;
            else if(x.sign == 1)
            {
                for(int i = tx; i >= 0; --i)
                {
                    if(x[i] != y[i])
                        return x[i] < y[i];
                }
                return false;
            }
            else
            {
                for(int i = tx; i >= 0; --i)
                {
                    if(x[i] != y[i])
                        return x[i] > y[i];
                }
                return false;
            }
        }
    }
    friend bool operator > (const BigInteger& x, const BigInteger& y)
    {
        return y < x;
    }
    friend bool operator <= (const BigInteger& x, const BigInteger& y)
    {
        return !(x > y);
    }
    friend bool operator >= (const BigInteger& x, const BigInteger& y)
    {
        return !(x < y);
    }
    friend bool operator == (const BigInteger &x, const BigInteger& y)
    {
        if(x.sign != y.sign)
            return false;
        int tx = (int)x.size() - 1, ty = (int)y.size() - 1;
        for(tx = x.size() - 1; tx >= 0; --tx)
        {
            if (x[tx] > 0)
                break;
        }
        for(ty = y.size() - 1; ty >= 0; --ty)
        {
            if(y[ty] > 0)
                break;
        }
        if(tx != ty)
            return false;
        for(int i = tx; i >= 0; --i)
        {
            if(x[i] != y[i])
                return false;
        }
        return true;
    }
    friend bool operator != (const BigInteger& x, const BigInteger& y)
    {
        return !(x == y);
    }
};

BigInteger toBigInteger(const string &is)
{
    string s = is;
    if(s[0] == '-')
        s = s.substr(1);
    while(s.size() % 8 != 0)
        s = "0" + s;
    int N = (int)s.size();
    BigInteger res(N / 8, 0);
    for(int i = 0; i < (int)s.size(); ++i)
    {
        res[(N - i - 1) / 8] *= 10;
        res[(N - i - 1) / 8] += s[i] - '0';
    }
    if(is[0] == '-')
        res.sign = -1;
    return res;
}

string toStr(const BigInteger &r)
{
    stringstream ss;
    if(r.sign == -1)
        ss << '-';
    int d = (int)r.size() - 1;
    for(; d >= 0; --d)
    {
        if(r[d] > 0)
            break;
    }
    if(d == -1)
        ss << 0;
    else
        ss << r[d];
    for(int i = d - 1; i >= 0; --i)
    {
        ss.width(BigInteger::BASE_DIGIT);
        ss.fill('0');
        ss << r[i];
    }
    return ss.str();
}

int main()
{
    string A, B;
    cin >> A >> B;
    cout << toBigInteger(A) + toBigInteger(B) << endl;
    //cout << toBigInteger(A) - toBigInteger(B) << endl;
    //cout << toBigInteger(A) * toBigInteger(B) << endl;
    //cout << toBigInteger(A) / toBigInteger(B) << endl;
    //cout << toBigInteger(A) % toBigInteger(B) << endl;
}


/* 模板三：快速傅里叶变换（FFT）求大数乘法 */

/* 需要数学分类中的FFT模板 */
void FFT_Mul(char *s1, char *s2)    //传入的是两个相乘的大数
{
    int len1 = strlen(s1), len2 = strlen(s2);
    reverse(s1, s1 + len1);
    reverse(s2, s2 + len2);
    int sign = 0;   //符号
    if(s1[len1 - 1] == '-')
    {
        len1--;
        sign ^= 1;
    }
    if(s2[len2 - 1] == '-')
    {
        len2--;
        sign ^= 1;
    }
    for(int i = 0; i < len1; i++)
        a[i] = (double)(s1[i] - '0');
    for(int i = 0; i < len2; i++)
        b[i] = (double)(s2[i] - '0');
    int len = 1;
    while(len < len1 + len2 - 1)
        len <<= 1;
    solve(len);
    for(int i = 0; i < len; i++)
    {
        ans[i] += (int)(a[i].real() + 0.5);
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }
    while(len >= 0 && !ans[len])
        len--;
    if(len == -1)
        puts("0");
    else
    {
        if(sign)
            printf("-");
        for(int i = len; i >= 0; i--)
        {
            if(i == len && !ans[len])
                continue;
            printf("%d", ans[i]);
        }
        puts("");
    }
}

int main()
{
    scanf("%s%s", s1, s2);
    FFT_Mul(s1, s2);
    return 0;
}

