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

struct Edge{
	int v,w;
	Edge(){}
	Edge(int v,int w):v(v),w(w){}
} e[MAXN<<1];

int head[MAXN],next[MAXN<<1],d[MAXN],fa[MAXN],ans[205];
bool vis[MAXN];
int cnt;

void addEdge(int u,int v,int w){
	e[cnt] = Edge(v,w);
	int tmp = head[u];
	head[u] = cnt;
	next[cnt++] = tmp;
}

struct Query{
	int idx;
	int u,v;
};

vector<Query> q[MAXN];

int find(int u){
	return u==fa[u]?u:fa[u] = find(fa[u]);
}

void dfs(int u,int d){
	::d[u] = d;
	vis[u] = true;
	for(int i = head[u];~i;i = next[i]){
		int v = e[i].v;
		if(!vis[v]){
			dfs(v,d+e[i].w);
			fa[find(v)] = find(u);
		}
	}
	int sz = q[u].size();
	for(int i = 0;i<sz;i++){
		if(vis[q[u][i].v]){
			int lca = find(q[u][i].v);
			ans[q[u][i].idx] = ::d[u]+::d[q[u][i].v]-::d[lca]*2;
		}
	}
}

int main(void){
#ifndef ONLINE_JUDGE 
      freopen("/home/xing89qs/桌面/data.in","r",stdin);
#endif
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m;
		scanf("%d %d",&n,&m);
		cnt = 0;
		for(int i = 1;i<=n;i++){
			head[i] = -1;
			q[i].clear();
			fa[i] = i;
			vis[i] = false;
		}
		for(int i = 1;i<n;i++){
			int u,v,w;
			scanf("%d %d %d",&u,&v,&w);
			addEdge(u,v,w);
			addEdge(v,u,w);
		}
		for(int i = 0;i<m;i++){
			Query query;
			scanf("%d %d",&query.u,&query.v);
			query.idx = i;
			q[query.u].PB(query);
			swap(query.u,query.v);
			q[query.u].PB(query);
		}
		dfs(1,0);
		for(int i = 0;i<m;i++) printf("%d\n",ans[i]);
	}
}

