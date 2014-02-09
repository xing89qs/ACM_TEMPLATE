//#pragma comment(linker,"/STACK:102400000,102400000")
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <climits>
#include <ctime>
#include <numeric>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <complex>
#include <deque>
#include <functional>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <stack>
#include <queue>
using namespace std;
template<class T> inline T sqr(T x) { return x * x; }
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<PII, int> PIII;
typedef pair<LL, LL> PLL;
typedef pair<LL, int> PLI;
typedef pair<LD, LD> PDD;
#define MP make_pair
#define PB push_back
#define sz(x) ((int)(x).size())
#define clr(ar,val) memset(ar, val, sizeof(ar))
#define istr stringstream
#define FOR(i,n) for(int i=0;i<(n);++i)
const double EPS = 1e-6;
const int INF = 0x3fffffff;
const LL LINF = INF * 1ll * INF;
const double PI = acos(-1.0);

using namespace std;

#define MAXN 40005

int dis[MAXN],cnt;
int head[MAXN],next[MAXN<<1];
struct Edge{
	int v,w;
	Edge(){}
	Edge(int v,int w):v(v),w(w){}
} e[MAXN<<1];

void addEdge(int u,int v,int w){
	e[cnt] = Edge(v,w);
	int tmp = head[u];
	head[u] = cnt;
	next[cnt++] = tmp;
}

int dfs_time = 0,dfs_cnt = 0;
int b[MAXN<<1],dfs_clock[MAXN],nd[MAXN];
int d[20][MAXN<<1],logg[MAXN<<1];

void dfs(int u,int fa,int d){
	dis[u] = d;
	b[dfs_cnt] = dfs_time;
	int now = dfs_time;
	nd[dfs_time++] = u;
	dfs_clock[u] = dfs_cnt++;
	for(int i = head[u];~i;i = next[i]){
		int v = e[i].v;
		if(v==fa) continue;
		dfs(v,u,d+e[i].w);
		b[dfs_cnt++] = now;
	}
}

void init_RMQ(int n){
	for(int i = 0;i<n;i++) d[0][i] = b[i];
	for(int j = 1;(1<<j)<n;j++){
		for(int i = 0;i<n-(1<<j)+1;i++)
			d[j][i] = min(d[j-1][i],d[j-1][i+(1<<(j-1))]);
	}
}

int RMQ(int l,int r){
	int k = logg[r-l+1];
	return min(d[k][l],d[k][r-(1<<k)+1]);
}

int LCA(int u,int v){
	if(dfs_clock[u]>dfs_clock[v]) swap(u,v);
	return nd[RMQ(dfs_clock[u],dfs_clock[v])];
}

int main(void){
#ifndef ONLINE_JUDGE 
      freopen("/home/xing89qs/桌面/data.in","r",stdin);
#endif
	int n,m;
	scanf("%d %d",&n,&m);
	char s[10];
	int now = 0;
	for(int i = 0;i<(MAXN<<1);i++){
		while((1<<(now+1))<=i) now++;
		logg[i] = now;
	}
	dfs_time = dfs_cnt = 0;
	for(int i = 1;i<=n;i++) head[i] = -1;
	for(int i = 1;i<n;i++){
		int u,v,w;
		scanf("%d %d %d %s",&u,&v,&w,s);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	dfs(1,-1,0);
	init_RMQ(dfs_cnt);
	scanf("%d",&m);
	while(m--){
		int u,v;
		scanf("%d %d",&u,&v);
		int lca = LCA(u,v);
		printf("%d\n",dis[u]+dis[v]-dis[lca]*2);
	}
}

