struct State{
	//状态定义
	
	void init(){
	}
	bool isFinal(){
	}
	int getScore(){
	}
};

int alphabeta(State& s,int player,int alpha,int beta){
	if(s.isFinal()) return s.getScore();
	for(;;){
		//expand();
		int v = alphabeta(child,nextPlayer,alpha,beta);
		if(!player) alpha = max(alpha,v);
		else beta = min(beta,v);
		//如果有必胜态也可直接退出
		if(beta<=alpha) break;
	}
	return !player?alpha:beta;
}

