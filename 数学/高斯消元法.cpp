void gauss(){
	int n = 21*21;
	for(int i = 0;i<n;i++){
        int r = i;
        for(int j = i+1;j<n;j++)
            if(fabs(a[j][i])>fabs(a[r][i])) r = j;
        if(r!=i) for(int j = 0;j<=n;j++) swap(a[r][j],a[i][j]);
		for(int k = i+1;k<n;k++){
            if(fabs(a[k][i])<EPS) continue;
			double f = a[k][i]/a[i][i];
			for(int j = i;j<=n;j++) a[k][j]-=f*a[i][j];
		}
	}
	for(int i = n-1;i>=0;i--){
		for(int j = i+1;j<n;j++)
			a[i][n]-=a[j][n]*a[i][j];
		a[i][n]/=a[i][i];
	}
}
