//Floyd（多源最短路）算法，复杂度O(n^3)

Type d[MAXN][MAXN];
int n,m;

void floyd(){
	for(int k = 0;k<n;k++){
		for(int i = 0;i<n;i++){
			for(int j = 0;j<n;j++){
				if(d[i][k]!=-1&&d[j][k]!=-1){
					if(d[i][j]==-1||d[i][j]>d[i][k]+d[j][k])
						d[i][j] = d[i][k]+d[j][k];
				}
			}
		}
	}
}

#define INF 0x3f3f3f3f

Type d[MAXN][MAXN];
int n,m;

//memset(d,INF,sizeof(d));
void floyd()
{
    for(int k=0; k<n; k++)
    {
        d[k][k]=0;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
        }
    }
}
