Type d[MAXN][MAXN];
int n,m;

void floyd(){
	for(int k = 0;k<n;k++)
		for(int i = 0;i<n;i++)
			for(int j = 0;j<n;j++){
				if(d[i][k]!=-1&&d[j][k]!=-1){
					if(d[i][j]==-1||d[i][j]>d[i][k]+d[j][k])
						d[i][j] = d[i][k]+d[j][k];
				}
			}
}
