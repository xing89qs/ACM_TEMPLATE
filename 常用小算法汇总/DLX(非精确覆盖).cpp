
class DLX{
public:
    int m,sz;//列数，结点数
    int S[MAXN];//每列结点数
    
    int row[MAXNODE],col[MAXNODE];
    int L[MAXNODE],R[MAXNODE],U[MAXNODE],D[MAXNODE];
    
    int ansd,ans[MAXN];
    
    void init(int m){
        this->m = m;
        
        for(int i = 0;i<=m;i++){
            U[i] = i,D[i] = i,L[i] = i-1,R[i] = i+1;
            col[i] = i;
        }
        R[m] = 0,L[0] = m;
        
        sz = m+1;
        memset(S,0,sizeof(S));
    }
    
    void addRow(int r,vector<int>& columns){
        int first = sz;
        for(int i = 0;i<(int)columns.size();i++){
            int c = columns[i];
            L[sz] = sz-1;R[sz] = sz+1;D[sz] = c;U[sz] = U[c];
            D[U[c]] = sz;U[c] = sz;
            row[sz] = r;col[sz] = c;
            S[c]++;sz++;
        }
        R[sz-1] = first;L[first] = sz-1;
    }
    
#define REP(i,A,s) for(int i = A[s];i!=s;i = A[i])
    
    void removeNode(int c){
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        --S[col[c]];
    }
    
    //删除列
    void removeCol(int c){
        REP(i,D,c) removeNode(i);
    }
    
    void restoreNode(int c){
        ++S[col[c]];
        L[R[c]] = c;
        R[L[c]] = c;
    }
    
    //恢复列
    void restoreCol(int c){
        REP(i,U,c) restoreNode(i);
    }
    
    void removeRow(int r){
        REP(j,R,r){
            U[D[j]] = U[j];D[U[j]] = D[j];--S[col[j]];
        }
    }
    
    void restoreRow(int r){
        REP(j,L,r){
            ++S[col[j]];U[D[j]] = j;D[U[j]] = j;
        }
    }
    
    int ret;
    int vis[MAXN];
    
    int h(){
        memset(vis, 0, sizeof(vis));
        int res = 0;
        REP(i,R,0){
            if (vis[col[i]]) continue;
            vis[col[i]] = 1;
            ++res;
            REP(j,D,i){
                if(col[j])
                    REP(k,R,j) vis[col[k]] = 1;
            }
        }
        return res;
    }
    
    
    bool dfs(int d,int cost){
        if(cost+h()>k) return false;
        if(R[0]==0) return true;
        
        //找S最小的列来删除加速
        int c = R[0];
        REP(i,R,0) if(S[i]<S[c]) c = i;
        REP(i,D,c){
            removeCol(i);
            REP(j,R,i) removeCol(j);
            if(dfs(d+1,cost+1)) return true;
            REP(j,L,i) restoreCol(j);
            restoreCol(i);
        }
        return false;
    }
    
    int solve(){
        return dfs(0,0);
    }
} dlx;