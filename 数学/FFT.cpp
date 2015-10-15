typedef complex<double> Complex;
void FFT(Complex* P, int n, int oper)//oper 1 DFT,oper -1 iDFT
{
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(P[i], P[j]);
        }
    }
    Complex unit_p0;
    for (int d = 0; (1 << d) < n; d++) {
        int m = 1 << d, m2 = m * 2;
        double p0 = PI / m * oper;
        unit_p0 = Complex(cos(p0), sin(p0));
        for (int i = 0; i < n; i += m2) {
            Complex unit = 1;
            for (int j = 0; j < m; j++) {
                Complex &P1 = P[i + j + m], &P2 = P[i + j];
                Complex t = unit * P1;
                P1 = P2 - t;
                P2 = P2 + t;
                unit = unit * unit_p0;
            }
        }
    }
    if (oper==-1){
        for (int i=0;i<n;i++)
            P[i]/=n;
    }
}

void solve(){
    FFT(a,len,1);
    FFT(b,len,1);
    for(int i = 0;i<len;i++) a[i] = a[i]*b[i];
    FFT(a,len,-1);
}