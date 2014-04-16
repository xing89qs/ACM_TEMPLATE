int manacher(char *c){
	int n,j;
	int max=0;
	str[0]='$';
	for(n=0,j=1; c[n]!='\0'; n++)
	{
		str[j++]='#';
		str[j++]=c[n];
	}
	str[j]='#';
	str[j+1]='\0';
	if(n==0) continue;
	int mx=0,id=0;
	for(int i=1; i<=j; i++)
	{
		if(mx>i) r[i] = MIN(r[2*id-i], mx-i);
		else r[i]=1;
		for(;str[i+r[i]] == str[i-r[i]]; r[i]++);
		if(r[i]>max) max=r[i];
		if(r[i]+i>mx){
			mx=r[i]+i;
			id=i;
		}
	}
	return max-1;
}
