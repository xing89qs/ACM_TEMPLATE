int Min(char *s,int len){
	int i = 0,j = 1,k = 0;
	while(i<len&&j<len&&k<len){
		if(s[i+k]==s[j+k]) k++;
		else{
			if(s[i+k]>s[j+k]) i = max(i+k+1,j);
			else j = max(j+k+1,i);
			if(i==j) j++;
			k = 0;
		}
	}
	return min(i,j);
}
