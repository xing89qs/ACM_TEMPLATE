void getNext(const char *t,int n){
	nxt[0] = n;
	int a = 0;
	while(a<n-1&&t[a]==t[a+1]) a++;
	nxt[1] = a;
	a = 1;
	for(int i = 2;i<n;i++){
		int p = a+nxt[a]-1,l = nxt[i-a];
		if(i+l-1>=p){
			int j = max(p-i+1,0);
			while(i+j<n&&t[i+j]==t[j]) j++;
			nxt[i] = j;
			a = i;
		}else nxt[i] = l;
	}
}

//extend[i]求出s[i]和t的最长匹配长度
void getExtend(const char *s,const char *t,int n,int m){
	getNext(t,m);
	int a = 0;
	int len = min(n,m);
	while(a<len&&s[a]==t[a]) a++;
	extend[0] = a;
	a = 0;
	for(int i = 0;i<n;i++){
		int p = a+extend[a]-1,l = next[i-a];
		if(i+l-1>=p){
			int j = max(p-i+1,0);
			while(i+j<n&&j<m&&s[i+j]==t[j]) j++;
			extend[i] = j;
			a = i;
		}else extend[i] = l;
	}
}
