LL getY(int i){
	//
}

LL getX(int i){
	//
}

LL deltaY(int i,int j){
	return getY(j)-getY(i);
}

LL deltaX(int i,int j){
	return getX(j)-getX(i);
}

LL getDp(){
	//
}

LL solve(){
	dp[0] = 0;
	int head = 0,tail = 0;
	q[tail++] = 0;
	for(int i = 1;i<=n;i++){
		while(tail-head>1&&deltaY(q[head],q[head+1])<=sum[i]*deltaX(q[head],q[head+1])) head++;
		dp[i] = getDp();
		while(tail-head>1&&deltaY(q[tail-2],q[tail-1])*deltaX(q[tail-1],i)>=
				deltaY(q[tail-1],i)*deltaX(q[tail-2],q[tail-1]))
			tail--;
		q[tail++] = i;
	}
}
