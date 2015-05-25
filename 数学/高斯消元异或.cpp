
int Gauss(int n){
    int rank = 0;
    for(int i = 0;i<n;i++){
        int r = rank;
        for(int j = rank+1;j<n;j++) if(a[j][i]) r = j;
        if(!a[r][i]) continue;
        if(r!=rank) for(int j = 0;j<=n;j++) swap(a[r][j],a[rank][j]);
        for(int k = rank+1;k<n;k++)
            if(a[k][i]) for(int j = i;j<=n;j++) a[k][j]^=a[rank][j];
        rank++;
    }
    for(int i = rank;i<n;i++) if(a[i][n]) return -1;
    return rank;
}