#define MAXN 100005

char s[MAXN];
int sa[MAXN],t[MAXN],t2[MAXN],c[MAXN],rank[MAXN],height[MAXN];
int d[20][MAXN];
int logg[MAXN];

void build_sa(int n){
    int *x = t,*y = t2,m = 128;
    for(int i = 0;i<m;i++) c[i] = 0;
    for(int i = 0;i<n;i++) c[x[i] = s[i]]++;
    for(int i = 1;i<m;i++) c[i]+=c[i-1];
    for(int i = n-1;i>=0;i--) sa[--c[x[i]]] = i;
    for(int k = 1;k<=n;k<<=1){
        int p = 0;
        for(int i = n-k;i<n;i++) y[p++] = i;
        for(int i = 0;i<n;i++) if(sa[i]>=k) y[p++] = sa[i]-k;
        for(int i = 0;i<m;i++) c[i] = 0;
        for(int i = 0;i<n;i++) c[x[y[i]]]++;
        for(int i = 1;i<m;i++) c[i]+=c[i-1];
        for(int i = n-1;i>=0;i--) sa[--c[x[y[i]]]] = y[i];
        int *tmp = x;x = y;y = tmp;
        p = 1;x[sa[0]] = 0;
        for(int i = 1;i<n;i++)
            x[sa[i]] = y[sa[i]]==y[sa[i-1]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
        if(p>=n) break;
        m = p;
    }
}

void getHeight(int n){
    int k = 0;
    for(int i = 0;i<=n;i++) rank[sa[i]] = i;
    for(int i = 0;i<n;i++){
        if(k) --k;
        int j = sa[rank[i]-1];
        while(s[i+k]==s[j+k]) k++;
        height[rank[i]] = k;
    }
}

void init_RMQ(int n){
	/*
    int now = 0;
    for(int i = 0;i<=MAXN;i++){
        while((1<<(now+1))<=i) now++;
        logg[i] = now;
    }*/
    for(int i = 0;i<=n;i++) d[0][i] = height[i];
    for(int i = 1;(1<<i)<=n;i++)
        for(int j = 1;j+(1<<i)-1<=n;j++)
            d[i][j] = min(d[i-1][j],d[i-1][j+(1<<(i-1))]);
}


int RMQ(int l,int r){
    int k = logg[r-l+1];
    return min(d[k][l],d[k][r-(1<<k)+1]);
}
