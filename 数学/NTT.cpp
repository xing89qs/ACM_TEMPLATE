#define MOD 998244353 //(2^23)*7*17+1
#define G 3

#define MOD 995622913 //(2^19)*3*3*211+1
#define G 5

#define MOD 1004535809 //(2^21)*479+1
#define G 3

#define MOD 50000000001507329ll
#define G 3

void NTT(int *a,int n,int oper,int MOD,int G){
    for (int i = 1, j = 0; i < n - 1; i++) {
        for (int s = n; j ^= s >>= 1, ~j & s;);
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for(int h = 2;h<=n;h<<=1){
        int wn = Pow(G,(MOD-1)/i,MOD);
        if(oper) wn = Pow(wn,MOD-2,MOD);
        for(int j = 0;j<n;j+=i){
            int w = 1;
            for(int k = j;k<j+h/2;k++){
                int u = a[k];
                int t = 1ll*w*a[k+h/2]%MOD;
                a[k] = (u+t)%MOD;
                a[k+h/2] = ((u-t)%MOD+MOD)%MOD;
                w = 1ll*w*wn%MOD;
            }
        }
    }
    if(oper==-1){
        int inv = Pow(n,MOD-2,MOD);
        for(int i = 0;i<n;i++) a[i] = 1ll*a[i]*inv%MOD;
    }
}

void solve(){
    NTT(a,n,1,MOD,G);
    NTT(b,n,1,MOD,G);
    for(int i = 0;i<n;i++) a[i] = 1ll*a[i]*b[i]%MOD;
    NTT(a,n,-1);
}